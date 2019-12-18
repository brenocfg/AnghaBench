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
typedef  int u32 ;
typedef  int u16 ;
struct TYPE_3__ {scalar_t__ (* check_overtemp ) (struct ixgbe_hw*) ;int /*<<< orphan*/  (* read_reg ) (struct ixgbe_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ;int /*<<< orphan*/  (* write_reg ) (struct ixgbe_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ;} ;
struct TYPE_4__ {scalar_t__ type; TYPE_1__ ops; int /*<<< orphan*/  reset_if_overtemp; } ;
struct ixgbe_hw {TYPE_2__ phy; } ;
typedef  scalar_t__ s32 ;

/* Variables and functions */
 scalar_t__ IXGBE_ERR_OVERTEMP ; 
 scalar_t__ IXGBE_ERR_RESET_FAILED ; 
 int /*<<< orphan*/  MDIO_CTRL1 ; 
 int MDIO_CTRL1_RESET ; 
 int /*<<< orphan*/  MDIO_MMD_PHYXS ; 
 int /*<<< orphan*/  hw_dbg (struct ixgbe_hw*,char*) ; 
 scalar_t__ ixgbe_identify_phy_generic (struct ixgbe_hw*) ; 
 scalar_t__ ixgbe_phy_none ; 
 scalar_t__ ixgbe_phy_unknown ; 
 int /*<<< orphan*/  msleep (int) ; 
 scalar_t__ stub1 (struct ixgbe_hw*) ; 
 int /*<<< orphan*/  stub2 (struct ixgbe_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub3 (struct ixgbe_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  udelay (int) ; 

s32 ixgbe_reset_phy_generic(struct ixgbe_hw *hw)
{
	u32 i;
	u16 ctrl = 0;
	s32 status = 0;

	if (hw->phy.type == ixgbe_phy_unknown)
		status = ixgbe_identify_phy_generic(hw);

	if (status != 0 || hw->phy.type == ixgbe_phy_none)
		goto out;

	/* Don't reset PHY if it's shut down due to overtemp. */
	if (!hw->phy.reset_if_overtemp &&
	    (IXGBE_ERR_OVERTEMP == hw->phy.ops.check_overtemp(hw)))
		goto out;

	/*
	 * Perform soft PHY reset to the PHY_XS.
	 * This will cause a soft reset to the PHY
	 */
	hw->phy.ops.write_reg(hw, MDIO_CTRL1,
			      MDIO_MMD_PHYXS,
			      MDIO_CTRL1_RESET);

	/*
	 * Poll for reset bit to self-clear indicating reset is complete.
	 * Some PHYs could take up to 3 seconds to complete and need about
	 * 1.7 usec delay after the reset is complete.
	 */
	for (i = 0; i < 30; i++) {
		msleep(100);
		hw->phy.ops.read_reg(hw, MDIO_CTRL1,
				     MDIO_MMD_PHYXS, &ctrl);
		if (!(ctrl & MDIO_CTRL1_RESET)) {
			udelay(2);
			break;
		}
	}

	if (ctrl & MDIO_CTRL1_RESET) {
		status = IXGBE_ERR_RESET_FAILED;
		hw_dbg(hw, "PHY reset polling failed to complete.\n");
	}

out:
	return status;
}