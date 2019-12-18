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
typedef  scalar_t__ u32 ;
struct ixgbe_hw {int dummy; } ;
typedef  int /*<<< orphan*/  s32 ;
typedef  int /*<<< orphan*/  ixgbe_link_speed ;

/* Variables and functions */
 int /*<<< orphan*/  IXGBE_LINKS ; 
 scalar_t__ IXGBE_LINKS_SPEED_100_82599 ; 
 scalar_t__ IXGBE_LINKS_SPEED_10G_82599 ; 
 scalar_t__ IXGBE_LINKS_SPEED_1G_82599 ; 
 scalar_t__ IXGBE_LINKS_SPEED_82599 ; 
 scalar_t__ IXGBE_LINKS_UP ; 
 int /*<<< orphan*/  IXGBE_LINK_SPEED_100_FULL ; 
 int /*<<< orphan*/  IXGBE_LINK_SPEED_10GB_FULL ; 
 int /*<<< orphan*/  IXGBE_LINK_SPEED_1GB_FULL ; 
 int /*<<< orphan*/  IXGBE_LINK_SPEED_UNKNOWN ; 
 scalar_t__ IXGBE_LINK_UP_TIME ; 
 scalar_t__ IXGBE_READ_REG (struct ixgbe_hw*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hw_dbg (struct ixgbe_hw*,char*,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  msleep (int) ; 

s32 ixgbe_check_mac_link_generic(struct ixgbe_hw *hw, ixgbe_link_speed *speed,
				 bool *link_up, bool link_up_wait_to_complete)
{
	u32 links_reg, links_orig;
	u32 i;

	/* clear the old state */
	links_orig = IXGBE_READ_REG(hw, IXGBE_LINKS);

	links_reg = IXGBE_READ_REG(hw, IXGBE_LINKS);

	if (links_orig != links_reg) {
		hw_dbg(hw, "LINKS changed from %08X to %08X\n",
		       links_orig, links_reg);
	}

	if (link_up_wait_to_complete) {
		for (i = 0; i < IXGBE_LINK_UP_TIME; i++) {
			if (links_reg & IXGBE_LINKS_UP) {
				*link_up = true;
				break;
			} else {
				*link_up = false;
			}
			msleep(100);
			links_reg = IXGBE_READ_REG(hw, IXGBE_LINKS);
		}
	} else {
		if (links_reg & IXGBE_LINKS_UP)
			*link_up = true;
		else
			*link_up = false;
	}

	if ((links_reg & IXGBE_LINKS_SPEED_82599) ==
	    IXGBE_LINKS_SPEED_10G_82599)
		*speed = IXGBE_LINK_SPEED_10GB_FULL;
	else if ((links_reg & IXGBE_LINKS_SPEED_82599) ==
		 IXGBE_LINKS_SPEED_1G_82599)
		*speed = IXGBE_LINK_SPEED_1GB_FULL;
	else if ((links_reg & IXGBE_LINKS_SPEED_82599) ==
		 IXGBE_LINKS_SPEED_100_82599)
		*speed = IXGBE_LINK_SPEED_100_FULL;
	else
		*speed = IXGBE_LINK_SPEED_UNKNOWN;

	return 0;
}