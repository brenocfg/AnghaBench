#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  get_info; int /*<<< orphan*/  get_cable_length; int /*<<< orphan*/  force_speed_duplex; int /*<<< orphan*/  check_polarity; int /*<<< orphan*/  commit; int /*<<< orphan*/  power_down; int /*<<< orphan*/  power_up; int /*<<< orphan*/  write_reg_page; int /*<<< orphan*/  write_reg_locked; int /*<<< orphan*/  write_reg; void* set_d3_lplu_state; void* set_d0_lplu_state; int /*<<< orphan*/  read_reg_page; int /*<<< orphan*/  read_reg_locked; int /*<<< orphan*/  read_reg; int /*<<< orphan*/  set_page; } ;
struct e1000_phy_info {int addr; int reset_delay_us; scalar_t__ id; int type; TYPE_2__ ops; int /*<<< orphan*/  autoneg_mask; } ;
struct TYPE_3__ {int type; } ;
struct e1000_hw {TYPE_1__ mac; struct e1000_phy_info phy; } ;
typedef  scalar_t__ s32 ;

/* Variables and functions */
 int /*<<< orphan*/  AUTONEG_ADVERTISE_SPEED_DEFAULT ; 
 scalar_t__ E1000_ERR_PHY ; 
 scalar_t__ PHY_REVISION_MASK ; 
 int /*<<< orphan*/  e1000_check_polarity_82577 ; 
 int /*<<< orphan*/  e1000_check_polarity_m88 ; 
 int /*<<< orphan*/  e1000_get_cable_length_82577 ; 
 int /*<<< orphan*/  e1000_get_phy_info_82577 ; 
 scalar_t__ e1000_init_phy_workarounds_pchlan (struct e1000_hw*) ; 
#define  e1000_pch2lan 133 
#define  e1000_pch_lpt 132 
#define  e1000_phy_82577 131 
#define  e1000_phy_82578 130 
#define  e1000_phy_82579 129 
 int /*<<< orphan*/  e1000_phy_force_speed_duplex_82577 ; 
#define  e1000_phy_i217 128 
 scalar_t__ e1000_phy_unknown ; 
 int /*<<< orphan*/  e1000_power_down_phy_copper_ich8lan ; 
 int /*<<< orphan*/  e1000_power_up_phy_copper ; 
 int /*<<< orphan*/  e1000_read_phy_reg_hv ; 
 int /*<<< orphan*/  e1000_read_phy_reg_hv_locked ; 
 int /*<<< orphan*/  e1000_read_phy_reg_page_hv ; 
 void* e1000_set_lplu_state_pchlan ; 
 scalar_t__ e1000_set_mdio_slow_mode_hv (struct e1000_hw*) ; 
 int /*<<< orphan*/  e1000_set_page_igp ; 
 int /*<<< orphan*/  e1000_write_phy_reg_hv ; 
 int /*<<< orphan*/  e1000_write_phy_reg_hv_locked ; 
 int /*<<< orphan*/  e1000_write_phy_reg_page_hv ; 
 int /*<<< orphan*/  e1000e_get_cable_length_m88 ; 
 scalar_t__ e1000e_get_phy_id (struct e1000_hw*) ; 
 int /*<<< orphan*/  e1000e_get_phy_info_m88 ; 
 int e1000e_get_phy_type_from_id (scalar_t__) ; 
 int /*<<< orphan*/  e1000e_phy_force_speed_duplex_m88 ; 
 int /*<<< orphan*/  e1000e_phy_sw_reset ; 

__attribute__((used)) static s32 e1000_init_phy_params_pchlan(struct e1000_hw *hw)
{
	struct e1000_phy_info *phy = &hw->phy;
	s32 ret_val;

	phy->addr = 1;
	phy->reset_delay_us = 100;

	phy->ops.set_page = e1000_set_page_igp;
	phy->ops.read_reg = e1000_read_phy_reg_hv;
	phy->ops.read_reg_locked = e1000_read_phy_reg_hv_locked;
	phy->ops.read_reg_page = e1000_read_phy_reg_page_hv;
	phy->ops.set_d0_lplu_state = e1000_set_lplu_state_pchlan;
	phy->ops.set_d3_lplu_state = e1000_set_lplu_state_pchlan;
	phy->ops.write_reg = e1000_write_phy_reg_hv;
	phy->ops.write_reg_locked = e1000_write_phy_reg_hv_locked;
	phy->ops.write_reg_page = e1000_write_phy_reg_page_hv;
	phy->ops.power_up = e1000_power_up_phy_copper;
	phy->ops.power_down = e1000_power_down_phy_copper_ich8lan;
	phy->autoneg_mask = AUTONEG_ADVERTISE_SPEED_DEFAULT;

	phy->id = e1000_phy_unknown;

	ret_val = e1000_init_phy_workarounds_pchlan(hw);
	if (ret_val)
		return ret_val;

	if (phy->id == e1000_phy_unknown)
		switch (hw->mac.type) {
		default:
			ret_val = e1000e_get_phy_id(hw);
			if (ret_val)
				return ret_val;
			if ((phy->id != 0) && (phy->id != PHY_REVISION_MASK))
				break;
			/* fall-through */
		case e1000_pch2lan:
		case e1000_pch_lpt:
			/* In case the PHY needs to be in mdio slow mode,
			 * set slow mode and try to get the PHY id again.
			 */
			ret_val = e1000_set_mdio_slow_mode_hv(hw);
			if (ret_val)
				return ret_val;
			ret_val = e1000e_get_phy_id(hw);
			if (ret_val)
				return ret_val;
			break;
		}
	phy->type = e1000e_get_phy_type_from_id(phy->id);

	switch (phy->type) {
	case e1000_phy_82577:
	case e1000_phy_82579:
	case e1000_phy_i217:
		phy->ops.check_polarity = e1000_check_polarity_82577;
		phy->ops.force_speed_duplex =
		    e1000_phy_force_speed_duplex_82577;
		phy->ops.get_cable_length = e1000_get_cable_length_82577;
		phy->ops.get_info = e1000_get_phy_info_82577;
		phy->ops.commit = e1000e_phy_sw_reset;
		break;
	case e1000_phy_82578:
		phy->ops.check_polarity = e1000_check_polarity_m88;
		phy->ops.force_speed_duplex = e1000e_phy_force_speed_duplex_m88;
		phy->ops.get_cable_length = e1000e_get_cable_length_m88;
		phy->ops.get_info = e1000e_get_phy_info_m88;
		break;
	default:
		ret_val = -E1000_ERR_PHY;
		break;
	}

	return ret_val;
}