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
struct TYPE_4__ {int /*<<< orphan*/  hard; } ;
struct TYPE_3__ {TYPE_2__ fpu; } ;
struct task_struct {TYPE_1__ thread; } ;
struct pt_regs {int /*<<< orphan*/  sr; } ;

/* Variables and functions */
 int /*<<< orphan*/  SR_FD ; 
 int THREAD_SIZE ; 
 int /*<<< orphan*/  disable_fpu () ; 
 int /*<<< orphan*/  enable_fpu () ; 
 int /*<<< orphan*/  fpinit (int /*<<< orphan*/ *) ; 
 struct task_struct* last_task_used_math ; 
 int /*<<< orphan*/  save_fpu (struct task_struct*,struct pt_regs*) ; 
 int /*<<< orphan*/  set_stopped_child_used_math (struct task_struct*) ; 
 int /*<<< orphan*/  tsk_used_math (struct task_struct*) ; 

__attribute__((used)) static inline int
put_fpu_long(struct task_struct *task, unsigned long addr, unsigned long data)
{
	struct pt_regs *regs;

	regs = (struct pt_regs*)((unsigned char *)task + THREAD_SIZE) - 1;

	if (!tsk_used_math(task)) {
		fpinit(&task->thread.fpu.hard);
		set_stopped_child_used_math(task);
	} else if (last_task_used_math == task) {
		enable_fpu();
		save_fpu(task, regs);
		disable_fpu();
		last_task_used_math = 0;
		regs->sr |= SR_FD;
	}

	((long *)&task->thread.fpu)[addr / sizeof(unsigned long)] = data;
	return 0;
}