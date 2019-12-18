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
typedef  int /*<<< orphan*/  u16 ;
struct TYPE_4__ {int /*<<< orphan*/  (* identify_sfp ) (struct ixgbe_hw*) ;int /*<<< orphan*/ * reset; int /*<<< orphan*/ * get_firmware_version; int /*<<< orphan*/ * check_link; int /*<<< orphan*/ * setup_link; int /*<<< orphan*/  (* identify ) (struct ixgbe_hw*) ;} ;
struct ixgbe_phy_info {int type; int /*<<< orphan*/  sfp_type; TYPE_2__ ops; } ;
struct TYPE_3__ {scalar_t__ (* get_media_type ) (struct ixgbe_hw*) ;int /*<<< orphan*/ * get_link_capabilities; int /*<<< orphan*/ * setup_link; } ;
struct ixgbe_mac_info {TYPE_1__ ops; } ;
struct ixgbe_hw {struct ixgbe_phy_info phy; struct ixgbe_mac_info mac; } ;
typedef  int /*<<< orphan*/  s32 ;

/* Variables and functions */
 int /*<<< orphan*/  IXGBE_ERR_SFP_NOT_SUPPORTED ; 
 int /*<<< orphan*/  ixgbe_check_phy_link_tnx ; 
 int /*<<< orphan*/  ixgbe_get_copper_link_capabilities_generic ; 
 int /*<<< orphan*/  ixgbe_get_phy_firmware_version_tnx ; 
 int /*<<< orphan*/  ixgbe_get_sfp_init_sequence_offsets (struct ixgbe_hw*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ ixgbe_media_type_copper ; 
#define  ixgbe_phy_nl 129 
#define  ixgbe_phy_tn 128 
 int /*<<< orphan*/  ixgbe_reset_phy_nl ; 
 int /*<<< orphan*/  ixgbe_setup_copper_link_82598 ; 
 int /*<<< orphan*/  ixgbe_setup_phy_link_tnx ; 
 int /*<<< orphan*/  ixgbe_sfp_type_unknown ; 
 int /*<<< orphan*/  stub1 (struct ixgbe_hw*) ; 
 scalar_t__ stub2 (struct ixgbe_hw*) ; 
 int /*<<< orphan*/  stub3 (struct ixgbe_hw*) ; 

__attribute__((used)) static s32 ixgbe_init_phy_ops_82598(struct ixgbe_hw *hw)
{
	struct ixgbe_mac_info *mac = &hw->mac;
	struct ixgbe_phy_info *phy = &hw->phy;
	s32 ret_val = 0;
	u16 list_offset, data_offset;

	/* Identify the PHY */
	phy->ops.identify(hw);

	/* Overwrite the link function pointers if copper PHY */
	if (mac->ops.get_media_type(hw) == ixgbe_media_type_copper) {
		mac->ops.setup_link = &ixgbe_setup_copper_link_82598;
		mac->ops.get_link_capabilities =
			&ixgbe_get_copper_link_capabilities_generic;
	}

	switch (hw->phy.type) {
	case ixgbe_phy_tn:
		phy->ops.setup_link = &ixgbe_setup_phy_link_tnx;
		phy->ops.check_link = &ixgbe_check_phy_link_tnx;
		phy->ops.get_firmware_version =
		             &ixgbe_get_phy_firmware_version_tnx;
		break;
	case ixgbe_phy_nl:
		phy->ops.reset = &ixgbe_reset_phy_nl;

		/* Call SFP+ identify routine to get the SFP+ module type */
		ret_val = phy->ops.identify_sfp(hw);
		if (ret_val != 0)
			goto out;
		else if (hw->phy.sfp_type == ixgbe_sfp_type_unknown) {
			ret_val = IXGBE_ERR_SFP_NOT_SUPPORTED;
			goto out;
		}

		/* Check to see if SFP+ module is supported */
		ret_val = ixgbe_get_sfp_init_sequence_offsets(hw,
		                                            &list_offset,
		                                            &data_offset);
		if (ret_val != 0) {
			ret_val = IXGBE_ERR_SFP_NOT_SUPPORTED;
			goto out;
		}
		break;
	default:
		break;
	}

out:
	return ret_val;
}