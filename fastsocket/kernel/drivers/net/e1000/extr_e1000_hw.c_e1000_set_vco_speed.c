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
struct e1000_hw {int mac_type; } ;
typedef  scalar_t__ s32 ;

/* Variables and functions */
 scalar_t__ E1000_SUCCESS ; 
 int /*<<< orphan*/  M88E1000_PHY_GEN_CONTROL ; 
 int /*<<< orphan*/  M88E1000_PHY_PAGE_SELECT ; 
 int M88E1000_PHY_VCO_REG_BIT11 ; 
 int M88E1000_PHY_VCO_REG_BIT8 ; 
#define  e1000_82545_rev_3 129 
#define  e1000_82546_rev_3 128 
 scalar_t__ e1000_read_phy_reg (struct e1000_hw*,int /*<<< orphan*/ ,int*) ; 
 scalar_t__ e1000_write_phy_reg (struct e1000_hw*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  e_dbg (char*) ; 

__attribute__((used)) static s32 e1000_set_vco_speed(struct e1000_hw *hw)
{
	s32 ret_val;
	u16 default_page = 0;
	u16 phy_data;

	e_dbg("e1000_set_vco_speed");

	switch (hw->mac_type) {
	case e1000_82545_rev_3:
	case e1000_82546_rev_3:
		break;
	default:
		return E1000_SUCCESS;
	}

	/* Set PHY register 30, page 5, bit 8 to 0 */

	ret_val =
	    e1000_read_phy_reg(hw, M88E1000_PHY_PAGE_SELECT, &default_page);
	if (ret_val)
		return ret_val;

	ret_val = e1000_write_phy_reg(hw, M88E1000_PHY_PAGE_SELECT, 0x0005);
	if (ret_val)
		return ret_val;

	ret_val = e1000_read_phy_reg(hw, M88E1000_PHY_GEN_CONTROL, &phy_data);
	if (ret_val)
		return ret_val;

	phy_data &= ~M88E1000_PHY_VCO_REG_BIT8;
	ret_val = e1000_write_phy_reg(hw, M88E1000_PHY_GEN_CONTROL, phy_data);
	if (ret_val)
		return ret_val;

	/* Set PHY register 30, page 4, bit 11 to 1 */

	ret_val = e1000_write_phy_reg(hw, M88E1000_PHY_PAGE_SELECT, 0x0004);
	if (ret_val)
		return ret_val;

	ret_val = e1000_read_phy_reg(hw, M88E1000_PHY_GEN_CONTROL, &phy_data);
	if (ret_val)
		return ret_val;

	phy_data |= M88E1000_PHY_VCO_REG_BIT11;
	ret_val = e1000_write_phy_reg(hw, M88E1000_PHY_GEN_CONTROL, phy_data);
	if (ret_val)
		return ret_val;

	ret_val =
	    e1000_write_phy_reg(hw, M88E1000_PHY_PAGE_SELECT, default_page);
	if (ret_val)
		return ret_val;

	return E1000_SUCCESS;
}