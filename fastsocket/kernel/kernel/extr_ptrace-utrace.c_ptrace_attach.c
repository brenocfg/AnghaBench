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
struct task_struct {int flags; int exit_state; int /*<<< orphan*/  cred_guard_mutex; int /*<<< orphan*/  ptrace; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CAP_SYS_PTRACE ; 
 int EPERM ; 
 int ERESTARTNOINTR ; 
 int PF_KTHREAD ; 
 int /*<<< orphan*/  PTRACE_MODE_ATTACH ; 
 int /*<<< orphan*/  PT_PTRACE_CAP ; 
 int /*<<< orphan*/  PT_UTRACED ; 
 int /*<<< orphan*/  SEND_SIG_FORCED ; 
 int /*<<< orphan*/  SIGSTOP ; 
 int /*<<< orphan*/  __ptrace_link (struct task_struct*,int /*<<< orphan*/ ) ; 
 int __ptrace_may_access (struct task_struct*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  audit_ptrace (struct task_struct*) ; 
 scalar_t__ capable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  current ; 
 scalar_t__ mutex_lock_interruptible (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int ptrace_attach_task (struct task_struct*,int /*<<< orphan*/ ) ; 
 scalar_t__ same_thread_group (struct task_struct*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  send_sig_info (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct task_struct*) ; 
 int /*<<< orphan*/  task_lock (struct task_struct*) ; 
 int /*<<< orphan*/  task_unlock (struct task_struct*) ; 
 int /*<<< orphan*/  tasklist_lock ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  write_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_unlock_irq (int /*<<< orphan*/ *) ; 

int ptrace_attach(struct task_struct *task)
{
	int retval;

	audit_ptrace(task);

	retval = -EPERM;
	if (unlikely(task->flags & PF_KTHREAD))
		goto out;
	if (same_thread_group(task, current))
		goto out;

	/*
	 * Protect exec's credential calculations against our interference;
	 * interference; SUID, SGID and LSM creds get determined differently
	 * under ptrace.
	 */
	retval = -ERESTARTNOINTR;
	if (mutex_lock_interruptible(&task->cred_guard_mutex))
		goto out;

	task_lock(task);
	retval = __ptrace_may_access(task, PTRACE_MODE_ATTACH);
	task_unlock(task);
	if (retval)
		goto unlock_creds;

	retval = ptrace_attach_task(task, 0);
	if (unlikely(retval))
		goto unlock_creds;

	write_lock_irq(&tasklist_lock);
	retval = -EPERM;
	if (unlikely(task->exit_state))
		goto unlock_tasklist;

	BUG_ON(task->ptrace);
	task->ptrace = PT_UTRACED;
	if (capable(CAP_SYS_PTRACE))
		task->ptrace |= PT_PTRACE_CAP;

	__ptrace_link(task, current);
	send_sig_info(SIGSTOP, SEND_SIG_FORCED, task);

	retval = 0;
unlock_tasklist:
	write_unlock_irq(&tasklist_lock);
unlock_creds:
	mutex_unlock(&task->cred_guard_mutex);
out:
	return retval;
}