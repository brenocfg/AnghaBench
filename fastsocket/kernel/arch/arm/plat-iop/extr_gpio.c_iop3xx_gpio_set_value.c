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
 int /*<<< orphan*/  gpio_line_set (unsigned int,int) ; 

__attribute__((used)) static void iop3xx_gpio_set_value(struct gpio_chip *chip, unsigned gpio, int value)
{
	gpio_line_set(gpio, value);
}