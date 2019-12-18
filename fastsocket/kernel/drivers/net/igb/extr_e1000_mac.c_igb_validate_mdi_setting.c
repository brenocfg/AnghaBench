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
struct TYPE_4__ {int mdix; } ;
struct TYPE_3__ {scalar_t__ type; int /*<<< orphan*/  autoneg; } ;
struct e1000_hw {TYPE_2__ phy; TYPE_1__ mac; } ;
typedef  int /*<<< orphan*/  s32 ;

/* Variables and functions */
 int /*<<< orphan*/  E1000_ERR_CONFIG ; 
 scalar_t__ e1000_82580 ; 
 int /*<<< orphan*/  hw_dbg (char*) ; 

s32 igb_validate_mdi_setting(struct e1000_hw *hw)
{
	s32 ret_val = 0;

	/* All MDI settings are supported on 82580 and newer. */
	if (hw->mac.type >= e1000_82580)
		goto out;

	if (!hw->mac.autoneg && (hw->phy.mdix == 0 || hw->phy.mdix == 3)) {
		hw_dbg("Invalid MDI setting detected\n");
		hw->phy.mdix = 1;
		ret_val = -E1000_ERR_CONFIG;
		goto out;
	}

out:
	return ret_val;
}