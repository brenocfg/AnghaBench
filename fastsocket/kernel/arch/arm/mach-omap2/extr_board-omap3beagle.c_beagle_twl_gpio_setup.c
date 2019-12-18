#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_5__ ;
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct device {int dummy; } ;
struct TYPE_9__ {int /*<<< orphan*/  dev; } ;
struct TYPE_8__ {int /*<<< orphan*/  dev; } ;
struct TYPE_7__ {unsigned int gpio; } ;
struct TYPE_6__ {int gpio_wp; unsigned int gpio_cd; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  AG9_34XX_GPIO23 ; 
 int /*<<< orphan*/  AH8_34XX_GPIO29 ; 
 unsigned int TWL4030_GPIO_MAX ; 
 TYPE_5__ beagle_vmmc1_supply ; 
 TYPE_4__ beagle_vsim_supply ; 
 int /*<<< orphan*/  gpio_direction_input (unsigned int) ; 
 int /*<<< orphan*/  gpio_direction_output (unsigned int,int /*<<< orphan*/ ) ; 
 TYPE_3__* gpio_leds ; 
 int /*<<< orphan*/  gpio_request (unsigned int,char*) ; 
 TYPE_1__* mmc ; 
 int /*<<< orphan*/  omap_cfg_reg (int /*<<< orphan*/ ) ; 
 int system_rev ; 
 int /*<<< orphan*/  twl4030_mmc_init (TYPE_1__*) ; 

__attribute__((used)) static int beagle_twl_gpio_setup(struct device *dev,
		unsigned gpio, unsigned ngpio)
{
	if (system_rev >= 0x20 && system_rev <= 0x34301000) {
		omap_cfg_reg(AG9_34XX_GPIO23);
		mmc[0].gpio_wp = 23;
	} else {
		omap_cfg_reg(AH8_34XX_GPIO29);
	}
	/* gpio + 0 is "mmc0_cd" (input/IRQ) */
	mmc[0].gpio_cd = gpio + 0;
	twl4030_mmc_init(mmc);

	/* link regulators to MMC adapters */
	beagle_vmmc1_supply.dev = mmc[0].dev;
	beagle_vsim_supply.dev = mmc[0].dev;

	/* REVISIT: need ehci-omap hooks for external VBUS
	 * power switch and overcurrent detect
	 */

	gpio_request(gpio + 1, "EHCI_nOC");
	gpio_direction_input(gpio + 1);

	/* TWL4030_GPIO_MAX + 0 == ledA, EHCI nEN_USB_PWR (out, active low) */
	gpio_request(gpio + TWL4030_GPIO_MAX, "nEN_USB_PWR");
	gpio_direction_output(gpio + TWL4030_GPIO_MAX, 0);

	/* TWL4030_GPIO_MAX + 1 == ledB, PMU_STAT (out, active low LED) */
	gpio_leds[2].gpio = gpio + TWL4030_GPIO_MAX + 1;

	return 0;
}