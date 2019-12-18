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
struct e1000_hw {scalar_t__ phy_type; scalar_t__ autoneg; } ;
typedef  scalar_t__ s32 ;

/* Variables and functions */
 scalar_t__ E1000_SUCCESS ; 
 int MII_SR_LINK_STATUS ; 
 int /*<<< orphan*/  PHY_STATUS ; 
 scalar_t__ e1000_copper_link_autoneg (struct e1000_hw*) ; 
 scalar_t__ e1000_copper_link_igp_setup (struct e1000_hw*) ; 
 scalar_t__ e1000_copper_link_mgp_setup (struct e1000_hw*) ; 
 scalar_t__ e1000_copper_link_postconfig (struct e1000_hw*) ; 
 scalar_t__ e1000_copper_link_preconfig (struct e1000_hw*) ; 
 scalar_t__ e1000_phy_force_speed_duplex (struct e1000_hw*) ; 
 scalar_t__ e1000_phy_igp ; 
 scalar_t__ e1000_phy_m88 ; 
 scalar_t__ e1000_read_phy_reg (struct e1000_hw*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  e_dbg (char*) ; 
 scalar_t__ gbe_dhg_phy_setup (struct e1000_hw*) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static s32 e1000_setup_copper_link(struct e1000_hw *hw)
{
	s32 ret_val;
	u16 i;
	u16 phy_data;

	e_dbg("e1000_setup_copper_link");

	/* Check if it is a valid PHY and set PHY mode if necessary. */
	ret_val = e1000_copper_link_preconfig(hw);
	if (ret_val)
		return ret_val;

	if (hw->phy_type == e1000_phy_igp) {
		ret_val = e1000_copper_link_igp_setup(hw);
		if (ret_val)
			return ret_val;
	} else if (hw->phy_type == e1000_phy_m88) {
		ret_val = e1000_copper_link_mgp_setup(hw);
		if (ret_val)
			return ret_val;
	} else {
		ret_val = gbe_dhg_phy_setup(hw);
		if (ret_val) {
			e_dbg("gbe_dhg_phy_setup failed!\n");
			return ret_val;
		}
	}

	if (hw->autoneg) {
		/* Setup autoneg and flow control advertisement
		 * and perform autonegotiation */
		ret_val = e1000_copper_link_autoneg(hw);
		if (ret_val)
			return ret_val;
	} else {
		/* PHY will be set to 10H, 10F, 100H,or 100F
		 * depending on value from forced_speed_duplex. */
		e_dbg("Forcing speed and duplex\n");
		ret_val = e1000_phy_force_speed_duplex(hw);
		if (ret_val) {
			e_dbg("Error Forcing Speed and Duplex\n");
			return ret_val;
		}
	}

	/* Check link status. Wait up to 100 microseconds for link to become
	 * valid.
	 */
	for (i = 0; i < 10; i++) {
		ret_val = e1000_read_phy_reg(hw, PHY_STATUS, &phy_data);
		if (ret_val)
			return ret_val;
		ret_val = e1000_read_phy_reg(hw, PHY_STATUS, &phy_data);
		if (ret_val)
			return ret_val;

		if (phy_data & MII_SR_LINK_STATUS) {
			/* Config the MAC and PHY after link is up */
			ret_val = e1000_copper_link_postconfig(hw);
			if (ret_val)
				return ret_val;

			e_dbg("Valid link established!!!\n");
			return E1000_SUCCESS;
		}
		udelay(10);
	}

	e_dbg("Unable to establish link!!!\n");
	return E1000_SUCCESS;
}