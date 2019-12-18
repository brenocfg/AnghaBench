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
struct of_mm_gpio_chip {scalar_t__ regs; } ;
struct gpio_chip {int dummy; } ;

/* Variables and functions */
 scalar_t__ GEF_GPIO_IN ; 
 unsigned int ioread32be (scalar_t__) ; 
 struct of_mm_gpio_chip* to_of_mm_gpio_chip (struct gpio_chip*) ; 

__attribute__((used)) static int gef_gpio_get(struct gpio_chip *chip, unsigned offset)
{
	unsigned int data;
	int state = 0;
	struct of_mm_gpio_chip *mmchip = to_of_mm_gpio_chip(chip);

	data = ioread32be(mmchip->regs + GEF_GPIO_IN);
	state = (int)((data >> offset) & 0x1);

	return state;
}