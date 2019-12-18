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
struct TYPE_2__ {int dbcr0; struct pt_regs* regs; } ;
struct task_struct {TYPE_1__ thread; } ;
struct pt_regs {int /*<<< orphan*/  msr; } ;

/* Variables and functions */
 int DBCR0_BT ; 
 int DBCR0_IC ; 
 int DBCR0_IDM ; 
 int /*<<< orphan*/  MSR_BE ; 
 int /*<<< orphan*/  MSR_DE ; 
 int /*<<< orphan*/  MSR_SE ; 
 int /*<<< orphan*/  TIF_SINGLESTEP ; 
 int /*<<< orphan*/  set_tsk_thread_flag (struct task_struct*,int /*<<< orphan*/ ) ; 

void user_enable_single_step(struct task_struct *task)
{
	struct pt_regs *regs = task->thread.regs;

	if (regs != NULL) {
#if defined(CONFIG_40x) || defined(CONFIG_BOOKE)
		task->thread.dbcr0 &= ~DBCR0_BT;
		task->thread.dbcr0 |= DBCR0_IDM | DBCR0_IC;
		regs->msr |= MSR_DE;
#else
		regs->msr &= ~MSR_BE;
		regs->msr |= MSR_SE;
#endif
	}
	set_tsk_thread_flag(task, TIF_SINGLESTEP);
}