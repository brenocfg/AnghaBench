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

/* Variables and functions */
 int /*<<< orphan*/  BLANK () ; 
 int /*<<< orphan*/  MM_pgd ; 
 int /*<<< orphan*/  OFFSET (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TI_cpu ; 
 int /*<<< orphan*/  TI_exec_domain ; 
 int /*<<< orphan*/  TI_flags ; 
 int /*<<< orphan*/  TI_preempt_count ; 
 int /*<<< orphan*/  TI_rar_saved ; 
 int /*<<< orphan*/  TI_restart_block ; 
 int /*<<< orphan*/  TI_rsr_saved ; 
 int /*<<< orphan*/  TI_task ; 
 int /*<<< orphan*/  TSK_active_mm ; 
 int /*<<< orphan*/  active_mm ; 
 int /*<<< orphan*/  cpu ; 
 int /*<<< orphan*/  exec_domain ; 
 int /*<<< orphan*/  flags ; 
 int /*<<< orphan*/  mm_struct ; 
 int /*<<< orphan*/  pgd ; 
 int /*<<< orphan*/  preempt_count ; 
 int /*<<< orphan*/  rar_saved ; 
 int /*<<< orphan*/  restart_block ; 
 int /*<<< orphan*/  rsr_saved ; 
 int /*<<< orphan*/  task ; 
 int /*<<< orphan*/  task_struct ; 
 int /*<<< orphan*/  thread_info ; 

void foo(void)
{
	OFFSET(TI_task, thread_info, task);
	OFFSET(TI_exec_domain, thread_info, exec_domain);
	OFFSET(TI_flags, thread_info, flags);
	OFFSET(TI_cpu, thread_info, cpu);
	OFFSET(TI_preempt_count, thread_info, preempt_count);
	OFFSET(TI_rar_saved, thread_info, rar_saved);
	OFFSET(TI_rsr_saved, thread_info, rsr_saved);
	OFFSET(TI_restart_block, thread_info, restart_block);
	BLANK();
	OFFSET(TSK_active_mm, task_struct, active_mm);
	BLANK();
	OFFSET(MM_pgd, mm_struct, pgd);
}