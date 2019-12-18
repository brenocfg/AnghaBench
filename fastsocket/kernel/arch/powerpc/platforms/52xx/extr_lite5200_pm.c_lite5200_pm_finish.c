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

/* Variables and functions */
 scalar_t__ PM_SUSPEND_STANDBY ; 
 scalar_t__ lite5200_pm_target_state ; 
 int /*<<< orphan*/  mpc52xx_pm_finish () ; 

__attribute__((used)) static void lite5200_pm_finish(void)
{
	/* deep sleep? let mpc52xx code handle that */
	if (lite5200_pm_target_state == PM_SUSPEND_STANDBY)
		mpc52xx_pm_finish();
}