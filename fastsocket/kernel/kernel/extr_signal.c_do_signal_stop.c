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
struct task_struct {int flags; int exit_code; TYPE_1__* sighand; struct signal_struct* signal; } ;
struct signal_struct {int group_stop_count; int flags; int group_exit_code; } ;
struct TYPE_2__ {int /*<<< orphan*/  siglock; } ;

/* Variables and functions */
 int CLD_STOPPED ; 
 int PF_EXITING ; 
 int SIGNAL_STOP_DEQUEUED ; 
 int SIGNAL_STOP_STOPPED ; 
 int /*<<< orphan*/  TASK_STOPPED ; 
 int /*<<< orphan*/  __set_current_state (int /*<<< orphan*/ ) ; 
 struct task_struct* current ; 
 int /*<<< orphan*/  do_notify_parent_cldstop (struct task_struct*,int) ; 
 int /*<<< orphan*/  likely (int) ; 
 struct task_struct* next_thread (struct task_struct*) ; 
 int /*<<< orphan*/  read_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  read_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  schedule () ; 
 int /*<<< orphan*/  signal_group_exit (struct signal_struct*) ; 
 int /*<<< orphan*/  signal_wake_up (struct task_struct*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  task_is_stopped_or_traced (struct task_struct*) ; 
 int /*<<< orphan*/  tasklist_lock ; 
 int /*<<< orphan*/  tracehook_finish_jctl () ; 
 int tracehook_notify_jctl (int,int) ; 
 scalar_t__ try_to_freeze () ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int do_signal_stop(int signr)
{
	struct signal_struct *sig = current->signal;
	int notify;

	if (!sig->group_stop_count) {
		struct task_struct *t;

		if (!likely(sig->flags & SIGNAL_STOP_DEQUEUED) ||
		    unlikely(signal_group_exit(sig)))
			return 0;
		/*
		 * There is no group stop already in progress.
		 * We must initiate one now.
		 */
		sig->group_exit_code = signr;

		sig->group_stop_count = 1;
		for (t = next_thread(current); t != current; t = next_thread(t))
			/*
			 * Setting state to TASK_STOPPED for a group
			 * stop is always done with the siglock held,
			 * so this check has no races.
			 */
			if (!(t->flags & PF_EXITING) &&
			    !task_is_stopped_or_traced(t)) {
				sig->group_stop_count++;
				signal_wake_up(t, 0);
			}
	}
	/*
	 * If there are no other threads in the group, or if there is
	 * a group stop in progress and we are the last to stop, report
	 * to the parent.  When ptraced, every thread reports itself.
	 */
	notify = sig->group_stop_count == 1 ? CLD_STOPPED : 0;
	notify = tracehook_notify_jctl(notify, CLD_STOPPED);
	/*
	 * tracehook_notify_jctl() can drop and reacquire siglock, so
	 * we keep ->group_stop_count != 0 before the call. If SIGCONT
	 * or SIGKILL comes in between ->group_stop_count == 0.
	 */
	if (sig->group_stop_count) {
		if (!--sig->group_stop_count)
			sig->flags = SIGNAL_STOP_STOPPED;
		current->exit_code = sig->group_exit_code;
		__set_current_state(TASK_STOPPED);
	}
	spin_unlock_irq(&current->sighand->siglock);

	if (notify) {
		read_lock(&tasklist_lock);
		do_notify_parent_cldstop(current, notify);
		read_unlock(&tasklist_lock);
	}

	/* Now we don't run again until woken by SIGCONT or SIGKILL */
	do {
		schedule();
	} while (try_to_freeze());

	tracehook_finish_jctl();
	current->exit_code = 0;

	return 1;
}