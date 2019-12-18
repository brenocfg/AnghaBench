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
struct lpphy_tx_gains {int gm; int pad; int pga; scalar_t__ dac; } ;
struct b43_wldev {int /*<<< orphan*/  wl; } ;

/* Variables and functions */
 scalar_t__ IEEE80211_BAND_2GHZ ; 
 scalar_t__ b43_current_band (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lpphy_set_bb_mult (struct b43_wldev*,int) ; 
 int /*<<< orphan*/  lpphy_set_tx_gains (struct b43_wldev*,struct lpphy_tx_gains) ; 

__attribute__((used)) static void lpphy_tx_pctl_init_sw(struct b43_wldev *dev)
{
	struct lpphy_tx_gains gains;

	if (b43_current_band(dev->wl) == IEEE80211_BAND_2GHZ) {
		gains.gm = 4;
		gains.pad = 12;
		gains.pga = 12;
		gains.dac = 0;
	} else {
		gains.gm = 7;
		gains.pad = 14;
		gains.pga = 15;
		gains.dac = 0;
	}
	lpphy_set_tx_gains(dev, gains);
	lpphy_set_bb_mult(dev, 150);
}