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
typedef  int u32 ;
typedef  int u16 ;
struct e1000_hw {int dummy; } ;
struct e1000_adapter {struct e1000_hw hw; } ;

/* Variables and functions */
 int /*<<< orphan*/  CTRL ; 
 int E1000_CTRL_FD ; 
 int E1000_CTRL_FRCDPX ; 
 int E1000_CTRL_FRCSPD ; 
 int E1000_CTRL_ILOS ; 
 int E1000_CTRL_SPD_1000 ; 
 int M88E1000_EXT_PHY_SPEC_CTRL ; 
 int M88E1000_PHY_SPEC_CTRL ; 
 int M88E1000_PSCR_AUTO_X_MODE ; 
 int MII_CR_LOOPBACK ; 
 int PHY_CTRL ; 
 int /*<<< orphan*/  e1000_phy_disable_receiver (struct e1000_adapter*) ; 
 int /*<<< orphan*/  e1000_phy_reset (struct e1000_hw*) ; 
 int /*<<< orphan*/  e1000_phy_reset_clk_and_crs (struct e1000_adapter*) ; 
 int /*<<< orphan*/  e1000_read_phy_reg (struct e1000_hw*,int,int*) ; 
 int /*<<< orphan*/  e1000_write_phy_reg (struct e1000_hw*,int,int) ; 
 int er32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ew32 (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static int e1000_nonintegrated_phy_loopback(struct e1000_adapter *adapter)
{
	struct e1000_hw *hw = &adapter->hw;
	u32 ctrl_reg;
	u16 phy_reg;

	/* Setup the Device Control Register for PHY loopback test. */

	ctrl_reg = er32(CTRL);
	ctrl_reg |= (E1000_CTRL_ILOS |		/* Invert Loss-Of-Signal */
		     E1000_CTRL_FRCSPD |	/* Set the Force Speed Bit */
		     E1000_CTRL_FRCDPX |	/* Set the Force Duplex Bit */
		     E1000_CTRL_SPD_1000 |	/* Force Speed to 1000 */
		     E1000_CTRL_FD);		/* Force Duplex to FULL */

	ew32(CTRL, ctrl_reg);

	/* Read the PHY Specific Control Register (0x10) */
	e1000_read_phy_reg(hw, M88E1000_PHY_SPEC_CTRL, &phy_reg);

	/* Clear Auto-Crossover bits in PHY Specific Control Register
	 * (bits 6:5).
	 */
	phy_reg &= ~M88E1000_PSCR_AUTO_X_MODE;
	e1000_write_phy_reg(hw, M88E1000_PHY_SPEC_CTRL, phy_reg);

	/* Perform software reset on the PHY */
	e1000_phy_reset(hw);

	/* Have to setup TX_CLK and TX_CRS after software reset */
	e1000_phy_reset_clk_and_crs(adapter);

	e1000_write_phy_reg(hw, PHY_CTRL, 0x8100);

	/* Wait for reset to complete. */
	udelay(500);

	/* Have to setup TX_CLK and TX_CRS after software reset */
	e1000_phy_reset_clk_and_crs(adapter);

	/* Write out to PHY registers 29 and 30 to disable the Receiver. */
	e1000_phy_disable_receiver(adapter);

	/* Set the loopback bit in the PHY control register. */
	e1000_read_phy_reg(hw, PHY_CTRL, &phy_reg);
	phy_reg |= MII_CR_LOOPBACK;
	e1000_write_phy_reg(hw, PHY_CTRL, phy_reg);

	/* Setup TX_CLK and TX_CRS one more time. */
	e1000_phy_reset_clk_and_crs(adapter);

	/* Check Phy Configuration */
	e1000_read_phy_reg(hw, PHY_CTRL, &phy_reg);
	if (phy_reg != 0x4100)
		 return 9;

	e1000_read_phy_reg(hw, M88E1000_EXT_PHY_SPEC_CTRL, &phy_reg);
	if (phy_reg != 0x0070)
		return 10;

	e1000_read_phy_reg(hw, 29, &phy_reg);
	if (phy_reg != 0x001A)
		return 11;

	return 0;
}