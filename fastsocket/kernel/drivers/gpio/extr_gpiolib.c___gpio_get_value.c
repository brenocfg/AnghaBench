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
struct gpio_chip {int (* get ) (struct gpio_chip*,unsigned int) ;unsigned int base; scalar_t__ can_sleep; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON (int) ; 
 scalar_t__ extra_checks ; 
 struct gpio_chip* gpio_to_chip (unsigned int) ; 
 int stub1 (struct gpio_chip*,unsigned int) ; 

int __gpio_get_value(unsigned gpio)
{
	struct gpio_chip	*chip;

	chip = gpio_to_chip(gpio);
	WARN_ON(extra_checks && chip->can_sleep);
	return chip->get ? chip->get(chip, gpio - chip->base) : 0;
}