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
struct ssb_sprom {int boardflags2_lo; } ;
struct b43_phy {int rev; struct b43_phy_n* n; } ;
struct b43_wldev {struct b43_phy phy; int /*<<< orphan*/  wl; TYPE_1__* dev; } ;
struct b43_phy_n {scalar_t__ band5g_pwrgain; } ;
struct TYPE_2__ {scalar_t__ board_type; struct ssb_sprom* bus_sprom; } ;

/* Variables and functions */
 int /*<<< orphan*/  B2055_C1_TX_RF_SPARE ; 
 int /*<<< orphan*/  B2055_C2_TX_RF_SPARE ; 
 int B43_BFL2_SKWRKFEM_BRD ; 
 int B43_HF_MLADVW ; 
 int /*<<< orphan*/  B43_NPHY_CRSCHECK2 ; 
 int /*<<< orphan*/  B43_NPHY_CRSCHECK3 ; 
 int /*<<< orphan*/  B43_NPHY_FINERX2_CGC ; 
 int /*<<< orphan*/  B43_NPHY_FINERX2_CGC_DECGC ; 
 int /*<<< orphan*/  B43_NPHY_PHASETR_A0 ; 
 int /*<<< orphan*/  B43_NPHY_PHASETR_A1 ; 
 int /*<<< orphan*/  B43_NPHY_PHASETR_A2 ; 
 int /*<<< orphan*/  B43_NPHY_PHASETR_B0 ; 
 int /*<<< orphan*/  B43_NPHY_PHASETR_B1 ; 
 int /*<<< orphan*/  B43_NPHY_PHASETR_B2 ; 
 int /*<<< orphan*/  B43_NPHY_PIL_DW1 ; 
 int B43_NPHY_PIL_DW_64QAM ; 
 int /*<<< orphan*/  B43_NPHY_RFCTL_LUT_TRSW_LO1 ; 
 int /*<<< orphan*/  B43_NPHY_RFCTL_LUT_TRSW_LO2 ; 
 int /*<<< orphan*/  B43_NPHY_RFCTL_LUT_TRSW_UP1 ; 
 int /*<<< orphan*/  B43_NPHY_RFCTL_LUT_TRSW_UP2 ; 
 int /*<<< orphan*/  B43_NPHY_RXCTL ; 
 int /*<<< orphan*/  B43_NPHY_SCRAM_SIGCTL ; 
 int B43_NPHY_SCRAM_SIGCTL_SCM ; 
 int /*<<< orphan*/  B43_NPHY_TXF_20CO_S2B1 ; 
 int /*<<< orphan*/  B43_NPHY_TXF_20CO_S2B2 ; 
 int /*<<< orphan*/  B43_NPHY_TXF_20CO_S2B3 ; 
 int /*<<< orphan*/  B43_NTAB16 (int,int) ; 
 scalar_t__ BCMA_BOARD_TYPE_BCM943224M93 ; 
 scalar_t__ IEEE80211_BAND_5GHZ ; 
 scalar_t__ b43_current_band (int /*<<< orphan*/ ) ; 
 int b43_hf_read (struct b43_wldev*) ; 
 int /*<<< orphan*/  b43_hf_write (struct b43_wldev*,int) ; 
 int /*<<< orphan*/  b43_nphy_gain_ctl_workarounds (struct b43_wldev*) ; 
 int /*<<< orphan*/  b43_nphy_set_rf_sequence (struct b43_wldev*,int,int*,int*,int) ; 
 int /*<<< orphan*/  b43_ntab_write (struct b43_wldev*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  b43_phy_mask (struct b43_wldev*,int /*<<< orphan*/ ,int) ; 
 int b43_phy_read (struct b43_wldev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  b43_phy_set (struct b43_wldev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  b43_phy_write (struct b43_wldev*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  b43_radio_mask (struct b43_wldev*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  b43_radio_set (struct b43_wldev*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void b43_nphy_workarounds_rev1_2(struct b43_wldev *dev)
{
	struct ssb_sprom *sprom = dev->dev->bus_sprom;
	struct b43_phy *phy = &dev->phy;
	struct b43_phy_n *nphy = phy->n;

	u8 events1[7] = { 0x0, 0x1, 0x2, 0x8, 0x4, 0x5, 0x3 };
	u8 delays1[7] = { 0x8, 0x6, 0x6, 0x2, 0x4, 0x3C, 0x1 };

	u8 events2[7] = { 0x0, 0x3, 0x5, 0x4, 0x2, 0x1, 0x8 };
	u8 delays2[7] = { 0x8, 0x6, 0x2, 0x4, 0x4, 0x6, 0x1 };

	if (sprom->boardflags2_lo & B43_BFL2_SKWRKFEM_BRD ||
	    dev->dev->board_type == BCMA_BOARD_TYPE_BCM943224M93) {
		delays1[0] = 0x1;
		delays1[5] = 0x14;
	}

	if (b43_current_band(dev->wl) == IEEE80211_BAND_5GHZ &&
	    nphy->band5g_pwrgain) {
		b43_radio_mask(dev, B2055_C1_TX_RF_SPARE, ~0x8);
		b43_radio_mask(dev, B2055_C2_TX_RF_SPARE, ~0x8);
	} else {
		b43_radio_set(dev, B2055_C1_TX_RF_SPARE, 0x8);
		b43_radio_set(dev, B2055_C2_TX_RF_SPARE, 0x8);
	}

	b43_ntab_write(dev, B43_NTAB16(8, 0x00), 0x000A);
	b43_ntab_write(dev, B43_NTAB16(8, 0x10), 0x000A);
	if (dev->phy.rev < 3) {
		b43_ntab_write(dev, B43_NTAB16(8, 0x02), 0xCDAA);
		b43_ntab_write(dev, B43_NTAB16(8, 0x12), 0xCDAA);
	}

	if (dev->phy.rev < 2) {
		b43_ntab_write(dev, B43_NTAB16(8, 0x08), 0x0000);
		b43_ntab_write(dev, B43_NTAB16(8, 0x18), 0x0000);
		b43_ntab_write(dev, B43_NTAB16(8, 0x07), 0x7AAB);
		b43_ntab_write(dev, B43_NTAB16(8, 0x17), 0x7AAB);
		b43_ntab_write(dev, B43_NTAB16(8, 0x06), 0x0800);
		b43_ntab_write(dev, B43_NTAB16(8, 0x16), 0x0800);
	}

	b43_phy_write(dev, B43_NPHY_RFCTL_LUT_TRSW_LO1, 0x2D8);
	b43_phy_write(dev, B43_NPHY_RFCTL_LUT_TRSW_UP1, 0x301);
	b43_phy_write(dev, B43_NPHY_RFCTL_LUT_TRSW_LO2, 0x2D8);
	b43_phy_write(dev, B43_NPHY_RFCTL_LUT_TRSW_UP2, 0x301);

	b43_nphy_set_rf_sequence(dev, 0, events1, delays1, 7);
	b43_nphy_set_rf_sequence(dev, 1, events2, delays2, 7);

	b43_nphy_gain_ctl_workarounds(dev);

	if (dev->phy.rev < 2) {
		if (b43_phy_read(dev, B43_NPHY_RXCTL) & 0x2)
			b43_hf_write(dev, b43_hf_read(dev) |
					B43_HF_MLADVW);
	} else if (dev->phy.rev == 2) {
		b43_phy_write(dev, B43_NPHY_CRSCHECK2, 0);
		b43_phy_write(dev, B43_NPHY_CRSCHECK3, 0);
	}

	if (dev->phy.rev < 2)
		b43_phy_mask(dev, B43_NPHY_SCRAM_SIGCTL,
				~B43_NPHY_SCRAM_SIGCTL_SCM);

	/* Set phase track alpha and beta */
	b43_phy_write(dev, B43_NPHY_PHASETR_A0, 0x125);
	b43_phy_write(dev, B43_NPHY_PHASETR_A1, 0x1B3);
	b43_phy_write(dev, B43_NPHY_PHASETR_A2, 0x105);
	b43_phy_write(dev, B43_NPHY_PHASETR_B0, 0x16E);
	b43_phy_write(dev, B43_NPHY_PHASETR_B1, 0xCD);
	b43_phy_write(dev, B43_NPHY_PHASETR_B2, 0x20);

	if (dev->phy.rev < 3) {
		b43_phy_mask(dev, B43_NPHY_PIL_DW1,
			     ~B43_NPHY_PIL_DW_64QAM & 0xFFFF);
		b43_phy_write(dev, B43_NPHY_TXF_20CO_S2B1, 0xB5);
		b43_phy_write(dev, B43_NPHY_TXF_20CO_S2B2, 0xA4);
		b43_phy_write(dev, B43_NPHY_TXF_20CO_S2B3, 0x00);
	}

	if (dev->phy.rev == 2)
		b43_phy_set(dev, B43_NPHY_FINERX2_CGC,
				B43_NPHY_FINERX2_CGC_DECGC);
}