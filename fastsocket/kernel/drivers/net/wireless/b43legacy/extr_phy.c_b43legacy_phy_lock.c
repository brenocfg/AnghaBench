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
struct TYPE_4__ {int phy_locked; } ;
struct b43legacy_wldev {int /*<<< orphan*/  wl; TYPE_3__* dev; TYPE_1__ phy; } ;
struct TYPE_5__ {int revision; } ;
struct TYPE_6__ {TYPE_2__ id; } ;

/* Variables and functions */
 int /*<<< orphan*/  B43legacy_WARN_ON (int) ; 
 int /*<<< orphan*/  NL80211_IFTYPE_AP ; 
 int /*<<< orphan*/  b43legacy_is_mode (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  b43legacy_mac_suspend (struct b43legacy_wldev*) ; 
 int /*<<< orphan*/  b43legacy_power_saving_ctl_bits (struct b43legacy_wldev*,int,int) ; 

void b43legacy_phy_lock(struct b43legacy_wldev *dev)
{
#if B43legacy_DEBUG
	B43legacy_WARN_ON(dev->phy.phy_locked);
	dev->phy.phy_locked = 1;
#endif

	if (dev->dev->id.revision < 3) {
		b43legacy_mac_suspend(dev);
	} else {
		if (!b43legacy_is_mode(dev->wl, NL80211_IFTYPE_AP))
			b43legacy_power_saving_ctl_bits(dev, -1, 1);
	}
}