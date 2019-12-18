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
struct TYPE_2__ {int /*<<< orphan*/ * intid; } ;

/* Variables and functions */
 int LEON3_BYPASS_LOAD_PA (int /*<<< orphan*/ *) ; 
 TYPE_1__* leon3_irqctrl_regs ; 

int sparc_leon_eirq_get(int eirq, int cpu)
{
	return LEON3_BYPASS_LOAD_PA(&leon3_irqctrl_regs->intid[cpu]) & 0x1f;
}