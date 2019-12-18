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
typedef  int /*<<< orphan*/  pid_t ;

/* Variables and functions */
 scalar_t__ CPUMON_MAKE_FATAL ; 
 int /*<<< orphan*/  EBUSY ; 
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  RLIMIT_CPU_USAGE_MONITOR ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  proc_disable_cpumon (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  proc_get_cpumon_params (int /*<<< orphan*/ ,int*,int*) ; 
 int proc_rlimit_control (int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*) ; 
 int proc_set_cpumon_params (int /*<<< orphan*/ ,int,int) ; 

int
proc_set_cpumon_params_fatal(pid_t pid, int percentage, int interval)
{
	int current_percentage = 0;
	int current_interval = 0;   /* intervals are in seconds */
	int ret = 0;

	if ((percentage <= 0)  || (interval <= 0)) {
		errno = EINVAL;
		return (-1);
	}

	/*
	 * Do a simple query to see if CPU monitoring is
	 * already active.  If either the percentage or the
	 * interval is nonzero, then CPU monitoring is
	 * already in use for this process.
	 * 
	 * XXX: need set...() and set..fatal() to behave similarly.
	 * Currently, this check prevents 1st party apps (which get a
	 * default non-fatal monitor) not to get a fatal monitor.
	 */
	(void)proc_get_cpumon_params(pid, &current_percentage, &current_interval);
	if (current_percentage || current_interval)
	{
		/*
		 * The CPU monitor appears to be active.
		 * We choose not to disturb those settings.
		 */
		errno = EBUSY;
		return (-1);
	}
	
	if ((ret = proc_set_cpumon_params(pid, percentage, interval)) != 0) {
		/* Failed to activate the CPU monitor */
		return (ret);
	}
	
	if ((ret = proc_rlimit_control(pid, RLIMIT_CPU_USAGE_MONITOR, (void *)(uintptr_t)CPUMON_MAKE_FATAL)) != 0) {
		/* Failed to set termination, back out the CPU monitor settings. */
		(void)proc_disable_cpumon(pid);
	}

	return (ret);
}