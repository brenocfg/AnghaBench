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
 int /*<<< orphan*/  chip_to_pinmux (struct gpio_chip*) ; 
 int sh_gpio_get_value (int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static int sh_gpio_get(struct gpio_chip *chip, unsigned offset)
{
	return sh_gpio_get_value(chip_to_pinmux(chip), offset);
}