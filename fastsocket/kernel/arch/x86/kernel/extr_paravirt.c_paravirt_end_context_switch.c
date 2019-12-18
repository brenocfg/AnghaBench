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
 int /*<<< orphan*/  TIF_LAZY_MMU_UPDATES ; 
 int /*<<< orphan*/  arch_enter_lazy_mmu_mode () ; 
 int /*<<< orphan*/  leave_lazy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  preemptible () ; 
 int /*<<< orphan*/  task_thread_info (struct task_struct*) ; 
 scalar_t__ test_and_clear_ti_thread_flag (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void paravirt_end_context_switch(struct task_struct *next)
{
	BUG_ON(preemptible());

	leave_lazy(PARAVIRT_LAZY_CPU);

	if (test_and_clear_ti_thread_flag(task_thread_info(next), TIF_LAZY_MMU_UPDATES))
		arch_enter_lazy_mmu_mode();
}