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
struct pinmux_info {int dummy; } ;
struct gpio_chip {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  PINMUX_TYPE_INPUT ; 
 struct pinmux_info* chip_to_pinmux (struct gpio_chip*) ; 
 int /*<<< orphan*/  gpio_lock ; 
 int pinmux_direction (struct pinmux_info*,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int sh_gpio_direction_input(struct gpio_chip *chip, unsigned offset)
{
	struct pinmux_info *gpioc = chip_to_pinmux(chip);
	unsigned long flags;
	int ret;

	spin_lock_irqsave(&gpio_lock, flags);
	ret = pinmux_direction(gpioc, offset, PINMUX_TYPE_INPUT);
	spin_unlock_irqrestore(&gpio_lock, flags);

	return ret;
}