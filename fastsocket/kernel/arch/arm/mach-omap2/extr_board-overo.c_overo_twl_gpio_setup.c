#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct device {int dummy; } ;
struct TYPE_5__ {int /*<<< orphan*/  dev; } ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 TYPE_1__* mmc ; 
 TYPE_2__ overo_vmmc1_supply ; 
 int /*<<< orphan*/  twl4030_mmc_init (TYPE_1__*) ; 

__attribute__((used)) static int overo_twl_gpio_setup(struct device *dev,
		unsigned gpio, unsigned ngpio)
{
	twl4030_mmc_init(mmc);

	overo_vmmc1_supply.dev = mmc[0].dev;

	return 0;
}