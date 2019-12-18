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
 int /*<<< orphan*/  MSP71XX_GPIO_OUTPUT ; 
 int /*<<< orphan*/  msp71xx_gpio_set (struct gpio_chip*,unsigned int,int) ; 
 int msp71xx_set_gpio_mode (struct gpio_chip*,unsigned int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int msp71xx_direction_output(struct gpio_chip *chip,
				    unsigned offset, int value)
{
	msp71xx_gpio_set(chip, offset, value);

	return msp71xx_set_gpio_mode(chip, offset, MSP71XX_GPIO_OUTPUT);
}