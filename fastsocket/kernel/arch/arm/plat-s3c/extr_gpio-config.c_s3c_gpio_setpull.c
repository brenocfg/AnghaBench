#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {unsigned int base; } ;
struct s3c_gpio_chip {TYPE_1__ chip; } ;
typedef  int /*<<< orphan*/  s3c_gpio_pull_t ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  local_irq_restore (unsigned long) ; 
 int /*<<< orphan*/  local_irq_save (unsigned long) ; 
 int s3c_gpio_do_setpull (struct s3c_gpio_chip*,int,int /*<<< orphan*/ ) ; 
 struct s3c_gpio_chip* s3c_gpiolib_getchip (unsigned int) ; 

int s3c_gpio_setpull(unsigned int pin, s3c_gpio_pull_t pull)
{
	struct s3c_gpio_chip *chip = s3c_gpiolib_getchip(pin);
	unsigned long flags;
	int offset, ret;

	if (!chip)
		return -EINVAL;

	offset = pin - chip->chip.base;

	local_irq_save(flags);
	ret = s3c_gpio_do_setpull(chip, offset, pull);
	local_irq_restore(flags);

	return ret;
}