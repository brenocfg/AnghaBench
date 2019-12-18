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
 int /*<<< orphan*/  EP93XX_GPIO_LINE_F (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  generic_handle_irq (int) ; 
 int gpio_to_irq (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ep93xx_gpio_f_irq_handler(unsigned int irq, struct irq_desc *desc)
{
	/*
	 * map discontiguous hw irq range to continous sw irq range:
	 *
	 *  IRQ_EP93XX_GPIO{0..7}MUX -> gpio_to_irq(EP93XX_GPIO_LINE_F({0..7})
	 */
	int port_f_idx = ((irq + 1) & 7) ^ 4; /* {19..22,47..50} -> {0..7} */
	int gpio_irq = gpio_to_irq(EP93XX_GPIO_LINE_F(0)) + port_f_idx;

	generic_handle_irq(gpio_irq);
}