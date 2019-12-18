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
struct TYPE_2__ {int send_flags; int num_sge; int /*<<< orphan*/ * next; int /*<<< orphan*/  opcode; } ;
struct rds_iw_send_work {struct ib_sge* s_sge; TYPE_1__ s_wr; int /*<<< orphan*/ * s_op; int /*<<< orphan*/  s_queued; } ;
struct rds_iw_connection {unsigned int i_send_hdrs_dma; struct rds_iw_send_work* i_sends; } ;
struct rds_header {int dummy; } ;
struct ib_sge {unsigned long addr; unsigned int length; void* lkey; } ;

/* Variables and functions */
 int /*<<< orphan*/  IB_WR_SEND ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  jiffies ; 
 struct ib_sge* rds_iw_data_sge (struct rds_iw_connection*,struct ib_sge*) ; 
 struct ib_sge* rds_iw_header_sge (struct rds_iw_connection*,struct ib_sge*) ; 
 void* rds_iw_local_dma_lkey (struct rds_iw_connection*) ; 

__attribute__((used)) static inline void
rds_iw_xmit_populate_wr(struct rds_iw_connection *ic,
		struct rds_iw_send_work *send, unsigned int pos,
		unsigned long buffer, unsigned int length,
		int send_flags)
{
	struct ib_sge *sge;

	WARN_ON(pos != send - ic->i_sends);

	send->s_wr.send_flags = send_flags;
	send->s_wr.opcode = IB_WR_SEND;
	send->s_wr.num_sge = 2;
	send->s_wr.next = NULL;
	send->s_queued = jiffies;
	send->s_op = NULL;

	if (length != 0) {
		sge = rds_iw_data_sge(ic, send->s_sge);
		sge->addr = buffer;
		sge->length = length;
		sge->lkey = rds_iw_local_dma_lkey(ic);

		sge = rds_iw_header_sge(ic, send->s_sge);
	} else {
		/* We're sending a packet with no payload. There is only
		 * one SGE */
		send->s_wr.num_sge = 1;
		sge = &send->s_sge[0];
	}

	sge->addr = ic->i_send_hdrs_dma + (pos * sizeof(struct rds_header));
	sge->length = sizeof(struct rds_header);
	sge->lkey = rds_iw_local_dma_lkey(ic);
}