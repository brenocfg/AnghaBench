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
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_NONE ; 
 int /*<<< orphan*/  IRQ_RETVAL (int /*<<< orphan*/ ) ; 
 unsigned long* R_IRQ_MASK1_CLR ; 
 unsigned long* R_IRQ_READ1 ; 
 int /*<<< orphan*/  etrax_gpio_wake_up_check () ; 
 int /*<<< orphan*/  gpio_lock ; 
 unsigned long gpio_pa_irq_enabled_mask ; 
 scalar_t__ gpio_some_alarms ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static irqreturn_t
gpio_interrupt(int irq, void *dev_id)
{
	unsigned long tmp;
	unsigned long flags;

	spin_lock_irqsave(&gpio_lock, flags);

	/* Find what PA interrupts are active */
	tmp = (*R_IRQ_READ1);

	/* Find those that we have enabled */
	tmp &= gpio_pa_irq_enabled_mask;

	/* Clear them.. */
	*R_IRQ_MASK1_CLR = tmp;
	gpio_pa_irq_enabled_mask &= ~tmp;

	spin_unlock_irqrestore(&gpio_lock, flags);

	if (gpio_some_alarms)
		return IRQ_RETVAL(etrax_gpio_wake_up_check());

        return IRQ_NONE;
}