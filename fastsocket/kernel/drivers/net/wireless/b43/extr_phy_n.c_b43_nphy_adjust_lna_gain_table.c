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
typedef  int u8 ;
typedef  int u16 ;
struct TYPE_2__ {int channel; struct b43_phy_n* n; } ;
struct b43_wldev {TYPE_1__ phy; int /*<<< orphan*/  wl; } ;
struct b43_phy_n {scalar_t__ hang_avoid; scalar_t__ elna_gain_config; scalar_t__ gain_boost; } ;
typedef  int s16 ;

/* Variables and functions */
 int /*<<< orphan*/  B43_NPHY_C1_MINGAIN ; 
 int B43_NPHY_C1_MINGAIN_SHIFT ; 
 int /*<<< orphan*/  B43_NPHY_C1_MINMAX_GAIN ; 
 int /*<<< orphan*/  B43_NPHY_C2_MINGAIN ; 
 int B43_NPHY_C2_MINGAIN_SHIFT ; 
 int /*<<< orphan*/  B43_NPHY_C2_MINMAX_GAIN ; 
 int /*<<< orphan*/  B43_NTAB16 (int,int) ; 
 scalar_t__ IEEE80211_BAND_2GHZ ; 
 scalar_t__ b43_current_band (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  b43_nphy_stay_in_carrier_search (struct b43_wldev*,int) ; 
 int /*<<< orphan*/  b43_ntab_write_bulk (struct b43_wldev*,int /*<<< orphan*/ ,int,int*) ; 
 int /*<<< orphan*/  b43_phy_maskset (struct b43_wldev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void b43_nphy_adjust_lna_gain_table(struct b43_wldev *dev)
{
	struct b43_phy_n *nphy = dev->phy.n;

	u8 i;
	s16 tmp;
	u16 data[4];
	s16 gain[2];
	u16 minmax[2];
	static const u16 lna_gain[4] = { -2, 10, 19, 25 };

	if (nphy->hang_avoid)
		b43_nphy_stay_in_carrier_search(dev, 1);

	if (nphy->gain_boost) {
		if (b43_current_band(dev->wl) == IEEE80211_BAND_2GHZ) {
			gain[0] = 6;
			gain[1] = 6;
		} else {
			tmp = 40370 - 315 * dev->phy.channel;
			gain[0] = ((tmp >> 13) + ((tmp >> 12) & 1));
			tmp = 23242 - 224 * dev->phy.channel;
			gain[1] = ((tmp >> 13) + ((tmp >> 12) & 1));
		}
	} else {
		gain[0] = 0;
		gain[1] = 0;
	}

	for (i = 0; i < 2; i++) {
		if (nphy->elna_gain_config) {
			data[0] = 19 + gain[i];
			data[1] = 25 + gain[i];
			data[2] = 25 + gain[i];
			data[3] = 25 + gain[i];
		} else {
			data[0] = lna_gain[0] + gain[i];
			data[1] = lna_gain[1] + gain[i];
			data[2] = lna_gain[2] + gain[i];
			data[3] = lna_gain[3] + gain[i];
		}
		b43_ntab_write_bulk(dev, B43_NTAB16(i, 8), 4, data);

		minmax[i] = 23 + gain[i];
	}

	b43_phy_maskset(dev, B43_NPHY_C1_MINMAX_GAIN, ~B43_NPHY_C1_MINGAIN,
				minmax[0] << B43_NPHY_C1_MINGAIN_SHIFT);
	b43_phy_maskset(dev, B43_NPHY_C2_MINMAX_GAIN, ~B43_NPHY_C2_MINGAIN,
				minmax[1] << B43_NPHY_C2_MINGAIN_SHIFT);

	if (nphy->hang_avoid)
		b43_nphy_stay_in_carrier_search(dev, 0);
}