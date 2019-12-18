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
struct proc_rlimit_control_wakeupmon {int wm_flags; int wm_rate; } ;
typedef  int /*<<< orphan*/  pid_t ;

/* Variables and functions */
 int /*<<< orphan*/  RLIMIT_WAKEUPS_MONITOR ; 
 int WAKEMON_GET_PARAMS ; 
 int proc_rlimit_control (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct proc_rlimit_control_wakeupmon*) ; 

int
proc_get_wakemon_params(pid_t pid, int *rate_hz, int *flags)
{
	struct proc_rlimit_control_wakeupmon params;
	int error;

	params.wm_flags = WAKEMON_GET_PARAMS;

	if ((error = proc_rlimit_control(pid, RLIMIT_WAKEUPS_MONITOR, &params)) != 0) {
		return (error);
	}

	*rate_hz = params.wm_rate;
	*flags = params.wm_flags;

	return (0);
}