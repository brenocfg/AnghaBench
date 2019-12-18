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
struct TYPE_2__ {unsigned long usp; unsigned long ksp; } ;
struct task_struct {TYPE_1__ thread; int /*<<< orphan*/ * clear_child_tid; int /*<<< orphan*/  set_child_tid; } ;
struct switch_stack {unsigned long return_ip; scalar_t__ r9; } ;
struct pt_regs {scalar_t__ r10; } ;

/* Variables and functions */
 int /*<<< orphan*/  printk (char*,struct pt_regs*) ; 
 scalar_t__ ret_from_fork ; 
 int /*<<< orphan*/  show_registers (struct pt_regs*) ; 
 struct pt_regs* task_pt_regs (struct task_struct*) ; 

int copy_thread(unsigned long clone_flags, unsigned long usp,
		unsigned long unused,
		struct task_struct *p, struct pt_regs *regs)
{
	struct pt_regs * childregs;
	struct switch_stack *swstack;
	
	/* put the pt_regs structure at the end of the new kernel stack page and fix it up
	 * remember that the task_struct doubles as the kernel stack for the task
	 */

	childregs = task_pt_regs(p);
        
	*childregs = *regs;  /* struct copy of pt_regs */
        
        p->set_child_tid = p->clear_child_tid = NULL;

        childregs->r10 = 0;  /* child returns 0 after a fork/clone */
	
	/* put the switch stack right below the pt_regs */

	swstack = ((struct switch_stack *)childregs) - 1;

	swstack->r9 = 0; /* parameter to ret_from_sys_call, 0 == dont restart the syscall */

	/* we want to return into ret_from_sys_call after the _resume */

	swstack->return_ip = (unsigned long) ret_from_fork; /* Will call ret_from_sys_call */
	
	/* fix the user-mode stackpointer */

	p->thread.usp = usp;	

	/* and the kernel-mode one */

	p->thread.ksp = (unsigned long) swstack;

#ifdef DEBUG
	printk("copy_thread: new regs at 0x%p, as shown below:\n", childregs);
	show_registers(childregs);
#endif

	return 0;
}