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
struct TYPE_2__ {int /*<<< orphan*/ * fph; int /*<<< orphan*/  flags; } ;
struct task_struct {TYPE_1__ thread; } ;
struct ia64_psr {scalar_t__ mfh; } ;

/* Variables and functions */
 int /*<<< orphan*/  IA64_THREAD_FPH_VALID ; 
 scalar_t__ ia64_is_local_fpu_owner (struct task_struct*) ; 
 struct ia64_psr* ia64_psr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ia64_save_fpu (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  preempt_disable () ; 
 int /*<<< orphan*/  preempt_enable () ; 
 int /*<<< orphan*/  task_pt_regs (struct task_struct*) ; 

inline void
ia64_flush_fph (struct task_struct *task)
{
	struct ia64_psr *psr = ia64_psr(task_pt_regs(task));

	/*
	 * Prevent migrating this task while
	 * we're fiddling with the FPU state
	 */
	preempt_disable();
	if (ia64_is_local_fpu_owner(task) && psr->mfh) {
		psr->mfh = 0;
		task->thread.flags |= IA64_THREAD_FPH_VALID;
		ia64_save_fpu(&task->thread.fph[0]);
	}
	preempt_enable();
}