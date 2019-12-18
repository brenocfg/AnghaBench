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
struct TYPE_3__ {int sr; unsigned long ksp; unsigned long pc; } ;
struct TYPE_4__ {TYPE_1__ cpu_context; } ;
struct task_struct {TYPE_2__ thread; } ;
struct pt_regs {unsigned long sp; scalar_t__ r12; } ;

/* Variables and functions */
 unsigned long CLONE_PTRACE ; 
 int MODE_SUPERVISOR ; 
 int SR_GM ; 
 unsigned long THREAD_SIZE ; 
 int /*<<< orphan*/  TIF_DEBUG ; 
 int /*<<< orphan*/  clear_tsk_thread_flag (struct task_struct*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ocd_enable (struct task_struct*) ; 
 scalar_t__ ret_from_fork ; 
 scalar_t__ task_stack_page (struct task_struct*) ; 
 scalar_t__ test_thread_flag (int /*<<< orphan*/ ) ; 
 scalar_t__ user_mode (struct pt_regs*) ; 

int copy_thread(unsigned long clone_flags, unsigned long usp,
		unsigned long unused,
		struct task_struct *p, struct pt_regs *regs)
{
	struct pt_regs *childregs;

	childregs = ((struct pt_regs *)(THREAD_SIZE + (unsigned long)task_stack_page(p))) - 1;
	*childregs = *regs;

	if (user_mode(regs))
		childregs->sp = usp;
	else
		childregs->sp = (unsigned long)task_stack_page(p) + THREAD_SIZE;

	childregs->r12 = 0; /* Set return value for child */

	p->thread.cpu_context.sr = MODE_SUPERVISOR | SR_GM;
	p->thread.cpu_context.ksp = (unsigned long)childregs;
	p->thread.cpu_context.pc = (unsigned long)ret_from_fork;

	clear_tsk_thread_flag(p, TIF_DEBUG);
	if ((clone_flags & CLONE_PTRACE) && test_thread_flag(TIF_DEBUG))
		ocd_enable(p);

	return 0;
}