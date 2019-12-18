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
struct task_struct {unsigned long nvcsw; unsigned long nivcsw; int flags; unsigned long last_switch_count; int /*<<< orphan*/  pid; int /*<<< orphan*/  comm; } ;
struct TYPE_2__ {int /*<<< orphan*/  version; int /*<<< orphan*/  release; } ;

/* Variables and functions */
 int PF_FROZEN ; 
 int /*<<< orphan*/  __debug_show_held_locks (struct task_struct*) ; 
 TYPE_1__* init_utsname () ; 
 int /*<<< orphan*/  panic (char*) ; 
 int /*<<< orphan*/  pr_err (char*,...) ; 
 int /*<<< orphan*/  print_tainted () ; 
 int /*<<< orphan*/  sched_show_task (struct task_struct*) ; 
 scalar_t__ strcspn (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ sysctl_hung_task_panic ; 
 int /*<<< orphan*/  sysctl_hung_task_warnings ; 
 int /*<<< orphan*/  touch_nmi_watchdog () ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static void check_hung_task(struct task_struct *t, unsigned long timeout)
{
	unsigned long switch_count = t->nvcsw + t->nivcsw;

	/*
	 * Ensure the task is not frozen.
	 * Also, when a freshly created task is scheduled once, changes
	 * its state to TASK_UNINTERRUPTIBLE without having ever been
	 * switched out once, it musn't be checked.
	 */
	if (unlikely(t->flags & PF_FROZEN || !switch_count))
		return;

	if (switch_count != t->last_switch_count) {
		t->last_switch_count = switch_count;
		return;
	}
	if (!sysctl_hung_task_warnings)
		return;
	sysctl_hung_task_warnings--;

	/*
	 * Ok, the task did not get scheduled for more than 2 minutes,
	 * complain:
	 */
	pr_err("INFO: task %s:%d blocked for more than %ld seconds.\n",
		t->comm, t->pid, timeout);
	pr_err("      %s %s %.*s\n",
		print_tainted(), init_utsname()->release,
		(int)strcspn(init_utsname()->version, " "),
		init_utsname()->version);
	pr_err("\"echo 0 > /proc/sys/kernel/hung_task_timeout_secs\""
		" disables this message.\n");
	sched_show_task(t);
	__debug_show_held_locks(t);

	touch_nmi_watchdog();

	if (sysctl_hung_task_panic)
		panic("hung_task: blocked tasks");
}