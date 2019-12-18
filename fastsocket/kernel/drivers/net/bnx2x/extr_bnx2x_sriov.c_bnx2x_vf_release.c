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
struct bnx2x_virtf {int /*<<< orphan*/  abs_vfid; } ;
struct bnx2x_vfop_cmd {int block; int /*<<< orphan*/ * done; } ;
struct bnx2x {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CHANNEL_TLV_PF_RELEASE_VF ; 
 int /*<<< orphan*/  WARN (int,char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  bnx2x_lock_vf_pf_channel (struct bnx2x*,struct bnx2x_virtf*,int /*<<< orphan*/ ) ; 
 int bnx2x_vfop_release_cmd (struct bnx2x*,struct bnx2x_virtf*,struct bnx2x_vfop_cmd*) ; 

void bnx2x_vf_release(struct bnx2x *bp, struct bnx2x_virtf *vf, bool block)
{
	struct bnx2x_vfop_cmd cmd = {
		.done = NULL,
		.block = block,
	};
	int rc;
	bnx2x_lock_vf_pf_channel(bp, vf, CHANNEL_TLV_PF_RELEASE_VF);

	rc = bnx2x_vfop_release_cmd(bp, vf, &cmd);
	if (rc)
		WARN(rc,
		     "VF[%d] Failed to allocate resources for release op- rc=%d\n",
		     vf->abs_vfid, rc);
}