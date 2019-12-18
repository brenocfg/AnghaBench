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
struct e1000_phy_info {void* remote_rx; void* local_rx; scalar_t__ cable_length; scalar_t__ mdix_mode; int /*<<< orphan*/  cable_polarity; int /*<<< orphan*/  polarity_correction; int /*<<< orphan*/  extended_10bt_distance; scalar_t__ downshift; } ;
struct e1000_hw {scalar_t__ speed_downgraded; } ;
typedef  scalar_t__ s32 ;
typedef  int /*<<< orphan*/  e1000_rev_polarity ;
typedef  scalar_t__ e1000_downshift ;
typedef  scalar_t__ e1000_cable_length ;
typedef  scalar_t__ e1000_auto_x_mode ;

/* Variables and functions */
 scalar_t__ E1000_SUCCESS ; 
 int /*<<< orphan*/  M88E1000_PHY_SPEC_CTRL ; 
 int /*<<< orphan*/  M88E1000_PHY_SPEC_STATUS ; 
 int M88E1000_PSCR_10BT_EXT_DIST_ENABLE ; 
 int M88E1000_PSCR_10BT_EXT_DIST_ENABLE_SHIFT ; 
 int M88E1000_PSCR_POLARITY_REVERSAL ; 
 int M88E1000_PSCR_POLARITY_REVERSAL_SHIFT ; 
 int M88E1000_PSSR_1000MBS ; 
 int M88E1000_PSSR_CABLE_LENGTH ; 
 int M88E1000_PSSR_CABLE_LENGTH_SHIFT ; 
 int M88E1000_PSSR_MDIX ; 
 int M88E1000_PSSR_MDIX_SHIFT ; 
 int M88E1000_PSSR_SPEED ; 
 int /*<<< orphan*/  PHY_1000T_STATUS ; 
 int SR_1000T_LOCAL_RX_STATUS ; 
 int SR_1000T_LOCAL_RX_STATUS_SHIFT ; 
 int SR_1000T_REMOTE_RX_STATUS ; 
 int SR_1000T_REMOTE_RX_STATUS_SHIFT ; 
 void* e1000_1000t_rx_status_not_ok ; 
 void* e1000_1000t_rx_status_ok ; 
 int /*<<< orphan*/  e1000_10bt_ext_dist_enable_lower ; 
 int /*<<< orphan*/  e1000_10bt_ext_dist_enable_normal ; 
 scalar_t__ e1000_check_polarity (struct e1000_hw*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  e1000_polarity_reversal_disabled ; 
 int /*<<< orphan*/  e1000_polarity_reversal_enabled ; 
 scalar_t__ e1000_read_phy_reg (struct e1000_hw*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  e_dbg (char*) ; 

__attribute__((used)) static s32 e1000_phy_m88_get_info(struct e1000_hw *hw,
				  struct e1000_phy_info *phy_info)
{
	s32 ret_val;
	u16 phy_data;
	e1000_rev_polarity polarity;

	e_dbg("e1000_phy_m88_get_info");

	/* The downshift status is checked only once, after link is established,
	 * and it stored in the hw->speed_downgraded parameter. */
	phy_info->downshift = (e1000_downshift) hw->speed_downgraded;

	ret_val = e1000_read_phy_reg(hw, M88E1000_PHY_SPEC_CTRL, &phy_data);
	if (ret_val)
		return ret_val;

	phy_info->extended_10bt_distance =
	    ((phy_data & M88E1000_PSCR_10BT_EXT_DIST_ENABLE) >>
	     M88E1000_PSCR_10BT_EXT_DIST_ENABLE_SHIFT) ?
	    e1000_10bt_ext_dist_enable_lower :
	    e1000_10bt_ext_dist_enable_normal;

	phy_info->polarity_correction =
	    ((phy_data & M88E1000_PSCR_POLARITY_REVERSAL) >>
	     M88E1000_PSCR_POLARITY_REVERSAL_SHIFT) ?
	    e1000_polarity_reversal_disabled : e1000_polarity_reversal_enabled;

	/* Check polarity status */
	ret_val = e1000_check_polarity(hw, &polarity);
	if (ret_val)
		return ret_val;
	phy_info->cable_polarity = polarity;

	ret_val = e1000_read_phy_reg(hw, M88E1000_PHY_SPEC_STATUS, &phy_data);
	if (ret_val)
		return ret_val;

	phy_info->mdix_mode =
	    (e1000_auto_x_mode) ((phy_data & M88E1000_PSSR_MDIX) >>
				 M88E1000_PSSR_MDIX_SHIFT);

	if ((phy_data & M88E1000_PSSR_SPEED) == M88E1000_PSSR_1000MBS) {
		/* Cable Length Estimation and Local/Remote Receiver Information
		 * are only valid at 1000 Mbps.
		 */
		phy_info->cable_length =
		    (e1000_cable_length) ((phy_data &
					   M88E1000_PSSR_CABLE_LENGTH) >>
					  M88E1000_PSSR_CABLE_LENGTH_SHIFT);

		ret_val = e1000_read_phy_reg(hw, PHY_1000T_STATUS, &phy_data);
		if (ret_val)
			return ret_val;

		phy_info->local_rx = ((phy_data & SR_1000T_LOCAL_RX_STATUS) >>
				      SR_1000T_LOCAL_RX_STATUS_SHIFT) ?
		    e1000_1000t_rx_status_ok : e1000_1000t_rx_status_not_ok;
		phy_info->remote_rx = ((phy_data & SR_1000T_REMOTE_RX_STATUS) >>
				       SR_1000T_REMOTE_RX_STATUS_SHIFT) ?
		    e1000_1000t_rx_status_ok : e1000_1000t_rx_status_not_ok;

	}

	return E1000_SUCCESS;
}