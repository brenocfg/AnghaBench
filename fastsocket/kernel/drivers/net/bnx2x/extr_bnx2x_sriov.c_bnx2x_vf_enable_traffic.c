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
struct bnx2x {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BP_ABS_FUNC (struct bnx2x*) ; 
 int /*<<< orphan*/  HW_VF_HANDLE (struct bnx2x*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PBF_REG_DISABLE_VF ; 
 int /*<<< orphan*/  REG_WR (struct bnx2x*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bnx2x_pretend_func (struct bnx2x*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bnx2x_vf_igu_reset (struct bnx2x*,struct bnx2x_virtf*) ; 

__attribute__((used)) static void bnx2x_vf_enable_traffic(struct bnx2x *bp, struct bnx2x_virtf *vf)
{
	/* Reset vf in IGU  interrupts are still disabled */
	bnx2x_vf_igu_reset(bp, vf);

	/* pretend to enable the vf with the PBF */
	bnx2x_pretend_func(bp, HW_VF_HANDLE(bp, vf->abs_vfid));
	REG_WR(bp, PBF_REG_DISABLE_VF, 0);
	bnx2x_pretend_func(bp, BP_ABS_FUNC(bp));
}