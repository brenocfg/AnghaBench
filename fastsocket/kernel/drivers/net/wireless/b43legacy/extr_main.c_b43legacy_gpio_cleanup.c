#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct ssb_device {int dummy; } ;
struct TYPE_6__ {scalar_t__ dev; } ;
struct TYPE_5__ {struct ssb_device* dev; } ;
struct ssb_bus {TYPE_3__ chipco; TYPE_2__ pcicore; } ;
struct b43legacy_wldev {TYPE_1__* dev; } ;
struct TYPE_4__ {struct ssb_bus* bus; } ;

/* Variables and functions */
 int /*<<< orphan*/  B43legacy_GPIO_CONTROL ; 
 int /*<<< orphan*/  ssb_write32 (struct ssb_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void b43legacy_gpio_cleanup(struct b43legacy_wldev *dev)
{
	struct ssb_bus *bus = dev->dev->bus;
	struct ssb_device *gpiodev, *pcidev = NULL;

#ifdef CONFIG_SSB_DRIVER_PCICORE
	pcidev = bus->pcicore.dev;
#endif
	gpiodev = bus->chipco.dev ? : pcidev;
	if (!gpiodev)
		return;
	ssb_write32(gpiodev, B43legacy_GPIO_CONTROL, 0);
}