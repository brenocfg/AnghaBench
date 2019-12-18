#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int (* begin ) () ;int (* prepare ) () ;int /*<<< orphan*/  (* end ) () ;int /*<<< orphan*/  (* finish ) () ;int /*<<< orphan*/  (* enter ) () ;int /*<<< orphan*/  (* recover ) () ;} ;

/* Variables and functions */
 int ENOSYS ; 
 int /*<<< orphan*/  PMSG_HIBERNATE ; 
 int /*<<< orphan*/  PMSG_RESTORE ; 
 int disable_nonboot_cpus () ; 
 int /*<<< orphan*/  dpm_resume_end (int /*<<< orphan*/ ) ; 
 int dpm_suspend_noirq (int /*<<< orphan*/ ) ; 
 int dpm_suspend_start (int /*<<< orphan*/ ) ; 
 int entering_platform_hibernation ; 
 TYPE_1__* hibernation_ops ; 
 int /*<<< orphan*/  local_irq_disable () ; 
 int /*<<< orphan*/  resume_console () ; 
 int stub1 () ; 
 int /*<<< orphan*/  stub2 () ; 
 int stub3 () ; 
 int /*<<< orphan*/  stub4 () ; 
 int /*<<< orphan*/  stub5 () ; 
 int /*<<< orphan*/  stub6 () ; 
 int /*<<< orphan*/  suspend_console () ; 
 int /*<<< orphan*/  sysdev_suspend (int /*<<< orphan*/ ) ; 

int hibernation_platform_enter(void)
{
	int error;

	if (!hibernation_ops)
		return -ENOSYS;

	/*
	 * We have cancelled the power transition by running
	 * hibernation_ops->finish() before saving the image, so we should let
	 * the firmware know that we're going to enter the sleep state after all
	 */
	error = hibernation_ops->begin();
	if (error)
		goto Close;

	entering_platform_hibernation = true;
	suspend_console();
	error = dpm_suspend_start(PMSG_HIBERNATE);
	if (error) {
		if (hibernation_ops->recover)
			hibernation_ops->recover();
		goto Resume_devices;
	}

	error = dpm_suspend_noirq(PMSG_HIBERNATE);
	if (error)
		goto Resume_devices;

	error = hibernation_ops->prepare();
	if (error)
		goto Platform_finish;

	error = disable_nonboot_cpus();
	if (error)
		goto Platform_finish;

	local_irq_disable();
	sysdev_suspend(PMSG_HIBERNATE);
	hibernation_ops->enter();
	/* We should never get here */
	while (1);

	/*
	 * We don't need to reenable the nonboot CPUs or resume consoles, since
	 * the system is going to be halted anyway.
	 */
 Platform_finish:
	hibernation_ops->finish();

	dpm_suspend_noirq(PMSG_RESTORE);

 Resume_devices:
	entering_platform_hibernation = false;
	dpm_resume_end(PMSG_RESTORE);
	resume_console();

 Close:
	hibernation_ops->end();

	return error;
}