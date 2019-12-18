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
typedef  scalar_t__ u32 ;

/* Variables and functions */
 scalar_t__ EMMA2RH_GPIO_IRQ_BASE ; 
 scalar_t__ NUM_EMMA2RH_IRQ_GPIO ; 
 int /*<<< orphan*/  emma2rh_gpio_irq_controller ; 
 int /*<<< orphan*/  handle_edge_irq ; 
 int /*<<< orphan*/  set_irq_chip_and_handler_name (scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 

void emma2rh_gpio_irq_init(void)
{
	u32 i;

	for (i = 0; i < NUM_EMMA2RH_IRQ_GPIO; i++)
		set_irq_chip_and_handler_name(EMMA2RH_GPIO_IRQ_BASE + i,
					      &emma2rh_gpio_irq_controller,
					      handle_edge_irq, "edge");
}