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
 int mcf_pinmux_request (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int mcf_gpio_request(struct gpio_chip *chip, unsigned offset)
{
	struct mcf_gpio_chip *mcf_chip = MCF_CHIP(chip);

	return mcf_chip->gpio_to_pinmux ?
		mcf_pinmux_request(mcf_chip->gpio_to_pinmux[offset], 0) : 0;
}