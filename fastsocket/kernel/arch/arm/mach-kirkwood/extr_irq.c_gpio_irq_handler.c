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
struct irq_desc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 unsigned int IRQ_KIRKWOOD_GPIO_HIGH_16_23 ; 
 unsigned int IRQ_KIRKWOOD_GPIO_LOW_0_7 ; 
 int /*<<< orphan*/  orion_gpio_irq_handler (unsigned int) ; 

__attribute__((used)) static void gpio_irq_handler(unsigned int irq, struct irq_desc *desc)
{
	BUG_ON(irq < IRQ_KIRKWOOD_GPIO_LOW_0_7);
	BUG_ON(irq > IRQ_KIRKWOOD_GPIO_HIGH_16_23);

	orion_gpio_irq_handler((irq - IRQ_KIRKWOOD_GPIO_LOW_0_7) << 3);
}