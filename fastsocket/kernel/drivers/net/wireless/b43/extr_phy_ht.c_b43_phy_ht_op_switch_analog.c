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
struct b43_wldev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  B43_PHY_HT_AFE_C1 ; 
 int /*<<< orphan*/  B43_PHY_HT_AFE_C1_OVER ; 
 int /*<<< orphan*/  B43_PHY_HT_AFE_C2 ; 
 int /*<<< orphan*/  B43_PHY_HT_AFE_C2_OVER ; 
 int /*<<< orphan*/  B43_PHY_HT_AFE_C3 ; 
 int /*<<< orphan*/  B43_PHY_HT_AFE_C3_OVER ; 
 int /*<<< orphan*/  b43_phy_write (struct b43_wldev*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void b43_phy_ht_op_switch_analog(struct b43_wldev *dev, bool on)
{
	if (on) {
		b43_phy_write(dev, B43_PHY_HT_AFE_C1, 0x00cd);
		b43_phy_write(dev, B43_PHY_HT_AFE_C1_OVER, 0x0000);
		b43_phy_write(dev, B43_PHY_HT_AFE_C2, 0x00cd);
		b43_phy_write(dev, B43_PHY_HT_AFE_C2_OVER, 0x0000);
		b43_phy_write(dev, B43_PHY_HT_AFE_C3, 0x00cd);
		b43_phy_write(dev, B43_PHY_HT_AFE_C3_OVER, 0x0000);
	} else {
		b43_phy_write(dev, B43_PHY_HT_AFE_C1_OVER, 0x07ff);
		b43_phy_write(dev, B43_PHY_HT_AFE_C1, 0x00fd);
		b43_phy_write(dev, B43_PHY_HT_AFE_C2_OVER, 0x07ff);
		b43_phy_write(dev, B43_PHY_HT_AFE_C2, 0x00fd);
		b43_phy_write(dev, B43_PHY_HT_AFE_C3_OVER, 0x07ff);
		b43_phy_write(dev, B43_PHY_HT_AFE_C3, 0x00fd);
	}
}