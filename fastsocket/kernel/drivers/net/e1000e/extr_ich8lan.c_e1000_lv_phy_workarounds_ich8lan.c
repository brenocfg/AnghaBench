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
struct TYPE_5__ {int /*<<< orphan*/  (* release ) (struct e1000_hw*) ;scalar_t__ (* acquire ) (struct e1000_hw*) ;} ;
struct TYPE_6__ {TYPE_2__ ops; } ;
struct TYPE_4__ {scalar_t__ type; } ;
struct e1000_hw {TYPE_3__ phy; TYPE_1__ mac; } ;
typedef  scalar_t__ s32 ;

/* Variables and functions */
 int /*<<< orphan*/  I82579_MSE_LINK_DOWN ; 
 int /*<<< orphan*/  I82579_MSE_THRESHOLD ; 
 scalar_t__ e1000_pch2lan ; 
 scalar_t__ e1000_set_mdio_slow_mode_hv (struct e1000_hw*) ; 
 scalar_t__ e1000_write_emi_reg_locked (struct e1000_hw*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ stub1 (struct e1000_hw*) ; 
 int /*<<< orphan*/  stub2 (struct e1000_hw*) ; 

__attribute__((used)) static s32 e1000_lv_phy_workarounds_ich8lan(struct e1000_hw *hw)
{
	s32 ret_val = 0;

	if (hw->mac.type != e1000_pch2lan)
		return 0;

	/* Set MDIO slow mode before any other MDIO access */
	ret_val = e1000_set_mdio_slow_mode_hv(hw);
	if (ret_val)
		return ret_val;

	ret_val = hw->phy.ops.acquire(hw);
	if (ret_val)
		return ret_val;
	/* set MSE higher to enable link to stay up when noise is high */
	ret_val = e1000_write_emi_reg_locked(hw, I82579_MSE_THRESHOLD, 0x0034);
	if (ret_val)
		goto release;
	/* drop link after 5 times MSE threshold was reached */
	ret_val = e1000_write_emi_reg_locked(hw, I82579_MSE_LINK_DOWN, 0x0005);
release:
	hw->phy.ops.release(hw);

	return ret_val;
}