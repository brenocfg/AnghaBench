#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int u32 ;
struct b43legacy_wldev {int dummy; } ;

/* Variables and functions */
 int B43legacy_MACCTL_RADIOLOCK ; 
 int /*<<< orphan*/  B43legacy_MMIO_MACCTL ; 
 int /*<<< orphan*/  B43legacy_WARN_ON (int) ; 
 int b43legacy_read32 (struct b43legacy_wldev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  b43legacy_write32 (struct b43legacy_wldev*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mmiowb () ; 
 int /*<<< orphan*/  udelay (int) ; 

void b43legacy_radio_lock(struct b43legacy_wldev *dev)
{
	u32 status;

	status = b43legacy_read32(dev, B43legacy_MMIO_MACCTL);
	B43legacy_WARN_ON(status & B43legacy_MACCTL_RADIOLOCK);
	status |= B43legacy_MACCTL_RADIOLOCK;
	b43legacy_write32(dev, B43legacy_MMIO_MACCTL, status);
	mmiowb();
	udelay(10);
}