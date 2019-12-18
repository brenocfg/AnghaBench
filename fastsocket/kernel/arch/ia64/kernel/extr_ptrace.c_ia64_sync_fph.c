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
struct TYPE_2__ {int flags; int /*<<< orphan*/  fph; } ;
struct task_struct {TYPE_1__ thread; } ;
struct ia64_psr {int dfh; } ;

/* Variables and functions */
 int IA64_THREAD_FPH_VALID ; 
 int /*<<< orphan*/  ia64_drop_fpu (struct task_struct*) ; 
 int /*<<< orphan*/  ia64_flush_fph (struct task_struct*) ; 
 struct ia64_psr* ia64_psr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  task_pt_regs (struct task_struct*) ; 

void
ia64_sync_fph (struct task_struct *task)
{
	struct ia64_psr *psr = ia64_psr(task_pt_regs(task));

	ia64_flush_fph(task);
	if (!(task->thread.flags & IA64_THREAD_FPH_VALID)) {
		task->thread.flags |= IA64_THREAD_FPH_VALID;
		memset(&task->thread.fph, 0, sizeof(task->thread.fph));
	}
	ia64_drop_fpu(task);
	psr->dfh = 1;
}