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
struct TYPE_3__ {int phy_locked; } ;
struct b43_wldev {int /*<<< orphan*/  wl; TYPE_2__* dev; TYPE_1__ phy; } ;
struct TYPE_4__ {int core_rev; } ;

/* Variables and functions */
 int /*<<< orphan*/  B43_PS_AWAKE ; 
 int /*<<< orphan*/  B43_WARN_ON (int) ; 
 int /*<<< orphan*/  NL80211_IFTYPE_AP ; 
 int /*<<< orphan*/  b43_is_mode (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  b43_power_saving_ctl_bits (struct b43_wldev*,int /*<<< orphan*/ ) ; 

void b43_phy_lock(struct b43_wldev *dev)
{
#if B43_DEBUG
	B43_WARN_ON(dev->phy.phy_locked);
	dev->phy.phy_locked = true;
#endif
	B43_WARN_ON(dev->dev->core_rev < 3);

	if (!b43_is_mode(dev->wl, NL80211_IFTYPE_AP))
		b43_power_saving_ctl_bits(dev, B43_PS_AWAKE);
}