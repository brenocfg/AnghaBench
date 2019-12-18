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
 int /*<<< orphan*/  GPIO_DATA_IN (unsigned int) ; 
 int /*<<< orphan*/  GPIO_IN_POL (unsigned int) ; 
 int /*<<< orphan*/  GPIO_IO_CONF (unsigned int) ; 
 int /*<<< orphan*/  GPIO_OUT (unsigned int) ; 
 int readl (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int orion_gpio_get_value(struct gpio_chip *chip, unsigned pin)
{
	int val;

	if (readl(GPIO_IO_CONF(pin)) & (1 << (pin & 31)))
		val = readl(GPIO_DATA_IN(pin)) ^ readl(GPIO_IN_POL(pin));
	else
		val = readl(GPIO_OUT(pin));

	return (val >> (pin & 31)) & 1;
}