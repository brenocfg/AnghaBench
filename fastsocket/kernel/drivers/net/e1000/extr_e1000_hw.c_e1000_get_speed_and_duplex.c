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
typedef  scalar_t__ u16 ;
struct e1000_hw {scalar_t__ mac_type; scalar_t__ phy_type; scalar_t__ speed_downgraded; } ;
typedef  scalar_t__ s32 ;

/* Variables and functions */
 int E1000_STATUS_FD ; 
 int E1000_STATUS_SPEED_100 ; 
 int E1000_STATUS_SPEED_1000 ; 
 scalar_t__ E1000_SUCCESS ; 
 scalar_t__ FULL_DUPLEX ; 
 scalar_t__ HALF_DUPLEX ; 
 scalar_t__ NWAY_ER_LP_NWAY_CAPS ; 
 scalar_t__ NWAY_LPAR_100TX_FD_CAPS ; 
 scalar_t__ NWAY_LPAR_10T_FD_CAPS ; 
 int /*<<< orphan*/  PHY_AUTONEG_EXP ; 
 int /*<<< orphan*/  PHY_LP_ABILITY ; 
 scalar_t__ SPEED_10 ; 
 scalar_t__ SPEED_100 ; 
 scalar_t__ SPEED_1000 ; 
 int /*<<< orphan*/  STATUS ; 
 scalar_t__ e1000_82543 ; 
 scalar_t__ e1000_phy_igp ; 
 scalar_t__ e1000_read_phy_reg (struct e1000_hw*,int /*<<< orphan*/ ,scalar_t__*) ; 
 int /*<<< orphan*/  e_dbg (char*) ; 
 int er32 (int /*<<< orphan*/ ) ; 

s32 e1000_get_speed_and_duplex(struct e1000_hw *hw, u16 *speed, u16 *duplex)
{
	u32 status;
	s32 ret_val;
	u16 phy_data;

	e_dbg("e1000_get_speed_and_duplex");

	if (hw->mac_type >= e1000_82543) {
		status = er32(STATUS);
		if (status & E1000_STATUS_SPEED_1000) {
			*speed = SPEED_1000;
			e_dbg("1000 Mbs, ");
		} else if (status & E1000_STATUS_SPEED_100) {
			*speed = SPEED_100;
			e_dbg("100 Mbs, ");
		} else {
			*speed = SPEED_10;
			e_dbg("10 Mbs, ");
		}

		if (status & E1000_STATUS_FD) {
			*duplex = FULL_DUPLEX;
			e_dbg("Full Duplex\n");
		} else {
			*duplex = HALF_DUPLEX;
			e_dbg(" Half Duplex\n");
		}
	} else {
		e_dbg("1000 Mbs, Full Duplex\n");
		*speed = SPEED_1000;
		*duplex = FULL_DUPLEX;
	}

	/* IGP01 PHY may advertise full duplex operation after speed downgrade even
	 * if it is operating at half duplex.  Here we set the duplex settings to
	 * match the duplex in the link partner's capabilities.
	 */
	if (hw->phy_type == e1000_phy_igp && hw->speed_downgraded) {
		ret_val = e1000_read_phy_reg(hw, PHY_AUTONEG_EXP, &phy_data);
		if (ret_val)
			return ret_val;

		if (!(phy_data & NWAY_ER_LP_NWAY_CAPS))
			*duplex = HALF_DUPLEX;
		else {
			ret_val =
			    e1000_read_phy_reg(hw, PHY_LP_ABILITY, &phy_data);
			if (ret_val)
				return ret_val;
			if ((*speed == SPEED_100
			     && !(phy_data & NWAY_LPAR_100TX_FD_CAPS))
			    || (*speed == SPEED_10
				&& !(phy_data & NWAY_LPAR_10T_FD_CAPS)))
				*duplex = HALF_DUPLEX;
		}
	}

	return E1000_SUCCESS;
}