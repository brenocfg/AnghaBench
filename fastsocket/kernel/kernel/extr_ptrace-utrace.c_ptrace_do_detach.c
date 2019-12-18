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
struct task_struct {scalar_t__ ptrace; } ;

/* Variables and functions */
 int __ptrace_detach (int /*<<< orphan*/ ,struct task_struct*) ; 
 int /*<<< orphan*/  current ; 
 scalar_t__ likely (int) ; 
 int /*<<< orphan*/  ptrace_detach_task (struct task_struct*,unsigned int) ; 
 int /*<<< orphan*/  release_task (struct task_struct*) ; 
 int /*<<< orphan*/  tasklist_lock ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  write_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_unlock_irq (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void ptrace_do_detach(struct task_struct *tracee, unsigned int data)
{
	bool detach, release;

	write_lock_irq(&tasklist_lock);
	/*
	 * This tracee can be already killed. Make sure de_thread() or
	 * our sub-thread doing do_wait() didn't do release_task() yet.
	 */
	detach = tracee->ptrace != 0;
	release = false;
	if (likely(detach))
		release = __ptrace_detach(current, tracee);
	write_unlock_irq(&tasklist_lock);

	if (unlikely(release))
		release_task(tracee);
	else if (likely(detach))
		ptrace_detach_task(tracee, data);
}