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
struct thread_info {unsigned long tp_value; int /*<<< orphan*/  addr_limit; } ;
struct TYPE_2__ {unsigned long reg29; unsigned long reg31; int cp0_status; } ;
struct task_struct {unsigned long pid; TYPE_1__ thread; int /*<<< orphan*/ * clear_child_tid; int /*<<< orphan*/  set_child_tid; } ;
struct pt_regs {unsigned long* regs; int cp0_status; int cp0_tcstatus; } ;

/* Variables and functions */
 unsigned long CLONE_SETTLS ; 
 int /*<<< orphan*/  KERNEL_DS ; 
 int ST0_CU0 ; 
 int ST0_CU1 ; 
 int ST0_CU2 ; 
 unsigned long THREAD_SIZE ; 
 int /*<<< orphan*/  TIF_FPUBOUND ; 
 int /*<<< orphan*/  TIF_USEDFPU ; 
 int /*<<< orphan*/  USER_DS ; 
 int /*<<< orphan*/  clear_tsk_thread_flag (struct task_struct*,int /*<<< orphan*/ ) ; 
 scalar_t__ cpu_has_dsp ; 
 scalar_t__ is_fpu_owner () ; 
 int /*<<< orphan*/  preempt_disable () ; 
 int /*<<< orphan*/  preempt_enable () ; 
 int read_c0_status () ; 
 scalar_t__ ret_from_fork ; 
 int /*<<< orphan*/  save_dsp (struct task_struct*) ; 
 int /*<<< orphan*/  save_fp (struct task_struct*) ; 
 scalar_t__ task_stack_page (struct task_struct*) ; 
 struct thread_info* task_thread_info (struct task_struct*) ; 

int copy_thread(unsigned long clone_flags, unsigned long usp,
	unsigned long unused, struct task_struct *p, struct pt_regs *regs)
{
	struct thread_info *ti = task_thread_info(p);
	struct pt_regs *childregs;
	unsigned long childksp;
	p->set_child_tid = p->clear_child_tid = NULL;

	childksp = (unsigned long)task_stack_page(p) + THREAD_SIZE - 32;

	preempt_disable();

	if (is_fpu_owner())
		save_fp(p);

	if (cpu_has_dsp)
		save_dsp(p);

	preempt_enable();

	/* set up new TSS. */
	childregs = (struct pt_regs *) childksp - 1;
	/*  Put the stack after the struct pt_regs.  */
	childksp = (unsigned long) childregs;
	*childregs = *regs;
	childregs->regs[7] = 0;	/* Clear error flag */

	childregs->regs[2] = 0;	/* Child gets zero as return value */
	regs->regs[2] = p->pid;

	if (childregs->cp0_status & ST0_CU0) {
		childregs->regs[28] = (unsigned long) ti;
		childregs->regs[29] = childksp;
		ti->addr_limit = KERNEL_DS;
	} else {
		childregs->regs[29] = usp;
		ti->addr_limit = USER_DS;
	}
	p->thread.reg29 = (unsigned long) childregs;
	p->thread.reg31 = (unsigned long) ret_from_fork;

	/*
	 * New tasks lose permission to use the fpu. This accelerates context
	 * switching for most programs since they don't use the fpu.
	 */
	p->thread.cp0_status = read_c0_status() & ~(ST0_CU2|ST0_CU1);
	childregs->cp0_status &= ~(ST0_CU2|ST0_CU1);

#ifdef CONFIG_MIPS_MT_SMTC
	/*
	 * SMTC restores TCStatus after Status, and the CU bits
	 * are aliased there.
	 */
	childregs->cp0_tcstatus &= ~(ST0_CU2|ST0_CU1);
#endif
	clear_tsk_thread_flag(p, TIF_USEDFPU);

#ifdef CONFIG_MIPS_MT_FPAFF
	clear_tsk_thread_flag(p, TIF_FPUBOUND);
#endif /* CONFIG_MIPS_MT_FPAFF */

	if (clone_flags & CLONE_SETTLS)
		ti->tp_value = regs->regs[7];

	return 0;
}