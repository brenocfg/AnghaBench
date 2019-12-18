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
typedef  int u32 ;
struct b43_phy {int rev; struct b43_phy_n* n; } ;
struct b43_wldev {struct b43_phy phy; } ;
struct b43_phy_n {TYPE_1__* pwr_ctl_info; } ;
typedef  int /*<<< orphan*/  s32 ;
struct TYPE_2__ {int idle_tssi_5g; int idle_tssi_2g; } ;

/* Variables and functions */
 int /*<<< orphan*/  N_RSSI_TSSI_2G ; 
 int /*<<< orphan*/  N_RSSI_W1 ; 
 scalar_t__ b43_nphy_ipa (struct b43_wldev*) ; 
 int /*<<< orphan*/  b43_nphy_ipa_internal_tssi_setup (struct b43_wldev*) ; 
 int b43_nphy_poll_rssi (struct b43_wldev*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  b43_nphy_rf_ctl_override (struct b43_wldev*,int,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  b43_nphy_rf_ctl_override_rev7 (struct b43_wldev*,int,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  b43_nphy_rssi_select (struct b43_wldev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  b43_nphy_stop_playback (struct b43_wldev*) ; 
 int /*<<< orphan*/  b43_nphy_tx_tone (struct b43_wldev*,int,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static void b43_nphy_tx_power_ctl_idle_tssi(struct b43_wldev *dev)
{
	struct b43_phy *phy = &dev->phy;
	struct b43_phy_n *nphy = dev->phy.n;

	u32 tmp;
	s32 rssi[4] = { };

	/* TODO: check if we can transmit */

	if (b43_nphy_ipa(dev))
		b43_nphy_ipa_internal_tssi_setup(dev);

	if (phy->rev >= 7)
		b43_nphy_rf_ctl_override_rev7(dev, 0x2000, 0, 3, false, 0);
	else if (phy->rev >= 3)
		b43_nphy_rf_ctl_override(dev, 0x2000, 0, 3, false);

	b43_nphy_stop_playback(dev);
	b43_nphy_tx_tone(dev, 0xFA0, 0, false, false);
	udelay(20);
	tmp = b43_nphy_poll_rssi(dev, N_RSSI_TSSI_2G, rssi, 1);
	b43_nphy_stop_playback(dev);
	b43_nphy_rssi_select(dev, 0, N_RSSI_W1);

	if (phy->rev >= 7)
		b43_nphy_rf_ctl_override_rev7(dev, 0x2000, 0, 3, true, 0);
	else if (phy->rev >= 3)
		b43_nphy_rf_ctl_override(dev, 0x2000, 0, 3, true);

	if (phy->rev >= 3) {
		nphy->pwr_ctl_info[0].idle_tssi_5g = (tmp >> 24) & 0xFF;
		nphy->pwr_ctl_info[1].idle_tssi_5g = (tmp >> 8) & 0xFF;
	} else {
		nphy->pwr_ctl_info[0].idle_tssi_5g = (tmp >> 16) & 0xFF;
		nphy->pwr_ctl_info[1].idle_tssi_5g = tmp & 0xFF;
	}
	nphy->pwr_ctl_info[0].idle_tssi_2g = (tmp >> 24) & 0xFF;
	nphy->pwr_ctl_info[1].idle_tssi_2g = (tmp >> 8) & 0xFF;
}