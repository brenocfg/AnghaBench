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
struct mcf_gpio_chip {int /*<<< orphan*/ * gpio_to_pinmux; } ;
struct gpio_chip {int dummy; } ;

/* Variables and functions */
 struct mcf_gpio_chip* MCF_CHIP (struct gpio_chip*) ; 
 int /*<<< orphan*/  mcf_gpio_direction_input (struct gpio_chip*,unsigned int) ; 
 int /*<<< orphan*/  mcf_pinmux_release (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void mcf_gpio_free(struct gpio_chip *chip, unsigned offset)
{
	struct mcf_gpio_chip *mcf_chip = MCF_CHIP(chip);

	mcf_gpio_direction_input(chip, offset);

	if (mcf_chip->gpio_to_pinmux)
		mcf_pinmux_release(mcf_chip->gpio_to_pinmux[offset], 0);
}