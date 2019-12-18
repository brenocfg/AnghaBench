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
struct TYPE_2__ {int rev; struct b43_phy_lp* lp; } ;
struct b43_wldev {int /*<<< orphan*/  wl; TYPE_1__ phy; } ;
struct b43_phy_lp {int /*<<< orphan*/  rc_cap; } ;

/* Variables and functions */
 scalar_t__ IEEE80211_BAND_2GHZ ; 
 scalar_t__ b43_current_band (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lpphy_rev0_1_rc_calib (struct b43_wldev*) ; 
 int /*<<< orphan*/  lpphy_rev2plus_rc_calib (struct b43_wldev*) ; 
 int /*<<< orphan*/  lpphy_set_rc_cap (struct b43_wldev*) ; 

__attribute__((used)) static void lpphy_calibrate_rc(struct b43_wldev *dev)
{
	struct b43_phy_lp *lpphy = dev->phy.lp;

	if (dev->phy.rev >= 2) {
		lpphy_rev2plus_rc_calib(dev);
	} else if (!lpphy->rc_cap) {
		if (b43_current_band(dev->wl) == IEEE80211_BAND_2GHZ)
			lpphy_rev0_1_rc_calib(dev);
	} else {
		lpphy_set_rc_cap(dev);
	}
}