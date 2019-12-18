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
typedef  int u16 ;
struct b43legacy_wldev {int /*<<< orphan*/  wl; TYPE_2__* dev; } ;
struct TYPE_3__ {int revision; } ;
struct TYPE_4__ {TYPE_1__ id; } ;

/* Variables and functions */
 int /*<<< orphan*/  B43legacy_MMIO_TSF_CFP_REP ; 
 int /*<<< orphan*/  B43legacy_MMIO_TSF_CFP_START ; 
 int /*<<< orphan*/  b43legacy_time_lock (struct b43legacy_wldev*) ; 
 int /*<<< orphan*/  b43legacy_time_unlock (struct b43legacy_wldev*) ; 
 int /*<<< orphan*/  b43legacy_write16 (struct b43legacy_wldev*,int,int) ; 
 int /*<<< orphan*/  b43legacy_write32 (struct b43legacy_wldev*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  b43legacydbg (int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static void b43legacy_set_beacon_int(struct b43legacy_wldev *dev,
				     u16 beacon_int)
{
	b43legacy_time_lock(dev);
	if (dev->dev->id.revision >= 3) {
		b43legacy_write32(dev, B43legacy_MMIO_TSF_CFP_REP,
				 (beacon_int << 16));
		b43legacy_write32(dev, B43legacy_MMIO_TSF_CFP_START,
				 (beacon_int << 10));
	} else {
		b43legacy_write16(dev, 0x606, (beacon_int >> 6));
		b43legacy_write16(dev, 0x610, beacon_int);
	}
	b43legacy_time_unlock(dev);
	b43legacydbg(dev->wl, "Set beacon interval to %u\n", beacon_int);
}