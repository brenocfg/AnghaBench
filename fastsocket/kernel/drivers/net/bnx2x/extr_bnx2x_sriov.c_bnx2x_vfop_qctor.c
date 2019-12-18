#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct bnx2x_virtf {int /*<<< orphan*/  abs_vfid; } ;
struct bnx2x_vfop_args_qctor {int /*<<< orphan*/  qid; int /*<<< orphan*/  sb_idx; } ;
struct TYPE_5__ {struct bnx2x_vfop_args_qctor qctor; } ;
struct bnx2x_vfop {int state; scalar_t__ rc; TYPE_4__* op_p; TYPE_1__ args; } ;
struct TYPE_6__ {int /*<<< orphan*/  setup; } ;
struct bnx2x_queue_state_params {int /*<<< orphan*/  cmd; TYPE_2__ params; int /*<<< orphan*/  q_obj; } ;
struct bnx2x {int dummy; } ;
typedef  enum bnx2x_vfop_qctor_state { ____Placeholder_bnx2x_vfop_qctor_state } bnx2x_vfop_qctor_state ;
struct TYPE_7__ {int /*<<< orphan*/  prep_qsetup; struct bnx2x_queue_state_params qstate; } ;
struct TYPE_8__ {TYPE_3__ qctor; } ;

/* Variables and functions */
 int /*<<< orphan*/  BNX2X_ERR (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  BNX2X_MSG_IOV ; 
 int /*<<< orphan*/  BNX2X_Q_CMD_INIT ; 
 int /*<<< orphan*/  BNX2X_Q_CMD_SETUP ; 
 int /*<<< orphan*/  BNX2X_Q_LOGICAL_STATE_ACTIVE ; 
#define  BNX2X_VFOP_QCTOR_INIT 130 
#define  BNX2X_VFOP_QCTOR_INT_EN 129 
#define  BNX2X_VFOP_QCTOR_SETUP 128 
 int /*<<< orphan*/  DP (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  IGU_INT_ENABLE ; 
 int /*<<< orphan*/  USTORM_ID ; 
 int /*<<< orphan*/  VFOP_CONT ; 
 int /*<<< orphan*/  bnx2x_get_q_logical_state (struct bnx2x*,int /*<<< orphan*/ ) ; 
 void* bnx2x_queue_state_change (struct bnx2x*,struct bnx2x_queue_state_params*) ; 
 int /*<<< orphan*/  bnx2x_vf_igu_ack_sb (struct bnx2x*,struct bnx2x_virtf*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct bnx2x_vfop* bnx2x_vfop_cur (struct bnx2x*,struct bnx2x_virtf*) ; 
 int /*<<< orphan*/  bnx2x_vfop_default (int) ; 
 int /*<<< orphan*/  bnx2x_vfop_end (struct bnx2x*,struct bnx2x_virtf*,struct bnx2x_vfop*) ; 
 int /*<<< orphan*/  bnx2x_vfop_finalize (struct bnx2x_virtf*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bnx2x_vfop_reset_wq (struct bnx2x_virtf*) ; 
 int /*<<< orphan*/  vf_igu_sb (struct bnx2x_virtf*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void bnx2x_vfop_qctor(struct bnx2x *bp, struct bnx2x_virtf *vf)
{
	struct bnx2x_vfop *vfop = bnx2x_vfop_cur(bp, vf);
	struct bnx2x_vfop_args_qctor *args = &vfop->args.qctor;
	struct bnx2x_queue_state_params *q_params = &vfop->op_p->qctor.qstate;
	enum bnx2x_vfop_qctor_state state = vfop->state;

	bnx2x_vfop_reset_wq(vf);

	if (vfop->rc < 0)
		goto op_err;

	DP(BNX2X_MSG_IOV, "vf[%d] STATE: %d\n", vf->abs_vfid, state);

	switch (state) {
	case BNX2X_VFOP_QCTOR_INIT:

		/* has this queue already been opened? */
		if (bnx2x_get_q_logical_state(bp, q_params->q_obj) ==
		    BNX2X_Q_LOGICAL_STATE_ACTIVE) {
			DP(BNX2X_MSG_IOV,
			   "Entered qctor but queue was already up. Aborting gracefully\n");
			goto op_done;
		}

		/* next state */
		vfop->state = BNX2X_VFOP_QCTOR_SETUP;

		q_params->cmd = BNX2X_Q_CMD_INIT;
		vfop->rc = bnx2x_queue_state_change(bp, q_params);

		bnx2x_vfop_finalize(vf, vfop->rc, VFOP_CONT);

	case BNX2X_VFOP_QCTOR_SETUP:
		/* next state */
		vfop->state = BNX2X_VFOP_QCTOR_INT_EN;

		/* copy pre-prepared setup params to the queue-state params */
		vfop->op_p->qctor.qstate.params.setup =
			vfop->op_p->qctor.prep_qsetup;

		q_params->cmd = BNX2X_Q_CMD_SETUP;
		vfop->rc = bnx2x_queue_state_change(bp, q_params);

		bnx2x_vfop_finalize(vf, vfop->rc, VFOP_CONT);

	case BNX2X_VFOP_QCTOR_INT_EN:

		/* enable interrupts */
		bnx2x_vf_igu_ack_sb(bp, vf, vf_igu_sb(vf, args->sb_idx),
				    USTORM_ID, 0, IGU_INT_ENABLE, 0);
		goto op_done;
	default:
		bnx2x_vfop_default(state);
	}
op_err:
	BNX2X_ERR("QCTOR[%d:%d] error: cmd %d, rc %d\n",
		  vf->abs_vfid, args->qid, q_params->cmd, vfop->rc);
op_done:
	bnx2x_vfop_end(bp, vf, vfop);
op_pending:
	return;
}