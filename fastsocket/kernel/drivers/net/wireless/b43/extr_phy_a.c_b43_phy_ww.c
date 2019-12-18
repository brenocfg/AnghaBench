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
typedef  int u16 ;
struct b43_wldev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  B43_OFDMTAB_AGC1 ; 
 int /*<<< orphan*/  B43_OFDMTAB_AGC1_R1 ; 
 int /*<<< orphan*/  B43_PHY_CRS0 ; 
 int B43_PHY_CRS0_EN ; 
 int /*<<< orphan*/  B43_PHY_OFDM (int) ; 
 int /*<<< orphan*/  B43_PHY_OFDM61 ; 
 int /*<<< orphan*/  B43_PHY_OTABLEQ ; 
 int /*<<< orphan*/  B43_PHY_PWRDOWN ; 
 int /*<<< orphan*/  b43_ofdmtab_write16 (struct b43_wldev*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  b43_phy_mask (struct b43_wldev*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  b43_phy_maskset (struct b43_wldev*,int /*<<< orphan*/ ,int,int) ; 
 int b43_phy_read (struct b43_wldev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  b43_phy_set (struct b43_wldev*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  b43_phy_write (struct b43_wldev*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  b43_radio_mask (struct b43_wldev*,int,int) ; 
 int /*<<< orphan*/  b43_radio_maskset (struct b43_wldev*,int,int,int) ; 
 int /*<<< orphan*/  b43_radio_set (struct b43_wldev*,int,int) ; 
 int /*<<< orphan*/  b43_radio_write16 (struct b43_wldev*,int,int) ; 
 int /*<<< orphan*/  b43_wa_initgains (struct b43_wldev*) ; 

__attribute__((used)) static void b43_phy_ww(struct b43_wldev *dev)
{
	u16 b, curr_s, best_s = 0xFFFF;
	int i;

	b43_phy_mask(dev, B43_PHY_CRS0, ~B43_PHY_CRS0_EN);
	b43_phy_set(dev, B43_PHY_OFDM(0x1B), 0x1000);
	b43_phy_maskset(dev, B43_PHY_OFDM(0x82), 0xF0FF, 0x0300);
	b43_radio_set(dev, 0x0009, 0x0080);
	b43_radio_maskset(dev, 0x0012, 0xFFFC, 0x0002);
	b43_wa_initgains(dev);
	b43_phy_write(dev, B43_PHY_OFDM(0xBA), 0x3ED5);
	b = b43_phy_read(dev, B43_PHY_PWRDOWN);
	b43_phy_write(dev, B43_PHY_PWRDOWN, (b & 0xFFF8) | 0x0005);
	b43_radio_set(dev, 0x0004, 0x0004);
	for (i = 0x10; i <= 0x20; i++) {
		b43_radio_write16(dev, 0x0013, i);
		curr_s = b43_phy_read(dev, B43_PHY_OTABLEQ) & 0x00FF;
		if (!curr_s) {
			best_s = 0x0000;
			break;
		} else if (curr_s >= 0x0080)
			curr_s = 0x0100 - curr_s;
		if (curr_s < best_s)
			best_s = curr_s;
	}
	b43_phy_write(dev, B43_PHY_PWRDOWN, b);
	b43_radio_mask(dev, 0x0004, 0xFFFB);
	b43_radio_write16(dev, 0x0013, best_s);
	b43_ofdmtab_write16(dev, B43_OFDMTAB_AGC1_R1, 0, 0xFFEC);
	b43_phy_write(dev, B43_PHY_OFDM(0xB7), 0x1E80);
	b43_phy_write(dev, B43_PHY_OFDM(0xB6), 0x1C00);
	b43_phy_write(dev, B43_PHY_OFDM(0xB5), 0x0EC0);
	b43_phy_write(dev, B43_PHY_OFDM(0xB2), 0x00C0);
	b43_phy_write(dev, B43_PHY_OFDM(0xB9), 0x1FFF);
	b43_phy_maskset(dev, B43_PHY_OFDM(0xBB), 0xF000, 0x0053);
	b43_phy_maskset(dev, B43_PHY_OFDM61, 0xFE1F, 0x0120);
	b43_phy_maskset(dev, B43_PHY_OFDM(0x13), 0x0FFF, 0x3000);
	b43_phy_maskset(dev, B43_PHY_OFDM(0x14), 0x0FFF, 0x3000);
	b43_ofdmtab_write16(dev, B43_OFDMTAB_AGC1, 6, 0x0017);
	for (i = 0; i < 6; i++)
		b43_ofdmtab_write16(dev, B43_OFDMTAB_AGC1, i, 0x000F);
	b43_ofdmtab_write16(dev, B43_OFDMTAB_AGC1, 0x0D, 0x000E);
	b43_ofdmtab_write16(dev, B43_OFDMTAB_AGC1, 0x0E, 0x0011);
	b43_ofdmtab_write16(dev, B43_OFDMTAB_AGC1, 0x0F, 0x0013);
	b43_phy_write(dev, B43_PHY_OFDM(0x33), 0x5030);
	b43_phy_set(dev, B43_PHY_CRS0, B43_PHY_CRS0_EN);
}