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
struct bnx2x_virtf {int /*<<< orphan*/  flr_clnup_stage; int /*<<< orphan*/  abs_vfid; } ;
struct bnx2x_vfop_cmd {void (* done ) (struct bnx2x*,struct bnx2x_virtf*) ;int block; } ;
struct bnx2x_vfop_args_qx {int /*<<< orphan*/  qid; } ;
struct TYPE_2__ {struct bnx2x_vfop_args_qx qx; } ;
struct bnx2x_vfop {int state; scalar_t__ rc; TYPE_1__ args; } ;
struct bnx2x {int dummy; } ;
typedef  enum bnx2x_vfop_flr_state { ____Placeholder_bnx2x_vfop_flr_state } bnx2x_vfop_flr_state ;

/* Variables and functions */
 int /*<<< orphan*/  BNX2X_ERR (char*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  BNX2X_MSG_IOV ; 
#define  BNX2X_VFOP_FLR_HW 129 
#define  BNX2X_VFOP_FLR_QUEUES 128 
 int /*<<< orphan*/  CHANNEL_TLV_FLR ; 
 int /*<<< orphan*/  DP (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  VF_FLR_ACK ; 
 int /*<<< orphan*/  bnx2x_unlock_vf_pf_channel (struct bnx2x*,struct bnx2x_virtf*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bnx2x_vf_enable_mbx (struct bnx2x*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bnx2x_vf_flr_clnup_hw (struct bnx2x*,struct bnx2x_virtf*) ; 
 int /*<<< orphan*/  bnx2x_vf_free_resc (struct bnx2x*,struct bnx2x_virtf*) ; 
 struct bnx2x_vfop* bnx2x_vfop_cur (struct bnx2x*,struct bnx2x_virtf*) ; 
 int /*<<< orphan*/  bnx2x_vfop_default (int) ; 
 int /*<<< orphan*/  bnx2x_vfop_end (struct bnx2x*,struct bnx2x_virtf*,struct bnx2x_vfop*) ; 
 scalar_t__ bnx2x_vfop_mcast_cmd (struct bnx2x*,struct bnx2x_virtf*,struct bnx2x_vfop_cmd*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 scalar_t__ bnx2x_vfop_qflr_cmd (struct bnx2x*,struct bnx2x_virtf*,struct bnx2x_vfop_cmd*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vf_rxq_count (struct bnx2x_virtf*) ; 

__attribute__((used)) static void bnx2x_vfop_flr(struct bnx2x *bp, struct bnx2x_virtf *vf)
{
	struct bnx2x_vfop *vfop = bnx2x_vfop_cur(bp, vf);
	struct bnx2x_vfop_args_qx *qx = &vfop->args.qx;
	enum bnx2x_vfop_flr_state state = vfop->state;
	struct bnx2x_vfop_cmd cmd = {
		.done = bnx2x_vfop_flr,
		.block = false,
	};

	if (vfop->rc < 0)
		goto op_err;

	DP(BNX2X_MSG_IOV, "vf[%d] STATE: %d\n", vf->abs_vfid, state);

	switch (state) {
	case BNX2X_VFOP_FLR_QUEUES:
		/* the cleanup operations are valid if and only if the VF
		 * was first acquired.
		 */
		if (++(qx->qid) < vf_rxq_count(vf)) {
			vfop->rc = bnx2x_vfop_qflr_cmd(bp, vf, &cmd,
						       qx->qid);
			if (vfop->rc)
				goto op_err;
			return;
		}
		/* remove multicasts */
		vfop->state = BNX2X_VFOP_FLR_HW;
		vfop->rc = bnx2x_vfop_mcast_cmd(bp, vf, &cmd, NULL,
						0, true);
		if (vfop->rc)
			goto op_err;
		return;
	case BNX2X_VFOP_FLR_HW:

		/* dispatch final cleanup and wait for HW queues to flush */
		bnx2x_vf_flr_clnup_hw(bp, vf);

		/* release VF resources */
		bnx2x_vf_free_resc(bp, vf);

		/* re-open the mailbox */
		bnx2x_vf_enable_mbx(bp, vf->abs_vfid);

		goto op_done;
	default:
		bnx2x_vfop_default(state);
	}
op_err:
	BNX2X_ERR("VF[%d] FLR error: rc %d\n", vf->abs_vfid, vfop->rc);
op_done:
	vf->flr_clnup_stage = VF_FLR_ACK;
	bnx2x_vfop_end(bp, vf, vfop);
	bnx2x_unlock_vf_pf_channel(bp, vf, CHANNEL_TLV_FLR);
}