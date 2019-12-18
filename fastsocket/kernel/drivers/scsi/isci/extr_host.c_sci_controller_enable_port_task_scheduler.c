#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct isci_host {TYPE_3__* scu_registers; } ;
struct TYPE_4__ {int /*<<< orphan*/  control; } ;
struct TYPE_5__ {TYPE_1__ ptsg; } ;
struct TYPE_6__ {TYPE_2__ peg0; } ;

/* Variables and functions */
 int /*<<< orphan*/  ETM_ENABLE ; 
 int /*<<< orphan*/  PTSG_ENABLE ; 
 int SCU_PTSGCR_GEN_BIT (int /*<<< orphan*/ ) ; 
 int readl (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  writel (int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void sci_controller_enable_port_task_scheduler(struct isci_host *ihost)
{
	u32 port_task_scheduler_value;

	port_task_scheduler_value =
		readl(&ihost->scu_registers->peg0.ptsg.control);
	port_task_scheduler_value |=
		(SCU_PTSGCR_GEN_BIT(ETM_ENABLE) |
		 SCU_PTSGCR_GEN_BIT(PTSG_ENABLE));
	writel(port_task_scheduler_value,
	       &ihost->scu_registers->peg0.ptsg.control);
}