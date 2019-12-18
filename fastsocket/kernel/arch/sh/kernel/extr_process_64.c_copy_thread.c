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
struct TYPE_2__ {unsigned long sp; unsigned long pc; struct pt_regs* uregs; } ;
struct task_struct {TYPE_1__ thread; } ;
struct pt_regs {int /*<<< orphan*/  sr; void** regs; } ;

/* Variables and functions */
 int /*<<< orphan*/  SR_FD ; 
 unsigned long THREAD_SIZE ; 
 int /*<<< orphan*/ * current ; 
 int /*<<< orphan*/  disable_fpu () ; 
 int /*<<< orphan*/  enable_fpu () ; 
 int /*<<< orphan*/ * last_task_used_math ; 
 void* neff_sign_extend (unsigned long) ; 
 scalar_t__ ret_from_fork ; 
 int /*<<< orphan*/  save_fpu (int /*<<< orphan*/ *,struct pt_regs*) ; 
 scalar_t__ task_stack_page (struct task_struct*) ; 
 scalar_t__ user_mode (struct pt_regs*) ; 

int copy_thread(unsigned long clone_flags, unsigned long usp,
		unsigned long unused,
		struct task_struct *p, struct pt_regs *regs)
{
	struct pt_regs *childregs;

#ifdef CONFIG_SH_FPU
	if(last_task_used_math == current) {
		enable_fpu();
		save_fpu(current, regs);
		disable_fpu();
		last_task_used_math = NULL;
		regs->sr |= SR_FD;
	}
#endif
	/* Copy from sh version */
	childregs = (struct pt_regs *)(THREAD_SIZE + task_stack_page(p)) - 1;

	*childregs = *regs;

	/*
	 * Sign extend the edited stack.
	 * Note that thread.pc and thread.pc will stay
	 * 32-bit wide and context switch must take care
	 * of NEFF sign extension.
	 */
	if (user_mode(regs)) {
		childregs->regs[15] = neff_sign_extend(usp);
		p->thread.uregs = childregs;
	} else {
		childregs->regs[15] =
			neff_sign_extend((unsigned long)task_stack_page(p) +
					 THREAD_SIZE);
	}

	childregs->regs[9] = 0; /* Set return value for child */
	childregs->sr |= SR_FD; /* Invalidate FPU flag */

	p->thread.sp = (unsigned long) childregs;
	p->thread.pc = (unsigned long) ret_from_fork;

	return 0;
}