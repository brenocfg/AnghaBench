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
struct gpio_chip {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  __set_level (unsigned int,int) ; 
 int /*<<< orphan*/  gpio_lock ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void orion_gpio_set_value(struct gpio_chip *chip, unsigned pin,
	int value)
{
	unsigned long flags;

	spin_lock_irqsave(&gpio_lock, flags);

	/* Configure GPIO output value. */
	__set_level(pin, value);

	spin_unlock_irqrestore(&gpio_lock, flags);
}