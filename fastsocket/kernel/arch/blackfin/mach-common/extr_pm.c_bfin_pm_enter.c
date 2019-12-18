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
typedef  int suspend_state_t ;

/* Variables and functions */
 int EINVAL ; 
#define  PM_SUSPEND_MEM 129 
#define  PM_SUSPEND_STANDBY 128 
 int /*<<< orphan*/  bfin_pm_suspend_mem_enter () ; 
 int /*<<< orphan*/  bfin_pm_suspend_standby_enter () ; 

__attribute__((used)) static int bfin_pm_enter(suspend_state_t state)
{
	switch (state) {
	case PM_SUSPEND_STANDBY:
		bfin_pm_suspend_standby_enter();
		break;
	case PM_SUSPEND_MEM:
		bfin_pm_suspend_mem_enter();
		break;
	default:
		return -EINVAL;
	}

	return 0;
}