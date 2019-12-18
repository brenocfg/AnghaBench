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
typedef  int /*<<< orphan*/  u16 ;
struct e1000_hw {int mac_type; scalar_t__ media_type; } ;
struct e1000_adapter {int /*<<< orphan*/  wol; struct e1000_hw hw; } ;

/* Variables and functions */
 int E1000_MANC_SMBUS_EN ; 
 int /*<<< orphan*/  MANC ; 
 int /*<<< orphan*/  MII_CR_POWER_DOWN ; 
 int /*<<< orphan*/  PHY_CTRL ; 
#define  e1000_82540 137 
#define  e1000_82541 136 
#define  e1000_82541_rev_2 135 
#define  e1000_82545 134 
#define  e1000_82545_rev_3 133 
#define  e1000_82546 132 
#define  e1000_82546_rev_3 131 
#define  e1000_82547 130 
#define  e1000_82547_rev_2 129 
#define  e1000_ce4100 128 
 scalar_t__ e1000_media_type_copper ; 
 int /*<<< orphan*/  e1000_read_phy_reg (struct e1000_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  e1000_write_phy_reg (struct e1000_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int er32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msleep (int) ; 

__attribute__((used)) static void e1000_power_down_phy(struct e1000_adapter *adapter)
{
	struct e1000_hw *hw = &adapter->hw;

	/* Power down the PHY so no link is implied when interface is down *
	 * The PHY cannot be powered down if any of the following is true *
	 * (a) WoL is enabled
	 * (b) AMT is active
	 * (c) SoL/IDER session is active */
	if (!adapter->wol && hw->mac_type >= e1000_82540 &&
	   hw->media_type == e1000_media_type_copper) {
		u16 mii_reg = 0;

		switch (hw->mac_type) {
		case e1000_82540:
		case e1000_82545:
		case e1000_82545_rev_3:
		case e1000_82546:
		case e1000_ce4100:
		case e1000_82546_rev_3:
		case e1000_82541:
		case e1000_82541_rev_2:
		case e1000_82547:
		case e1000_82547_rev_2:
			if (er32(MANC) & E1000_MANC_SMBUS_EN)
				goto out;
			break;
		default:
			goto out;
		}
		e1000_read_phy_reg(hw, PHY_CTRL, &mii_reg);
		mii_reg |= MII_CR_POWER_DOWN;
		e1000_write_phy_reg(hw, PHY_CTRL, mii_reg);
		msleep(1);
	}
out:
	return;
}