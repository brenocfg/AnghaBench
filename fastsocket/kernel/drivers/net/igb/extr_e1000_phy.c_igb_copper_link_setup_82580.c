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
typedef  int /*<<< orphan*/  u16 ;
struct TYPE_2__ {scalar_t__ (* write_reg ) (struct e1000_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;scalar_t__ (* read_reg ) (struct e1000_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ;scalar_t__ (* reset ) (struct e1000_hw*) ;} ;
struct e1000_phy_info {scalar_t__ type; int mdix; TYPE_1__ ops; scalar_t__ reset_disable; } ;
struct e1000_hw {struct e1000_phy_info phy; } ;
typedef  scalar_t__ s32 ;

/* Variables and functions */
 int /*<<< orphan*/  I82580_CFG_ASSERT_CRS_ON_TX ; 
 int /*<<< orphan*/  I82580_CFG_ENABLE_DOWNSHIFT ; 
 int /*<<< orphan*/  I82580_CFG_REG ; 
 int /*<<< orphan*/  I82580_PHY_CTRL2_AUTO_MDI_MDIX ; 
 int /*<<< orphan*/  I82580_PHY_CTRL2_MANUAL_MDIX ; 
 int /*<<< orphan*/  I82580_PHY_CTRL2_MDIX_CFG_MASK ; 
 int /*<<< orphan*/  I82580_PHY_CTRL_2 ; 
 scalar_t__ e1000_phy_82580 ; 
 int /*<<< orphan*/  hw_dbg (char*) ; 
 scalar_t__ stub1 (struct e1000_hw*) ; 
 scalar_t__ stub2 (struct e1000_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ stub3 (struct e1000_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ stub4 (struct e1000_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ stub5 (struct e1000_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

s32 igb_copper_link_setup_82580(struct e1000_hw *hw)
{
	struct e1000_phy_info *phy = &hw->phy;
	s32 ret_val;
	u16 phy_data;

	if (phy->reset_disable) {
		ret_val = 0;
		goto out;
	}

	if (phy->type == e1000_phy_82580) {
		ret_val = hw->phy.ops.reset(hw);
		if (ret_val) {
			hw_dbg("Error resetting the PHY.\n");
			goto out;
		}
	}

	/* Enable CRS on TX. This must be set for half-duplex operation. */
	ret_val = phy->ops.read_reg(hw, I82580_CFG_REG, &phy_data);
	if (ret_val)
		goto out;

	phy_data |= I82580_CFG_ASSERT_CRS_ON_TX;

	/* Enable downshift */
	phy_data |= I82580_CFG_ENABLE_DOWNSHIFT;

	ret_val = phy->ops.write_reg(hw, I82580_CFG_REG, phy_data);
	if (ret_val)
		goto out;

	/* Set MDI/MDIX mode */
	ret_val = phy->ops.read_reg(hw, I82580_PHY_CTRL_2, &phy_data);
	if (ret_val)
		goto out;
	phy_data &= ~I82580_PHY_CTRL2_MDIX_CFG_MASK;
	/* Options:
	 *   0 - Auto (default)
	 *   1 - MDI mode
	 *   2 - MDI-X mode
	 */
	switch (hw->phy.mdix) {
	case 1:
		break;
	case 2:
		phy_data |= I82580_PHY_CTRL2_MANUAL_MDIX;
		break;
	case 0:
	default:
		phy_data |= I82580_PHY_CTRL2_AUTO_MDI_MDIX;
		break;
	}
	ret_val = hw->phy.ops.write_reg(hw, I82580_PHY_CTRL_2, phy_data);

out:
	return ret_val;
}