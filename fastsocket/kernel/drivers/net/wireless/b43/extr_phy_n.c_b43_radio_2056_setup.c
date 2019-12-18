#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
typedef  int u16 ;
struct ssb_sprom {int boardflags2_lo; } ;
struct TYPE_6__ {int rev; int channel_freq; TYPE_2__* n; scalar_t__ is_40mhz; } ;
struct b43_wldev {TYPE_3__ phy; TYPE_1__* dev; int /*<<< orphan*/  wl; } ;
struct b43_nphy_channeltab_entry_rev3 {int dummy; } ;
typedef  enum ieee80211_band { ____Placeholder_ieee80211_band } ieee80211_band ;
struct TYPE_5__ {scalar_t__ ipa5g_on; scalar_t__ ipa2g_on; } ;
struct TYPE_4__ {int chip_id; struct ssb_sprom* bus_sprom; } ;

/* Variables and functions */
 int B2056_SYN_PLL_CP2 ; 
 int B2056_SYN_PLL_LOOPFILTER1 ; 
 int B2056_SYN_PLL_LOOPFILTER2 ; 
 int B2056_SYN_PLL_LOOPFILTER4 ; 
 int B2056_SYN_PLL_VCOCAL12 ; 
 int B2056_TX0 ; 
 int B2056_TX1 ; 
 int B2056_TX_INTPAA_BOOST_TUNE ; 
 int B2056_TX_INTPAA_CASCBIAS ; 
 int B2056_TX_INTPAA_IAUX_STAT ; 
 int B2056_TX_INTPAA_IMAIN_STAT ; 
 int B2056_TX_INTPAA_PA_MISC ; 
 int B2056_TX_INTPAG_BOOST_TUNE ; 
 int B2056_TX_INTPAG_CASCBIAS ; 
 int B2056_TX_INTPAG_IAUX_STAT ; 
 int B2056_TX_INTPAG_IMAIN_STAT ; 
 int B2056_TX_MIXA_BOOST_TUNE ; 
 int B2056_TX_MIXG_BOOST_TUNE ; 
 int B2056_TX_PADA_BOOST_TUNE ; 
 int B2056_TX_PADA_CASCBIAS ; 
 int B2056_TX_PADG_BOOST_TUNE ; 
 int B2056_TX_PADG_IDAC ; 
 int B2056_TX_PA_SPARE1 ; 
 int B2056_TX_PA_SPARE2 ; 
 int B2056_TX_PGAA_BOOST_TUNE ; 
 int B2056_TX_PGAG_BOOST_TUNE ; 
 int B2056_TX_TXSPARE1 ; 
 int B43_BFL2_APLL_WAR ; 
 int B43_BFL2_GPLL_WAR ; 
 int /*<<< orphan*/  B43_WARN_ON (int) ; 
 scalar_t__ IEEE80211_BAND_2GHZ ; 
 int IEEE80211_BAND_5GHZ ; 
 int /*<<< orphan*/  b2056_upload_syn_pll_cp2 (struct b43_wldev*,int) ; 
 int /*<<< orphan*/  b43_chantab_radio_2056_upload (struct b43_wldev*,struct b43_nphy_channeltab_entry_rev3 const*) ; 
 int b43_current_band (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  b43_radio_write (struct b43_wldev*,int,int) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static void b43_radio_2056_setup(struct b43_wldev *dev,
				const struct b43_nphy_channeltab_entry_rev3 *e)
{
	struct ssb_sprom *sprom = dev->dev->bus_sprom;
	enum ieee80211_band band = b43_current_band(dev->wl);
	u16 offset;
	u8 i;
	u16 bias, cbias;
	u16 pag_boost, padg_boost, pgag_boost, mixg_boost;
	u16 paa_boost, pada_boost, pgaa_boost, mixa_boost;

	B43_WARN_ON(dev->phy.rev < 3);

	b43_chantab_radio_2056_upload(dev, e);
	b2056_upload_syn_pll_cp2(dev, band == IEEE80211_BAND_5GHZ);

	if (sprom->boardflags2_lo & B43_BFL2_GPLL_WAR &&
	    b43_current_band(dev->wl) == IEEE80211_BAND_2GHZ) {
		b43_radio_write(dev, B2056_SYN_PLL_LOOPFILTER1, 0x1F);
		b43_radio_write(dev, B2056_SYN_PLL_LOOPFILTER2, 0x1F);
		if (dev->dev->chip_id == 0x4716) {
			b43_radio_write(dev, B2056_SYN_PLL_LOOPFILTER4, 0x14);
			b43_radio_write(dev, B2056_SYN_PLL_CP2, 0);
		} else {
			b43_radio_write(dev, B2056_SYN_PLL_LOOPFILTER4, 0x0B);
			b43_radio_write(dev, B2056_SYN_PLL_CP2, 0x14);
		}
	}
	if (sprom->boardflags2_lo & B43_BFL2_APLL_WAR &&
	    b43_current_band(dev->wl) == IEEE80211_BAND_5GHZ) {
		b43_radio_write(dev, B2056_SYN_PLL_LOOPFILTER1, 0x1F);
		b43_radio_write(dev, B2056_SYN_PLL_LOOPFILTER2, 0x1F);
		b43_radio_write(dev, B2056_SYN_PLL_LOOPFILTER4, 0x05);
		b43_radio_write(dev, B2056_SYN_PLL_CP2, 0x0C);
	}

	if (dev->phy.n->ipa2g_on && band == IEEE80211_BAND_2GHZ) {
		for (i = 0; i < 2; i++) {
			offset = i ? B2056_TX1 : B2056_TX0;
			if (dev->phy.rev >= 5) {
				b43_radio_write(dev,
					offset | B2056_TX_PADG_IDAC, 0xcc);

				if (dev->dev->chip_id == 0x4716) {
					bias = 0x40;
					cbias = 0x45;
					pag_boost = 0x5;
					pgag_boost = 0x33;
					mixg_boost = 0x55;
				} else {
					bias = 0x25;
					cbias = 0x20;
					pag_boost = 0x4;
					pgag_boost = 0x03;
					mixg_boost = 0x65;
				}
				padg_boost = 0x77;

				b43_radio_write(dev,
					offset | B2056_TX_INTPAG_IMAIN_STAT,
					bias);
				b43_radio_write(dev,
					offset | B2056_TX_INTPAG_IAUX_STAT,
					bias);
				b43_radio_write(dev,
					offset | B2056_TX_INTPAG_CASCBIAS,
					cbias);
				b43_radio_write(dev,
					offset | B2056_TX_INTPAG_BOOST_TUNE,
					pag_boost);
				b43_radio_write(dev,
					offset | B2056_TX_PGAG_BOOST_TUNE,
					pgag_boost);
				b43_radio_write(dev,
					offset | B2056_TX_PADG_BOOST_TUNE,
					padg_boost);
				b43_radio_write(dev,
					offset | B2056_TX_MIXG_BOOST_TUNE,
					mixg_boost);
			} else {
				bias = dev->phy.is_40mhz ? 0x40 : 0x20;
				b43_radio_write(dev,
					offset | B2056_TX_INTPAG_IMAIN_STAT,
					bias);
				b43_radio_write(dev,
					offset | B2056_TX_INTPAG_IAUX_STAT,
					bias);
				b43_radio_write(dev,
					offset | B2056_TX_INTPAG_CASCBIAS,
					0x30);
			}
			b43_radio_write(dev, offset | B2056_TX_PA_SPARE1, 0xee);
		}
	} else if (dev->phy.n->ipa5g_on && band == IEEE80211_BAND_5GHZ) {
		u16 freq = dev->phy.channel_freq;
		if (freq < 5100) {
			paa_boost = 0xA;
			pada_boost = 0x77;
			pgaa_boost = 0xF;
			mixa_boost = 0xF;
		} else if (freq < 5340) {
			paa_boost = 0x8;
			pada_boost = 0x77;
			pgaa_boost = 0xFB;
			mixa_boost = 0xF;
		} else if (freq < 5650) {
			paa_boost = 0x0;
			pada_boost = 0x77;
			pgaa_boost = 0xB;
			mixa_boost = 0xF;
		} else {
			paa_boost = 0x0;
			pada_boost = 0x77;
			if (freq != 5825)
				pgaa_boost = -(freq - 18) / 36 + 168;
			else
				pgaa_boost = 6;
			mixa_boost = 0xF;
		}

		for (i = 0; i < 2; i++) {
			offset = i ? B2056_TX1 : B2056_TX0;

			b43_radio_write(dev,
				offset | B2056_TX_INTPAA_BOOST_TUNE, paa_boost);
			b43_radio_write(dev,
				offset | B2056_TX_PADA_BOOST_TUNE, pada_boost);
			b43_radio_write(dev,
				offset | B2056_TX_PGAA_BOOST_TUNE, pgaa_boost);
			b43_radio_write(dev,
				offset | B2056_TX_MIXA_BOOST_TUNE, mixa_boost);
			b43_radio_write(dev,
				offset | B2056_TX_TXSPARE1, 0x30);
			b43_radio_write(dev,
				offset | B2056_TX_PA_SPARE2, 0xee);
			b43_radio_write(dev,
				offset | B2056_TX_PADA_CASCBIAS, 0x03);
			b43_radio_write(dev,
				offset | B2056_TX_INTPAA_IAUX_STAT, 0x50);
			b43_radio_write(dev,
				offset | B2056_TX_INTPAA_IMAIN_STAT, 0x50);
			b43_radio_write(dev,
				offset | B2056_TX_INTPAA_CASCBIAS, 0x30);
		}
	}

	udelay(50);
	/* VCO calibration */
	b43_radio_write(dev, B2056_SYN_PLL_VCOCAL12, 0x00);
	b43_radio_write(dev, B2056_TX_INTPAA_PA_MISC, 0x38);
	b43_radio_write(dev, B2056_TX_INTPAA_PA_MISC, 0x18);
	b43_radio_write(dev, B2056_TX_INTPAA_PA_MISC, 0x38);
	b43_radio_write(dev, B2056_TX_INTPAA_PA_MISC, 0x39);
	udelay(300);
}