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
 int /*<<< orphan*/  AWA_DUMMY_READ (int /*<<< orphan*/ ) ; 
 int EINVAL ; 
 int /*<<< orphan*/  __bfin_gpio_direction_input (unsigned int) ; 
 size_t gpio_bank (unsigned int) ; 
 int gpio_bit (unsigned int) ; 
 int /*<<< orphan*/  gpio_error (unsigned int) ; 
 int /*<<< orphan*/  inen ; 
 int /*<<< orphan*/  local_irq_restore_hw (unsigned long) ; 
 int /*<<< orphan*/  local_irq_save_hw (unsigned long) ; 
 int* reserved_gpio_map ; 

int bfin_gpio_direction_input(unsigned gpio)
{
	unsigned long flags;

	if (!(reserved_gpio_map[gpio_bank(gpio)] & gpio_bit(gpio))) {
		gpio_error(gpio);
		return -EINVAL;
	}

	local_irq_save_hw(flags);
	__bfin_gpio_direction_input(gpio);
	AWA_DUMMY_READ(inen);
	local_irq_restore_hw(flags);

	return 0;
}