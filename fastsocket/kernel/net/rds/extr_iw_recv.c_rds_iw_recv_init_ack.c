#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct ib_sge {int length; int /*<<< orphan*/  lkey; int /*<<< orphan*/  addr; } ;
struct ib_send_wr {int num_sge; int send_flags; int /*<<< orphan*/  wr_id; int /*<<< orphan*/  opcode; struct ib_sge* sg_list; } ;
struct rds_iw_connection {int /*<<< orphan*/  i_ack_dma; struct ib_sge i_ack_sge; struct ib_send_wr i_ack_wr; } ;
struct rds_header {int dummy; } ;

/* Variables and functions */
 int IB_SEND_SIGNALED ; 
 int IB_SEND_SOLICITED ; 
 int /*<<< orphan*/  IB_WR_SEND ; 
 int /*<<< orphan*/  RDS_IW_ACK_WR_ID ; 
 int /*<<< orphan*/  rds_iw_local_dma_lkey (struct rds_iw_connection*) ; 

void rds_iw_recv_init_ack(struct rds_iw_connection *ic)
{
	struct ib_send_wr *wr = &ic->i_ack_wr;
	struct ib_sge *sge = &ic->i_ack_sge;

	sge->addr = ic->i_ack_dma;
	sge->length = sizeof(struct rds_header);
	sge->lkey = rds_iw_local_dma_lkey(ic);

	wr->sg_list = sge;
	wr->num_sge = 1;
	wr->opcode = IB_WR_SEND;
	wr->wr_id = RDS_IW_ACK_WR_ID;
	wr->send_flags = IB_SEND_SIGNALED | IB_SEND_SOLICITED;
}