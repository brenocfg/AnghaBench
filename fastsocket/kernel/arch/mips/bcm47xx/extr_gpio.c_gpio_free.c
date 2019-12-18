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
struct TYPE_2__ {int /*<<< orphan*/  extif; int /*<<< orphan*/  chipco; } ;

/* Variables and functions */
 unsigned int BCM47XX_CHIPCO_GPIO_LINES ; 
 unsigned int BCM47XX_EXTIF_GPIO_LINES ; 
 int /*<<< orphan*/  clear_bit (unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gpio_in_use ; 
 TYPE_1__ ssb_bcm47xx ; 
 scalar_t__ ssb_chipco_available (int /*<<< orphan*/ *) ; 
 scalar_t__ ssb_extif_available (int /*<<< orphan*/ *) ; 

void gpio_free(unsigned gpio)
{
	if (ssb_chipco_available(&ssb_bcm47xx.chipco) &&
	    ((unsigned)gpio >= BCM47XX_CHIPCO_GPIO_LINES))
		return;

	if (ssb_extif_available(&ssb_bcm47xx.extif) &&
	    ((unsigned)gpio >= BCM47XX_EXTIF_GPIO_LINES))
		return;

	clear_bit(gpio, gpio_in_use);
}