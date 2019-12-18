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
typedef  scalar_t__ suspend_state_t ;

/* Variables and functions */
 scalar_t__ PM_SUSPEND_STANDBY ; 
 int /*<<< orphan*/  enable_kernel_fp () ; 
 int /*<<< orphan*/  iounmap (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lite5200_low_power (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lite5200_restore_regs () ; 
 int /*<<< orphan*/  lite5200_save_regs () ; 
 int /*<<< orphan*/  mbar ; 
 int mpc52xx_pm_enter (scalar_t__) ; 
 int /*<<< orphan*/  sram ; 
 int /*<<< orphan*/  wakeup_decrementer () ; 

__attribute__((used)) static int lite5200_pm_enter(suspend_state_t state)
{
	/* deep sleep? let mpc52xx code handle that */
	if (state == PM_SUSPEND_STANDBY) {
		return mpc52xx_pm_enter(state);
	}

	lite5200_save_regs();

	/* effectively save FP regs */
	enable_kernel_fp();

	lite5200_low_power(sram, mbar);

	lite5200_restore_regs();

	/* restart jiffies */
	wakeup_decrementer();

	iounmap(mbar);
	return 0;
}