#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u32 ;
struct TYPE_2__ {int multi_phy_config; } ;
struct bnx2x {TYPE_1__ link_params; } ;

/* Variables and functions */
 scalar_t__ EXT_PHY1 ; 
 scalar_t__ EXT_PHY2 ; 
 int LINK_CONFIG_IDX (scalar_t__) ; 
 int PORT_HW_CFG_PHY_SWAPPED_ENABLED ; 
 scalar_t__ bnx2x_get_cur_phy_idx (struct bnx2x*) ; 

int bnx2x_get_link_cfg_idx(struct bnx2x *bp)
{
	u32 sel_phy_idx = bnx2x_get_cur_phy_idx(bp);
	/*
	 * The selected activated PHY is always after swapping (in case PHY
	 * swapping is enabled). So when swapping is enabled, we need to reverse
	 * the configuration
	 */

	if (bp->link_params.multi_phy_config &
	    PORT_HW_CFG_PHY_SWAPPED_ENABLED) {
		if (sel_phy_idx == EXT_PHY1)
			sel_phy_idx = EXT_PHY2;
		else if (sel_phy_idx == EXT_PHY2)
			sel_phy_idx = EXT_PHY1;
	}
	return LINK_CONFIG_IDX(sel_phy_idx);
}