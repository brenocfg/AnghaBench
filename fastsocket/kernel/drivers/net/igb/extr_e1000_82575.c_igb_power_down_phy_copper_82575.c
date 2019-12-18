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
struct e1000_hw {int dummy; } ;

/* Variables and functions */
 scalar_t__ igb_check_reset_block (struct e1000_hw*) ; 
 scalar_t__ igb_enable_mng_pass_thru (struct e1000_hw*) ; 
 int /*<<< orphan*/  igb_power_down_phy_copper (struct e1000_hw*) ; 

void igb_power_down_phy_copper_82575(struct e1000_hw *hw)
{
	/* If the management interface is not enabled, then power down */
	if (!(igb_enable_mng_pass_thru(hw) || igb_check_reset_block(hw)))
		igb_power_down_phy_copper(hw);
}