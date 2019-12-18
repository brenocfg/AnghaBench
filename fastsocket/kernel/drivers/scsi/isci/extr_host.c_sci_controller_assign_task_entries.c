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
typedef  int u32 ;
struct isci_host {TYPE_1__* smu_registers; scalar_t__ task_context_entries; } ;
struct TYPE_2__ {int /*<<< orphan*/ * task_context_assignment; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENDING ; 
 int /*<<< orphan*/  RANGE_CHECK_ENABLE ; 
 int SMU_TCA_GEN_BIT (int /*<<< orphan*/ ) ; 
 int SMU_TCA_GEN_VAL (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  STARTING ; 
 int readl (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  writel (int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void sci_controller_assign_task_entries(struct isci_host *ihost)
{
	u32 task_assignment;

	/*
	 * Assign all the TCs to function 0
	 * TODO: Do we actually need to read this register to write it back?
	 */

	task_assignment =
		readl(&ihost->smu_registers->task_context_assignment[0]);

	task_assignment |= (SMU_TCA_GEN_VAL(STARTING, 0)) |
		(SMU_TCA_GEN_VAL(ENDING,  ihost->task_context_entries - 1)) |
		(SMU_TCA_GEN_BIT(RANGE_CHECK_ENABLE));

	writel(task_assignment,
		&ihost->smu_registers->task_context_assignment[0]);

}