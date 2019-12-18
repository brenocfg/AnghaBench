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
struct task_struct {unsigned int exit_code; int /*<<< orphan*/  exit_state; scalar_t__ ptrace; } ;

/* Variables and functions */
 int EIO ; 
 int /*<<< orphan*/  TIF_SYSCALL_TRACE ; 
 int __ptrace_detach (int /*<<< orphan*/ ,struct task_struct*) ; 
 int /*<<< orphan*/  clear_tsk_thread_flag (struct task_struct*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  current ; 
 int /*<<< orphan*/  ptrace_disable (struct task_struct*) ; 
 int /*<<< orphan*/  release_task (struct task_struct*) ; 
 int /*<<< orphan*/  tasklist_lock ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  valid_signal (unsigned int) ; 
 int /*<<< orphan*/  wake_up_process (struct task_struct*) ; 
 int /*<<< orphan*/  write_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_unlock_irq (int /*<<< orphan*/ *) ; 

int ptrace_detach(struct task_struct *child, unsigned int data)
{
	bool dead = false;

	if (!valid_signal(data))
		return -EIO;

	/* Architecture-specific hardware disable .. */
	ptrace_disable(child);
	clear_tsk_thread_flag(child, TIF_SYSCALL_TRACE);

	write_lock_irq(&tasklist_lock);
	/*
	 * This child can be already killed. Make sure de_thread() or
	 * our sub-thread doing do_wait() didn't do release_task() yet.
	 */
	if (child->ptrace) {
		child->exit_code = data;
		dead = __ptrace_detach(current, child);
		if (!child->exit_state)
			wake_up_process(child);
	}
	write_unlock_irq(&tasklist_lock);

	if (unlikely(dead))
		release_task(child);

	return 0;
}