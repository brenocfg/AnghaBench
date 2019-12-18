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
typedef  int u32 ;

/* Variables and functions */
 int PIN_TO_PORT (unsigned int) ; 
 int U300_GPIO_PORTX_SPACING ; 
 scalar_t__ U300_GPIO_PXPDOR ; 
 int /*<<< orphan*/  local_irq_restore (unsigned long) ; 
 int /*<<< orphan*/  local_irq_save (unsigned long) ; 
 int readl (scalar_t__) ; 
 scalar_t__ virtbase ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

void gpio_set_value(unsigned gpio, int value)
{
	u32 val;
	unsigned long flags;

	local_irq_save(flags);
	if (value) {
		/* set */
		val = readl(virtbase + U300_GPIO_PXPDOR +
		  PIN_TO_PORT(gpio) * U300_GPIO_PORTX_SPACING)
		  & (1 << (gpio & 0x07));
		writel(val | (1 << (gpio & 0x07)), virtbase +
		  U300_GPIO_PXPDOR +
		  PIN_TO_PORT(gpio) * U300_GPIO_PORTX_SPACING);
	} else {
		/* clear */
		val = readl(virtbase + U300_GPIO_PXPDOR +
		  PIN_TO_PORT(gpio) * U300_GPIO_PORTX_SPACING)
		  & (1 << (gpio & 0x07));
		writel(val & ~(1 << (gpio & 0x07)), virtbase +
		  U300_GPIO_PXPDOR +
		  PIN_TO_PORT(gpio) * U300_GPIO_PORTX_SPACING);
	}
	local_irq_restore(flags);
}