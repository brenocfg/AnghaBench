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
 int /*<<< orphan*/  cpuidle_kick_cpus () ; 
 scalar_t__ enabled_devices ; 
 scalar_t__ pm_idle ; 
 scalar_t__ pm_idle_old ; 

void cpuidle_uninstall_idle_handler(void)
{
	if (enabled_devices && pm_idle_old && (pm_idle != pm_idle_old)) {
		pm_idle = pm_idle_old;
		cpuidle_kick_cpus();
	}
}