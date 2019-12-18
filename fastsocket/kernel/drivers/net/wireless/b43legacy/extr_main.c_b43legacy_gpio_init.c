#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct ssb_device {int dummy; } ;
struct TYPE_10__ {scalar_t__ dev; } ;
struct TYPE_9__ {struct ssb_device* dev; } ;
struct TYPE_6__ {int boardflags_lo; } ;
struct ssb_bus {int chip_id; TYPE_5__ chipco; TYPE_4__ pcicore; TYPE_1__ sprom; } ;
struct b43legacy_wldev {TYPE_3__* dev; } ;
struct TYPE_7__ {int revision; } ;
struct TYPE_8__ {TYPE_2__ id; struct ssb_bus* bus; } ;

/* Variables and functions */
 int B43legacy_BFL_PACTRL ; 
 int /*<<< orphan*/  B43legacy_GPIO_CONTROL ; 
 int /*<<< orphan*/  B43legacy_MMIO_GPIO_MASK ; 
 int /*<<< orphan*/  B43legacy_MMIO_MACCTL ; 
 int b43legacy_read16 (struct b43legacy_wldev*,int /*<<< orphan*/ ) ; 
 int b43legacy_read32 (struct b43legacy_wldev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  b43legacy_write16 (struct b43legacy_wldev*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  b43legacy_write32 (struct b43legacy_wldev*,int /*<<< orphan*/ ,int) ; 
 int ssb_read32 (struct ssb_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ssb_write32 (struct ssb_device*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int b43legacy_gpio_init(struct b43legacy_wldev *dev)
{
	struct ssb_bus *bus = dev->dev->bus;
	struct ssb_device *gpiodev, *pcidev = NULL;
	u32 mask;
	u32 set;

	b43legacy_write32(dev, B43legacy_MMIO_MACCTL,
			  b43legacy_read32(dev,
			  B43legacy_MMIO_MACCTL)
			  & 0xFFFF3FFF);

	b43legacy_write16(dev, B43legacy_MMIO_GPIO_MASK,
			  b43legacy_read16(dev,
			  B43legacy_MMIO_GPIO_MASK)
			  | 0x000F);

	mask = 0x0000001F;
	set = 0x0000000F;
	if (dev->dev->bus->chip_id == 0x4301) {
		mask |= 0x0060;
		set |= 0x0060;
	}
	if (dev->dev->bus->sprom.boardflags_lo & B43legacy_BFL_PACTRL) {
		b43legacy_write16(dev, B43legacy_MMIO_GPIO_MASK,
				  b43legacy_read16(dev,
				  B43legacy_MMIO_GPIO_MASK)
				  | 0x0200);
		mask |= 0x0200;
		set |= 0x0200;
	}
	if (dev->dev->id.revision >= 2)
		mask  |= 0x0010; /* FIXME: This is redundant. */

#ifdef CONFIG_SSB_DRIVER_PCICORE
	pcidev = bus->pcicore.dev;
#endif
	gpiodev = bus->chipco.dev ? : pcidev;
	if (!gpiodev)
		return 0;
	ssb_write32(gpiodev, B43legacy_GPIO_CONTROL,
		    (ssb_read32(gpiodev, B43legacy_GPIO_CONTROL)
		     & ~mask) | set);

	return 0;
}