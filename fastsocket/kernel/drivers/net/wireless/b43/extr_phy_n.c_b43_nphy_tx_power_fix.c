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
typedef  int u32 ;
typedef  int u16 ;
struct ssb_sprom {int revision; int* txpid2g; int* txpid5gl; int* txpid5g; int* txpid5gh; } ;
struct TYPE_4__ {int channel_freq; int rev; struct b43_phy_n* n; } ;
struct b43_wldev {TYPE_2__ phy; int /*<<< orphan*/  wl; TYPE_1__* dev; } ;
struct b43_phy_n {scalar_t__ hang_avoid; } ;
struct TYPE_3__ {struct ssb_sprom* bus_sprom; } ;

/* Variables and functions */
 int /*<<< orphan*/  B43_NPHY_AFECTL_DACGAIN1 ; 
 int /*<<< orphan*/  B43_NPHY_AFECTL_DACGAIN2 ; 
 int B43_NPHY_AFECTL_OVER ; 
 int B43_NPHY_AFECTL_OVER1 ; 
 int /*<<< orphan*/  B43_NPHY_BPHY_CTL2 ; 
 int /*<<< orphan*/  B43_NPHY_BPHY_CTL2_LUT ; 
 int B43_NPHY_PAPD_EN0 ; 
 int B43_NPHY_PAPD_EN1 ; 
 int /*<<< orphan*/  B43_NTAB16 (int,int) ; 
 int /*<<< orphan*/  B43_NTAB32 (int,int) ; 
 scalar_t__ IEEE80211_BAND_2GHZ ; 
 scalar_t__ b43_current_band (int /*<<< orphan*/ ) ; 
 int* b43_nphy_get_tx_gain_table (struct b43_wldev*) ; 
 scalar_t__ b43_nphy_ipa (struct b43_wldev*) ; 
 int /*<<< orphan*/  b43_nphy_stay_in_carrier_search (struct b43_wldev*,int) ; 
 int b43_ntab_read (struct b43_wldev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  b43_ntab_write (struct b43_wldev*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  b43_phy_mask (struct b43_wldev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  b43_phy_maskset (struct b43_wldev*,int,int,int) ; 
 int /*<<< orphan*/  b43_phy_set (struct b43_wldev*,int,int) ; 
 int /*<<< orphan*/  b43_phy_write (struct b43_wldev*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void b43_nphy_tx_power_fix(struct b43_wldev *dev)
{
	struct b43_phy_n *nphy = dev->phy.n;
	struct ssb_sprom *sprom = dev->dev->bus_sprom;

	u8 txpi[2], bbmult, i;
	u16 tmp, radio_gain, dac_gain;
	u16 freq = dev->phy.channel_freq;
	u32 txgain;
	/* u32 gaintbl; rev3+ */

	if (nphy->hang_avoid)
		b43_nphy_stay_in_carrier_search(dev, 1);

	if (dev->phy.rev >= 7) {
		txpi[0] = txpi[1] = 30;
	} else if (dev->phy.rev >= 3) {
		txpi[0] = 40;
		txpi[1] = 40;
	} else if (sprom->revision < 4) {
		txpi[0] = 72;
		txpi[1] = 72;
	} else {
		if (b43_current_band(dev->wl) == IEEE80211_BAND_2GHZ) {
			txpi[0] = sprom->txpid2g[0];
			txpi[1] = sprom->txpid2g[1];
		} else if (freq >= 4900 && freq < 5100) {
			txpi[0] = sprom->txpid5gl[0];
			txpi[1] = sprom->txpid5gl[1];
		} else if (freq >= 5100 && freq < 5500) {
			txpi[0] = sprom->txpid5g[0];
			txpi[1] = sprom->txpid5g[1];
		} else if (freq >= 5500) {
			txpi[0] = sprom->txpid5gh[0];
			txpi[1] = sprom->txpid5gh[1];
		} else {
			txpi[0] = 91;
			txpi[1] = 91;
		}
	}
	if (dev->phy.rev < 7 &&
	    (txpi[0] < 40 || txpi[0] > 100 || txpi[1] < 40 || txpi[1] > 100))
		txpi[0] = txpi[1] = 91;

	/*
	for (i = 0; i < 2; i++) {
		nphy->txpwrindex[i].index_internal = txpi[i];
		nphy->txpwrindex[i].index_internal_save = txpi[i];
	}
	*/

	for (i = 0; i < 2; i++) {
		txgain = *(b43_nphy_get_tx_gain_table(dev) + txpi[i]);

		if (dev->phy.rev >= 3)
			radio_gain = (txgain >> 16) & 0x1FFFF;
		else
			radio_gain = (txgain >> 16) & 0x1FFF;

		if (dev->phy.rev >= 7)
			dac_gain = (txgain >> 8) & 0x7;
		else
			dac_gain = (txgain >> 8) & 0x3F;
		bbmult = txgain & 0xFF;

		if (dev->phy.rev >= 3) {
			if (i == 0)
				b43_phy_set(dev, B43_NPHY_AFECTL_OVER1, 0x0100);
			else
				b43_phy_set(dev, B43_NPHY_AFECTL_OVER, 0x0100);
		} else {
			b43_phy_set(dev, B43_NPHY_AFECTL_OVER, 0x4000);
		}

		if (i == 0)
			b43_phy_write(dev, B43_NPHY_AFECTL_DACGAIN1, dac_gain);
		else
			b43_phy_write(dev, B43_NPHY_AFECTL_DACGAIN2, dac_gain);

		b43_ntab_write(dev, B43_NTAB16(0x7, 0x110 + i), radio_gain);

		tmp = b43_ntab_read(dev, B43_NTAB16(0xF, 0x57));
		if (i == 0)
			tmp = (tmp & 0x00FF) | (bbmult << 8);
		else
			tmp = (tmp & 0xFF00) | bbmult;
		b43_ntab_write(dev, B43_NTAB16(0xF, 0x57), tmp);

		if (b43_nphy_ipa(dev)) {
			u32 tmp32;
			u16 reg = (i == 0) ?
				B43_NPHY_PAPD_EN0 : B43_NPHY_PAPD_EN1;
			tmp32 = b43_ntab_read(dev, B43_NTAB32(26 + i,
							      576 + txpi[i]));
			b43_phy_maskset(dev, reg, 0xE00F, (u32) tmp32 << 4);
			b43_phy_set(dev, reg, 0x4);
		}
	}

	b43_phy_mask(dev, B43_NPHY_BPHY_CTL2, ~B43_NPHY_BPHY_CTL2_LUT);

	if (nphy->hang_avoid)
		b43_nphy_stay_in_carrier_search(dev, 0);
}