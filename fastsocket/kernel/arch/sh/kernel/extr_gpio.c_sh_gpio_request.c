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
struct pinmux_data_reg {int dummy; } ;
struct gpio_chip {int dummy; } ;
struct TYPE_2__ {int flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG () ; 
 int EINVAL ; 
 int /*<<< orphan*/  GPIO_CFG_DRYRUN ; 
 int /*<<< orphan*/  GPIO_CFG_REQ ; 
 int PINMUX_FLAG_TYPE ; 
 int PINMUX_TYPE_FUNCTION ; 
 int PINMUX_TYPE_GPIO ; 
 int PINMUX_TYPE_NONE ; 
 struct pinmux_info* chip_to_pinmux (struct gpio_chip*) ; 
 scalar_t__ get_data_reg (struct pinmux_info*,unsigned int,struct pinmux_data_reg**,int*) ; 
 int /*<<< orphan*/  gpio_lock ; 
 scalar_t__ pinmux_config_gpio (struct pinmux_info*,unsigned int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int sh_gpio_request(struct gpio_chip *chip, unsigned offset)
{
	struct pinmux_info *gpioc = chip_to_pinmux(chip);
	struct pinmux_data_reg *dummy;
	unsigned long flags;
	int i, ret, pinmux_type;

	ret = -EINVAL;

	if (!gpioc)
		goto err_out;

	spin_lock_irqsave(&gpio_lock, flags);

	if ((gpioc->gpios[offset].flags & PINMUX_FLAG_TYPE) != PINMUX_TYPE_NONE)
		goto err_unlock;

	/* setup pin function here if no data is associated with pin */

	if (get_data_reg(gpioc, offset, &dummy, &i) != 0)
		pinmux_type = PINMUX_TYPE_FUNCTION;
	else
		pinmux_type = PINMUX_TYPE_GPIO;

	if (pinmux_type == PINMUX_TYPE_FUNCTION) {
		if (pinmux_config_gpio(gpioc, offset,
				       pinmux_type,
				       GPIO_CFG_DRYRUN) != 0)
			goto err_unlock;

		if (pinmux_config_gpio(gpioc, offset,
				       pinmux_type,
				       GPIO_CFG_REQ) != 0)
			BUG();
	}

	gpioc->gpios[offset].flags &= ~PINMUX_FLAG_TYPE;
	gpioc->gpios[offset].flags |= pinmux_type;

	ret = 0;
 err_unlock:
	spin_unlock_irqrestore(&gpio_lock, flags);
 err_out:
	return ret;
}