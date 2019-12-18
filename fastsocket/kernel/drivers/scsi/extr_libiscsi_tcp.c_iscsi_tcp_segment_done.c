#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_5__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct scatterlist {int dummy; } ;
struct iscsi_tcp_conn {TYPE_5__* iscsi_conn; } ;
struct iscsi_segment {unsigned int copied; unsigned int size; unsigned int data; unsigned int sg_offset; unsigned int total_copied; scalar_t__ total_size; unsigned int padbuf; int /*<<< orphan*/  digest; int /*<<< orphan*/  recv_digest; scalar_t__ hash; TYPE_3__* sg; } ;
struct TYPE_9__ {TYPE_2__* session; } ;
struct TYPE_8__ {unsigned int offset; } ;
struct TYPE_7__ {TYPE_1__* tt; } ;
struct TYPE_6__ {int caps; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int CAP_PADDING_OFFLOAD ; 
 int /*<<< orphan*/  ISCSI_DBG_TCP (TYPE_5__*,char*,unsigned int,...) ; 
 int /*<<< orphan*/  crypto_hash_final (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  crypto_hash_update (scalar_t__,struct scatterlist*,unsigned int) ; 
 unsigned int iscsi_padding (scalar_t__) ; 
 int /*<<< orphan*/  iscsi_tcp_segment_init_sg (struct iscsi_segment*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iscsi_tcp_segment_map (struct iscsi_segment*,int) ; 
 int /*<<< orphan*/  iscsi_tcp_segment_splice_digest (struct iscsi_segment*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iscsi_tcp_segment_unmap (struct iscsi_segment*) ; 
 int /*<<< orphan*/  sg_init_one (struct scatterlist*,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  sg_init_table (struct scatterlist*,int) ; 
 int /*<<< orphan*/  sg_next (TYPE_3__*) ; 
 int /*<<< orphan*/  sg_page (TYPE_3__*) ; 
 int /*<<< orphan*/  sg_set_page (struct scatterlist*,int /*<<< orphan*/ ,unsigned int,unsigned int) ; 

int iscsi_tcp_segment_done(struct iscsi_tcp_conn *tcp_conn,
			   struct iscsi_segment *segment, int recv,
			   unsigned copied)
{
	struct scatterlist sg;
	unsigned int pad;

	ISCSI_DBG_TCP(tcp_conn->iscsi_conn, "copied %u %u size %u %s\n",
		      segment->copied, copied, segment->size,
		      recv ? "recv" : "xmit");
	if (segment->hash && copied) {
		/*
		 * If a segment is kmapd we must unmap it before sending
		 * to the crypto layer since that will try to kmap it again.
		 */
		iscsi_tcp_segment_unmap(segment);

		if (!segment->data) {
			sg_init_table(&sg, 1);
			sg_set_page(&sg, sg_page(segment->sg), copied,
				    segment->copied + segment->sg_offset +
							segment->sg->offset);
		} else
			sg_init_one(&sg, segment->data + segment->copied,
				    copied);
		crypto_hash_update(segment->hash, &sg, copied);
	}

	segment->copied += copied;
	if (segment->copied < segment->size) {
		iscsi_tcp_segment_map(segment, recv);
		return 0;
	}

	segment->total_copied += segment->copied;
	segment->copied = 0;
	segment->size = 0;

	/* Unmap the current scatterlist page, if there is one. */
	iscsi_tcp_segment_unmap(segment);

	/* Do we have more scatterlist entries? */
	ISCSI_DBG_TCP(tcp_conn->iscsi_conn, "total copied %u total size %u\n",
		      segment->total_copied, segment->total_size);
	if (segment->total_copied < segment->total_size) {
		/* Proceed to the next entry in the scatterlist. */
		iscsi_tcp_segment_init_sg(segment, sg_next(segment->sg),
					  0);
		iscsi_tcp_segment_map(segment, recv);
		BUG_ON(segment->size == 0);
		return 0;
	}

	/* Do we need to handle padding? */
	if (!(tcp_conn->iscsi_conn->session->tt->caps & CAP_PADDING_OFFLOAD)) {
		pad = iscsi_padding(segment->total_copied);
		if (pad != 0) {
			ISCSI_DBG_TCP(tcp_conn->iscsi_conn,
				      "consume %d pad bytes\n", pad);
			segment->total_size += pad;
			segment->size = pad;
			segment->data = segment->padbuf;
			return 0;
		}
	}

	/*
	 * Set us up for transferring the data digest. hdr digest
	 * is completely handled in hdr done function.
	 */
	if (segment->hash) {
		crypto_hash_final(segment->hash, segment->digest);
		iscsi_tcp_segment_splice_digest(segment,
				 recv ? segment->recv_digest : segment->digest);
		return 0;
	}

	return 1;
}