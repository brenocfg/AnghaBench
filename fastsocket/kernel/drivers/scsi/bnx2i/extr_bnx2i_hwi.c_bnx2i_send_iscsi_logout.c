#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u64 ;
typedef  void* u32 ;
typedef  int u16 ;
struct iscsi_task {scalar_t__ itt; scalar_t__ hdr; scalar_t__ dd_data; } ;
struct iscsi_logout {int flags; int /*<<< orphan*/  cmdsn; int /*<<< orphan*/  opcode; } ;
struct bnx2i_logout_request {int op_attr; int itt; int num_bds; scalar_t__ cq_index; void* bd_list_addr_hi; void* bd_list_addr_lo; scalar_t__ cid; scalar_t__ data_length; int /*<<< orphan*/  cmd_sn; int /*<<< orphan*/  op_code; } ;
struct bnx2i_conn {TYPE_3__* ep; TYPE_2__* hba; } ;
struct bnx2i_cmd {int dummy; } ;
struct TYPE_4__ {scalar_t__ sq_prod_qe; } ;
struct TYPE_6__ {int /*<<< orphan*/  state; TYPE_1__ qp; } ;
struct TYPE_5__ {scalar_t__ mp_bd_dma; } ;

/* Variables and functions */
 int /*<<< orphan*/  EP_STATE_LOGOUT_SENT ; 
 int ISCSI_LOGOUT_REQUEST_ALWAYS_ONE ; 
 int ISCSI_LOGOUT_REQUEST_TYPE_SHIFT ; 
 int ISCSI_TASK_TYPE_MPATH ; 
 int /*<<< orphan*/  be32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bnx2i_ring_dbell_update_sq_params (struct bnx2i_conn*,int) ; 
 int /*<<< orphan*/  memset (struct bnx2i_logout_request*,int,int) ; 

int bnx2i_send_iscsi_logout(struct bnx2i_conn *bnx2i_conn,
			    struct iscsi_task *task)
{
	struct bnx2i_cmd *bnx2i_cmd;
	struct bnx2i_logout_request *logout_wqe;
	struct iscsi_logout *logout_hdr;

	bnx2i_cmd = (struct bnx2i_cmd *)task->dd_data;
	logout_hdr = (struct iscsi_logout *)task->hdr;

	logout_wqe = (struct bnx2i_logout_request *)
						bnx2i_conn->ep->qp.sq_prod_qe;
	memset(logout_wqe, 0x00, sizeof(struct bnx2i_logout_request));

	logout_wqe->op_code = logout_hdr->opcode;
	logout_wqe->cmd_sn = be32_to_cpu(logout_hdr->cmdsn);
	logout_wqe->op_attr =
			logout_hdr->flags | ISCSI_LOGOUT_REQUEST_ALWAYS_ONE;
	logout_wqe->itt = ((u16)task->itt |
			   (ISCSI_TASK_TYPE_MPATH <<
			    ISCSI_LOGOUT_REQUEST_TYPE_SHIFT));
	logout_wqe->data_length = 0;
	logout_wqe->cid = 0;

	logout_wqe->bd_list_addr_lo = (u32) bnx2i_conn->hba->mp_bd_dma;
	logout_wqe->bd_list_addr_hi = (u32)
				((u64) bnx2i_conn->hba->mp_bd_dma >> 32);
	logout_wqe->num_bds = 1;
	logout_wqe->cq_index = 0; /* CQ# used for completion, 5771x only */

	bnx2i_conn->ep->state = EP_STATE_LOGOUT_SENT;

	bnx2i_ring_dbell_update_sq_params(bnx2i_conn, 1);
	return 0;
}