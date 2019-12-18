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
typedef  int /*<<< orphan*/  u16 ;
struct ixgb_hw {scalar_t__ phy_type; } ;

/* Variables and functions */
 int /*<<< orphan*/  IXGB_PHY_ADDRESS ; 
 int /*<<< orphan*/  MDIO_CTRL1 ; 
 int /*<<< orphan*/  MDIO_CTRL1_RESET ; 
 int /*<<< orphan*/  MDIO_MMD_PMAPMD ; 
 scalar_t__ ixgb_phy_type_txn17401 ; 
 int /*<<< orphan*/  ixgb_read_phy_reg (struct ixgb_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ixgb_write_phy_reg (struct ixgb_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
ixgb_optics_reset(struct ixgb_hw *hw)
{
	if (hw->phy_type == ixgb_phy_type_txn17401) {
		u16 mdio_reg;

		ixgb_write_phy_reg(hw,
				   MDIO_CTRL1,
				   IXGB_PHY_ADDRESS,
				   MDIO_MMD_PMAPMD,
				   MDIO_CTRL1_RESET);

		mdio_reg = ixgb_read_phy_reg(hw,
					     MDIO_CTRL1,
					     IXGB_PHY_ADDRESS,
					     MDIO_MMD_PMAPMD);
	}

	return;
}