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
typedef  int u16 ;
struct TYPE_3__ {scalar_t__ (* read_reg ) (struct ixgbe_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ;} ;
struct TYPE_4__ {TYPE_1__ ops; } ;
struct ixgbe_hw {TYPE_2__ phy; } ;
typedef  scalar_t__ s32 ;
typedef  int /*<<< orphan*/  ixgbe_link_speed ;

/* Variables and functions */
 scalar_t__ IXGBE_ERR_LINK_SETUP ; 
 int /*<<< orphan*/  IXGBE_LINK_SPEED_100_FULL ; 
 int /*<<< orphan*/  IXGBE_LINK_SPEED_10GB_FULL ; 
 int /*<<< orphan*/  IXGBE_LINK_SPEED_1GB_FULL ; 
 int /*<<< orphan*/  MDIO_MMD_PMAPMD ; 
 int MDIO_PMA_SPEED_100 ; 
 int MDIO_PMA_SPEED_1000 ; 
 int /*<<< orphan*/  MDIO_SPEED ; 
 int MDIO_SPEED_10G ; 
 scalar_t__ stub1 (struct ixgbe_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 

s32 ixgbe_get_copper_link_capabilities_generic(struct ixgbe_hw *hw,
                                               ixgbe_link_speed *speed,
                                               bool *autoneg)
{
	s32 status = IXGBE_ERR_LINK_SETUP;
	u16 speed_ability;

	*speed = 0;
	*autoneg = true;

	status = hw->phy.ops.read_reg(hw, MDIO_SPEED, MDIO_MMD_PMAPMD,
	                              &speed_ability);

	if (status == 0) {
		if (speed_ability & MDIO_SPEED_10G)
			*speed |= IXGBE_LINK_SPEED_10GB_FULL;
		if (speed_ability & MDIO_PMA_SPEED_1000)
			*speed |= IXGBE_LINK_SPEED_1GB_FULL;
		if (speed_ability & MDIO_PMA_SPEED_100)
			*speed |= IXGBE_LINK_SPEED_100_FULL;
	}

	return status;
}