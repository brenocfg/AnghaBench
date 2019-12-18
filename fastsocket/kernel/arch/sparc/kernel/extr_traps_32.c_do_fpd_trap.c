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
struct TYPE_2__ {int /*<<< orphan*/  fsr; int /*<<< orphan*/ * float_regs; int /*<<< orphan*/  fpqdepth; int /*<<< orphan*/ * fpqueue; } ;
struct task_struct {TYPE_1__ thread; } ;
struct pt_regs {int psr; } ;

/* Variables and functions */
 int PSR_EF ; 
 unsigned long PSR_PS ; 
 int /*<<< orphan*/  TIF_USEDFPU ; 
 struct task_struct* current ; 
 int /*<<< orphan*/  die_if_kernel (char*,struct pt_regs*) ; 
 int /*<<< orphan*/  fpload (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fpsave (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int get_psr () ; 
 int /*<<< orphan*/ * init_fregs ; 
 int /*<<< orphan*/  init_fsr ; 
 struct task_struct* last_task_used_math ; 
 int /*<<< orphan*/  put_psr (int) ; 
 int /*<<< orphan*/  set_thread_flag (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_used_math () ; 
 scalar_t__ used_math () ; 

void do_fpd_trap(struct pt_regs *regs, unsigned long pc, unsigned long npc,
		 unsigned long psr)
{
	/* Sanity check... */
	if(psr & PSR_PS)
		die_if_kernel("Kernel gets FloatingPenguinUnit disabled trap", regs);

	put_psr(get_psr() | PSR_EF);    /* Allow FPU ops. */
	regs->psr |= PSR_EF;
#ifndef CONFIG_SMP
	if(last_task_used_math == current)
		return;
	if(last_task_used_math) {
		/* Other processes fpu state, save away */
		struct task_struct *fptask = last_task_used_math;
		fpsave(&fptask->thread.float_regs[0], &fptask->thread.fsr,
		       &fptask->thread.fpqueue[0], &fptask->thread.fpqdepth);
	}
	last_task_used_math = current;
	if(used_math()) {
		fpload(&current->thread.float_regs[0], &current->thread.fsr);
	} else {
		/* Set initial sane state. */
		fpload(&init_fregs[0], &init_fsr);
		set_used_math();
	}
#else
	if(!used_math()) {
		fpload(&init_fregs[0], &init_fsr);
		set_used_math();
	} else {
		fpload(&current->thread.float_regs[0], &current->thread.fsr);
	}
	set_thread_flag(TIF_USEDFPU);
#endif
}