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
 int /*<<< orphan*/  check_hung_uninterruptible_tasks (unsigned long) ; 
 int /*<<< orphan*/  current ; 
 scalar_t__ schedule_timeout_interruptible (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_user_nice (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 unsigned long sysctl_hung_task_timeout_secs ; 
 int /*<<< orphan*/  timeout_jiffies (unsigned long) ; 

__attribute__((used)) static int watchdog(void *dummy)
{
	set_user_nice(current, 0);

	for ( ; ; ) {
		unsigned long timeout = sysctl_hung_task_timeout_secs;

		while (schedule_timeout_interruptible(timeout_jiffies(timeout)))
			timeout = sysctl_hung_task_timeout_secs;

		check_hung_uninterruptible_tasks(timeout);
	}

	return 0;
}