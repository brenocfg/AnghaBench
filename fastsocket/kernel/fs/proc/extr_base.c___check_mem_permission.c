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
struct task_struct {int dummy; } ;
struct mm_struct {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  EPERM ; 
 struct mm_struct* ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PTRACE_MODE_ATTACH ; 
 struct task_struct* current ; 
 struct mm_struct* get_task_mm (struct task_struct*) ; 
 int /*<<< orphan*/  mmput (struct mm_struct*) ; 
 scalar_t__ ptrace_may_access (struct task_struct*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 scalar_t__ task_is_stopped_or_traced (struct task_struct*) ; 
 struct task_struct* tracehook_tracer_task (struct task_struct*) ; 

__attribute__((used)) static struct mm_struct *__check_mem_permission(struct task_struct *task)
{
	struct mm_struct *mm;

	mm = get_task_mm(task);
	if (!mm)
		return ERR_PTR(-EINVAL);

	/*
	 * A task can always look at itself, in case it chooses
	 * to use system calls instead of load instructions.
	 */
	if (task == current)
		return mm;

	/*
	 * If current is actively ptrace'ing, and would also be
	 * permitted to freshly attach with ptrace now, permit it.
	 */
	if (task_is_stopped_or_traced(task)) {
		int match;
		rcu_read_lock();
		match = (tracehook_tracer_task(task) == current);
		rcu_read_unlock();
		if (match && ptrace_may_access(task, PTRACE_MODE_ATTACH))
			return mm;
	}

	/*
	 * Noone else is allowed.
	 */
	mmput(mm);
	return ERR_PTR(-EPERM);
}