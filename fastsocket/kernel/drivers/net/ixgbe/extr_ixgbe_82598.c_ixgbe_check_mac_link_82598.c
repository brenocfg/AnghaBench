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
typedef  scalar_t__ u32 ;
typedef  int u16 ;
struct TYPE_3__ {int /*<<< orphan*/  (* read_reg ) (struct ixgbe_hw*,int,int /*<<< orphan*/ ,int*) ;} ;
struct TYPE_4__ {scalar_t__ type; TYPE_1__ ops; } ;
struct ixgbe_hw {scalar_t__ device_id; TYPE_2__ phy; } ;
typedef  int /*<<< orphan*/  s32 ;
typedef  int /*<<< orphan*/  ixgbe_link_speed ;

/* Variables and functions */
 scalar_t__ IXGBE_DEV_ID_82598AT2 ; 
 int /*<<< orphan*/  IXGBE_LINKS ; 
 scalar_t__ IXGBE_LINKS_SPEED ; 
 scalar_t__ IXGBE_LINKS_UP ; 
 int /*<<< orphan*/  IXGBE_LINK_SPEED_10GB_FULL ; 
 int /*<<< orphan*/  IXGBE_LINK_SPEED_1GB_FULL ; 
 scalar_t__ IXGBE_LINK_UP_TIME ; 
 scalar_t__ IXGBE_READ_REG (struct ixgbe_hw*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MDIO_MMD_PMAPMD ; 
 scalar_t__ ixgbe_phy_nl ; 
 scalar_t__ ixgbe_validate_link_ready (struct ixgbe_hw*) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  stub1 (struct ixgbe_hw*,int,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  stub2 (struct ixgbe_hw*,int,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  stub3 (struct ixgbe_hw*,int,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  stub4 (struct ixgbe_hw*,int,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  stub5 (struct ixgbe_hw*,int,int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static s32 ixgbe_check_mac_link_82598(struct ixgbe_hw *hw,
                                      ixgbe_link_speed *speed, bool *link_up,
                                      bool link_up_wait_to_complete)
{
	u32 links_reg;
	u32 i;
	u16 link_reg, adapt_comp_reg;

	/*
	 * SERDES PHY requires us to read link status from register 0xC79F.
	 * Bit 0 set indicates link is up/ready; clear indicates link down.
	 * 0xC00C is read to check that the XAUI lanes are active.  Bit 0
	 * clear indicates active; set indicates inactive.
	 */
	if (hw->phy.type == ixgbe_phy_nl) {
		hw->phy.ops.read_reg(hw, 0xC79F, MDIO_MMD_PMAPMD, &link_reg);
		hw->phy.ops.read_reg(hw, 0xC79F, MDIO_MMD_PMAPMD, &link_reg);
		hw->phy.ops.read_reg(hw, 0xC00C, MDIO_MMD_PMAPMD,
		                     &adapt_comp_reg);
		if (link_up_wait_to_complete) {
			for (i = 0; i < IXGBE_LINK_UP_TIME; i++) {
				if ((link_reg & 1) &&
				    ((adapt_comp_reg & 1) == 0)) {
					*link_up = true;
					break;
				} else {
					*link_up = false;
				}
				msleep(100);
				hw->phy.ops.read_reg(hw, 0xC79F,
				                     MDIO_MMD_PMAPMD,
				                     &link_reg);
				hw->phy.ops.read_reg(hw, 0xC00C,
				                     MDIO_MMD_PMAPMD,
				                     &adapt_comp_reg);
			}
		} else {
			if ((link_reg & 1) && ((adapt_comp_reg & 1) == 0))
				*link_up = true;
			else
				*link_up = false;
		}

		if (!*link_up)
			goto out;
	}

	links_reg = IXGBE_READ_REG(hw, IXGBE_LINKS);
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

	if (links_reg & IXGBE_LINKS_SPEED)
		*speed = IXGBE_LINK_SPEED_10GB_FULL;
	else
		*speed = IXGBE_LINK_SPEED_1GB_FULL;

	if ((hw->device_id == IXGBE_DEV_ID_82598AT2) && *link_up &&
	    (ixgbe_validate_link_ready(hw) != 0))
		*link_up = false;

out:
	return 0;
}