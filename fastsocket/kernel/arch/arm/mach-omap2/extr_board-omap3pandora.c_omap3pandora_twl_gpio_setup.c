#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct device {int dummy; } ;
struct TYPE_7__ {int /*<<< orphan*/  dev; } ;
struct TYPE_6__ {int /*<<< orphan*/  dev; } ;
struct TYPE_5__ {unsigned int gpio_cd; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 TYPE_1__* omap3pandora_mmc ; 
 TYPE_3__ pandora_vmmc1_supply ; 
 TYPE_2__ pandora_vmmc2_supply ; 
 int /*<<< orphan*/  twl4030_mmc_init (TYPE_1__*) ; 

__attribute__((used)) static int omap3pandora_twl_gpio_setup(struct device *dev,
		unsigned gpio, unsigned ngpio)
{
	/* gpio + {0,1} is "mmc{0,1}_cd" (input/IRQ) */
	omap3pandora_mmc[0].gpio_cd = gpio + 0;
	omap3pandora_mmc[1].gpio_cd = gpio + 1;
	twl4030_mmc_init(omap3pandora_mmc);

	/* link regulators to MMC adapters */
	pandora_vmmc1_supply.dev = omap3pandora_mmc[0].dev;
	pandora_vmmc2_supply.dev = omap3pandora_mmc[1].dev;

	return 0;
}