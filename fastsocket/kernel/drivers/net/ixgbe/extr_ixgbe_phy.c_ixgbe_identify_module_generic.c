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
struct TYPE_6__ {int /*<<< orphan*/  sfp_type; } ;
struct TYPE_4__ {int (* get_media_type ) (struct ixgbe_hw*) ;} ;
struct TYPE_5__ {TYPE_1__ ops; } ;
struct ixgbe_hw {TYPE_3__ phy; TYPE_2__ mac; } ;
typedef  int /*<<< orphan*/  s32 ;

/* Variables and functions */
 int /*<<< orphan*/  IXGBE_ERR_SFP_NOT_PRESENT ; 
 int /*<<< orphan*/  ixgbe_identify_qsfp_module_generic (struct ixgbe_hw*) ; 
 int /*<<< orphan*/  ixgbe_identify_sfp_module_generic (struct ixgbe_hw*) ; 
#define  ixgbe_media_type_fiber 129 
#define  ixgbe_media_type_fiber_qsfp 128 
 int /*<<< orphan*/  ixgbe_sfp_type_not_present ; 
 int stub1 (struct ixgbe_hw*) ; 

s32 ixgbe_identify_module_generic(struct ixgbe_hw *hw)
{
	s32 status = IXGBE_ERR_SFP_NOT_PRESENT;

	switch (hw->mac.ops.get_media_type(hw)) {
	case ixgbe_media_type_fiber:
		status = ixgbe_identify_sfp_module_generic(hw);
		break;
	case ixgbe_media_type_fiber_qsfp:
		status = ixgbe_identify_qsfp_module_generic(hw);
		break;
	default:
		hw->phy.sfp_type = ixgbe_sfp_type_not_present;
		status = IXGBE_ERR_SFP_NOT_PRESENT;
		break;
	}

	return status;
}