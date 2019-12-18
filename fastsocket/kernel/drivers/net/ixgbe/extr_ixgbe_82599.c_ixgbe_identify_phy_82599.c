#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {scalar_t__ type; } ;
struct TYPE_4__ {scalar_t__ (* get_media_type ) (struct ixgbe_hw*) ;} ;
struct TYPE_5__ {TYPE_1__ ops; } ;
struct ixgbe_hw {TYPE_3__ phy; TYPE_2__ mac; } ;
typedef  scalar_t__ s32 ;

/* Variables and functions */
 scalar_t__ IXGBE_ERR_PHY_ADDR_INVALID ; 
 scalar_t__ IXGBE_ERR_SFP_NOT_SUPPORTED ; 
 scalar_t__ ixgbe_identify_module_generic (struct ixgbe_hw*) ; 
 scalar_t__ ixgbe_identify_phy_generic (struct ixgbe_hw*) ; 
 scalar_t__ ixgbe_media_type_copper ; 
 scalar_t__ ixgbe_phy_none ; 
 scalar_t__ ixgbe_phy_sfp_unsupported ; 
 scalar_t__ ixgbe_phy_unknown ; 
 scalar_t__ stub1 (struct ixgbe_hw*) ; 

__attribute__((used)) static s32 ixgbe_identify_phy_82599(struct ixgbe_hw *hw)
{
	s32 status = IXGBE_ERR_PHY_ADDR_INVALID;

	/* Detect PHY if not unknown - returns success if already detected. */
	status = ixgbe_identify_phy_generic(hw);
	if (status != 0) {
		/* 82599 10GBASE-T requires an external PHY */
		if (hw->mac.ops.get_media_type(hw) == ixgbe_media_type_copper)
			goto out;
		else
			status = ixgbe_identify_module_generic(hw);
	}

	/* Set PHY type none if no PHY detected */
	if (hw->phy.type == ixgbe_phy_unknown) {
		hw->phy.type = ixgbe_phy_none;
		status = 0;
	}

	/* Return error if SFP module has been detected but is not supported */
	if (hw->phy.type == ixgbe_phy_sfp_unsupported)
		status = IXGBE_ERR_SFP_NOT_SUPPORTED;

out:
	return status;
}