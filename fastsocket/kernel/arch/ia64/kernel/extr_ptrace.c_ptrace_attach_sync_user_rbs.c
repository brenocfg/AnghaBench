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
struct unw_frame_info {int dummy; } ;
struct task_struct {scalar_t__ state; TYPE_2__* sighand; TYPE_1__* signal; } ;
struct TYPE_4__ {int /*<<< orphan*/  siglock; } ;
struct TYPE_3__ {int flags; } ;

/* Variables and functions */
 int SIGNAL_STOP_STOPPED ; 
 scalar_t__ TASK_STOPPED ; 
 scalar_t__ TASK_TRACED ; 
 int /*<<< orphan*/  TIF_RESTORE_RSE ; 
 int /*<<< orphan*/  do_sync_rbs (struct unw_frame_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ia64_sync_user_rbs ; 
 int /*<<< orphan*/  read_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  read_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_notify_resume (struct task_struct*) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tasklist_lock ; 
 int /*<<< orphan*/  test_and_set_tsk_thread_flag (struct task_struct*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  unw_init_from_blocked_task (struct unw_frame_info*,struct task_struct*) ; 

void
ptrace_attach_sync_user_rbs (struct task_struct *child)
{
	int stopped = 0;
	struct unw_frame_info info;

	/*
	 * If the child is in TASK_STOPPED, we need to change that to
	 * TASK_TRACED momentarily while we operate on it.  This ensures
	 * that the child won't be woken up and return to user mode while
	 * we are doing the sync.  (It can only be woken up for SIGKILL.)
	 */

	read_lock(&tasklist_lock);
	if (child->signal) {
		spin_lock_irq(&child->sighand->siglock);
		if (child->state == TASK_STOPPED &&
		    !test_and_set_tsk_thread_flag(child, TIF_RESTORE_RSE)) {
			set_notify_resume(child);

			child->state = TASK_TRACED;
			stopped = 1;
		}
		spin_unlock_irq(&child->sighand->siglock);
	}
	read_unlock(&tasklist_lock);

	if (!stopped)
		return;

	unw_init_from_blocked_task(&info, child);
	do_sync_rbs(&info, ia64_sync_user_rbs);

	/*
	 * Now move the child back into TASK_STOPPED if it should be in a
	 * job control stop, so that SIGCONT can be used to wake it up.
	 */
	read_lock(&tasklist_lock);
	if (child->signal) {
		spin_lock_irq(&child->sighand->siglock);
		if (child->state == TASK_TRACED &&
		    (child->signal->flags & SIGNAL_STOP_STOPPED)) {
			child->state = TASK_STOPPED;
		}
		spin_unlock_irq(&child->sighand->siglock);
	}
	read_unlock(&tasklist_lock);
}