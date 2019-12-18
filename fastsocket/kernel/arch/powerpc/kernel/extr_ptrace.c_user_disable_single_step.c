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
struct TYPE_2__ {int dbcr0; scalar_t__ dabr; struct pt_regs* regs; } ;
struct task_struct {TYPE_1__ thread; } ;
struct pt_regs {int msr; } ;

/* Variables and functions */
 int DBCR0_BT ; 
 int DBCR0_IC ; 
 int DBCR0_IDM ; 
 int MSR_BE ; 
 int MSR_DE ; 
 int MSR_SE ; 
 int /*<<< orphan*/  TIF_SINGLESTEP ; 
 int /*<<< orphan*/  clear_tsk_thread_flag (struct task_struct*,int /*<<< orphan*/ ) ; 

void user_disable_single_step(struct task_struct *task)
{
	struct pt_regs *regs = task->thread.regs;

	if (regs != NULL) {
#if defined(CONFIG_BOOKE)
		/* If DAC don't clear DBCRO_IDM or MSR_DE */
		if (task->thread.dabr)
			task->thread.dbcr0 &= ~(DBCR0_IC | DBCR0_BT);
		else {
			task->thread.dbcr0 &= ~(DBCR0_IC | DBCR0_BT | DBCR0_IDM);
			regs->msr &= ~MSR_DE;
		}
#elif defined(CONFIG_40x)
		task->thread.dbcr0 &= ~(DBCR0_IC | DBCR0_BT | DBCR0_IDM);
		regs->msr &= ~MSR_DE;
#else
		regs->msr &= ~(MSR_SE | MSR_BE);
#endif
	}
	clear_tsk_thread_flag(task, TIF_SINGLESTEP);
}