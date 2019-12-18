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
struct msp71xx_gpio_chip {int /*<<< orphan*/  data_reg; } ;
struct gpio_chip {int dummy; } ;

/* Variables and functions */
 int __raw_readl (int /*<<< orphan*/ ) ; 
 struct msp71xx_gpio_chip* to_msp71xx_gpio_chip (struct gpio_chip*) ; 

__attribute__((used)) static int msp71xx_gpio_get(struct gpio_chip *chip, unsigned offset)
{
	struct msp71xx_gpio_chip *msp_chip = to_msp71xx_gpio_chip(chip);

	return __raw_readl(msp_chip->data_reg) & (1 << offset);
}