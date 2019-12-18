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
typedef  scalar_t__ u8 ;
typedef  int u32 ;
struct e1000_sfp_flags {scalar_t__ e1000_base_t; scalar_t__ e100_base_fx; scalar_t__ e1000_base_sx; scalar_t__ e1000_base_lx; } ;
struct TYPE_4__ {void* media_type; } ;
struct e1000_dev_spec_82575 {int module_plugged; int sgmii_active; struct e1000_sfp_flags eth_flags; } ;
struct TYPE_3__ {struct e1000_dev_spec_82575 _82575; } ;
struct e1000_hw {TYPE_2__ phy; TYPE_1__ dev_spec; } ;
typedef  scalar_t__ s32 ;

/* Variables and functions */
 int /*<<< orphan*/  E1000_CTRL_EXT ; 
 int E1000_CTRL_EXT_SDP3_DATA ; 
 int E1000_CTRL_I2C_ENA ; 
 scalar_t__ E1000_ERR_CONFIG ; 
 int /*<<< orphan*/  E1000_I2CCMD_SFP_DATA_ADDR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  E1000_SFF_ETH_FLAGS_OFFSET ; 
 int /*<<< orphan*/  E1000_SFF_IDENTIFIER_OFFSET ; 
 scalar_t__ E1000_SFF_IDENTIFIER_SFF ; 
 scalar_t__ E1000_SFF_IDENTIFIER_SFP ; 
 void* e1000_media_type_copper ; 
 void* e1000_media_type_internal_serdes ; 
 void* e1000_media_type_unknown ; 
 int /*<<< orphan*/  hw_dbg (char*) ; 
 scalar_t__ igb_read_sfp_data_byte (struct e1000_hw*,int /*<<< orphan*/ ,scalar_t__*) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int rd32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wr32 (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  wrfl () ; 

__attribute__((used)) static s32 igb_set_sfp_media_type_82575(struct e1000_hw *hw)
{
	s32 ret_val = E1000_ERR_CONFIG;
	u32 ctrl_ext = 0;
	struct e1000_dev_spec_82575 *dev_spec = &hw->dev_spec._82575;
	struct e1000_sfp_flags *eth_flags = &dev_spec->eth_flags;
	u8 tranceiver_type = 0;
	s32 timeout = 3;

	/* Turn I2C interface ON and power on sfp cage */
	ctrl_ext = rd32(E1000_CTRL_EXT);
	ctrl_ext &= ~E1000_CTRL_EXT_SDP3_DATA;
	wr32(E1000_CTRL_EXT, ctrl_ext | E1000_CTRL_I2C_ENA);

	wrfl();

	/* Read SFP module data */
	while (timeout) {
		ret_val = igb_read_sfp_data_byte(hw,
			E1000_I2CCMD_SFP_DATA_ADDR(E1000_SFF_IDENTIFIER_OFFSET),
			&tranceiver_type);
		if (ret_val == 0)
			break;
		msleep(100);
		timeout--;
	}
	if (ret_val != 0)
		goto out;

	ret_val = igb_read_sfp_data_byte(hw,
			E1000_I2CCMD_SFP_DATA_ADDR(E1000_SFF_ETH_FLAGS_OFFSET),
			(u8 *)eth_flags);
	if (ret_val != 0)
		goto out;

	/* Check if there is some SFP module plugged and powered */
	if ((tranceiver_type == E1000_SFF_IDENTIFIER_SFP) ||
	    (tranceiver_type == E1000_SFF_IDENTIFIER_SFF)) {
		dev_spec->module_plugged = true;
		if (eth_flags->e1000_base_lx || eth_flags->e1000_base_sx) {
			hw->phy.media_type = e1000_media_type_internal_serdes;
		} else if (eth_flags->e100_base_fx) {
			dev_spec->sgmii_active = true;
			hw->phy.media_type = e1000_media_type_internal_serdes;
		} else if (eth_flags->e1000_base_t) {
			dev_spec->sgmii_active = true;
			hw->phy.media_type = e1000_media_type_copper;
		} else {
			hw->phy.media_type = e1000_media_type_unknown;
			hw_dbg("PHY module has not been recognized\n");
			goto out;
		}
	} else {
		hw->phy.media_type = e1000_media_type_unknown;
	}
	ret_val = 0;
out:
	/* Restore I2C interface setting */
	wr32(E1000_CTRL_EXT, ctrl_ext);
	return ret_val;
}