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
struct b43_phy {int rev; } ;
struct b43_wldev {struct b43_phy phy; } ;

/* Variables and functions */
 int /*<<< orphan*/  B43_OFDMTAB_LPFGAIN ; 
 int B43_PHY_LNAHPFCTL ; 
 int /*<<< orphan*/  B43_PHY_LPFGAINCTL ; 
 int /*<<< orphan*/  b43_ofdmtab_write16 (struct b43_wldev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  b43_phy_mask (struct b43_wldev*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  b43_phy_maskset (struct b43_wldev*,int,int,int) ; 
 int /*<<< orphan*/  b43_phy_write (struct b43_wldev*,int,int) ; 
 int /*<<< orphan*/  b43_radio_write16 (struct b43_wldev*,int,int) ; 

void b43_wa_initgains(struct b43_wldev *dev)
{
	struct b43_phy *phy = &dev->phy;

	b43_phy_write(dev, B43_PHY_LNAHPFCTL, 0x1FF9);
	b43_phy_mask(dev, B43_PHY_LPFGAINCTL, 0xFF0F);
	if (phy->rev <= 2)
		b43_ofdmtab_write16(dev, B43_OFDMTAB_LPFGAIN, 0, 0x1FBF);
	b43_radio_write16(dev, 0x0002, 0x1FBF);

	b43_phy_write(dev, 0x0024, 0x4680);
	b43_phy_write(dev, 0x0020, 0x0003);
	b43_phy_write(dev, 0x001D, 0x0F40);
	b43_phy_write(dev, 0x001F, 0x1C00);
	if (phy->rev <= 3)
		b43_phy_maskset(dev, 0x002A, 0x00FF, 0x0400);
	else if (phy->rev == 5) {
		b43_phy_maskset(dev, 0x002A, 0x00FF, 0x1A00);
		b43_phy_write(dev, 0x00CC, 0x2121);
	}
	if (phy->rev >= 3)
		b43_phy_write(dev, 0x00BA, 0x3ED5);
}