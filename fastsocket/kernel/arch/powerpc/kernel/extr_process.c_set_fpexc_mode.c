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
struct TYPE_2__ {unsigned int fpexc_mode; struct pt_regs* regs; } ;
struct task_struct {TYPE_1__ thread; } ;
struct pt_regs {int msr; } ;

/* Variables and functions */
 int /*<<< orphan*/  CPU_FTR_SPE ; 
 int EINVAL ; 
 int MSR_FE0 ; 
 int MSR_FE1 ; 
 int MSR_FP ; 
 unsigned int PR_FP_ALL_EXCEPT ; 
 unsigned int PR_FP_EXC_PRECISE ; 
 unsigned int PR_FP_EXC_SW_ENABLE ; 
 int __pack_fe01 (unsigned int) ; 
 scalar_t__ cpu_has_feature (int /*<<< orphan*/ ) ; 

int set_fpexc_mode(struct task_struct *tsk, unsigned int val)
{
	struct pt_regs *regs = tsk->thread.regs;

	/* This is a bit hairy.  If we are an SPE enabled  processor
	 * (have embedded fp) we store the IEEE exception enable flags in
	 * fpexc_mode.  fpexc_mode is also used for setting FP exception
	 * mode (asyn, precise, disabled) for 'Classic' FP. */
	if (val & PR_FP_EXC_SW_ENABLE) {
#ifdef CONFIG_SPE
		if (cpu_has_feature(CPU_FTR_SPE)) {
			tsk->thread.fpexc_mode = val &
				(PR_FP_EXC_SW_ENABLE | PR_FP_ALL_EXCEPT);
			return 0;
		} else {
			return -EINVAL;
		}
#else
		return -EINVAL;
#endif
	}

	/* on a CONFIG_SPE this does not hurt us.  The bits that
	 * __pack_fe01 use do not overlap with bits used for
	 * PR_FP_EXC_SW_ENABLE.  Additionally, the MSR[FE0,FE1] bits
	 * on CONFIG_SPE implementations are reserved so writing to
	 * them does not change anything */
	if (val > PR_FP_EXC_PRECISE)
		return -EINVAL;
	tsk->thread.fpexc_mode = __pack_fe01(val);
	if (regs != NULL && (regs->msr & MSR_FP) != 0)
		regs->msr = (regs->msr & ~(MSR_FE0|MSR_FE1))
			| tsk->thread.fpexc_mode;
	return 0;
}