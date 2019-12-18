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
typedef  int u16 ;
struct ssb_sprom {int boardflags_lo; } ;
struct lo_g_saved_values {int reg_3F4; int reg_3E2; int radio_7A; int phy_syncctl; int radio_52; void* phy_cck_06; void* phy_cck_30; void* phy_dacctl; void* phy_cck_2A; void* phy_pgactl; void* radio_43; void* phy_crs0; void* phy_cck_3E; void* phy_classctl; void* phy_rfoverval; void* phy_rfover; void* phy_analogoverval; void* phy_analogover; void* phy_hpwr_tssictl; void* phy_cck_14; void* phy_dacctl_hwpctl; void* phy_extg_01; void* phy_lo_mask; } ;
struct b43_phy {scalar_t__ type; int radio_ver; int radio_rev; int rev; struct b43_phy_g* g; } ;
struct b43_wldev {struct b43_phy phy; TYPE_1__* dev; } ;
struct b43_txpower_lo_control {int /*<<< orphan*/  txctl_measured_time; } ;
struct b43_phy_g {struct b43_txpower_lo_control* lo_control; } ;
struct TYPE_2__ {struct ssb_sprom* bus_sprom; } ;

/* Variables and functions */
 int B43_BFL_EXTLNA ; 
 scalar_t__ B43_LO_TXCTL_EXPIRE ; 
 scalar_t__ B43_PHYTYPE_B ; 
 scalar_t__ B43_PHYTYPE_G ; 
 int B43_PHY_ANALOGOVER ; 
 int B43_PHY_ANALOGOVERVAL ; 
 int B43_PHY_CCK (int) ; 
 int B43_PHY_CLASSCTL ; 
 int B43_PHY_CRS0 ; 
 int B43_PHY_DACCTL ; 
 int B43_PHY_EXTG (int) ; 
 int B43_PHY_HPWR_TSSICTL ; 
 int B43_PHY_LO_MASK ; 
 int B43_PHY_PGACTL ; 
 int B43_PHY_RFOVER ; 
 int B43_PHY_RFOVERVAL ; 
 int B43_PHY_SYNCCTL ; 
 int /*<<< orphan*/  b43_dummy_transmission (struct b43_wldev*,int,int) ; 
 int /*<<< orphan*/  b43_gphy_channel_switch (struct b43_wldev*,int,int /*<<< orphan*/ ) ; 
 scalar_t__ b43_has_hardware_pctl (struct b43_wldev*) ; 
 int /*<<< orphan*/  b43_phy_mask (struct b43_wldev*,int,int) ; 
 void* b43_phy_read (struct b43_wldev*,int) ; 
 int /*<<< orphan*/  b43_phy_set (struct b43_wldev*,int,int) ; 
 int /*<<< orphan*/  b43_phy_write (struct b43_wldev*,int,int) ; 
 void* b43_radio_read16 (struct b43_wldev*,int) ; 
 int /*<<< orphan*/  b43_radio_write16 (struct b43_wldev*,int,int) ; 
 int b43_read16 (struct b43_wldev*,int) ; 
 int /*<<< orphan*/  b43_write16 (struct b43_wldev*,int,int) ; 
 int /*<<< orphan*/  has_tx_magnification (struct b43_phy*) ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  lo_measure_txctl_values (struct b43_wldev*) ; 
 scalar_t__ time_before (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void lo_measure_setup(struct b43_wldev *dev,
			     struct lo_g_saved_values *sav)
{
	struct ssb_sprom *sprom = dev->dev->bus_sprom;
	struct b43_phy *phy = &dev->phy;
	struct b43_phy_g *gphy = phy->g;
	struct b43_txpower_lo_control *lo = gphy->lo_control;
	u16 tmp;

	if (b43_has_hardware_pctl(dev)) {
		sav->phy_lo_mask = b43_phy_read(dev, B43_PHY_LO_MASK);
		sav->phy_extg_01 = b43_phy_read(dev, B43_PHY_EXTG(0x01));
		sav->phy_dacctl_hwpctl = b43_phy_read(dev, B43_PHY_DACCTL);
		sav->phy_cck_14 = b43_phy_read(dev, B43_PHY_CCK(0x14));
		sav->phy_hpwr_tssictl = b43_phy_read(dev, B43_PHY_HPWR_TSSICTL);

		b43_phy_set(dev, B43_PHY_HPWR_TSSICTL, 0x100);
		b43_phy_set(dev, B43_PHY_EXTG(0x01), 0x40);
		b43_phy_set(dev, B43_PHY_DACCTL, 0x40);
		b43_phy_set(dev, B43_PHY_CCK(0x14), 0x200);
	}
	if (phy->type == B43_PHYTYPE_B &&
	    phy->radio_ver == 0x2050 && phy->radio_rev < 6) {
		b43_phy_write(dev, B43_PHY_CCK(0x16), 0x410);
		b43_phy_write(dev, B43_PHY_CCK(0x17), 0x820);
	}
	if (phy->rev >= 2) {
		sav->phy_analogover = b43_phy_read(dev, B43_PHY_ANALOGOVER);
		sav->phy_analogoverval =
		    b43_phy_read(dev, B43_PHY_ANALOGOVERVAL);
		sav->phy_rfover = b43_phy_read(dev, B43_PHY_RFOVER);
		sav->phy_rfoverval = b43_phy_read(dev, B43_PHY_RFOVERVAL);
		sav->phy_classctl = b43_phy_read(dev, B43_PHY_CLASSCTL);
		sav->phy_cck_3E = b43_phy_read(dev, B43_PHY_CCK(0x3E));
		sav->phy_crs0 = b43_phy_read(dev, B43_PHY_CRS0);

		b43_phy_mask(dev, B43_PHY_CLASSCTL, 0xFFFC);
		b43_phy_mask(dev, B43_PHY_CRS0, 0x7FFF);
		b43_phy_set(dev, B43_PHY_ANALOGOVER, 0x0003);
		b43_phy_mask(dev, B43_PHY_ANALOGOVERVAL, 0xFFFC);
		if (phy->type == B43_PHYTYPE_G) {
			if ((phy->rev >= 7) &&
			    (sprom->boardflags_lo & B43_BFL_EXTLNA)) {
				b43_phy_write(dev, B43_PHY_RFOVER, 0x933);
			} else {
				b43_phy_write(dev, B43_PHY_RFOVER, 0x133);
			}
		} else {
			b43_phy_write(dev, B43_PHY_RFOVER, 0);
		}
		b43_phy_write(dev, B43_PHY_CCK(0x3E), 0);
	}
	sav->reg_3F4 = b43_read16(dev, 0x3F4);
	sav->reg_3E2 = b43_read16(dev, 0x3E2);
	sav->radio_43 = b43_radio_read16(dev, 0x43);
	sav->radio_7A = b43_radio_read16(dev, 0x7A);
	sav->phy_pgactl = b43_phy_read(dev, B43_PHY_PGACTL);
	sav->phy_cck_2A = b43_phy_read(dev, B43_PHY_CCK(0x2A));
	sav->phy_syncctl = b43_phy_read(dev, B43_PHY_SYNCCTL);
	sav->phy_dacctl = b43_phy_read(dev, B43_PHY_DACCTL);

	if (!has_tx_magnification(phy)) {
		sav->radio_52 = b43_radio_read16(dev, 0x52);
		sav->radio_52 &= 0x00F0;
	}
	if (phy->type == B43_PHYTYPE_B) {
		sav->phy_cck_30 = b43_phy_read(dev, B43_PHY_CCK(0x30));
		sav->phy_cck_06 = b43_phy_read(dev, B43_PHY_CCK(0x06));
		b43_phy_write(dev, B43_PHY_CCK(0x30), 0x00FF);
		b43_phy_write(dev, B43_PHY_CCK(0x06), 0x3F3F);
	} else {
		b43_write16(dev, 0x3E2, b43_read16(dev, 0x3E2)
			    | 0x8000);
	}
	b43_write16(dev, 0x3F4, b43_read16(dev, 0x3F4)
		    & 0xF000);

	tmp =
	    (phy->type == B43_PHYTYPE_G) ? B43_PHY_LO_MASK : B43_PHY_CCK(0x2E);
	b43_phy_write(dev, tmp, 0x007F);

	tmp = sav->phy_syncctl;
	b43_phy_write(dev, B43_PHY_SYNCCTL, tmp & 0xFF7F);
	tmp = sav->radio_7A;
	b43_radio_write16(dev, 0x007A, tmp & 0xFFF0);

	b43_phy_write(dev, B43_PHY_CCK(0x2A), 0x8A3);
	if (phy->type == B43_PHYTYPE_G ||
	    (phy->type == B43_PHYTYPE_B &&
	     phy->radio_ver == 0x2050 && phy->radio_rev >= 6)) {
		b43_phy_write(dev, B43_PHY_CCK(0x2B), 0x1003);
	} else
		b43_phy_write(dev, B43_PHY_CCK(0x2B), 0x0802);
	if (phy->rev >= 2)
		b43_dummy_transmission(dev, false, true);
	b43_gphy_channel_switch(dev, 6, 0);
	b43_radio_read16(dev, 0x51);	/* dummy read */
	if (phy->type == B43_PHYTYPE_G)
		b43_phy_write(dev, B43_PHY_CCK(0x2F), 0);

	/* Re-measure the txctl values, if needed. */
	if (time_before(lo->txctl_measured_time,
			jiffies - B43_LO_TXCTL_EXPIRE))
		lo_measure_txctl_values(dev);

	if (phy->type == B43_PHYTYPE_G && phy->rev >= 3) {
		b43_phy_write(dev, B43_PHY_LO_MASK, 0xC078);
	} else {
		if (phy->type == B43_PHYTYPE_B)
			b43_phy_write(dev, B43_PHY_CCK(0x2E), 0x8078);
		else
			b43_phy_write(dev, B43_PHY_LO_MASK, 0x8078);
	}
}