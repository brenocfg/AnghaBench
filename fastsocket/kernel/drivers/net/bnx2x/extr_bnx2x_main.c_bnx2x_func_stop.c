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
struct bnx2x_func_state_params {int /*<<< orphan*/  ramrod_flags; int /*<<< orphan*/  cmd; int /*<<< orphan*/ * f_obj; int /*<<< orphan*/ * member_0; } ;
struct bnx2x {int /*<<< orphan*/  func_obj; } ;

/* Variables and functions */
 int /*<<< orphan*/  BNX2X_ERR (char*) ; 
 int /*<<< orphan*/  BNX2X_F_CMD_STOP ; 
 int /*<<< orphan*/  RAMROD_COMP_WAIT ; 
 int /*<<< orphan*/  RAMROD_DRV_CLR_ONLY ; 
 int /*<<< orphan*/  __set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int bnx2x_func_state_change (struct bnx2x*,struct bnx2x_func_state_params*) ; 

__attribute__((used)) static int bnx2x_func_stop(struct bnx2x *bp)
{
	struct bnx2x_func_state_params func_params = {NULL};
	int rc;

	/* Prepare parameters for function state transitions */
	__set_bit(RAMROD_COMP_WAIT, &func_params.ramrod_flags);
	func_params.f_obj = &bp->func_obj;
	func_params.cmd = BNX2X_F_CMD_STOP;

	/*
	 * Try to stop the function the 'good way'. If fails (in case
	 * of a parity error during bnx2x_chip_cleanup()) and we are
	 * not in a debug mode, perform a state transaction in order to
	 * enable further HW_RESET transaction.
	 */
	rc = bnx2x_func_state_change(bp, &func_params);
	if (rc) {
#ifdef BNX2X_STOP_ON_ERROR
		return rc;
#else
		BNX2X_ERR("FUNC_STOP ramrod failed. Running a dry transaction\n");
		__set_bit(RAMROD_DRV_CLR_ONLY, &func_params.ramrod_flags);
		return bnx2x_func_state_change(bp, &func_params);
#endif
	}

	return 0;
}