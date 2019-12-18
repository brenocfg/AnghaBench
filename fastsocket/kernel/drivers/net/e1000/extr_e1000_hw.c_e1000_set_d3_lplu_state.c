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
struct e1000_hw {scalar_t__ phy_type; scalar_t__ mac_type; scalar_t__ smart_speed; scalar_t__ autoneg_advertised; } ;
typedef  scalar_t__ s32 ;

/* Variables and functions */
 scalar_t__ AUTONEG_ADVERTISE_10_100_ALL ; 
 scalar_t__ AUTONEG_ADVERTISE_10_ALL ; 
 scalar_t__ AUTONEG_ADVERTISE_SPEED_DEFAULT ; 
 scalar_t__ E1000_SUCCESS ; 
 int /*<<< orphan*/  IGP01E1000_GMII_FIFO ; 
 int /*<<< orphan*/  IGP01E1000_GMII_FLEX_SPD ; 
 int /*<<< orphan*/  IGP01E1000_PHY_PORT_CONFIG ; 
 int /*<<< orphan*/  IGP01E1000_PSCFR_SMART_SPEED ; 
 scalar_t__ e1000_82541_rev_2 ; 
 scalar_t__ e1000_82547_rev_2 ; 
 scalar_t__ e1000_phy_igp ; 
 scalar_t__ e1000_read_phy_reg (struct e1000_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ e1000_smart_speed_off ; 
 scalar_t__ e1000_smart_speed_on ; 
 scalar_t__ e1000_write_phy_reg (struct e1000_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  e_dbg (char*) ; 

__attribute__((used)) static s32 e1000_set_d3_lplu_state(struct e1000_hw *hw, bool active)
{
	s32 ret_val;
	u16 phy_data;
	e_dbg("e1000_set_d3_lplu_state");

	if (hw->phy_type != e1000_phy_igp)
		return E1000_SUCCESS;

	/* During driver activity LPLU should not be used or it will attain link
	 * from the lowest speeds starting from 10Mbps. The capability is used for
	 * Dx transitions and states */
	if (hw->mac_type == e1000_82541_rev_2
	    || hw->mac_type == e1000_82547_rev_2) {
		ret_val =
		    e1000_read_phy_reg(hw, IGP01E1000_GMII_FIFO, &phy_data);
		if (ret_val)
			return ret_val;
	}

	if (!active) {
		if (hw->mac_type == e1000_82541_rev_2 ||
		    hw->mac_type == e1000_82547_rev_2) {
			phy_data &= ~IGP01E1000_GMII_FLEX_SPD;
			ret_val =
			    e1000_write_phy_reg(hw, IGP01E1000_GMII_FIFO,
						phy_data);
			if (ret_val)
				return ret_val;
		}

		/* LPLU and SmartSpeed are mutually exclusive.  LPLU is used during
		 * Dx states where the power conservation is most important.  During
		 * driver activity we should enable SmartSpeed, so performance is
		 * maintained. */
		if (hw->smart_speed == e1000_smart_speed_on) {
			ret_val =
			    e1000_read_phy_reg(hw, IGP01E1000_PHY_PORT_CONFIG,
					       &phy_data);
			if (ret_val)
				return ret_val;

			phy_data |= IGP01E1000_PSCFR_SMART_SPEED;
			ret_val =
			    e1000_write_phy_reg(hw, IGP01E1000_PHY_PORT_CONFIG,
						phy_data);
			if (ret_val)
				return ret_val;
		} else if (hw->smart_speed == e1000_smart_speed_off) {
			ret_val =
			    e1000_read_phy_reg(hw, IGP01E1000_PHY_PORT_CONFIG,
					       &phy_data);
			if (ret_val)
				return ret_val;

			phy_data &= ~IGP01E1000_PSCFR_SMART_SPEED;
			ret_val =
			    e1000_write_phy_reg(hw, IGP01E1000_PHY_PORT_CONFIG,
						phy_data);
			if (ret_val)
				return ret_val;
		}
	} else if ((hw->autoneg_advertised == AUTONEG_ADVERTISE_SPEED_DEFAULT)
		   || (hw->autoneg_advertised == AUTONEG_ADVERTISE_10_ALL)
		   || (hw->autoneg_advertised ==
		       AUTONEG_ADVERTISE_10_100_ALL)) {

		if (hw->mac_type == e1000_82541_rev_2 ||
		    hw->mac_type == e1000_82547_rev_2) {
			phy_data |= IGP01E1000_GMII_FLEX_SPD;
			ret_val =
			    e1000_write_phy_reg(hw, IGP01E1000_GMII_FIFO,
						phy_data);
			if (ret_val)
				return ret_val;
		}

		/* When LPLU is enabled we should disable SmartSpeed */
		ret_val =
		    e1000_read_phy_reg(hw, IGP01E1000_PHY_PORT_CONFIG,
				       &phy_data);
		if (ret_val)
			return ret_val;

		phy_data &= ~IGP01E1000_PSCFR_SMART_SPEED;
		ret_val =
		    e1000_write_phy_reg(hw, IGP01E1000_PHY_PORT_CONFIG,
					phy_data);
		if (ret_val)
			return ret_val;

	}
	return E1000_SUCCESS;
}