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
 int EINVAL ; 
 int /*<<< orphan*/  GPIO_INPUT_OK ; 
 int /*<<< orphan*/  __set_direction (unsigned int,int) ; 
 int /*<<< orphan*/  gpio_lock ; 
 int /*<<< orphan*/  orion_gpio_is_valid (unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int orion_gpio_direction_input(struct gpio_chip *chip, unsigned pin)
{
	unsigned long flags;

	if (!orion_gpio_is_valid(pin, GPIO_INPUT_OK))
		return -EINVAL;

	spin_lock_irqsave(&gpio_lock, flags);

	/* Configure GPIO direction. */
	__set_direction(pin, 1);

	spin_unlock_irqrestore(&gpio_lock, flags);

	return 0;
}