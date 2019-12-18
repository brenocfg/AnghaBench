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
struct mcf_gpio_chip {int /*<<< orphan*/  ppdr; } ;
struct gpio_chip {unsigned int base; } ;

/* Variables and functions */
 struct mcf_gpio_chip* MCF_CHIP (struct gpio_chip*) ; 
 int mcfgpio_bit (unsigned int) ; 
 int mcfgpio_read (int /*<<< orphan*/ ) ; 

int mcf_gpio_get_value(struct gpio_chip *chip, unsigned offset)
{
	struct mcf_gpio_chip *mcf_chip = MCF_CHIP(chip);

	return mcfgpio_read(mcf_chip->ppdr) & mcfgpio_bit(chip->base + offset);
}