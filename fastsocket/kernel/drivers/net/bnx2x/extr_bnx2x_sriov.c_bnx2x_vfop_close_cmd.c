#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct bnx2x_virtf {int dummy; } ;
struct bnx2x_vfop_cmd {int /*<<< orphan*/  block; int /*<<< orphan*/  done; } ;
struct TYPE_3__ {int qid; } ;
struct TYPE_4__ {TYPE_1__ qx; } ;
struct bnx2x_vfop {TYPE_2__ args; } ;
struct bnx2x {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BNX2X_VFOP_CLOSE_QUEUES ; 
 int ENOMEM ; 
 struct bnx2x_vfop* bnx2x_vfop_add (struct bnx2x*,struct bnx2x_virtf*) ; 
 int /*<<< orphan*/  bnx2x_vfop_close ; 
 int /*<<< orphan*/  bnx2x_vfop_opset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int bnx2x_vfop_transition (struct bnx2x*,struct bnx2x_virtf*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int bnx2x_vfop_close_cmd(struct bnx2x *bp,
			 struct bnx2x_virtf *vf,
			 struct bnx2x_vfop_cmd *cmd)
{
	struct bnx2x_vfop *vfop = bnx2x_vfop_add(bp, vf);
	if (vfop) {
		vfop->args.qx.qid = -1; /* loop */
		bnx2x_vfop_opset(BNX2X_VFOP_CLOSE_QUEUES,
				 bnx2x_vfop_close, cmd->done);
		return bnx2x_vfop_transition(bp, vf, bnx2x_vfop_close,
					     cmd->block);
	}
	return -ENOMEM;
}