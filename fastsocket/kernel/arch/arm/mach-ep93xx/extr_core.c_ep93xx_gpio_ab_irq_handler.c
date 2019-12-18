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
 int /*<<< orphan*/  EP93XX_GPIO_A_INT_STATUS ; 
 int /*<<< orphan*/  EP93XX_GPIO_B_INT_STATUS ; 
 int /*<<< orphan*/  EP93XX_GPIO_LINE_A (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EP93XX_GPIO_LINE_B (int /*<<< orphan*/ ) ; 
 unsigned char __raw_readb (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  generic_handle_irq (int) ; 
 int gpio_to_irq (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ep93xx_gpio_ab_irq_handler(unsigned int irq, struct irq_desc *desc)
{
	unsigned char status;
	int i;

	status = __raw_readb(EP93XX_GPIO_A_INT_STATUS);
	for (i = 0; i < 8; i++) {
		if (status & (1 << i)) {
			int gpio_irq = gpio_to_irq(EP93XX_GPIO_LINE_A(0)) + i;
			generic_handle_irq(gpio_irq);
		}
	}

	status = __raw_readb(EP93XX_GPIO_B_INT_STATUS);
	for (i = 0; i < 8; i++) {
		if (status & (1 << i)) {
			int gpio_irq = gpio_to_irq(EP93XX_GPIO_LINE_B(0)) + i;
			generic_handle_irq(gpio_irq);
		}
	}
}