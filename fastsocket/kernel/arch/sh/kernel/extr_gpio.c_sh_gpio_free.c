#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct pinmux_info {TYPE_1__* gpios; } ;
struct gpio_chip {int dummy; } ;
struct TYPE_2__ {int flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  GPIO_CFG_FREE ; 
 int PINMUX_FLAG_TYPE ; 
 int PINMUX_TYPE_NONE ; 
 struct pinmux_info* chip_to_pinmux (struct gpio_chip*) ; 
 int /*<<< orphan*/  gpio_lock ; 
 int /*<<< orphan*/  pinmux_config_gpio (struct pinmux_info*,unsigned int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void sh_gpio_free(struct gpio_chip *chip, unsigned offset)
{
	struct pinmux_info *gpioc = chip_to_pinmux(chip);
	unsigned long flags;
	int pinmux_type;

	if (!gpioc)
		return;

	spin_lock_irqsave(&gpio_lock, flags);

	pinmux_type = gpioc->gpios[offset].flags & PINMUX_FLAG_TYPE;
	pinmux_config_gpio(gpioc, offset, pinmux_type, GPIO_CFG_FREE);
	gpioc->gpios[offset].flags &= ~PINMUX_FLAG_TYPE;
	gpioc->gpios[offset].flags |= PINMUX_TYPE_NONE;

	spin_unlock_irqrestore(&gpio_lock, flags);
}