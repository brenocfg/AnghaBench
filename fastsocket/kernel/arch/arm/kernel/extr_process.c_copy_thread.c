#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {unsigned long sp; unsigned long pc; } ;
struct thread_info {int /*<<< orphan*/  tp_value; TYPE_1__ cpu_context; } ;
struct task_struct {int dummy; } ;
struct pt_regs {unsigned long ARM_sp; int /*<<< orphan*/  ARM_r3; scalar_t__ ARM_r0; } ;
struct cpu_context_save {int dummy; } ;

/* Variables and functions */
 unsigned long CLONE_SETTLS ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ ret_from_fork ; 
 struct pt_regs* task_pt_regs (struct task_struct*) ; 
 struct thread_info* task_thread_info (struct task_struct*) ; 

int
copy_thread(unsigned long clone_flags, unsigned long stack_start,
	    unsigned long stk_sz, struct task_struct *p, struct pt_regs *regs)
{
	struct thread_info *thread = task_thread_info(p);
	struct pt_regs *childregs = task_pt_regs(p);

	*childregs = *regs;
	childregs->ARM_r0 = 0;
	childregs->ARM_sp = stack_start;

	memset(&thread->cpu_context, 0, sizeof(struct cpu_context_save));
	thread->cpu_context.sp = (unsigned long)childregs;
	thread->cpu_context.pc = (unsigned long)ret_from_fork;

	if (clone_flags & CLONE_SETTLS)
		thread->tp_value = regs->ARM_r3;

	return 0;
}