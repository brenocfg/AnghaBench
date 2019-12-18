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
 unsigned int PNX833X_GPIO_IRQ_BASE ; 
 int /*<<< orphan*/  pnx833x_gpio_disable_irq (int) ; 
 int /*<<< orphan*/  pnx833x_gpio_pnx833x_irq_lock ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void pnx833x_disable_gpio_irq(unsigned int irq)
{
	int pin = irq - PNX833X_GPIO_IRQ_BASE;
	unsigned long flags;
	spin_lock_irqsave(&pnx833x_gpio_pnx833x_irq_lock, flags);
	pnx833x_gpio_disable_irq(pin);
	spin_unlock_irqrestore(&pnx833x_gpio_pnx833x_irq_lock, flags);
}