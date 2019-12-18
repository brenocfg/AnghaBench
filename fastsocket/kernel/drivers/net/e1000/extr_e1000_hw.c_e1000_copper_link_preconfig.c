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
typedef  int u32 ;
typedef  int u16 ;
struct e1000_hw {scalar_t__ mac_type; int phy_reset_disable; int /*<<< orphan*/  phy_id; } ;
typedef  scalar_t__ s32 ;

/* Variables and functions */
 int /*<<< orphan*/  CTRL ; 
 int E1000_CTRL_FRCDPX ; 
 int E1000_CTRL_FRCSPD ; 
 int E1000_CTRL_SLU ; 
 scalar_t__ E1000_SUCCESS ; 
 int /*<<< orphan*/  M88E1000_PHY_SPEC_CTRL ; 
 scalar_t__ e1000_82541 ; 
 scalar_t__ e1000_82541_rev_2 ; 
 scalar_t__ e1000_82543 ; 
 scalar_t__ e1000_82545_rev_3 ; 
 scalar_t__ e1000_82546_rev_3 ; 
 scalar_t__ e1000_82547 ; 
 scalar_t__ e1000_82547_rev_2 ; 
 scalar_t__ e1000_detect_gig_phy (struct e1000_hw*) ; 
 scalar_t__ e1000_phy_hw_reset (struct e1000_hw*) ; 
 scalar_t__ e1000_read_phy_reg (struct e1000_hw*,int /*<<< orphan*/ ,int*) ; 
 scalar_t__ e1000_set_phy_mode (struct e1000_hw*) ; 
 scalar_t__ e1000_write_phy_reg (struct e1000_hw*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  e_dbg (char*,...) ; 
 int er32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ew32 (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static s32 e1000_copper_link_preconfig(struct e1000_hw *hw)
{
	u32 ctrl;
	s32 ret_val;
	u16 phy_data;

	e_dbg("e1000_copper_link_preconfig");

	ctrl = er32(CTRL);
	/* With 82543, we need to force speed and duplex on the MAC equal to what
	 * the PHY speed and duplex configuration is. In addition, we need to
	 * perform a hardware reset on the PHY to take it out of reset.
	 */
	if (hw->mac_type > e1000_82543) {
		ctrl |= E1000_CTRL_SLU;
		ctrl &= ~(E1000_CTRL_FRCSPD | E1000_CTRL_FRCDPX);
		ew32(CTRL, ctrl);
	} else {
		ctrl |=
		    (E1000_CTRL_FRCSPD | E1000_CTRL_FRCDPX | E1000_CTRL_SLU);
		ew32(CTRL, ctrl);
		ret_val = e1000_phy_hw_reset(hw);
		if (ret_val)
			return ret_val;
	}

	/* Make sure we have a valid PHY */
	ret_val = e1000_detect_gig_phy(hw);
	if (ret_val) {
		e_dbg("Error, did not detect valid phy.\n");
		return ret_val;
	}
	e_dbg("Phy ID = %x\n", hw->phy_id);

	/* Set PHY to class A mode (if necessary) */
	ret_val = e1000_set_phy_mode(hw);
	if (ret_val)
		return ret_val;

	if ((hw->mac_type == e1000_82545_rev_3) ||
	    (hw->mac_type == e1000_82546_rev_3)) {
		ret_val =
		    e1000_read_phy_reg(hw, M88E1000_PHY_SPEC_CTRL, &phy_data);
		phy_data |= 0x00000008;
		ret_val =
		    e1000_write_phy_reg(hw, M88E1000_PHY_SPEC_CTRL, phy_data);
	}

	if (hw->mac_type <= e1000_82543 ||
	    hw->mac_type == e1000_82541 || hw->mac_type == e1000_82547 ||
	    hw->mac_type == e1000_82541_rev_2
	    || hw->mac_type == e1000_82547_rev_2)
		hw->phy_reset_disable = false;

	return E1000_SUCCESS;
}