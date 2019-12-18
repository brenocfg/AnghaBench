#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_4__ {scalar_t__ type; } ;
struct b43_wldev {TYPE_1__* dev; TYPE_2__ phy; } ;
struct TYPE_3__ {int bus_type; int /*<<< orphan*/  sdev; int /*<<< orphan*/  bdev; } ;

/* Variables and functions */
#define  B43_BUS_BCMA 129 
#define  B43_BUS_SSB 128 
 scalar_t__ B43_PHYTYPE_HT ; 
 scalar_t__ B43_PHYTYPE_N ; 
 int /*<<< orphan*/  BCMA_IOCTL ; 
 int /*<<< orphan*/  BCMA_IOCTL_FGC ; 
 int /*<<< orphan*/  SSB_TMSLOW ; 
 int /*<<< orphan*/  SSB_TMSLOW_FGC ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  bcma_aread32 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bcma_awrite32 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ssb_read32 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ssb_write32 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void b43_phy_force_clock(struct b43_wldev *dev, bool force)
{
	u32 tmp;

	WARN_ON(dev->phy.type != B43_PHYTYPE_N &&
		dev->phy.type != B43_PHYTYPE_HT);

	switch (dev->dev->bus_type) {
#ifdef CONFIG_B43_BCMA
	case B43_BUS_BCMA:
		tmp = bcma_aread32(dev->dev->bdev, BCMA_IOCTL);
		if (force)
			tmp |= BCMA_IOCTL_FGC;
		else
			tmp &= ~BCMA_IOCTL_FGC;
		bcma_awrite32(dev->dev->bdev, BCMA_IOCTL, tmp);
		break;
#endif
#ifdef CONFIG_B43_SSB
	case B43_BUS_SSB:
		tmp = ssb_read32(dev->dev->sdev, SSB_TMSLOW);
		if (force)
			tmp |= SSB_TMSLOW_FGC;
		else
			tmp &= ~SSB_TMSLOW_FGC;
		ssb_write32(dev->dev->sdev, SSB_TMSLOW, tmp);
		break;
#endif
	}
}