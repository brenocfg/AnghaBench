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
 int /*<<< orphan*/  IRQ_EB11MP_PMU_CPU0 ; 
 int /*<<< orphan*/  IRQ_EB11MP_PMU_CPU1 ; 
 int /*<<< orphan*/  IRQ_EB11MP_PMU_CPU2 ; 
 int /*<<< orphan*/  IRQ_EB11MP_PMU_CPU3 ; 
 int /*<<< orphan*/  IRQ_EB11MP_PMU_SCU0 ; 
 int /*<<< orphan*/  IRQ_EB11MP_PMU_SCU1 ; 
 int /*<<< orphan*/  IRQ_EB11MP_PMU_SCU2 ; 
 int /*<<< orphan*/  IRQ_EB11MP_PMU_SCU3 ; 
 int /*<<< orphan*/  IRQ_EB11MP_PMU_SCU4 ; 
 int /*<<< orphan*/  IRQ_EB11MP_PMU_SCU5 ; 
 int /*<<< orphan*/  IRQ_EB11MP_PMU_SCU6 ; 
 int /*<<< orphan*/  IRQ_EB11MP_PMU_SCU7 ; 
 int /*<<< orphan*/  em_route_irq (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int em_setup(void)
{
	/*
	 * Send SCU PMU interrupts to the "owner" CPU.
	 */
	em_route_irq(IRQ_EB11MP_PMU_SCU0, 0);
	em_route_irq(IRQ_EB11MP_PMU_SCU1, 0);
	em_route_irq(IRQ_EB11MP_PMU_SCU2, 1);
	em_route_irq(IRQ_EB11MP_PMU_SCU3, 1);
	em_route_irq(IRQ_EB11MP_PMU_SCU4, 2);
	em_route_irq(IRQ_EB11MP_PMU_SCU5, 2);
	em_route_irq(IRQ_EB11MP_PMU_SCU6, 3);
	em_route_irq(IRQ_EB11MP_PMU_SCU7, 3);

	/*
	 * Send CP15 PMU interrupts to the owner CPU.
	 */
	em_route_irq(IRQ_EB11MP_PMU_CPU0, 0);
	em_route_irq(IRQ_EB11MP_PMU_CPU1, 1);
	em_route_irq(IRQ_EB11MP_PMU_CPU2, 2);
	em_route_irq(IRQ_EB11MP_PMU_CPU3, 3);

	return 0;
}