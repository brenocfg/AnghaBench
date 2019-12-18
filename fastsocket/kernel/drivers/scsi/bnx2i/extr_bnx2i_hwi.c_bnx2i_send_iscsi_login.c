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
typedef  int /*<<< orphan*/  u16 ;
struct iscsi_task {int itt; scalar_t__ hdr; scalar_t__ dd_data; } ;
struct iscsi_login {int /*<<< orphan*/  exp_statsn; int /*<<< orphan*/  cmdsn; int /*<<< orphan*/  cid; int /*<<< orphan*/  tsih; scalar_t__ isid; int /*<<< orphan*/  dlength; int /*<<< orphan*/  min_version; int /*<<< orphan*/  max_version; int /*<<< orphan*/  flags; int /*<<< orphan*/  opcode; } ;
struct bnx2i_login_request {int itt; int num_bds; scalar_t__ cq_index; void* bd_list_addr_hi; void* bd_list_addr_lo; void* resp_buffer; void* resp_bd_list_addr_hi; void* resp_bd_list_addr_lo; int /*<<< orphan*/  flags; void* exp_stat_sn; void* cmd_sn; int /*<<< orphan*/  cid; int /*<<< orphan*/  tsih; int /*<<< orphan*/  isid_hi; void* isid_lo; int /*<<< orphan*/  data_length; int /*<<< orphan*/  version_min; int /*<<< orphan*/  version_max; int /*<<< orphan*/  op_attr; int /*<<< orphan*/  op_code; } ;
struct TYPE_6__ {int resp_buf_size; scalar_t__ req_bd_dma; scalar_t__ resp_bd_dma; } ;
struct bnx2i_conn {TYPE_3__ gen_pdu; TYPE_2__* ep; } ;
struct bnx2i_cmd {int dummy; } ;
struct TYPE_4__ {scalar_t__ sq_prod_qe; } ;
struct TYPE_5__ {TYPE_1__ qp; } ;

/* Variables and functions */
 int ISCSI_LOGIN_REQUEST_NUM_RESP_BDS_SHIFT ; 
 int ISCSI_LOGIN_REQUEST_RESP_BUFFER_LENGTH_SHIFT ; 
 int ISCSI_LOGIN_REQUEST_TYPE_SHIFT ; 
 int /*<<< orphan*/  ISCSI_LOGIN_REQUEST_UPDATE_EXP_STAT_SN ; 
 int ISCSI_TASK_TYPE_MPATH ; 
 void* be32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bnx2i_ring_dbell_update_sq_params (struct bnx2i_conn*,int) ; 
 int /*<<< orphan*/  ntoh24 (int /*<<< orphan*/ ) ; 

int bnx2i_send_iscsi_login(struct bnx2i_conn *bnx2i_conn,
			   struct iscsi_task *task)
{
	struct bnx2i_cmd *bnx2i_cmd;
	struct bnx2i_login_request *login_wqe;
	struct iscsi_login *login_hdr;
	u32 dword;

	bnx2i_cmd = (struct bnx2i_cmd *)task->dd_data;
	login_hdr = (struct iscsi_login *)task->hdr;
	login_wqe = (struct bnx2i_login_request *)
						bnx2i_conn->ep->qp.sq_prod_qe;

	login_wqe->op_code = login_hdr->opcode;
	login_wqe->op_attr = login_hdr->flags;
	login_wqe->version_max = login_hdr->max_version;
	login_wqe->version_min = login_hdr->min_version;
	login_wqe->data_length = ntoh24(login_hdr->dlength);
	login_wqe->isid_lo = *((u32 *) login_hdr->isid);
	login_wqe->isid_hi = *((u16 *) login_hdr->isid + 2);
	login_wqe->tsih = login_hdr->tsih;
	login_wqe->itt = task->itt |
		(ISCSI_TASK_TYPE_MPATH << ISCSI_LOGIN_REQUEST_TYPE_SHIFT);
	login_wqe->cid = login_hdr->cid;

	login_wqe->cmd_sn = be32_to_cpu(login_hdr->cmdsn);
	login_wqe->exp_stat_sn = be32_to_cpu(login_hdr->exp_statsn);
	login_wqe->flags = ISCSI_LOGIN_REQUEST_UPDATE_EXP_STAT_SN;

	login_wqe->resp_bd_list_addr_lo = (u32) bnx2i_conn->gen_pdu.resp_bd_dma;
	login_wqe->resp_bd_list_addr_hi =
		(u32) ((u64) bnx2i_conn->gen_pdu.resp_bd_dma >> 32);

	dword = ((1 << ISCSI_LOGIN_REQUEST_NUM_RESP_BDS_SHIFT) |
		 (bnx2i_conn->gen_pdu.resp_buf_size <<
		  ISCSI_LOGIN_REQUEST_RESP_BUFFER_LENGTH_SHIFT));
	login_wqe->resp_buffer = dword;
	login_wqe->bd_list_addr_lo = (u32) bnx2i_conn->gen_pdu.req_bd_dma;
	login_wqe->bd_list_addr_hi =
		(u32) ((u64) bnx2i_conn->gen_pdu.req_bd_dma >> 32);
	login_wqe->num_bds = 1;
	login_wqe->cq_index = 0; /* CQ# used for completion, 5771x only */

	bnx2i_ring_dbell_update_sq_params(bnx2i_conn, 1);
	return 0;
}