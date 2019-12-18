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
struct b43_phy {int radio_ver; int radio_rev; } ;
struct b43_wldev {struct b43_phy phy; } ;

/* Variables and functions */
 int /*<<< orphan*/  b43_has_hardware_pctl (struct b43_wldev*) ; 
 int /*<<< orphan*/  b43_phy_mask (struct b43_wldev*,int,int) ; 
 int /*<<< orphan*/  b43_phy_maskset (struct b43_wldev*,int,int,int) ; 
 int /*<<< orphan*/  b43_phy_set (struct b43_wldev*,int,int) ; 
 int /*<<< orphan*/  b43_phy_write (struct b43_wldev*,int,int) ; 

__attribute__((used)) static void b43_hardware_pctl_early_init(struct b43_wldev *dev)
{
	struct b43_phy *phy = &dev->phy;

	if (!b43_has_hardware_pctl(dev)) {
		b43_phy_write(dev, 0x047A, 0xC111);
		return;
	}

	b43_phy_mask(dev, 0x0036, 0xFEFF);
	b43_phy_write(dev, 0x002F, 0x0202);
	b43_phy_set(dev, 0x047C, 0x0002);
	b43_phy_set(dev, 0x047A, 0xF000);
	if (phy->radio_ver == 0x2050 && phy->radio_rev == 8) {
		b43_phy_maskset(dev, 0x047A, 0xFF0F, 0x0010);
		b43_phy_set(dev, 0x005D, 0x8000);
		b43_phy_maskset(dev, 0x004E, 0xFFC0, 0x0010);
		b43_phy_write(dev, 0x002E, 0xC07F);
		b43_phy_set(dev, 0x0036, 0x0400);
	} else {
		b43_phy_set(dev, 0x0036, 0x0200);
		b43_phy_set(dev, 0x0036, 0x0400);
		b43_phy_mask(dev, 0x005D, 0x7FFF);
		b43_phy_mask(dev, 0x004F, 0xFFFE);
		b43_phy_maskset(dev, 0x004E, 0xFFC0, 0x0010);
		b43_phy_write(dev, 0x002E, 0xC07F);
		b43_phy_maskset(dev, 0x047A, 0xFF0F, 0x0010);
	}
}