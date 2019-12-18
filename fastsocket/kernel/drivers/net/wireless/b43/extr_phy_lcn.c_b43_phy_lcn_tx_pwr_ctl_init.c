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
typedef  int u8 ;
struct lcn_tx_gains {int gm_gain; int pga_gain; int pad_gain; scalar_t__ dac_gain; } ;
struct TYPE_3__ {TYPE_2__* lcn; } ;
struct b43_wldev {int /*<<< orphan*/  wl; TYPE_1__ phy; } ;
struct TYPE_4__ {int /*<<< orphan*/  hw_pwr_ctl_capable; } ;

/* Variables and functions */
 int /*<<< orphan*/  B43_SENSE_TEMP ; 
 scalar_t__ IEEE80211_BAND_2GHZ ; 
 scalar_t__ b43_current_band (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  b43_mac_enable (struct b43_wldev*) ; 
 int /*<<< orphan*/  b43_mac_suspend (struct b43_wldev*) ; 
 int /*<<< orphan*/  b43_phy_lcn_sense_setup (struct b43_wldev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  b43_phy_lcn_set_bbmult (struct b43_wldev*,int) ; 
 int /*<<< orphan*/  b43_phy_lcn_set_tx_gain (struct b43_wldev*,struct lcn_tx_gains*) ; 
 int /*<<< orphan*/  b43err (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void b43_phy_lcn_tx_pwr_ctl_init(struct b43_wldev *dev)
{
	struct lcn_tx_gains tx_gains;
	u8 bbmult;

	b43_mac_suspend(dev);

	if (!dev->phy.lcn->hw_pwr_ctl_capable) {
		if (b43_current_band(dev->wl) == IEEE80211_BAND_2GHZ) {
			tx_gains.gm_gain = 4;
			tx_gains.pga_gain = 12;
			tx_gains.pad_gain = 12;
			tx_gains.dac_gain = 0;
			bbmult = 150;
		} else {
			tx_gains.gm_gain = 7;
			tx_gains.pga_gain = 15;
			tx_gains.pad_gain = 14;
			tx_gains.dac_gain = 0;
			bbmult = 150;
		}
		b43_phy_lcn_set_tx_gain(dev, &tx_gains);
		b43_phy_lcn_set_bbmult(dev, bbmult);
		b43_phy_lcn_sense_setup(dev, B43_SENSE_TEMP);
	} else {
		b43err(dev->wl, "TX power control not supported for this HW\n");
	}

	b43_mac_enable(dev);
}