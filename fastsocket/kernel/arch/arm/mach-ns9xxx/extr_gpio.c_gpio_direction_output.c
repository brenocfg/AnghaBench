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
 int /*<<< orphan*/  BUG () ; 
 int EINVAL ; 
 int __ns9360_gpio_configure (unsigned int,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  gpio_lock ; 
 int /*<<< orphan*/  gpio_set_value (unsigned int,int) ; 
 scalar_t__ likely (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ns9xxx_valid_gpio (unsigned int) ; 
 scalar_t__ processor_is_ns9360 () ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

int gpio_direction_output(unsigned gpio, int value)
{
	if (likely(ns9xxx_valid_gpio(gpio))) {
		int ret = -EINVAL;
		unsigned long flags;

		gpio_set_value(gpio, value);

		spin_lock_irqsave(&gpio_lock, flags);
#if defined(CONFIG_PROCESSOR_NS9360)
		if (processor_is_ns9360())
			ret = __ns9360_gpio_configure(gpio, 1, 0, 3);
		else
#endif
			BUG();

		spin_unlock_irqrestore(&gpio_lock, flags);

		return ret;
	} else
		return -EINVAL;
}