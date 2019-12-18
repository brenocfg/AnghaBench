#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_3__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct device {int dummy; } ;
struct TYPE_5__ {unsigned int gpio; } ;
struct TYPE_4__ {unsigned int gpio_cd; } ;

/* Variables and functions */
 int /*<<< orphan*/  L8_34XX_GPIO63 ; 
 unsigned int TWL4030_GPIO_MAX ; 
 TYPE_3__* gpio_leds ; 
 int /*<<< orphan*/  leds_gpio ; 
 TYPE_1__* mmc ; 
 int /*<<< orphan*/  omap_cfg_reg (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_device_register (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  twl4030_mmc_init (TYPE_1__*) ; 

__attribute__((used)) static int omap3evm_twl_gpio_setup(struct device *dev,
		unsigned gpio, unsigned ngpio)
{
	/* gpio + 0 is "mmc0_cd" (input/IRQ) */
	omap_cfg_reg(L8_34XX_GPIO63);
	mmc[0].gpio_cd = gpio + 0;
	twl4030_mmc_init(mmc);

	/*
	 * Most GPIOs are for USB OTG.  Some are mostly sent to
	 * the P2 connector; notably LEDA for the LCD backlight.
	 */

	/* TWL4030_GPIO_MAX + 1 == ledB (out, active low LED) */
	gpio_leds[2].gpio = gpio + TWL4030_GPIO_MAX + 1;

	platform_device_register(&leds_gpio);

	return 0;
}