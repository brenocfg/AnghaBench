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
struct TYPE_4__ {TYPE_1__* uregs; } ;
struct task_struct {TYPE_2__ thread; } ;
struct TYPE_3__ {int /*<<< orphan*/  epsw; } ;

/* Variables and functions */
 int /*<<< orphan*/  EPSW_FE ; 
 int /*<<< orphan*/  clear_using_fpu (struct task_struct*) ; 
 struct task_struct* fpu_state_owner ; 
 int /*<<< orphan*/  preempt_disable () ; 
 int /*<<< orphan*/  preempt_enable () ; 

void fpu_kill_state(struct task_struct *tsk)
{
#ifdef CONFIG_FPU
	/* disown anything left in the FPU */
	preempt_disable();

	if (fpu_state_owner == tsk) {
		fpu_state_owner->thread.uregs->epsw &= ~EPSW_FE;
		fpu_state_owner = NULL;
	}

	preempt_enable();
#endif
	/* we no longer have a valid current FPU state */
	clear_using_fpu(tsk);
}