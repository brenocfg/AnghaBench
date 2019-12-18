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
typedef  int /*<<< orphan*/  u64 ;
typedef  enum xp_retval { ____Placeholder_xp_retval } xp_retval ;

/* Variables and functions */
 int /*<<< orphan*/  SH1_IPI_ACCESS ; 
 int /*<<< orphan*/  SH2_IPI_ACCESS0 ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 scalar_t__ is_shub1 () ; 
 scalar_t__ is_shub2 () ; 
 int sn_register_nofault_code (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  xp ; 
 int xpSalError ; 
 int xpSuccess ; 
 scalar_t__ xp_error_PIOR ; 
 scalar_t__ xp_nofault_PIOR ; 
 int /*<<< orphan*/  xp_nofault_PIOR_target ; 

__attribute__((used)) static enum xp_retval
xp_register_nofault_code_sn2(void)
{
	int ret;
	u64 func_addr;
	u64 err_func_addr;

	func_addr = *(u64 *)xp_nofault_PIOR;
	err_func_addr = *(u64 *)xp_error_PIOR;
	ret = sn_register_nofault_code(func_addr, err_func_addr, err_func_addr,
				       1, 1);
	if (ret != 0) {
		dev_err(xp, "can't register nofault code, error=%d\n", ret);
		return xpSalError;
	}
	/*
	 * Setup the nofault PIO read target. (There is no special reason why
	 * SH_IPI_ACCESS was selected.)
	 */
	if (is_shub1())
		xp_nofault_PIOR_target = SH1_IPI_ACCESS;
	else if (is_shub2())
		xp_nofault_PIOR_target = SH2_IPI_ACCESS0;

	return xpSuccess;
}