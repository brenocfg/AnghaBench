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
typedef  scalar_t__ u16 ;
struct e1000_hw {int dummy; } ;
typedef  scalar_t__ s32 ;

/* Variables and functions */
 scalar_t__ E1000_SUCCESS ; 
 int /*<<< orphan*/  M88E1000_PHY_GEN_CONTROL ; 
 int /*<<< orphan*/  M88E1000_PHY_PAGE_SELECT ; 
 scalar_t__ MII_SR_LINK_STATUS ; 
 scalar_t__ PHY_FORCE_TIME ; 
 int /*<<< orphan*/  PHY_STATUS ; 
 scalar_t__ e1000_read_phy_reg (struct e1000_hw*,int /*<<< orphan*/ ,scalar_t__*) ; 
 scalar_t__ e1000_write_phy_reg (struct e1000_hw*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  msleep (int) ; 

__attribute__((used)) static s32 e1000_polarity_reversal_workaround(struct e1000_hw *hw)
{
	s32 ret_val;
	u16 mii_status_reg;
	u16 i;

	/* Polarity reversal workaround for forced 10F/10H links. */

	/* Disable the transmitter on the PHY */

	ret_val = e1000_write_phy_reg(hw, M88E1000_PHY_PAGE_SELECT, 0x0019);
	if (ret_val)
		return ret_val;
	ret_val = e1000_write_phy_reg(hw, M88E1000_PHY_GEN_CONTROL, 0xFFFF);
	if (ret_val)
		return ret_val;

	ret_val = e1000_write_phy_reg(hw, M88E1000_PHY_PAGE_SELECT, 0x0000);
	if (ret_val)
		return ret_val;

	/* This loop will early-out if the NO link condition has been met. */
	for (i = PHY_FORCE_TIME; i > 0; i--) {
		/* Read the MII Status Register and wait for Link Status bit
		 * to be clear.
		 */

		ret_val = e1000_read_phy_reg(hw, PHY_STATUS, &mii_status_reg);
		if (ret_val)
			return ret_val;

		ret_val = e1000_read_phy_reg(hw, PHY_STATUS, &mii_status_reg);
		if (ret_val)
			return ret_val;

		if ((mii_status_reg & ~MII_SR_LINK_STATUS) == 0)
			break;
		msleep(100);
	}

	/* Recommended delay time after link has been lost */
	msleep(1000);

	/* Now we will re-enable th transmitter on the PHY */

	ret_val = e1000_write_phy_reg(hw, M88E1000_PHY_PAGE_SELECT, 0x0019);
	if (ret_val)
		return ret_val;
	msleep(50);
	ret_val = e1000_write_phy_reg(hw, M88E1000_PHY_GEN_CONTROL, 0xFFF0);
	if (ret_val)
		return ret_val;
	msleep(50);
	ret_val = e1000_write_phy_reg(hw, M88E1000_PHY_GEN_CONTROL, 0xFF00);
	if (ret_val)
		return ret_val;
	msleep(50);
	ret_val = e1000_write_phy_reg(hw, M88E1000_PHY_GEN_CONTROL, 0x0000);
	if (ret_val)
		return ret_val;

	ret_val = e1000_write_phy_reg(hw, M88E1000_PHY_PAGE_SELECT, 0x0000);
	if (ret_val)
		return ret_val;

	/* This loop will early-out if the link condition has been met. */
	for (i = PHY_FORCE_TIME; i > 0; i--) {
		/* Read the MII Status Register and wait for Link Status bit
		 * to be set.
		 */

		ret_val = e1000_read_phy_reg(hw, PHY_STATUS, &mii_status_reg);
		if (ret_val)
			return ret_val;

		ret_val = e1000_read_phy_reg(hw, PHY_STATUS, &mii_status_reg);
		if (ret_val)
			return ret_val;

		if (mii_status_reg & MII_SR_LINK_STATUS)
			break;
		msleep(100);
	}
	return E1000_SUCCESS;
}