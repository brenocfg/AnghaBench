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
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_2__ {int radio_locked; } ;
struct b43_wldev {TYPE_1__ phy; } ;

/* Variables and functions */
 int /*<<< orphan*/  B43_MACCTL_RADIOLOCK ; 
 int /*<<< orphan*/  B43_MMIO_MACCTL ; 
 int /*<<< orphan*/  B43_WARN_ON (int) ; 
 int /*<<< orphan*/  b43_read32 (struct b43_wldev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  b43_write32 (struct b43_wldev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  udelay (int) ; 

void b43_radio_lock(struct b43_wldev *dev)
{
	u32 macctl;

#if B43_DEBUG
	B43_WARN_ON(dev->phy.radio_locked);
	dev->phy.radio_locked = true;
#endif

	macctl = b43_read32(dev, B43_MMIO_MACCTL);
	macctl |= B43_MACCTL_RADIOLOCK;
	b43_write32(dev, B43_MMIO_MACCTL, macctl);
	/* Commit the write and wait for the firmware
	 * to finish any radio register access. */
	b43_read32(dev, B43_MMIO_MACCTL);
	udelay(10);
}