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
struct bnx2x_virtf {int state; int /*<<< orphan*/  abs_vfid; } ;
struct bnx2x_vfop_cmd {void (* done ) (struct bnx2x*,struct bnx2x_virtf*) ;int block; } ;
struct bnx2x_vfop {scalar_t__ rc; } ;
struct bnx2x {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BNX2X_ERR (char*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  BNX2X_MSG_IOV ; 
 int /*<<< orphan*/  DP (int /*<<< orphan*/ ,char*,...) ; 
#define  VF_ACQUIRED 131 
#define  VF_ENABLED 130 
#define  VF_FREE 129 
#define  VF_RESET 128 
 int /*<<< orphan*/  bnx2x_vf_free_resc (struct bnx2x*,struct bnx2x_virtf*) ; 
 scalar_t__ bnx2x_vfop_close_cmd (struct bnx2x*,struct bnx2x_virtf*,struct bnx2x_vfop_cmd*) ; 
 struct bnx2x_vfop* bnx2x_vfop_cur (struct bnx2x*,struct bnx2x_virtf*) ; 
 int /*<<< orphan*/  bnx2x_vfop_default (int) ; 
 int /*<<< orphan*/  bnx2x_vfop_end (struct bnx2x*,struct bnx2x_virtf*,struct bnx2x_vfop*) ; 

__attribute__((used)) static void bnx2x_vfop_release(struct bnx2x *bp, struct bnx2x_virtf *vf)
{
	struct bnx2x_vfop *vfop = bnx2x_vfop_cur(bp, vf);
	struct bnx2x_vfop_cmd cmd = {
		.done = bnx2x_vfop_release,
		.block = false,
	};

	DP(BNX2X_MSG_IOV, "vfop->rc %d\n", vfop->rc);

	if (vfop->rc < 0)
		goto op_err;

	DP(BNX2X_MSG_IOV, "VF[%d] STATE: %s\n", vf->abs_vfid,
	   vf->state == VF_FREE ? "Free" :
	   vf->state == VF_ACQUIRED ? "Acquired" :
	   vf->state == VF_ENABLED ? "Enabled" :
	   vf->state == VF_RESET ? "Reset" :
	   "Unknown");

	switch (vf->state) {
	case VF_ENABLED:
		vfop->rc = bnx2x_vfop_close_cmd(bp, vf, &cmd);
		if (vfop->rc)
			goto op_err;
		return;

	case VF_ACQUIRED:
		DP(BNX2X_MSG_IOV, "about to free resources\n");
		bnx2x_vf_free_resc(bp, vf);
		DP(BNX2X_MSG_IOV, "vfop->rc %d\n", vfop->rc);
		goto op_done;

	case VF_FREE:
	case VF_RESET:
		/* do nothing */
		goto op_done;
	default:
		bnx2x_vfop_default(vf->state);
	}
op_err:
	BNX2X_ERR("VF[%d] RELEASE error: rc %d\n", vf->abs_vfid, vfop->rc);
op_done:
	bnx2x_vfop_end(bp, vf, vfop);
}