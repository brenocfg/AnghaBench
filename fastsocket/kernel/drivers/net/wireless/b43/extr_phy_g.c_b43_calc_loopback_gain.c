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
typedef  int u16 ;
struct b43_phy {int rev; int radio_rev; struct b43_phy_g* g; } ;
struct b43_wldev {TYPE_2__* dev; struct b43_phy phy; } ;
struct TYPE_6__ {int att; } ;
struct b43_phy_g {int max_lb_gain; int trsw_rx_gain; TYPE_3__ bbatt; } ;
struct TYPE_5__ {TYPE_1__* bus_sprom; } ;
struct TYPE_4__ {int boardflags_lo; } ;

/* Variables and functions */
 int B43_BFL_EXTLNA ; 
 int /*<<< orphan*/  B43_PHY_ANALOGOVER ; 
 int /*<<< orphan*/  B43_PHY_ANALOGOVERVAL ; 
 int /*<<< orphan*/  B43_PHY_CCK (int) ; 
 int /*<<< orphan*/  B43_PHY_CCKBBANDCFG ; 
 int /*<<< orphan*/  B43_PHY_CRS0 ; 
 int /*<<< orphan*/  B43_PHY_LO_CTL ; 
 int /*<<< orphan*/  B43_PHY_LO_LEAKAGE ; 
 int /*<<< orphan*/  B43_PHY_LO_MASK ; 
 int /*<<< orphan*/  B43_PHY_PGACTL ; 
 int /*<<< orphan*/  B43_PHY_RFOVER ; 
 int /*<<< orphan*/  B43_PHY_RFOVERVAL ; 
 int /*<<< orphan*/  b43_gphy_set_baseband_attenuation (struct b43_wldev*,int) ; 
 int /*<<< orphan*/  b43_phy_mask (struct b43_wldev*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  b43_phy_maskset (struct b43_wldev*,int /*<<< orphan*/ ,int,int) ; 
 int b43_phy_read (struct b43_wldev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  b43_phy_set (struct b43_wldev*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  b43_phy_write (struct b43_wldev*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  b43_radio_mask (struct b43_wldev*,int,int) ; 
 int /*<<< orphan*/  b43_radio_maskset (struct b43_wldev*,int,int,int) ; 
 int b43_radio_read16 (struct b43_wldev*,int) ; 
 int /*<<< orphan*/  b43_radio_write16 (struct b43_wldev*,int,int) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static void b43_calc_loopback_gain(struct b43_wldev *dev)
{
	struct b43_phy *phy = &dev->phy;
	struct b43_phy_g *gphy = phy->g;
	u16 backup_phy[16] = { 0 };
	u16 backup_radio[3];
	u16 backup_bband;
	u16 i, j, loop_i_max;
	u16 trsw_rx;
	u16 loop1_outer_done, loop1_inner_done;

	backup_phy[0] = b43_phy_read(dev, B43_PHY_CRS0);
	backup_phy[1] = b43_phy_read(dev, B43_PHY_CCKBBANDCFG);
	backup_phy[2] = b43_phy_read(dev, B43_PHY_RFOVER);
	backup_phy[3] = b43_phy_read(dev, B43_PHY_RFOVERVAL);
	if (phy->rev != 1) {	/* Not in specs, but needed to prevent PPC machine check */
		backup_phy[4] = b43_phy_read(dev, B43_PHY_ANALOGOVER);
		backup_phy[5] = b43_phy_read(dev, B43_PHY_ANALOGOVERVAL);
	}
	backup_phy[6] = b43_phy_read(dev, B43_PHY_CCK(0x5A));
	backup_phy[7] = b43_phy_read(dev, B43_PHY_CCK(0x59));
	backup_phy[8] = b43_phy_read(dev, B43_PHY_CCK(0x58));
	backup_phy[9] = b43_phy_read(dev, B43_PHY_CCK(0x0A));
	backup_phy[10] = b43_phy_read(dev, B43_PHY_CCK(0x03));
	backup_phy[11] = b43_phy_read(dev, B43_PHY_LO_MASK);
	backup_phy[12] = b43_phy_read(dev, B43_PHY_LO_CTL);
	backup_phy[13] = b43_phy_read(dev, B43_PHY_CCK(0x2B));
	backup_phy[14] = b43_phy_read(dev, B43_PHY_PGACTL);
	backup_phy[15] = b43_phy_read(dev, B43_PHY_LO_LEAKAGE);
	backup_bband = gphy->bbatt.att;
	backup_radio[0] = b43_radio_read16(dev, 0x52);
	backup_radio[1] = b43_radio_read16(dev, 0x43);
	backup_radio[2] = b43_radio_read16(dev, 0x7A);

	b43_phy_mask(dev, B43_PHY_CRS0, 0x3FFF);
	b43_phy_set(dev, B43_PHY_CCKBBANDCFG, 0x8000);
	b43_phy_set(dev, B43_PHY_RFOVER, 0x0002);
	b43_phy_mask(dev, B43_PHY_RFOVERVAL, 0xFFFD);
	b43_phy_set(dev, B43_PHY_RFOVER, 0x0001);
	b43_phy_mask(dev, B43_PHY_RFOVERVAL, 0xFFFE);
	if (phy->rev != 1) {	/* Not in specs, but needed to prevent PPC machine check */
		b43_phy_set(dev, B43_PHY_ANALOGOVER, 0x0001);
		b43_phy_mask(dev, B43_PHY_ANALOGOVERVAL, 0xFFFE);
		b43_phy_set(dev, B43_PHY_ANALOGOVER, 0x0002);
		b43_phy_mask(dev, B43_PHY_ANALOGOVERVAL, 0xFFFD);
	}
	b43_phy_set(dev, B43_PHY_RFOVER, 0x000C);
	b43_phy_set(dev, B43_PHY_RFOVERVAL, 0x000C);
	b43_phy_set(dev, B43_PHY_RFOVER, 0x0030);
	b43_phy_maskset(dev, B43_PHY_RFOVERVAL, 0xFFCF, 0x10);

	b43_phy_write(dev, B43_PHY_CCK(0x5A), 0x0780);
	b43_phy_write(dev, B43_PHY_CCK(0x59), 0xC810);
	b43_phy_write(dev, B43_PHY_CCK(0x58), 0x000D);

	b43_phy_set(dev, B43_PHY_CCK(0x0A), 0x2000);
	if (phy->rev != 1) {	/* Not in specs, but needed to prevent PPC machine check */
		b43_phy_set(dev, B43_PHY_ANALOGOVER, 0x0004);
		b43_phy_mask(dev, B43_PHY_ANALOGOVERVAL, 0xFFFB);
	}
	b43_phy_maskset(dev, B43_PHY_CCK(0x03), 0xFF9F, 0x40);

	if (phy->radio_rev == 8) {
		b43_radio_write16(dev, 0x43, 0x000F);
	} else {
		b43_radio_write16(dev, 0x52, 0);
		b43_radio_maskset(dev, 0x43, 0xFFF0, 0x9);
	}
	b43_gphy_set_baseband_attenuation(dev, 11);

	if (phy->rev >= 3)
		b43_phy_write(dev, B43_PHY_LO_MASK, 0xC020);
	else
		b43_phy_write(dev, B43_PHY_LO_MASK, 0x8020);
	b43_phy_write(dev, B43_PHY_LO_CTL, 0);

	b43_phy_maskset(dev, B43_PHY_CCK(0x2B), 0xFFC0, 0x01);
	b43_phy_maskset(dev, B43_PHY_CCK(0x2B), 0xC0FF, 0x800);

	b43_phy_set(dev, B43_PHY_RFOVER, 0x0100);
	b43_phy_mask(dev, B43_PHY_RFOVERVAL, 0xCFFF);

	if (dev->dev->bus_sprom->boardflags_lo & B43_BFL_EXTLNA) {
		if (phy->rev >= 7) {
			b43_phy_set(dev, B43_PHY_RFOVER, 0x0800);
			b43_phy_set(dev, B43_PHY_RFOVERVAL, 0x8000);
		}
	}
	b43_radio_mask(dev, 0x7A, 0x00F7);

	j = 0;
	loop_i_max = (phy->radio_rev == 8) ? 15 : 9;
	for (i = 0; i < loop_i_max; i++) {
		for (j = 0; j < 16; j++) {
			b43_radio_write16(dev, 0x43, i);
			b43_phy_maskset(dev, B43_PHY_RFOVERVAL, 0xF0FF, (j << 8));
			b43_phy_maskset(dev, B43_PHY_PGACTL, 0x0FFF, 0xA000);
			b43_phy_set(dev, B43_PHY_PGACTL, 0xF000);
			udelay(20);
			if (b43_phy_read(dev, B43_PHY_LO_LEAKAGE) >= 0xDFC)
				goto exit_loop1;
		}
	}
      exit_loop1:
	loop1_outer_done = i;
	loop1_inner_done = j;
	if (j >= 8) {
		b43_phy_set(dev, B43_PHY_RFOVERVAL, 0x30);
		trsw_rx = 0x1B;
		for (j = j - 8; j < 16; j++) {
			b43_phy_maskset(dev, B43_PHY_RFOVERVAL, 0xF0FF, (j << 8));
			b43_phy_maskset(dev, B43_PHY_PGACTL, 0x0FFF, 0xA000);
			b43_phy_set(dev, B43_PHY_PGACTL, 0xF000);
			udelay(20);
			trsw_rx -= 3;
			if (b43_phy_read(dev, B43_PHY_LO_LEAKAGE) >= 0xDFC)
				goto exit_loop2;
		}
	} else
		trsw_rx = 0x18;
      exit_loop2:

	if (phy->rev != 1) {	/* Not in specs, but needed to prevent PPC machine check */
		b43_phy_write(dev, B43_PHY_ANALOGOVER, backup_phy[4]);
		b43_phy_write(dev, B43_PHY_ANALOGOVERVAL, backup_phy[5]);
	}
	b43_phy_write(dev, B43_PHY_CCK(0x5A), backup_phy[6]);
	b43_phy_write(dev, B43_PHY_CCK(0x59), backup_phy[7]);
	b43_phy_write(dev, B43_PHY_CCK(0x58), backup_phy[8]);
	b43_phy_write(dev, B43_PHY_CCK(0x0A), backup_phy[9]);
	b43_phy_write(dev, B43_PHY_CCK(0x03), backup_phy[10]);
	b43_phy_write(dev, B43_PHY_LO_MASK, backup_phy[11]);
	b43_phy_write(dev, B43_PHY_LO_CTL, backup_phy[12]);
	b43_phy_write(dev, B43_PHY_CCK(0x2B), backup_phy[13]);
	b43_phy_write(dev, B43_PHY_PGACTL, backup_phy[14]);

	b43_gphy_set_baseband_attenuation(dev, backup_bband);

	b43_radio_write16(dev, 0x52, backup_radio[0]);
	b43_radio_write16(dev, 0x43, backup_radio[1]);
	b43_radio_write16(dev, 0x7A, backup_radio[2]);

	b43_phy_write(dev, B43_PHY_RFOVER, backup_phy[2] | 0x0003);
	udelay(10);
	b43_phy_write(dev, B43_PHY_RFOVER, backup_phy[2]);
	b43_phy_write(dev, B43_PHY_RFOVERVAL, backup_phy[3]);
	b43_phy_write(dev, B43_PHY_CRS0, backup_phy[0]);
	b43_phy_write(dev, B43_PHY_CCKBBANDCFG, backup_phy[1]);

	gphy->max_lb_gain =
	    ((loop1_inner_done * 6) - (loop1_outer_done * 4)) - 11;
	gphy->trsw_rx_gain = trsw_rx * 2;
}