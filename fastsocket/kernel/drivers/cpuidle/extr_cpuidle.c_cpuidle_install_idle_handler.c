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
 scalar_t__ cpuidle_idle_call ; 
 scalar_t__ enabled_devices ; 
 scalar_t__ pm_idle ; 
 int /*<<< orphan*/  smp_wmb () ; 

void cpuidle_install_idle_handler(void)
{
	if (enabled_devices && (pm_idle != cpuidle_idle_call)) {
		/* Make sure all changes finished before we switch to new idle */
		smp_wmb();
		pm_idle = cpuidle_idle_call;
	}
}