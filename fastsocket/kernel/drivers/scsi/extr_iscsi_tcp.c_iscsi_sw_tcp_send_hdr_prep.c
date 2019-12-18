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
struct iscsi_tcp_conn {struct iscsi_sw_tcp_conn* dd_data; } ;
struct TYPE_2__ {int /*<<< orphan*/  segment; void* hdr; int /*<<< orphan*/  data_segment; } ;
struct iscsi_sw_tcp_conn {TYPE_1__ out; int /*<<< orphan*/  tx_hash; } ;
struct iscsi_segment {int dummy; } ;
struct iscsi_conn {scalar_t__ hdrdgst_en; struct iscsi_tcp_conn* dd_data; } ;

/* Variables and functions */
 scalar_t__ ISCSI_DIGEST_SIZE ; 
 int /*<<< orphan*/  ISCSI_SW_TCP_DBG (struct iscsi_conn*,char*,char*) ; 
 int /*<<< orphan*/  iscsi_segment_init_linear (int /*<<< orphan*/ *,void*,size_t,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  iscsi_sw_tcp_send_hdr_done ; 
 int /*<<< orphan*/  iscsi_tcp_dgst_header (int /*<<< orphan*/ *,void*,size_t,void*) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void iscsi_sw_tcp_send_hdr_prep(struct iscsi_conn *conn, void *hdr,
				       size_t hdrlen)
{
	struct iscsi_tcp_conn *tcp_conn = conn->dd_data;
	struct iscsi_sw_tcp_conn *tcp_sw_conn = tcp_conn->dd_data;

	ISCSI_SW_TCP_DBG(conn, "%s\n", conn->hdrdgst_en ?
			 "digest enabled" : "digest disabled");

	/* Clear the data segment - needs to be filled in by the
	 * caller using iscsi_tcp_send_data_prep() */
	memset(&tcp_sw_conn->out.data_segment, 0,
	       sizeof(struct iscsi_segment));

	/* If header digest is enabled, compute the CRC and
	 * place the digest into the same buffer. We make
	 * sure that both iscsi_tcp_task and mtask have
	 * sufficient room.
	 */
	if (conn->hdrdgst_en) {
		iscsi_tcp_dgst_header(&tcp_sw_conn->tx_hash, hdr, hdrlen,
				      hdr + hdrlen);
		hdrlen += ISCSI_DIGEST_SIZE;
	}

	/* Remember header pointer for later, when we need
	 * to decide whether there's a payload to go along
	 * with the header. */
	tcp_sw_conn->out.hdr = hdr;

	iscsi_segment_init_linear(&tcp_sw_conn->out.segment, hdr, hdrlen,
				  iscsi_sw_tcp_send_hdr_done, NULL);
}