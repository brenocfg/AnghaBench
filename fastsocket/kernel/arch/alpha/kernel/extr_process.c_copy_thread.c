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
struct TYPE_2__ {unsigned long usp; unsigned long ksp; int flags; unsigned long unique; } ;
struct thread_info {TYPE_1__ pcb; } ;
struct task_struct {int dummy; } ;
struct switch_stack {unsigned long r26; } ;
struct pt_regs {int ps; unsigned long r20; scalar_t__ r19; scalar_t__ r0; } ;

/* Variables and functions */
 unsigned long CLONE_SETTLS ; 
 int PAGE_SIZE ; 
 scalar_t__ task_stack_page (struct task_struct*) ; 
 struct thread_info* task_thread_info (struct task_struct*) ; 

int
copy_thread(unsigned long clone_flags, unsigned long usp,
	    unsigned long unused,
	    struct task_struct * p, struct pt_regs * regs)
{
	extern void ret_from_fork(void);

	struct thread_info *childti = task_thread_info(p);
	struct pt_regs * childregs;
	struct switch_stack * childstack, *stack;
	unsigned long stack_offset, settls;

	stack_offset = PAGE_SIZE - sizeof(struct pt_regs);
	if (!(regs->ps & 8))
		stack_offset = (PAGE_SIZE-1) & (unsigned long) regs;
	childregs = (struct pt_regs *)
	  (stack_offset + PAGE_SIZE + task_stack_page(p));
		
	*childregs = *regs;
	settls = regs->r20;
	childregs->r0 = 0;
	childregs->r19 = 0;
	childregs->r20 = 1;	/* OSF/1 has some strange fork() semantics.  */
	regs->r20 = 0;
	stack = ((struct switch_stack *) regs) - 1;
	childstack = ((struct switch_stack *) childregs) - 1;
	*childstack = *stack;
	childstack->r26 = (unsigned long) ret_from_fork;
	childti->pcb.usp = usp;
	childti->pcb.ksp = (unsigned long) childstack;
	childti->pcb.flags = 1;	/* set FEN, clear everything else */

	/* Set a new TLS for the child thread?  Peek back into the
	   syscall arguments that we saved on syscall entry.  Oops,
	   except we'd have clobbered it with the parent/child set
	   of r20.  Read the saved copy.  */
	/* Note: if CLONE_SETTLS is not set, then we must inherit the
	   value from the parent, which will have been set by the block
	   copy in dup_task_struct.  This is non-intuitive, but is
	   required for proper operation in the case of a threaded
	   application calling fork.  */
	if (clone_flags & CLONE_SETTLS)
		childti->pcb.unique = settls;

	return 0;
}