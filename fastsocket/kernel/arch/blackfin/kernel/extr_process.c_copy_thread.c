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
struct TYPE_2__ {unsigned long usp; unsigned long ksp; unsigned long pc; } ;
struct task_struct {TYPE_1__ thread; } ;
struct pt_regs {scalar_t__ r0; } ;

/* Variables and functions */
 scalar_t__ THREAD_SIZE ; 
 scalar_t__ ret_from_fork ; 
 scalar_t__ task_stack_page (struct task_struct*) ; 

int
copy_thread(unsigned long clone_flags,
	    unsigned long usp, unsigned long topstk,
	    struct task_struct *p, struct pt_regs *regs)
{
	struct pt_regs *childregs;

	childregs = (struct pt_regs *) (task_stack_page(p) + THREAD_SIZE) - 1;
	*childregs = *regs;
	childregs->r0 = 0;

	p->thread.usp = usp;
	p->thread.ksp = (unsigned long)childregs;
	p->thread.pc = (unsigned long)ret_from_fork;

	return 0;
}