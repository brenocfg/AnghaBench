#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct skb_seq_state {int dummy; } ;
struct sk_buff {int len; } ;
struct iscsi_segment {scalar_t__ total_copied; scalar_t__ total_size; scalar_t__ copied; scalar_t__ size; int (* done ) (struct iscsi_tcp_conn*,struct iscsi_segment*) ;} ;
struct TYPE_2__ {struct iscsi_segment segment; } ;
struct iscsi_tcp_conn {TYPE_1__ in; } ;
struct iscsi_conn {unsigned int rxdata_octets; int /*<<< orphan*/  suspend_rx; int /*<<< orphan*/  last_recv; struct iscsi_tcp_conn* dd_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  ISCSI_DBG_TCP (struct iscsi_conn*,char*,...) ; 
 int ISCSI_TCP_CONN_ERR ; 
 int ISCSI_TCP_SEGMENT_DONE ; 
 int ISCSI_TCP_SKB_DONE ; 
 int ISCSI_TCP_SUSPENDED ; 
 int /*<<< orphan*/  iscsi_conn_failure (struct iscsi_conn*,int) ; 
 int iscsi_tcp_segment_recv (struct iscsi_tcp_conn*,struct iscsi_segment*,int /*<<< orphan*/  const*,unsigned int) ; 
 int /*<<< orphan*/  jiffies ; 
 int /*<<< orphan*/  skb_abort_seq_read (struct skb_seq_state*) ; 
 int /*<<< orphan*/  skb_prepare_seq_read (struct sk_buff*,unsigned int,int,struct skb_seq_state*) ; 
 unsigned int skb_seq_read (unsigned int,int /*<<< orphan*/  const**,struct skb_seq_state*) ; 
 int stub1 (struct iscsi_tcp_conn*,struct iscsi_segment*) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 

int iscsi_tcp_recv_skb(struct iscsi_conn *conn, struct sk_buff *skb,
		       unsigned int offset, bool offloaded, int *status)
{
	struct iscsi_tcp_conn *tcp_conn = conn->dd_data;
	struct iscsi_segment *segment = &tcp_conn->in.segment;
	struct skb_seq_state seq;
	unsigned int consumed = 0;
	int rc = 0;

	ISCSI_DBG_TCP(conn, "in %d bytes\n", skb->len - offset);
	/*
	 * Update for each skb instead of pdu, because over slow networks a
	 * data_in's data could take a while to read in. We also want to
	 * account for r2ts.
	 */
	conn->last_recv = jiffies;

	if (unlikely(conn->suspend_rx)) {
		ISCSI_DBG_TCP(conn, "Rx suspended!\n");
		*status = ISCSI_TCP_SUSPENDED;
		return 0;
	}

	if (offloaded) {
		segment->total_copied = segment->total_size;
		goto segment_done;
	}

	skb_prepare_seq_read(skb, offset, skb->len, &seq);
	while (1) {
		unsigned int avail;
		const u8 *ptr;

		avail = skb_seq_read(consumed, &ptr, &seq);
		if (avail == 0) {
			ISCSI_DBG_TCP(conn, "no more data avail. Consumed %d\n",
				      consumed);
			*status = ISCSI_TCP_SKB_DONE;
			skb_abort_seq_read(&seq);
			goto skb_done;
		}
		BUG_ON(segment->copied >= segment->size);

		ISCSI_DBG_TCP(conn, "skb %p ptr=%p avail=%u\n", skb, ptr,
			      avail);
		rc = iscsi_tcp_segment_recv(tcp_conn, segment, ptr, avail);
		BUG_ON(rc == 0);
		consumed += rc;

		if (segment->total_copied >= segment->total_size) {
			skb_abort_seq_read(&seq);
			goto segment_done;
		}
	}

segment_done:
	*status = ISCSI_TCP_SEGMENT_DONE;
	ISCSI_DBG_TCP(conn, "segment done\n");
	rc = segment->done(tcp_conn, segment);
	if (rc != 0) {
		*status = ISCSI_TCP_CONN_ERR;
		ISCSI_DBG_TCP(conn, "Error receiving PDU, errno=%d\n", rc);
		iscsi_conn_failure(conn, rc);
		return 0;
	}
	/* The done() functions sets up the next segment. */

skb_done:
	conn->rxdata_octets += consumed;
	return consumed;
}