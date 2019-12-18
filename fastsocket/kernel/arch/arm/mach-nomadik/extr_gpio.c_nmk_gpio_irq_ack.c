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
struct nmk_gpio_chip {scalar_t__ addr; } ;

/* Variables and functions */
 scalar_t__ NMK_GPIO_IC ; 
 int NOMADIK_IRQ_TO_GPIO (unsigned int) ; 
 struct nmk_gpio_chip* get_irq_chip_data (unsigned int) ; 
 int /*<<< orphan*/  nmk_gpio_get_bitmask (int) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void nmk_gpio_irq_ack(unsigned int irq)
{
	int gpio;
	struct nmk_gpio_chip *nmk_chip;

	gpio = NOMADIK_IRQ_TO_GPIO(irq);
	nmk_chip = get_irq_chip_data(irq);
	if (!nmk_chip)
		return;
	writel(nmk_gpio_get_bitmask(gpio), nmk_chip->addr + NMK_GPIO_IC);
}