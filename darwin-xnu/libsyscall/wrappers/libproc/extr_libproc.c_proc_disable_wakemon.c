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
struct proc_rlimit_control_wakeupmon {int wm_rate; int /*<<< orphan*/  wm_flags; } ;
typedef  int /*<<< orphan*/  pid_t ;

/* Variables and functions */
 int /*<<< orphan*/  RLIMIT_WAKEUPS_MONITOR ; 
 int /*<<< orphan*/  WAKEMON_DISABLE ; 
 int proc_rlimit_control (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct proc_rlimit_control_wakeupmon*) ; 

int
proc_disable_wakemon(pid_t pid)
{
	struct proc_rlimit_control_wakeupmon params;

	params.wm_flags = WAKEMON_DISABLE;
	params.wm_rate = -1;

	return (proc_rlimit_control(pid, RLIMIT_WAKEUPS_MONITOR, &params));
}