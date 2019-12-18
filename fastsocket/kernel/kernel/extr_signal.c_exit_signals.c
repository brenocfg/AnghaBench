#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct task_struct {int flags; TYPE_1__* sighand; TYPE_2__* signal; } ;
struct TYPE_4__ {int group_stop_count; int /*<<< orphan*/  flags; } ;
struct TYPE_3__ {int /*<<< orphan*/  siglock; } ;

/* Variables and functions */
 int /*<<< orphan*/  CLD_STOPPED ; 
 int PF_EXITING ; 
 int /*<<< orphan*/  SIGNAL_STOP_STOPPED ; 
 int /*<<< orphan*/  do_notify_parent_cldstop (struct task_struct*,int) ; 
 struct task_struct* next_thread (struct task_struct*) ; 
 int /*<<< orphan*/  read_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  read_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  recalc_sigpending_and_wake (struct task_struct*) ; 
 scalar_t__ signal_group_exit (TYPE_2__*) ; 
 int /*<<< orphan*/  signal_pending (struct task_struct*) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tasklist_lock ; 
 scalar_t__ thread_group_empty (struct task_struct*) ; 
 int tracehook_notify_jctl (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int) ; 

void exit_signals(struct task_struct *tsk)
{
	int group_stop = 0;
	struct task_struct *t;

	if (thread_group_empty(tsk) || signal_group_exit(tsk->signal)) {
		tsk->flags |= PF_EXITING;
		return;
	}

	spin_lock_irq(&tsk->sighand->siglock);
	/*
	 * From now this task is not visible for group-wide signals,
	 * see wants_signal(), do_signal_stop().
	 */
	tsk->flags |= PF_EXITING;
	if (!signal_pending(tsk))
		goto out;

	/* It could be that __group_complete_signal() choose us to
	 * notify about group-wide signal. Another thread should be
	 * woken now to take the signal since we will not.
	 */
	for (t = tsk; (t = next_thread(t)) != tsk; )
		if (!signal_pending(t) && !(t->flags & PF_EXITING))
			recalc_sigpending_and_wake(t);

	if (unlikely(tsk->signal->group_stop_count) &&
			!--tsk->signal->group_stop_count) {
		tsk->signal->flags = SIGNAL_STOP_STOPPED;
		group_stop = tracehook_notify_jctl(CLD_STOPPED, CLD_STOPPED);
	}
out:
	spin_unlock_irq(&tsk->sighand->siglock);

	if (unlikely(group_stop)) {
		read_lock(&tasklist_lock);
		do_notify_parent_cldstop(tsk, group_stop);
		read_unlock(&tasklist_lock);
	}
}