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
struct task_struct {int exit_code; } ;
struct ptrace_context {int stop_code; } ;

/* Variables and functions */
 int /*<<< orphan*/  CLD_TRAPPED ; 
 int PTRACE_EVENT_MASK ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  do_notify_parent_cldstop (struct task_struct*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  preempt_disable () ; 
 int /*<<< orphan*/  preempt_enable_no_resched () ; 
 int /*<<< orphan*/  read_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  read_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ task_ptrace (struct task_struct*) ; 
 int /*<<< orphan*/  tasklist_lock ; 

__attribute__((used)) static void do_ptrace_notify_stop(struct ptrace_context *ctx,
					struct task_struct *tracee)
{
	/*
	 * This can race with SIGKILL, but we borrow this race from
	 * the old ptrace implementation. ->exit_code is only needed
	 * for wait_task_stopped()->task_stopped_code(), we should
	 * change it to use ptrace_context.
	 */
	tracee->exit_code = ctx->stop_code & PTRACE_EVENT_MASK;
	WARN_ON(!tracee->exit_code);

	read_lock(&tasklist_lock);
	/*
	 * Don't want to allow preemption here, because
	 * sys_ptrace() needs this task to be inactive.
	 */
	preempt_disable();
	/*
	 * It can be killed and then released by our subthread,
	 * or ptrace_attach() has not completed yet.
	 */
	if (task_ptrace(tracee))
		do_notify_parent_cldstop(tracee, CLD_TRAPPED);
	read_unlock(&tasklist_lock);
	preempt_enable_no_resched();
}