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
struct bnx2x_vfop_args_mcast {int mc_num; TYPE_4__* mc; } ;
struct TYPE_7__ {struct bnx2x_vfop_args_mcast mc_list; } ;
struct bnx2x_vfop {int state; scalar_t__ rc; TYPE_3__ args; TYPE_1__* op_p; } ;
struct bnx2x_raw_obj {int /*<<< orphan*/  (* check_pending ) (struct bnx2x_raw_obj*) ;} ;
struct bnx2x_mcast_ramrod_params {int /*<<< orphan*/  mcast_list; TYPE_2__* mcast_obj; } ;
struct bnx2x {int dummy; } ;
typedef  enum bnx2x_vfop_mcast_state { ____Placeholder_bnx2x_vfop_mcast_state } bnx2x_vfop_mcast_state ;
struct TYPE_8__ {int /*<<< orphan*/  link; } ;
struct TYPE_6__ {struct bnx2x_raw_obj raw; } ;
struct TYPE_5__ {struct bnx2x_mcast_ramrod_params mcast; } ;

/* Variables and functions */
 int /*<<< orphan*/  BNX2X_ERR (char*,scalar_t__) ; 
 int /*<<< orphan*/  BNX2X_MCAST_CMD_ADD ; 
 int /*<<< orphan*/  BNX2X_MCAST_CMD_DEL ; 
 int /*<<< orphan*/  BNX2X_MSG_IOV ; 
#define  BNX2X_VFOP_MCAST_ADD 130 
#define  BNX2X_VFOP_MCAST_CHK_DONE 129 
#define  BNX2X_VFOP_MCAST_DEL 128 
 int /*<<< orphan*/  DP (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  VFOP_CONT ; 
 int /*<<< orphan*/  VFOP_DONE ; 
 void* bnx2x_config_mcast (struct bnx2x*,struct bnx2x_mcast_ramrod_params*,int /*<<< orphan*/ ) ; 
 struct bnx2x_vfop* bnx2x_vfop_cur (struct bnx2x*,struct bnx2x_virtf*) ; 
 int /*<<< orphan*/  bnx2x_vfop_default (int) ; 
 int /*<<< orphan*/  bnx2x_vfop_end (struct bnx2x*,struct bnx2x_virtf*,struct bnx2x_vfop*) ; 
 int /*<<< orphan*/  bnx2x_vfop_finalize (struct bnx2x_virtf*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bnx2x_vfop_reset_wq (struct bnx2x_virtf*) ; 
 int /*<<< orphan*/  kfree (TYPE_4__*) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct bnx2x_raw_obj*) ; 
 int /*<<< orphan*/  stub2 (struct bnx2x_raw_obj*) ; 

__attribute__((used)) static void bnx2x_vfop_mcast(struct bnx2x *bp, struct bnx2x_virtf *vf)
{
	struct bnx2x_vfop *vfop = bnx2x_vfop_cur(bp, vf);
	struct bnx2x_mcast_ramrod_params *mcast = &vfop->op_p->mcast;
	struct bnx2x_raw_obj *raw = &mcast->mcast_obj->raw;
	struct bnx2x_vfop_args_mcast *args = &vfop->args.mc_list;
	enum bnx2x_vfop_mcast_state state = vfop->state;
	int i;

	bnx2x_vfop_reset_wq(vf);

	if (vfop->rc < 0)
		goto op_err;

	DP(BNX2X_MSG_IOV, "vf[%d] STATE: %d\n", vf->abs_vfid, state);

	switch (state) {
	case BNX2X_VFOP_MCAST_DEL:
		/* clear existing mcasts */
		vfop->state = BNX2X_VFOP_MCAST_ADD;
		vfop->rc = bnx2x_config_mcast(bp, mcast, BNX2X_MCAST_CMD_DEL);
		bnx2x_vfop_finalize(vf, vfop->rc, VFOP_CONT);

	case BNX2X_VFOP_MCAST_ADD:
		if (raw->check_pending(raw))
			goto op_pending;

		if (args->mc_num) {
			/* update mcast list on the ramrod params */
			INIT_LIST_HEAD(&mcast->mcast_list);
			for (i = 0; i < args->mc_num; i++)
				list_add_tail(&(args->mc[i].link),
					      &mcast->mcast_list);
			/* add new mcasts */
			vfop->state = BNX2X_VFOP_MCAST_CHK_DONE;
			vfop->rc = bnx2x_config_mcast(bp, mcast,
						      BNX2X_MCAST_CMD_ADD);
		}
		bnx2x_vfop_finalize(vf, vfop->rc, VFOP_DONE);

	case BNX2X_VFOP_MCAST_CHK_DONE:
		vfop->rc = raw->check_pending(raw) ? 1 : 0;
		bnx2x_vfop_finalize(vf, vfop->rc, VFOP_DONE);
	default:
		bnx2x_vfop_default(state);
	}
op_err:
	BNX2X_ERR("MCAST CONFIG error: rc %d\n", vfop->rc);
op_done:
	kfree(args->mc);
	bnx2x_vfop_end(bp, vf, vfop);
op_pending:
	return;
}