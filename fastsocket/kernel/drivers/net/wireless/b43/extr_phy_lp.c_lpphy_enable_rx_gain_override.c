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
struct TYPE_2__ {int rev; } ;
struct b43_wldev {int /*<<< orphan*/  wl; TYPE_1__ phy; } ;

/* Variables and functions */
 int /*<<< orphan*/  B43_LPPHY_RF_OVERRIDE_0 ; 
 int /*<<< orphan*/  B43_LPPHY_RF_OVERRIDE_2 ; 
 int /*<<< orphan*/  B43_PHY_OFDM (int) ; 
 scalar_t__ IEEE80211_BAND_2GHZ ; 
 scalar_t__ b43_current_band (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  b43_phy_set (struct b43_wldev*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void lpphy_enable_rx_gain_override(struct b43_wldev *dev)
{
	b43_phy_set(dev, B43_LPPHY_RF_OVERRIDE_0, 0x1);
	b43_phy_set(dev, B43_LPPHY_RF_OVERRIDE_0, 0x10);
	b43_phy_set(dev, B43_LPPHY_RF_OVERRIDE_0, 0x40);
	if (dev->phy.rev >= 2) {
		b43_phy_set(dev, B43_LPPHY_RF_OVERRIDE_2, 0x100);
		if (b43_current_band(dev->wl) == IEEE80211_BAND_2GHZ) {
			b43_phy_set(dev, B43_LPPHY_RF_OVERRIDE_2, 0x400);
			b43_phy_set(dev, B43_PHY_OFDM(0xE5), 0x8);
		}
	} else {
		b43_phy_set(dev, B43_LPPHY_RF_OVERRIDE_2, 0x200);
	}
}