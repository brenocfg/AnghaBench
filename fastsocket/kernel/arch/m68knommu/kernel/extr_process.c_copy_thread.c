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
struct TYPE_3__ {unsigned long usp; unsigned long ksp; scalar_t__* fpstate; int /*<<< orphan*/  fs; } ;
struct task_struct {TYPE_1__ thread; } ;
struct switch_stack {unsigned long retpc; } ;
struct pt_regs {scalar_t__ d0; } ;
struct TYPE_4__ {int /*<<< orphan*/  seg; } ;

/* Variables and functions */
 int /*<<< orphan*/  FPU_IS_EMU ; 
 scalar_t__ THREAD_SIZE ; 
 TYPE_2__ get_fs () ; 
 scalar_t__ ret_from_fork ; 
 scalar_t__ task_stack_page (struct task_struct*) ; 

int copy_thread(unsigned long clone_flags,
		unsigned long usp, unsigned long topstk,
		struct task_struct * p, struct pt_regs * regs)
{
	struct pt_regs * childregs;
	struct switch_stack * childstack, *stack;
	unsigned long *retp;

	childregs = (struct pt_regs *) (task_stack_page(p) + THREAD_SIZE) - 1;

	*childregs = *regs;
	childregs->d0 = 0;

	retp = ((unsigned long *) regs);
	stack = ((struct switch_stack *) retp) - 1;

	childstack = ((struct switch_stack *) childregs) - 1;
	*childstack = *stack;
	childstack->retpc = (unsigned long)ret_from_fork;

	p->thread.usp = usp;
	p->thread.ksp = (unsigned long)childstack;
	/*
	 * Must save the current SFC/DFC value, NOT the value when
	 * the parent was last descheduled - RGH  10-08-96
	 */
	p->thread.fs = get_fs().seg;

#ifdef CONFIG_FPU
	if (!FPU_IS_EMU) {
		/* Copy the current fpu state */
		asm volatile ("fsave %0" : : "m" (p->thread.fpstate[0]) : "memory");

		if (p->thread.fpstate[0])
		  asm volatile ("fmovemx %/fp0-%/fp7,%0\n\t"
				"fmoveml %/fpiar/%/fpcr/%/fpsr,%1"
				: : "m" (p->thread.fp[0]), "m" (p->thread.fpcntl[0])
				: "memory");
		/* Restore the state in case the fpu was busy */
		asm volatile ("frestore %0" : : "m" (p->thread.fpstate[0]));
	}
#endif

	return 0;
}