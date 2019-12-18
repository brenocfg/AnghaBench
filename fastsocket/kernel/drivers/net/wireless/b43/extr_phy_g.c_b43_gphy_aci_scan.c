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
typedef  int u8 ;
struct b43_phy {unsigned int channel; scalar_t__ type; scalar_t__ rev; } ;
struct b43_wldev {struct b43_phy phy; } ;

/* Variables and functions */
 scalar_t__ B43_PHYTYPE_G ; 
 int B43_PHY_G_CRS ; 
 int abs (unsigned int) ; 
 int b43_gphy_aci_detect (struct b43_wldev*,unsigned int) ; 
 int /*<<< orphan*/  b43_phy_lock (struct b43_wldev*) ; 
 int /*<<< orphan*/  b43_phy_mask (struct b43_wldev*,int,int) ; 
 int /*<<< orphan*/  b43_phy_maskset (struct b43_wldev*,int,int,int) ; 
 int /*<<< orphan*/  b43_phy_set (struct b43_wldev*,int,int) ; 
 int /*<<< orphan*/  b43_phy_unlock (struct b43_wldev*) ; 
 int /*<<< orphan*/  b43_radio_lock (struct b43_wldev*) ; 
 int /*<<< orphan*/  b43_radio_unlock (struct b43_wldev*) ; 
 int /*<<< orphan*/  b43_set_all_gains (struct b43_wldev*,int,int,int) ; 
 int /*<<< orphan*/  b43_set_original_gains (struct b43_wldev*) ; 
 int /*<<< orphan*/  b43_switch_channel (struct b43_wldev*,unsigned int) ; 

__attribute__((used)) static u8 b43_gphy_aci_scan(struct b43_wldev *dev)
{
	struct b43_phy *phy = &dev->phy;
	u8 ret[13];
	unsigned int channel = phy->channel;
	unsigned int i, j, start, end;

	if (!((phy->type == B43_PHYTYPE_G) && (phy->rev > 0)))
		return 0;

	b43_phy_lock(dev);
	b43_radio_lock(dev);
	b43_phy_mask(dev, 0x0802, 0xFFFC);
	b43_phy_mask(dev, B43_PHY_G_CRS, 0x7FFF);
	b43_set_all_gains(dev, 3, 8, 1);

	start = (channel - 5 > 0) ? channel - 5 : 1;
	end = (channel + 5 < 14) ? channel + 5 : 13;

	for (i = start; i <= end; i++) {
		if (abs(channel - i) > 2)
			ret[i - 1] = b43_gphy_aci_detect(dev, i);
	}
	b43_switch_channel(dev, channel);
	b43_phy_maskset(dev, 0x0802, 0xFFFC, 0x0003);
	b43_phy_mask(dev, 0x0403, 0xFFF8);
	b43_phy_set(dev, B43_PHY_G_CRS, 0x8000);
	b43_set_original_gains(dev);
	for (i = 0; i < 13; i++) {
		if (!ret[i])
			continue;
		end = (i + 5 < 13) ? i + 5 : 13;
		for (j = i; j < end; j++)
			ret[j] = 1;
	}
	b43_radio_unlock(dev);
	b43_phy_unlock(dev);

	return ret[channel - 1];
}