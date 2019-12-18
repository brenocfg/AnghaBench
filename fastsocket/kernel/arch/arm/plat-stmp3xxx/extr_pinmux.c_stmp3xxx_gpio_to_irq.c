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
struct stmp3xxx_pinmux_bank {int virq; } ;
struct gpio_chip {int dummy; } ;

/* Variables and functions */
 struct stmp3xxx_pinmux_bank* to_pinmux_bank (struct gpio_chip*) ; 

__attribute__((used)) static int stmp3xxx_gpio_to_irq(struct gpio_chip *chip, unsigned offset)
{
	struct stmp3xxx_pinmux_bank *pm = to_pinmux_bank(chip);
	return pm->virq + offset;
}