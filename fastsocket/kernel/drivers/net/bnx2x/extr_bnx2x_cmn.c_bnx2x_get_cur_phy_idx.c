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
struct TYPE_6__ {int num_phys; TYPE_2__* phy; } ;
struct TYPE_4__ {int link_status; scalar_t__ link_up; } ;
struct bnx2x {TYPE_3__ link_params; TYPE_1__ link_vars; } ;
struct TYPE_5__ {int supported; } ;

/* Variables and functions */
 int EXT_PHY1 ; 
 size_t EXT_PHY2 ; 
 int INT_PHY ; 
 int LINK_STATUS_SERDES_LINK ; 
#define  PORT_HW_CFG_PHY_SELECTION_FIRST_PHY 132 
#define  PORT_HW_CFG_PHY_SELECTION_FIRST_PHY_PRIORITY 131 
#define  PORT_HW_CFG_PHY_SELECTION_HARDWARE_DEFAULT 130 
#define  PORT_HW_CFG_PHY_SELECTION_SECOND_PHY 129 
#define  PORT_HW_CFG_PHY_SELECTION_SECOND_PHY_PRIORITY 128 
 int SUPPORTED_FIBRE ; 
 int bnx2x_phy_selection (TYPE_3__*) ; 

int bnx2x_get_cur_phy_idx(struct bnx2x *bp)
{
	u32 sel_phy_idx = 0;
	if (bp->link_params.num_phys <= 1)
		return INT_PHY;

	if (bp->link_vars.link_up) {
		sel_phy_idx = EXT_PHY1;
		/* In case link is SERDES, check if the EXT_PHY2 is the one */
		if ((bp->link_vars.link_status & LINK_STATUS_SERDES_LINK) &&
		    (bp->link_params.phy[EXT_PHY2].supported & SUPPORTED_FIBRE))
			sel_phy_idx = EXT_PHY2;
	} else {

		switch (bnx2x_phy_selection(&bp->link_params)) {
		case PORT_HW_CFG_PHY_SELECTION_HARDWARE_DEFAULT:
		case PORT_HW_CFG_PHY_SELECTION_FIRST_PHY:
		case PORT_HW_CFG_PHY_SELECTION_FIRST_PHY_PRIORITY:
		       sel_phy_idx = EXT_PHY1;
		       break;
		case PORT_HW_CFG_PHY_SELECTION_SECOND_PHY:
		case PORT_HW_CFG_PHY_SELECTION_SECOND_PHY_PRIORITY:
		       sel_phy_idx = EXT_PHY2;
		       break;
		}
	}

	return sel_phy_idx;
}