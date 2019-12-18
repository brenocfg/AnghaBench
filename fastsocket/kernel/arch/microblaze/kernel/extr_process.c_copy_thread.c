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
struct cpu_context {unsigned long r1; unsigned long msr; unsigned long r15; } ;
struct thread_info {struct cpu_context cpu_context; } ;
struct task_struct {int dummy; } ;
struct pt_regs {unsigned long r1; int msr; unsigned long CURRENT_TASK; } ;

/* Variables and functions */
 unsigned long CLONE_SETTLS ; 
 int MSR_BIP ; 
 int MSR_EE ; 
 int MSR_EIP ; 
 int MSR_IE ; 
 int MSR_UMS ; 
 int MSR_VM ; 
 int MSR_VMS ; 
 unsigned long STATE_SAVE_ARG_SPACE ; 
 unsigned long THREAD_SIZE ; 
 scalar_t__ kernel_mode (struct pt_regs*) ; 
 int /*<<< orphan*/  memset (struct cpu_context*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ ret_from_fork ; 
 struct pt_regs* task_pt_regs (struct task_struct*) ; 
 struct thread_info* task_thread_info (struct task_struct*) ; 
 scalar_t__ user_mode (struct pt_regs*) ; 

int copy_thread(unsigned long clone_flags, unsigned long usp,
		unsigned long unused,
		struct task_struct *p, struct pt_regs *regs)
{
	struct pt_regs *childregs = task_pt_regs(p);
	struct thread_info *ti = task_thread_info(p);

	*childregs = *regs;
	if (user_mode(regs))
		childregs->r1 = usp;
	else
		childregs->r1 = ((unsigned long) ti) + THREAD_SIZE;

#ifndef CONFIG_MMU
	memset(&ti->cpu_context, 0, sizeof(struct cpu_context));
	ti->cpu_context.r1 = (unsigned long)childregs;
	ti->cpu_context.msr = (unsigned long)childregs->msr;
#else

	/* if creating a kernel thread then update the current reg (we don't
	 * want to use the parent's value when restoring by POP_STATE) */
	if (kernel_mode(regs))
		/* save new current on stack to use POP_STATE */
		childregs->CURRENT_TASK = (unsigned long)p;
	/* if returning to user then use the parent's value of this register */

	/* if we're creating a new kernel thread then just zeroing all
	 * the registers. That's OK for a brand new thread.*/
	/* Pls. note that some of them will be restored in POP_STATE */
	if (kernel_mode(regs))
		memset(&ti->cpu_context, 0, sizeof(struct cpu_context));
	/* if this thread is created for fork/vfork/clone, then we want to
	 * restore all the parent's context */
	/* in addition to the registers which will be restored by POP_STATE */
	else {
		ti->cpu_context = *(struct cpu_context *)regs;
		childregs->msr |= MSR_UMS;
	}

	/* FIXME STATE_SAVE_PT_OFFSET; */
	ti->cpu_context.r1  = (unsigned long)childregs - STATE_SAVE_ARG_SPACE;
	/* we should consider the fact that childregs is a copy of the parent
	 * regs which were saved immediately after entering the kernel state
	 * before enabling VM. This MSR will be restored in switch_to and
	 * RETURN() and we want to have the right machine state there
	 * specifically this state must have INTs disabled before and enabled
	 * after performing rtbd
	 * compose the right MSR for RETURN(). It will work for switch_to also
	 * excepting for VM and UMS
	 * don't touch UMS , CARRY and cache bits
	 * right now MSR is a copy of parent one */
	childregs->msr |= MSR_BIP;
	childregs->msr &= ~MSR_EIP;
	childregs->msr |= MSR_IE;
	childregs->msr &= ~MSR_VM;
	childregs->msr |= MSR_VMS;
	childregs->msr |= MSR_EE; /* exceptions will be enabled*/

	ti->cpu_context.msr = (childregs->msr|MSR_VM);
	ti->cpu_context.msr &= ~MSR_UMS; /* switch_to to kernel mode */
#endif
	ti->cpu_context.r15 = (unsigned long)ret_from_fork - 8;

	if (clone_flags & CLONE_SETTLS)
		;

	return 0;
}