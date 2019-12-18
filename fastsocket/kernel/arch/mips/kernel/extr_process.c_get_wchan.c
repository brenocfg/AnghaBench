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
struct TYPE_3__ {unsigned long reg29; } ;
struct task_struct {scalar_t__ state; TYPE_1__ thread; } ;
struct TYPE_4__ {unsigned long frame_size; } ;

/* Variables and functions */
 scalar_t__ TASK_RUNNING ; 
 struct task_struct* current ; 
 scalar_t__ in_sched_functions (unsigned long) ; 
 TYPE_2__ schedule_mfi ; 
 int /*<<< orphan*/  task_stack_page (struct task_struct*) ; 
 unsigned long thread_saved_pc (struct task_struct*) ; 
 unsigned long unwind_stack (struct task_struct*,unsigned long*,unsigned long,unsigned long*) ; 

unsigned long get_wchan(struct task_struct *task)
{
	unsigned long pc = 0;
#ifdef CONFIG_KALLSYMS
	unsigned long sp;
	unsigned long ra = 0;
#endif

	if (!task || task == current || task->state == TASK_RUNNING)
		goto out;
	if (!task_stack_page(task))
		goto out;

	pc = thread_saved_pc(task);

#ifdef CONFIG_KALLSYMS
	sp = task->thread.reg29 + schedule_mfi.frame_size;

	while (in_sched_functions(pc))
		pc = unwind_stack(task, &sp, pc, &ra);
#endif

out:
	return pc;
}