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
struct stmp3xxx_pinmux_bank {int /*<<< orphan*/  hw_gpio_doe; } ;
struct gpio_chip {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  stmp3xxx_gpio_set (struct gpio_chip*,unsigned int,int) ; 
 int /*<<< orphan*/  stmp3xxx_setl (int,int /*<<< orphan*/ ) ; 
 struct stmp3xxx_pinmux_bank* to_pinmux_bank (struct gpio_chip*) ; 

__attribute__((used)) static int stmp3xxx_gpio_output(struct gpio_chip *chip, unsigned offset, int v)
{
	struct stmp3xxx_pinmux_bank *pm = to_pinmux_bank(chip);

	stmp3xxx_setl(1 << offset, pm->hw_gpio_doe);
	stmp3xxx_gpio_set(chip, offset, v);
	return 0;
}