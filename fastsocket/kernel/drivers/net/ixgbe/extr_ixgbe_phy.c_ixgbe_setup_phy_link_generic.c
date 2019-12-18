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
struct TYPE_3__ {int /*<<< orphan*/  (* read_reg ) (struct ixgbe_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ;int /*<<< orphan*/  (* write_reg ) (struct ixgbe_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ;} ;
struct TYPE_4__ {int autoneg_advertised; TYPE_1__ ops; } ;
struct ixgbe_hw {TYPE_2__ phy; } ;
typedef  int /*<<< orphan*/  s32 ;
typedef  int ixgbe_link_speed ;

/* Variables and functions */
 int ADVERTISE_100FULL ; 
 int ADVERTISE_100HALF ; 
 int /*<<< orphan*/  IXGBE_ERR_LINK_SETUP ; 
 int IXGBE_LINK_SPEED_100_FULL ; 
 int IXGBE_LINK_SPEED_10GB_FULL ; 
 int IXGBE_LINK_SPEED_1GB_FULL ; 
 int IXGBE_MII_1GBASE_T_ADVERTISE ; 
 int IXGBE_MII_AUTONEG_REG ; 
 int /*<<< orphan*/  IXGBE_MII_AUTONEG_VENDOR_PROVISION_1_REG ; 
 int /*<<< orphan*/  MDIO_AN_10GBT_CTRL ; 
 int MDIO_AN_10GBT_CTRL_ADV10G ; 
 int /*<<< orphan*/  MDIO_AN_ADVERTISE ; 
 int MDIO_AN_CTRL1_RESTART ; 
 int MDIO_AN_STAT1_COMPLETE ; 
 int /*<<< orphan*/  MDIO_CTRL1 ; 
 int /*<<< orphan*/  MDIO_MMD_AN ; 
 int /*<<< orphan*/  MDIO_STAT1 ; 
 int /*<<< orphan*/  hw_dbg (struct ixgbe_hw*,char*) ; 
 int /*<<< orphan*/  ixgbe_get_copper_link_capabilities_generic (struct ixgbe_hw*,int*,int*) ; 
 int /*<<< orphan*/  stub1 (struct ixgbe_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  stub2 (struct ixgbe_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub3 (struct ixgbe_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  stub4 (struct ixgbe_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub5 (struct ixgbe_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  stub6 (struct ixgbe_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub7 (struct ixgbe_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  stub8 (struct ixgbe_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub9 (struct ixgbe_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  udelay (int) ; 

s32 ixgbe_setup_phy_link_generic(struct ixgbe_hw *hw)
{
	s32 status = 0;
	u32 time_out;
	u32 max_time_out = 10;
	u16 autoneg_reg = IXGBE_MII_AUTONEG_REG;
	bool autoneg = false;
	ixgbe_link_speed speed;

	ixgbe_get_copper_link_capabilities_generic(hw, &speed, &autoneg);

	if (speed & IXGBE_LINK_SPEED_10GB_FULL) {
		/* Set or unset auto-negotiation 10G advertisement */
		hw->phy.ops.read_reg(hw, MDIO_AN_10GBT_CTRL,
				     MDIO_MMD_AN,
				     &autoneg_reg);

		autoneg_reg &= ~MDIO_AN_10GBT_CTRL_ADV10G;
		if (hw->phy.autoneg_advertised & IXGBE_LINK_SPEED_10GB_FULL)
			autoneg_reg |= MDIO_AN_10GBT_CTRL_ADV10G;

		hw->phy.ops.write_reg(hw, MDIO_AN_10GBT_CTRL,
				      MDIO_MMD_AN,
				      autoneg_reg);
	}

	if (speed & IXGBE_LINK_SPEED_1GB_FULL) {
		/* Set or unset auto-negotiation 1G advertisement */
		hw->phy.ops.read_reg(hw,
				     IXGBE_MII_AUTONEG_VENDOR_PROVISION_1_REG,
				     MDIO_MMD_AN,
				     &autoneg_reg);

		autoneg_reg &= ~IXGBE_MII_1GBASE_T_ADVERTISE;
		if (hw->phy.autoneg_advertised & IXGBE_LINK_SPEED_1GB_FULL)
			autoneg_reg |= IXGBE_MII_1GBASE_T_ADVERTISE;

		hw->phy.ops.write_reg(hw,
				      IXGBE_MII_AUTONEG_VENDOR_PROVISION_1_REG,
				      MDIO_MMD_AN,
				      autoneg_reg);
	}

	if (speed & IXGBE_LINK_SPEED_100_FULL) {
		/* Set or unset auto-negotiation 100M advertisement */
		hw->phy.ops.read_reg(hw, MDIO_AN_ADVERTISE,
				     MDIO_MMD_AN,
				     &autoneg_reg);

		autoneg_reg &= ~(ADVERTISE_100FULL |
				 ADVERTISE_100HALF);
		if (hw->phy.autoneg_advertised & IXGBE_LINK_SPEED_100_FULL)
			autoneg_reg |= ADVERTISE_100FULL;

		hw->phy.ops.write_reg(hw, MDIO_AN_ADVERTISE,
				      MDIO_MMD_AN,
				      autoneg_reg);
	}

	/* Restart PHY autonegotiation and wait for completion */
	hw->phy.ops.read_reg(hw, MDIO_CTRL1,
			     MDIO_MMD_AN, &autoneg_reg);

	autoneg_reg |= MDIO_AN_CTRL1_RESTART;

	hw->phy.ops.write_reg(hw, MDIO_CTRL1,
			      MDIO_MMD_AN, autoneg_reg);

	/* Wait for autonegotiation to finish */
	for (time_out = 0; time_out < max_time_out; time_out++) {
		udelay(10);
		/* Restart PHY autonegotiation and wait for completion */
		status = hw->phy.ops.read_reg(hw, MDIO_STAT1,
					      MDIO_MMD_AN,
					      &autoneg_reg);

		autoneg_reg &= MDIO_AN_STAT1_COMPLETE;
		if (autoneg_reg == MDIO_AN_STAT1_COMPLETE) {
			break;
		}
	}

	if (time_out == max_time_out) {
		status = IXGBE_ERR_LINK_SETUP;
		hw_dbg(hw, "ixgbe_setup_phy_link_generic: time out");
	}

	return status;
}