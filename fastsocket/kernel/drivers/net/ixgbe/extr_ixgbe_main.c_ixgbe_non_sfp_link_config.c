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
typedef  int u32 ;
struct TYPE_5__ {int (* check_link ) (struct ixgbe_hw*,int*,int*,int) ;int (* get_link_capabilities ) (struct ixgbe_hw*,int*,int*) ;int (* setup_link ) (struct ixgbe_hw*,int,int) ;} ;
struct TYPE_6__ {TYPE_2__ ops; } ;
struct TYPE_4__ {int autoneg_advertised; } ;
struct ixgbe_hw {TYPE_3__ mac; TYPE_1__ phy; } ;

/* Variables and functions */
 int IXGBE_ERR_LINK_SETUP ; 
 int stub1 (struct ixgbe_hw*,int*,int*,int) ; 
 int stub2 (struct ixgbe_hw*,int*,int*) ; 
 int stub3 (struct ixgbe_hw*,int,int) ; 

__attribute__((used)) static int ixgbe_non_sfp_link_config(struct ixgbe_hw *hw)
{
	u32 speed;
	bool autoneg, link_up = false;
	u32 ret = IXGBE_ERR_LINK_SETUP;

	if (hw->mac.ops.check_link)
		ret = hw->mac.ops.check_link(hw, &speed, &link_up, false);

	if (ret)
		goto link_cfg_out;

	speed = hw->phy.autoneg_advertised;
	if ((!speed) && (hw->mac.ops.get_link_capabilities))
		ret = hw->mac.ops.get_link_capabilities(hw, &speed,
							&autoneg);
	if (ret)
		goto link_cfg_out;

	if (hw->mac.ops.setup_link)
		ret = hw->mac.ops.setup_link(hw, speed, link_up);
link_cfg_out:
	return ret;
}