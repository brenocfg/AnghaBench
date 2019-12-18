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
 int /*<<< orphan*/  B43_PHY_ANTDWELL ; 
 int /*<<< orphan*/  B43_PHY_CRSTHRES1 ; 
 int /*<<< orphan*/  B43_PHY_CRSTHRES1_R1 ; 
 int /*<<< orphan*/  B43_PHY_CRSTHRES2 ; 
 int /*<<< orphan*/  B43_PHY_OFDM (int) ; 
 int /*<<< orphan*/  b43_phy_set (struct b43_wldev*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  b43_phy_write (struct b43_wldev*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void b43_wa_crs_ed(struct b43_wldev *dev)
{
	struct b43_phy *phy = &dev->phy;

	if (phy->rev == 1) {
		b43_phy_write(dev, B43_PHY_CRSTHRES1_R1, 0x4F19);
	} else if (phy->rev == 2) {
		b43_phy_write(dev, B43_PHY_CRSTHRES1, 0x1861);
		b43_phy_write(dev, B43_PHY_CRSTHRES2, 0x0271);
		b43_phy_set(dev, B43_PHY_ANTDWELL, 0x0800);
	} else {
		b43_phy_write(dev, B43_PHY_CRSTHRES1, 0x0098);
		b43_phy_write(dev, B43_PHY_CRSTHRES2, 0x0070);
		b43_phy_write(dev, B43_PHY_OFDM(0xC9), 0x0080);
		b43_phy_set(dev, B43_PHY_ANTDWELL, 0x0800);
	}
}