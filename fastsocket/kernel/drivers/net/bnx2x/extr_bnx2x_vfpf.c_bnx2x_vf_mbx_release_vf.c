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
struct bnx2x_virtf {int /*<<< orphan*/  op_rc; int /*<<< orphan*/  abs_vfid; } ;
struct bnx2x_vfop_cmd {int block; int /*<<< orphan*/  (* done ) (struct bnx2x*,struct bnx2x_virtf*) ;} ;
struct bnx2x_vf_mbx {int dummy; } ;
struct bnx2x {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BNX2X_MSG_IOV ; 
 int /*<<< orphan*/  DP (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bnx2x_vf_mbx_resp (struct bnx2x*,struct bnx2x_virtf*) ; 
 int /*<<< orphan*/  bnx2x_vfop_release_cmd (struct bnx2x*,struct bnx2x_virtf*,struct bnx2x_vfop_cmd*) ; 

__attribute__((used)) static void bnx2x_vf_mbx_release_vf(struct bnx2x *bp, struct bnx2x_virtf *vf,
				    struct bnx2x_vf_mbx *mbx)
{
	struct bnx2x_vfop_cmd cmd = {
		.done = bnx2x_vf_mbx_resp,
		.block = false,
	};

	DP(BNX2X_MSG_IOV, "VF[%d] VF_RELEASE\n", vf->abs_vfid);

	vf->op_rc = bnx2x_vfop_release_cmd(bp, vf, &cmd);
	if (vf->op_rc)
		bnx2x_vf_mbx_resp(bp, vf);
}