#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct task_struct {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PARAVIRT_LAZY_CPU ; 
 scalar_t__ PARAVIRT_LAZY_MMU ; 
 int /*<<< orphan*/  TIF_LAZY_MMU_UPDATES ; 
 int /*<<< orphan*/  arch_leave_lazy_mmu_mode () ; 
 int /*<<< orphan*/  enter_lazy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  paravirt_lazy_mode ; 
 scalar_t__ percpu_read (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  preemptible () ; 
 int /*<<< orphan*/  set_ti_thread_flag (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  task_thread_info (struct task_struct*) ; 

void paravirt_start_context_switch(struct task_struct *prev)
{
	BUG_ON(preemptible());

	if (percpu_read(paravirt_lazy_mode) == PARAVIRT_LAZY_MMU) {
		arch_leave_lazy_mmu_mode();
		set_ti_thread_flag(task_thread_info(prev), TIF_LAZY_MMU_UPDATES);
	}
	enter_lazy(PARAVIRT_LAZY_CPU);
}