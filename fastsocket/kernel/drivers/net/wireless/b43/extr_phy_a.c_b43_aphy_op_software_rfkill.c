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
struct b43_phy {scalar_t__ radio_on; } ;
struct b43_wldev {struct b43_phy phy; } ;

/* Variables and functions */
 int /*<<< orphan*/  b43_phy_mask (struct b43_wldev*,int,int) ; 
 int /*<<< orphan*/  b43_phy_set (struct b43_wldev*,int,int) ; 
 int /*<<< orphan*/  b43_radio_init2060 (struct b43_wldev*) ; 
 int /*<<< orphan*/  b43_radio_write16 (struct b43_wldev*,int,int) ; 

__attribute__((used)) static void b43_aphy_op_software_rfkill(struct b43_wldev *dev,
					bool blocked)
{
	struct b43_phy *phy = &dev->phy;

	if (!blocked) {
		if (phy->radio_on)
			return;
		b43_radio_write16(dev, 0x0004, 0x00C0);
		b43_radio_write16(dev, 0x0005, 0x0008);
		b43_phy_mask(dev, 0x0010, 0xFFF7);
		b43_phy_mask(dev, 0x0011, 0xFFF7);
		b43_radio_init2060(dev);
	} else {
		b43_radio_write16(dev, 0x0004, 0x00FF);
		b43_radio_write16(dev, 0x0005, 0x00FB);
		b43_phy_set(dev, 0x0010, 0x0008);
		b43_phy_set(dev, 0x0011, 0x0008);
	}
}