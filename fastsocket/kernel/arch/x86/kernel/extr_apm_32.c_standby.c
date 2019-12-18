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
 int APM_NO_ERROR ; 
 int /*<<< orphan*/  APM_STATE_STANDBY ; 
 int APM_SUCCESS ; 
 int /*<<< orphan*/  PMSG_RESUME ; 
 int /*<<< orphan*/  PMSG_SUSPEND ; 
 int /*<<< orphan*/  apm_error (char*,int) ; 
 int /*<<< orphan*/  dpm_resume_noirq (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dpm_suspend_noirq (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  local_irq_disable () ; 
 int /*<<< orphan*/  local_irq_enable () ; 
 int set_system_power_state (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sysdev_resume () ; 
 int /*<<< orphan*/  sysdev_suspend (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void standby(void)
{
	int err;

	dpm_suspend_noirq(PMSG_SUSPEND);

	local_irq_disable();
	sysdev_suspend(PMSG_SUSPEND);
	local_irq_enable();

	err = set_system_power_state(APM_STATE_STANDBY);
	if ((err != APM_SUCCESS) && (err != APM_NO_ERROR))
		apm_error("standby", err);

	local_irq_disable();
	sysdev_resume();
	local_irq_enable();

	dpm_resume_noirq(PMSG_RESUME);
}