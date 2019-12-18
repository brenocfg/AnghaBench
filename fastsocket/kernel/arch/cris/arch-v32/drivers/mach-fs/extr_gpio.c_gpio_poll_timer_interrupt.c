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
 int /*<<< orphan*/  etrax_gpio_wake_up_check () ; 
 scalar_t__ gpio_some_alarms ; 

__attribute__((used)) static irqreturn_t
gpio_poll_timer_interrupt(int irq, void *dev_id)
{
	if (gpio_some_alarms)
		return IRQ_RETVAL(etrax_gpio_wake_up_check());
	return IRQ_NONE;
}