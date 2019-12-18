#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  siginfo_t ;
struct TYPE_9__ {int exit_code; int /*<<< orphan*/ * last_siginfo; TYPE_2__* sighand; TYPE_1__* signal; } ;
struct TYPE_8__ {int /*<<< orphan*/  siglock; } ;
struct TYPE_7__ {scalar_t__ group_stop_count; } ;

/* Variables and functions */
 int /*<<< orphan*/  CLD_TRAPPED ; 
 int /*<<< orphan*/  TASK_RUNNING ; 
 int /*<<< orphan*/  TASK_TRACED ; 
 int /*<<< orphan*/  __set_current_state (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  arch_ptrace_stop (int,int /*<<< orphan*/ *) ; 
 scalar_t__ arch_ptrace_stop_needed (int,int /*<<< orphan*/ *) ; 
 TYPE_3__* current ; 
 int /*<<< orphan*/  do_notify_parent_cldstop (TYPE_3__*,int /*<<< orphan*/ ) ; 
 scalar_t__ may_ptrace_stop () ; 
 int /*<<< orphan*/  preempt_disable () ; 
 int /*<<< orphan*/  preempt_enable_no_resched () ; 
 int /*<<< orphan*/  read_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  read_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  recalc_sigpending_tsk (TYPE_3__*) ; 
 int /*<<< orphan*/  schedule () ; 
 scalar_t__ sigkill_pending (TYPE_3__*) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tasklist_lock ; 
 int /*<<< orphan*/  try_to_freeze () ; 

__attribute__((used)) static void ptrace_stop(int exit_code, int clear_code, siginfo_t *info)
{
	if (arch_ptrace_stop_needed(exit_code, info)) {
		/*
		 * The arch code has something special to do before a
		 * ptrace stop.  This is allowed to block, e.g. for faults
		 * on user stack pages.  We can't keep the siglock while
		 * calling arch_ptrace_stop, so we must release it now.
		 * To preserve proper semantics, we must do this before
		 * any signal bookkeeping like checking group_stop_count.
		 * Meanwhile, a SIGKILL could come in before we retake the
		 * siglock.  That must prevent us from sleeping in TASK_TRACED.
		 * So after regaining the lock, we must check for SIGKILL.
		 */
		spin_unlock_irq(&current->sighand->siglock);
		arch_ptrace_stop(exit_code, info);
		spin_lock_irq(&current->sighand->siglock);
		if (sigkill_pending(current))
			return;
	}

	/*
	 * If there is a group stop in progress,
	 * we must participate in the bookkeeping.
	 */
	if (current->signal->group_stop_count > 0)
		--current->signal->group_stop_count;

	current->last_siginfo = info;
	current->exit_code = exit_code;

	/* Let the debugger run.  */
	__set_current_state(TASK_TRACED);
	spin_unlock_irq(&current->sighand->siglock);
	read_lock(&tasklist_lock);
	if (may_ptrace_stop()) {
		do_notify_parent_cldstop(current, CLD_TRAPPED);
		/*
		 * Don't want to allow preemption here, because
		 * sys_ptrace() needs this task to be inactive.
		 *
		 * XXX: implement read_unlock_no_resched().
		 */
		preempt_disable();
		read_unlock(&tasklist_lock);
		preempt_enable_no_resched();
		schedule();
	} else {
		/*
		 * By the time we got the lock, our tracer went away.
		 * Don't drop the lock yet, another tracer may come.
		 */
		__set_current_state(TASK_RUNNING);
		if (clear_code)
			current->exit_code = 0;
		read_unlock(&tasklist_lock);
	}

	/*
	 * While in TASK_TRACED, we were considered "frozen enough".
	 * Now that we woke up, it's crucial if we're supposed to be
	 * frozen that we freeze now before running anything substantial.
	 */
	try_to_freeze();

	/*
	 * We are back.  Now reacquire the siglock before touching
	 * last_siginfo, so that we are sure to have synchronized with
	 * any signal-sending on another CPU that wants to examine it.
	 */
	spin_lock_irq(&current->sighand->siglock);
	current->last_siginfo = NULL;

	/*
	 * Queued signals ignored us while we were stopped for tracing.
	 * So check for any that we should take before resuming user mode.
	 * This sets TIF_SIGPENDING, but never clears it.
	 */
	recalc_sigpending_tsk(current);
}