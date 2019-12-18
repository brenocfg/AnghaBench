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
 int /*<<< orphan*/  GPIO_IN ; 
 int /*<<< orphan*/  gpio_line_config (unsigned int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int iop3xx_gpio_direction_input(struct gpio_chip *chip, unsigned gpio)
{
	gpio_line_config(gpio, GPIO_IN);
	return 0;
}