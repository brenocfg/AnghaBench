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
 int /*<<< orphan*/  GPDR ; 
 int /*<<< orphan*/  GPIO_GPIO (unsigned int) ; 
 int /*<<< orphan*/  local_irq_restore (unsigned long) ; 
 int /*<<< orphan*/  local_irq_save (unsigned long) ; 
 int /*<<< orphan*/  sa1100_gpio_set (struct gpio_chip*,unsigned int,int) ; 

__attribute__((used)) static int sa1100_direction_output(struct gpio_chip *chip, unsigned offset, int value)
{
	unsigned long flags;

	local_irq_save(flags);
	sa1100_gpio_set(chip, offset, value);
	GPDR |= GPIO_GPIO(offset);
	local_irq_restore(flags);
	return 0;
}