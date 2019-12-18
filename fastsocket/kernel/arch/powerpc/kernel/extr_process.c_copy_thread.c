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
struct thread_info {int dummy; } ;
struct TYPE_3__ {unsigned long ksp; unsigned long ksp_vsid; scalar_t__ ksp_limit; struct pt_regs* regs; } ;
struct task_struct {TYPE_1__ thread; } ;
struct pt_regs {int msr; unsigned long* gpr; unsigned long nip; } ;
struct TYPE_4__ {unsigned long sllp; } ;

/* Variables and functions */
 int /*<<< orphan*/  CHECK_FULL_REGS (struct pt_regs*) ; 
 unsigned long CLONE_SETTLS ; 
 int /*<<< orphan*/  CPU_FTR_1T_SEGMENT ; 
 int /*<<< orphan*/  CPU_FTR_SLB ; 
 int /*<<< orphan*/  MMU_SEGSIZE_1T ; 
 int /*<<< orphan*/  MMU_SEGSIZE_256M ; 
 int MSR_PR ; 
 unsigned long SLB_VSID_KERNEL ; 
 unsigned long SLB_VSID_SHIFT ; 
 unsigned long SLB_VSID_SHIFT_1T ; 
 scalar_t__ STACK_FRAME_OVERHEAD ; 
 unsigned long THREAD_SIZE ; 
 int /*<<< orphan*/  TIF_32BIT ; 
 scalar_t__ _ALIGN_UP (int,int) ; 
 int /*<<< orphan*/  clear_tsk_thread_flag (struct task_struct*,int /*<<< orphan*/ ) ; 
 scalar_t__ cpu_has_feature (int /*<<< orphan*/ ) ; 
 unsigned long get_kernel_vsid (unsigned long,int /*<<< orphan*/ ) ; 
 size_t mmu_linear_psize ; 
 TYPE_2__* mmu_psize_defs ; 
 scalar_t__ task_stack_page (struct task_struct*) ; 
 int /*<<< orphan*/  test_thread_flag (int /*<<< orphan*/ ) ; 

int copy_thread(unsigned long clone_flags, unsigned long usp,
		unsigned long unused, struct task_struct *p,
		struct pt_regs *regs)
{
	struct pt_regs *childregs, *kregs;
	extern void ret_from_fork(void);
	unsigned long sp = (unsigned long)task_stack_page(p) + THREAD_SIZE;

	CHECK_FULL_REGS(regs);
	/* Copy registers */
	sp -= sizeof(struct pt_regs);
	childregs = (struct pt_regs *) sp;
	*childregs = *regs;
	if ((childregs->msr & MSR_PR) == 0) {
		/* for kernel thread, set `current' and stackptr in new task */
		childregs->gpr[1] = sp + sizeof(struct pt_regs);
#ifdef CONFIG_PPC32
		childregs->gpr[2] = (unsigned long) p;
#else
		clear_tsk_thread_flag(p, TIF_32BIT);
#endif
		p->thread.regs = NULL;	/* no user register state */
	} else {
		childregs->gpr[1] = usp;
		p->thread.regs = childregs;
		if (clone_flags & CLONE_SETTLS) {
#ifdef CONFIG_PPC64
			if (!test_thread_flag(TIF_32BIT))
				childregs->gpr[13] = childregs->gpr[6];
			else
#endif
				childregs->gpr[2] = childregs->gpr[6];
		}
	}
	childregs->gpr[3] = 0;  /* Result from fork() */
	sp -= STACK_FRAME_OVERHEAD;

	/*
	 * The way this works is that at some point in the future
	 * some task will call _switch to switch to the new task.
	 * That will pop off the stack frame created below and start
	 * the new task running at ret_from_fork.  The new task will
	 * do some house keeping and then return from the fork or clone
	 * system call, using the stack frame created above.
	 */
	sp -= sizeof(struct pt_regs);
	kregs = (struct pt_regs *) sp;
	sp -= STACK_FRAME_OVERHEAD;
	p->thread.ksp = sp;
	p->thread.ksp_limit = (unsigned long)task_stack_page(p) +
				_ALIGN_UP(sizeof(struct thread_info), 16);

#ifdef CONFIG_PPC_STD_MMU_64
	if (cpu_has_feature(CPU_FTR_SLB)) {
		unsigned long sp_vsid;
		unsigned long llp = mmu_psize_defs[mmu_linear_psize].sllp;

		if (cpu_has_feature(CPU_FTR_1T_SEGMENT))
			sp_vsid = get_kernel_vsid(sp, MMU_SEGSIZE_1T)
				<< SLB_VSID_SHIFT_1T;
		else
			sp_vsid = get_kernel_vsid(sp, MMU_SEGSIZE_256M)
				<< SLB_VSID_SHIFT;
		sp_vsid |= SLB_VSID_KERNEL | llp;
		p->thread.ksp_vsid = sp_vsid;
	}
#endif /* CONFIG_PPC_STD_MMU_64 */

	/*
	 * The PPC64 ABI makes use of a TOC to contain function 
	 * pointers.  The function (ret_from_except) is actually a pointer
	 * to the TOC entry.  The first entry is a pointer to the actual
	 * function.
 	 */
#ifdef CONFIG_PPC64
	kregs->nip = *((unsigned long *)ret_from_fork);
#else
	kregs->nip = (unsigned long)ret_from_fork;
#endif

	return 0;
}