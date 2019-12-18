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
struct TYPE_4__ {int get_link_status; int /*<<< orphan*/  serdes_has_link; } ;
struct TYPE_3__ {scalar_t__ media_type; } ;
struct e1000_hw {TYPE_2__ mac; TYPE_1__ phy; } ;
typedef  scalar_t__ s32 ;

/* Variables and functions */
 scalar_t__ e1000_media_type_copper ; 
 int /*<<< orphan*/  hw_dbg (char*) ; 
 scalar_t__ igb_check_for_copper_link (struct e1000_hw*) ; 
 scalar_t__ igb_config_fc_after_link_up (struct e1000_hw*) ; 
 scalar_t__ igb_get_pcs_speed_and_duplex_82575 (struct e1000_hw*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static s32 igb_check_for_link_82575(struct e1000_hw *hw)
{
	s32 ret_val;
	u16 speed, duplex;

	if (hw->phy.media_type != e1000_media_type_copper) {
		ret_val = igb_get_pcs_speed_and_duplex_82575(hw, &speed,
		                                             &duplex);
		/* Use this flag to determine if link needs to be checked or
		 * not.  If  we have link clear the flag so that we do not
		 * continue to check for link.
		 */
		hw->mac.get_link_status = !hw->mac.serdes_has_link;

		/* Configure Flow Control now that Auto-Neg has completed.
		 * First, we need to restore the desired flow control
		 * settings because we may have had to re-autoneg with a
		 * different link partner.
		 */
		ret_val = igb_config_fc_after_link_up(hw);
		if (ret_val)
			hw_dbg("Error configuring flow control\n");
	} else {
		ret_val = igb_check_for_copper_link(hw);
	}

	return ret_val;
}