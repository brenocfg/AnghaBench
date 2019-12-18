#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u16 ;
struct TYPE_8__ {int rev; struct b43_phy_n* n; } ;
struct b43_wldev {TYPE_4__ phy; int /*<<< orphan*/  wl; } ;
struct TYPE_7__ {int /*<<< orphan*/ * rssical_phy_regs_5G; int /*<<< orphan*/ * rssical_radio_regs_5G; int /*<<< orphan*/ * rssical_phy_regs_2G; int /*<<< orphan*/ * rssical_radio_regs_2G; } ;
struct TYPE_6__ {int /*<<< orphan*/  center_freq; } ;
struct TYPE_5__ {int /*<<< orphan*/  center_freq; } ;
struct b43_phy_n {TYPE_3__ rssical_cache; TYPE_2__ rssical_chanspec_5G; TYPE_1__ rssical_chanspec_2G; } ;

/* Variables and functions */
 int B2056_RX0 ; 
 int B2056_RX1 ; 
 int B2056_RX_RSSI_MISC ; 
 int /*<<< orphan*/  B43_NPHY_RSSIMC_0I_RSSI_X ; 
 int /*<<< orphan*/  B43_NPHY_RSSIMC_0I_RSSI_Y ; 
 int /*<<< orphan*/  B43_NPHY_RSSIMC_0I_RSSI_Z ; 
 int /*<<< orphan*/  B43_NPHY_RSSIMC_0Q_RSSI_X ; 
 int /*<<< orphan*/  B43_NPHY_RSSIMC_0Q_RSSI_Y ; 
 int /*<<< orphan*/  B43_NPHY_RSSIMC_0Q_RSSI_Z ; 
 int /*<<< orphan*/  B43_NPHY_RSSIMC_1I_RSSI_X ; 
 int /*<<< orphan*/  B43_NPHY_RSSIMC_1I_RSSI_Y ; 
 int /*<<< orphan*/  B43_NPHY_RSSIMC_1I_RSSI_Z ; 
 int /*<<< orphan*/  B43_NPHY_RSSIMC_1Q_RSSI_X ; 
 int /*<<< orphan*/  B43_NPHY_RSSIMC_1Q_RSSI_Y ; 
 int /*<<< orphan*/  B43_NPHY_RSSIMC_1Q_RSSI_Z ; 
 scalar_t__ IEEE80211_BAND_2GHZ ; 
 scalar_t__ b43_current_band (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  b43_phy_write (struct b43_wldev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  b43_radio_maskset (struct b43_wldev*,int,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void b43_nphy_restore_rssi_cal(struct b43_wldev *dev)
{
	struct b43_phy_n *nphy = dev->phy.n;

	u16 *rssical_radio_regs = NULL;
	u16 *rssical_phy_regs = NULL;

	if (b43_current_band(dev->wl) == IEEE80211_BAND_2GHZ) {
		if (!nphy->rssical_chanspec_2G.center_freq)
			return;
		rssical_radio_regs = nphy->rssical_cache.rssical_radio_regs_2G;
		rssical_phy_regs = nphy->rssical_cache.rssical_phy_regs_2G;
	} else {
		if (!nphy->rssical_chanspec_5G.center_freq)
			return;
		rssical_radio_regs = nphy->rssical_cache.rssical_radio_regs_5G;
		rssical_phy_regs = nphy->rssical_cache.rssical_phy_regs_5G;
	}

	if (dev->phy.rev >= 7) {
	} else {
		b43_radio_maskset(dev, B2056_RX0 | B2056_RX_RSSI_MISC, 0xE3,
				  rssical_radio_regs[0]);
		b43_radio_maskset(dev, B2056_RX1 | B2056_RX_RSSI_MISC, 0xE3,
				  rssical_radio_regs[1]);
	}

	b43_phy_write(dev, B43_NPHY_RSSIMC_0I_RSSI_Z, rssical_phy_regs[0]);
	b43_phy_write(dev, B43_NPHY_RSSIMC_0Q_RSSI_Z, rssical_phy_regs[1]);
	b43_phy_write(dev, B43_NPHY_RSSIMC_1I_RSSI_Z, rssical_phy_regs[2]);
	b43_phy_write(dev, B43_NPHY_RSSIMC_1Q_RSSI_Z, rssical_phy_regs[3]);

	b43_phy_write(dev, B43_NPHY_RSSIMC_0I_RSSI_X, rssical_phy_regs[4]);
	b43_phy_write(dev, B43_NPHY_RSSIMC_0Q_RSSI_X, rssical_phy_regs[5]);
	b43_phy_write(dev, B43_NPHY_RSSIMC_1I_RSSI_X, rssical_phy_regs[6]);
	b43_phy_write(dev, B43_NPHY_RSSIMC_1Q_RSSI_X, rssical_phy_regs[7]);

	b43_phy_write(dev, B43_NPHY_RSSIMC_0I_RSSI_Y, rssical_phy_regs[8]);
	b43_phy_write(dev, B43_NPHY_RSSIMC_0Q_RSSI_Y, rssical_phy_regs[9]);
	b43_phy_write(dev, B43_NPHY_RSSIMC_1I_RSSI_Y, rssical_phy_regs[10]);
	b43_phy_write(dev, B43_NPHY_RSSIMC_1Q_RSSI_Y, rssical_phy_regs[11]);
}