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
struct ssb_sprom {int boardflags2_lo; } ;
struct TYPE_4__ {int rev; int /*<<< orphan*/  is_40mhz; struct b43_phy_n* n; } ;
struct b43_wldev {TYPE_2__ phy; int /*<<< orphan*/  wl; TYPE_1__* dev; } ;
struct b43_phy_n {int hw_phyrxchain; int hw_phytxchain; } ;
struct TYPE_3__ {struct ssb_sprom* bus_sprom; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int*) ; 
 int B2056_RX0 ; 
 int B2056_RX1 ; 
 int B2056_RX_MIXA_BIAS_AUX ; 
 int B2056_RX_MIXA_BIAS_MAIN ; 
 int B2056_RX_MIXA_CMFB_IDAC ; 
 int B2056_RX_MIXA_LOB_BIAS ; 
 int B2056_RX_MIXA_MAST_BIAS ; 
 int B2056_RX_MIXG_CMFB_IDAC ; 
 int B2056_TX0 ; 
 int B2056_TX1 ; 
 int B2056_TX_GMBB_IDAC ; 
 int B43_BFL2_APLL_WAR ; 
 int B43_BFL2_GPLL_WAR ; 
 int B43_BFL2_SINGLEANT_CCK ; 
 int /*<<< orphan*/  B43_NPHY_ED_CRS20LASSERTTHRESH0 ; 
 int /*<<< orphan*/  B43_NPHY_ED_CRS20LASSERTTHRESH1 ; 
 int /*<<< orphan*/  B43_NPHY_ED_CRS20LDEASSERTTHRESH0 ; 
 int /*<<< orphan*/  B43_NPHY_ED_CRS20LDEASSERTTHRESH1 ; 
 int /*<<< orphan*/  B43_NPHY_ED_CRS20UASSERTTHRESH0 ; 
 int /*<<< orphan*/  B43_NPHY_ED_CRS20UASSERTTHRESH1 ; 
 int /*<<< orphan*/  B43_NPHY_ED_CRS20UDEASSERTTHRESH0 ; 
 int /*<<< orphan*/  B43_NPHY_ED_CRS20UDEASSERTTHRESH1 ; 
 int /*<<< orphan*/  B43_NPHY_ED_CRS40ASSERTTHRESH0 ; 
 int /*<<< orphan*/  B43_NPHY_ED_CRS40ASSERTTHRESH1 ; 
 int /*<<< orphan*/  B43_NPHY_ED_CRS40DEASSERTTHRESH1 ; 
 int /*<<< orphan*/  B43_NPHY_ENDROP_TLEN ; 
 int /*<<< orphan*/  B43_NPHY_FORCEFRONT0 ; 
 int /*<<< orphan*/  B43_NPHY_FORCEFRONT1 ; 
 int /*<<< orphan*/  B43_NPHY_PHASETR_A0 ; 
 int /*<<< orphan*/  B43_NPHY_PHASETR_A1 ; 
 int /*<<< orphan*/  B43_NPHY_PHASETR_A2 ; 
 int /*<<< orphan*/  B43_NPHY_PHASETR_B0 ; 
 int /*<<< orphan*/  B43_NPHY_PHASETR_B1 ; 
 int /*<<< orphan*/  B43_NPHY_PHASETR_B2 ; 
 int /*<<< orphan*/  B43_NPHY_REV3_C1_CLIP_LOGAIN_B ; 
 int /*<<< orphan*/  B43_NPHY_REV3_C2_CLIP_LOGAIN_B ; 
 int /*<<< orphan*/  B43_NPHY_SGILTRNOFFSET ; 
 int /*<<< orphan*/  B43_NTAB16 (int,int) ; 
 int /*<<< orphan*/  B43_NTAB32 (int,int) ; 
 scalar_t__ IEEE80211_BAND_2GHZ ; 
 scalar_t__ IEEE80211_BAND_5GHZ ; 
 scalar_t__ b43_current_band (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  b43_nphy_gain_ctl_workarounds (struct b43_wldev*) ; 
 scalar_t__ b43_nphy_ipa (struct b43_wldev*) ; 
 int /*<<< orphan*/  b43_nphy_set_rf_sequence (struct b43_wldev*,int,int*,int*,int /*<<< orphan*/ ) ; 
 int b43_ntab_read (struct b43_wldev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  b43_ntab_write (struct b43_wldev*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  b43_phy_maskset (struct b43_wldev*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  b43_phy_write (struct b43_wldev*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  b43_radio_write (struct b43_wldev*,int,int) ; 

__attribute__((used)) static void b43_nphy_workarounds_rev3plus(struct b43_wldev *dev)
{
	struct b43_phy_n *nphy = dev->phy.n;
	struct ssb_sprom *sprom = dev->dev->bus_sprom;

	/* TX to RX */
	u8 tx2rx_events[8] = { 0x4, 0x3, 0x6, 0x5, 0x2, 0x1, 0x8, 0x1F };
	u8 tx2rx_delays[8] = { 8, 4, 2, 2, 4, 4, 6, 1 };
	/* RX to TX */
	u8 rx2tx_events_ipa[9] = { 0x0, 0x1, 0x2, 0x8, 0x5, 0x6, 0xF, 0x3,
					0x1F };
	u8 rx2tx_delays_ipa[9] = { 8, 6, 6, 4, 4, 16, 43, 1, 1 };
	u8 rx2tx_events[9] = { 0x0, 0x1, 0x2, 0x8, 0x5, 0x6, 0x3, 0x4, 0x1F };
	u8 rx2tx_delays[9] = { 8, 6, 6, 4, 4, 18, 42, 1, 1 };

	u16 tmp16;
	u32 tmp32;

	b43_phy_write(dev, B43_NPHY_FORCEFRONT0, 0x1f8);
	b43_phy_write(dev, B43_NPHY_FORCEFRONT1, 0x1f8);

	tmp32 = b43_ntab_read(dev, B43_NTAB32(30, 0));
	tmp32 &= 0xffffff;
	b43_ntab_write(dev, B43_NTAB32(30, 0), tmp32);

	b43_phy_write(dev, B43_NPHY_PHASETR_A0, 0x0125);
	b43_phy_write(dev, B43_NPHY_PHASETR_A1, 0x01B3);
	b43_phy_write(dev, B43_NPHY_PHASETR_A2, 0x0105);
	b43_phy_write(dev, B43_NPHY_PHASETR_B0, 0x016E);
	b43_phy_write(dev, B43_NPHY_PHASETR_B1, 0x00CD);
	b43_phy_write(dev, B43_NPHY_PHASETR_B2, 0x0020);

	b43_phy_write(dev, B43_NPHY_REV3_C1_CLIP_LOGAIN_B, 0x000C);
	b43_phy_write(dev, B43_NPHY_REV3_C2_CLIP_LOGAIN_B, 0x000C);

	/* TX to RX */
	b43_nphy_set_rf_sequence(dev, 1, tx2rx_events, tx2rx_delays,
				 ARRAY_SIZE(tx2rx_events));

	/* RX to TX */
	if (b43_nphy_ipa(dev))
		b43_nphy_set_rf_sequence(dev, 0, rx2tx_events_ipa,
				rx2tx_delays_ipa, ARRAY_SIZE(rx2tx_events_ipa));
	if (nphy->hw_phyrxchain != 3 &&
	    nphy->hw_phyrxchain != nphy->hw_phytxchain) {
		if (b43_nphy_ipa(dev)) {
			rx2tx_delays[5] = 59;
			rx2tx_delays[6] = 1;
			rx2tx_events[7] = 0x1F;
		}
		b43_nphy_set_rf_sequence(dev, 0, rx2tx_events, rx2tx_delays,
					 ARRAY_SIZE(rx2tx_events));
	}

	tmp16 = (b43_current_band(dev->wl) == IEEE80211_BAND_2GHZ) ?
		0x2 : 0x9C40;
	b43_phy_write(dev, B43_NPHY_ENDROP_TLEN, tmp16);

	b43_phy_maskset(dev, B43_NPHY_SGILTRNOFFSET, 0xF0FF, 0x0700);

	if (!dev->phy.is_40mhz) {
		b43_ntab_write(dev, B43_NTAB32(16, 3), 0x18D);
		b43_ntab_write(dev, B43_NTAB32(16, 127), 0x18D);
	} else {
		b43_ntab_write(dev, B43_NTAB32(16, 3), 0x14D);
		b43_ntab_write(dev, B43_NTAB32(16, 127), 0x14D);
	}

	b43_nphy_gain_ctl_workarounds(dev);

	b43_ntab_write(dev, B43_NTAB16(8, 0), 2);
	b43_ntab_write(dev, B43_NTAB16(8, 16), 2);

	/* TODO */

	b43_radio_write(dev, B2056_RX0 | B2056_RX_MIXA_MAST_BIAS, 0x00);
	b43_radio_write(dev, B2056_RX1 | B2056_RX_MIXA_MAST_BIAS, 0x00);
	b43_radio_write(dev, B2056_RX0 | B2056_RX_MIXA_BIAS_MAIN, 0x06);
	b43_radio_write(dev, B2056_RX1 | B2056_RX_MIXA_BIAS_MAIN, 0x06);
	b43_radio_write(dev, B2056_RX0 | B2056_RX_MIXA_BIAS_AUX, 0x07);
	b43_radio_write(dev, B2056_RX1 | B2056_RX_MIXA_BIAS_AUX, 0x07);
	b43_radio_write(dev, B2056_RX0 | B2056_RX_MIXA_LOB_BIAS, 0x88);
	b43_radio_write(dev, B2056_RX1 | B2056_RX_MIXA_LOB_BIAS, 0x88);
	b43_radio_write(dev, B2056_RX0 | B2056_RX_MIXA_CMFB_IDAC, 0x00);
	b43_radio_write(dev, B2056_RX1 | B2056_RX_MIXA_CMFB_IDAC, 0x00);
	b43_radio_write(dev, B2056_RX0 | B2056_RX_MIXG_CMFB_IDAC, 0x00);
	b43_radio_write(dev, B2056_RX1 | B2056_RX_MIXG_CMFB_IDAC, 0x00);

	/* N PHY WAR TX Chain Update with hw_phytxchain as argument */

	if ((sprom->boardflags2_lo & B43_BFL2_APLL_WAR &&
	     b43_current_band(dev->wl) == IEEE80211_BAND_5GHZ) ||
	    (sprom->boardflags2_lo & B43_BFL2_GPLL_WAR &&
	     b43_current_band(dev->wl) == IEEE80211_BAND_2GHZ))
		tmp32 = 0x00088888;
	else
		tmp32 = 0x88888888;
	b43_ntab_write(dev, B43_NTAB32(30, 1), tmp32);
	b43_ntab_write(dev, B43_NTAB32(30, 2), tmp32);
	b43_ntab_write(dev, B43_NTAB32(30, 3), tmp32);

	if (dev->phy.rev == 4 &&
	    b43_current_band(dev->wl) == IEEE80211_BAND_5GHZ) {
		b43_radio_write(dev, B2056_TX0 | B2056_TX_GMBB_IDAC,
				0x70);
		b43_radio_write(dev, B2056_TX1 | B2056_TX_GMBB_IDAC,
				0x70);
	}

	/* Dropped probably-always-true condition */
	b43_phy_write(dev, B43_NPHY_ED_CRS40ASSERTTHRESH0, 0x03eb);
	b43_phy_write(dev, B43_NPHY_ED_CRS40ASSERTTHRESH1, 0x03eb);
	b43_phy_write(dev, B43_NPHY_ED_CRS40DEASSERTTHRESH1, 0x0341);
	b43_phy_write(dev, B43_NPHY_ED_CRS40DEASSERTTHRESH1, 0x0341);
	b43_phy_write(dev, B43_NPHY_ED_CRS20LASSERTTHRESH0, 0x042b);
	b43_phy_write(dev, B43_NPHY_ED_CRS20LASSERTTHRESH1, 0x042b);
	b43_phy_write(dev, B43_NPHY_ED_CRS20LDEASSERTTHRESH0, 0x0381);
	b43_phy_write(dev, B43_NPHY_ED_CRS20LDEASSERTTHRESH1, 0x0381);
	b43_phy_write(dev, B43_NPHY_ED_CRS20UASSERTTHRESH0, 0x042b);
	b43_phy_write(dev, B43_NPHY_ED_CRS20UASSERTTHRESH1, 0x042b);
	b43_phy_write(dev, B43_NPHY_ED_CRS20UDEASSERTTHRESH0, 0x0381);
	b43_phy_write(dev, B43_NPHY_ED_CRS20UDEASSERTTHRESH1, 0x0381);

	if (dev->phy.rev >= 6 && sprom->boardflags2_lo & B43_BFL2_SINGLEANT_CCK)
		; /* TODO: 0x0080000000000000 HF */
}