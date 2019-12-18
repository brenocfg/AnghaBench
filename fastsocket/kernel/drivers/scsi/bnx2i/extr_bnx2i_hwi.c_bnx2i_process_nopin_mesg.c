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
typedef  int u16 ;
struct iscsi_task {TYPE_3__* hdr; } ;
struct iscsi_session {int /*<<< orphan*/  lock; } ;
struct iscsi_nopin {int /*<<< orphan*/  lun; void* ttt; scalar_t__ itt; int /*<<< orphan*/  flags; void* exp_cmdsn; void* max_cmdsn; int /*<<< orphan*/  opcode; } ;
struct iscsi_hdr {int dummy; } ;
struct iscsi_conn {int dummy; } ;
struct cqe {int dummy; } ;
struct bnx2i_nop_in_msg {int itt; int /*<<< orphan*/  lun; int /*<<< orphan*/  ttt; int /*<<< orphan*/  exp_cmd_sn; int /*<<< orphan*/  max_cmd_sn; int /*<<< orphan*/  op_code; } ;
struct TYPE_5__ {int /*<<< orphan*/  resp_hdr; } ;
struct bnx2i_conn {TYPE_2__ gen_pdu; TYPE_1__* cls_conn; } ;
typedef  int /*<<< orphan*/  itt_t ;
struct TYPE_6__ {scalar_t__ itt; } ;
struct TYPE_4__ {struct iscsi_conn* dd_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  ISCSI_FLAG_CMD_FINAL ; 
 int ISCSI_NOP_IN_MSG_INDEX ; 
 scalar_t__ RESERVED_ITT ; 
 int /*<<< orphan*/  __iscsi_complete_pdu (struct iscsi_conn*,struct iscsi_hdr*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bnx2i_unsol_pdu_adjust_rq (struct bnx2i_conn*) ; 
 void* cpu_to_be32 (int /*<<< orphan*/ ) ; 
 struct iscsi_task* iscsi_itt_to_task (struct iscsi_conn*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  memset (struct iscsi_nopin*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int bnx2i_process_nopin_mesg(struct iscsi_session *session,
				     struct bnx2i_conn *bnx2i_conn,
				     struct cqe *cqe)
{
	struct iscsi_conn *conn = bnx2i_conn->cls_conn->dd_data;
	struct iscsi_task *task;
	struct bnx2i_nop_in_msg *nop_in;
	struct iscsi_nopin *hdr;
	int tgt_async_nop = 0;

	nop_in = (struct bnx2i_nop_in_msg *)cqe;

	spin_lock(&session->lock);
	hdr = (struct iscsi_nopin *)&bnx2i_conn->gen_pdu.resp_hdr;
	memset(hdr, 0, sizeof(struct iscsi_hdr));
	hdr->opcode = nop_in->op_code;
	hdr->max_cmdsn = cpu_to_be32(nop_in->max_cmd_sn);
	hdr->exp_cmdsn = cpu_to_be32(nop_in->exp_cmd_sn);
	hdr->ttt = cpu_to_be32(nop_in->ttt);

	if (nop_in->itt == (u16) RESERVED_ITT) {
		bnx2i_unsol_pdu_adjust_rq(bnx2i_conn);
		hdr->itt = RESERVED_ITT;
		tgt_async_nop = 1;
		goto done;
	}

	/* this is a response to one of our nop-outs */
	task = iscsi_itt_to_task(conn,
			 (itt_t) (nop_in->itt & ISCSI_NOP_IN_MSG_INDEX));
	if (task) {
		hdr->flags = ISCSI_FLAG_CMD_FINAL;
		hdr->itt = task->hdr->itt;
		hdr->ttt = cpu_to_be32(nop_in->ttt);
		memcpy(&hdr->lun, nop_in->lun, 8);
	}
done:
	__iscsi_complete_pdu(conn, (struct iscsi_hdr *)hdr, NULL, 0);
	spin_unlock(&session->lock);

	return tgt_async_nop;
}