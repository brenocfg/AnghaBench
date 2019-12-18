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
struct ieee80211_channel {scalar_t__ band; int hw_value; } ;
struct b43_wldev {int dummy; } ;
struct b43_phy_ht_channeltab_e_phy {int bw1; int bw2; int bw3; int bw4; int bw5; int bw6; } ;

/* Variables and functions */
 int /*<<< orphan*/  B43_PHY_HT_BANDCTL ; 
 int B43_PHY_HT_BW1 ; 
 int B43_PHY_HT_BW2 ; 
 int B43_PHY_HT_BW3 ; 
 int B43_PHY_HT_BW4 ; 
 int B43_PHY_HT_BW5 ; 
 int B43_PHY_HT_BW6 ; 
 int /*<<< orphan*/  B43_PHY_HT_CLASS_CTL_OFDM_EN ; 
 int /*<<< orphan*/  B43_PHY_HT_TEST ; 
 scalar_t__ IEEE80211_BAND_2GHZ ; 
 scalar_t__ IEEE80211_BAND_5GHZ ; 
 int /*<<< orphan*/  b43_phy_ht_classifier (struct b43_wldev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  b43_phy_ht_spur_avoid (struct b43_wldev*,struct ieee80211_channel*) ; 
 int /*<<< orphan*/  b43_phy_ht_tx_power_fix (struct b43_wldev*) ; 
 int /*<<< orphan*/  b43_phy_mask (struct b43_wldev*,int /*<<< orphan*/ ,int) ; 
 int b43_phy_read (struct b43_wldev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  b43_phy_set (struct b43_wldev*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  b43_phy_write (struct b43_wldev*,int,int) ; 

__attribute__((used)) static void b43_phy_ht_channel_setup(struct b43_wldev *dev,
				const struct b43_phy_ht_channeltab_e_phy *e,
				struct ieee80211_channel *new_channel)
{
	bool old_band_5ghz;

	old_band_5ghz = b43_phy_read(dev, B43_PHY_HT_BANDCTL) & 0; /* FIXME */
	if (new_channel->band == IEEE80211_BAND_5GHZ && !old_band_5ghz) {
		/* TODO */
	} else if (new_channel->band == IEEE80211_BAND_2GHZ && old_band_5ghz) {
		/* TODO */
	}

	b43_phy_write(dev, B43_PHY_HT_BW1, e->bw1);
	b43_phy_write(dev, B43_PHY_HT_BW2, e->bw2);
	b43_phy_write(dev, B43_PHY_HT_BW3, e->bw3);
	b43_phy_write(dev, B43_PHY_HT_BW4, e->bw4);
	b43_phy_write(dev, B43_PHY_HT_BW5, e->bw5);
	b43_phy_write(dev, B43_PHY_HT_BW6, e->bw6);

	if (new_channel->hw_value == 14) {
		b43_phy_ht_classifier(dev, B43_PHY_HT_CLASS_CTL_OFDM_EN, 0);
		b43_phy_set(dev, B43_PHY_HT_TEST, 0x0800);
	} else {
		b43_phy_ht_classifier(dev, B43_PHY_HT_CLASS_CTL_OFDM_EN,
				      B43_PHY_HT_CLASS_CTL_OFDM_EN);
		if (new_channel->band == IEEE80211_BAND_2GHZ)
			b43_phy_mask(dev, B43_PHY_HT_TEST, ~0x840);
	}

	if (1) /* TODO: On N it's for early devices only, what about HT? */
		b43_phy_ht_tx_power_fix(dev);

	b43_phy_ht_spur_avoid(dev, new_channel);

	b43_phy_write(dev, 0x017e, 0x3830);
}