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
typedef  int u16 ;
struct TYPE_2__ {scalar_t__ (* commit ) (struct e1000_hw*) ;} ;
struct e1000_phy_info {scalar_t__ type; scalar_t__ autoneg_wait_to_complete; TYPE_1__ ops; } ;
struct e1000_hw {struct e1000_phy_info phy; } ;
typedef  scalar_t__ s32 ;

/* Variables and functions */
 int M88E1000_EPSCR_TX_CLK_25 ; 
 int /*<<< orphan*/  M88E1000_EXT_PHY_SPEC_CTRL ; 
 int /*<<< orphan*/  M88E1000_PHY_PAGE_SELECT ; 
 int /*<<< orphan*/  M88E1000_PHY_SPEC_CTRL ; 
 int M88E1000_PSCR_ASSERT_CRS_ON_TX ; 
 int M88E1000_PSCR_AUTO_X_MODE ; 
 int /*<<< orphan*/  MII_BMCR ; 
 int /*<<< orphan*/  PHY_FORCE_LIMIT ; 
 scalar_t__ e1000_phy_m88 ; 
 int /*<<< orphan*/  e1000e_phy_force_speed_duplex_setup (struct e1000_hw*,int*) ; 
 scalar_t__ e1000e_phy_has_link_generic (struct e1000_hw*,int /*<<< orphan*/ ,int,int*) ; 
 scalar_t__ e1000e_phy_reset_dsp (struct e1000_hw*) ; 
 scalar_t__ e1e_rphy (struct e1000_hw*,int /*<<< orphan*/ ,int*) ; 
 scalar_t__ e1e_wphy (struct e1000_hw*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  e_dbg (char*,...) ; 
 scalar_t__ stub1 (struct e1000_hw*) ; 

s32 e1000e_phy_force_speed_duplex_m88(struct e1000_hw *hw)
{
	struct e1000_phy_info *phy = &hw->phy;
	s32 ret_val;
	u16 phy_data;
	bool link;

	/* Clear Auto-Crossover to force MDI manually.  M88E1000 requires MDI
	 * forced whenever speed and duplex are forced.
	 */
	ret_val = e1e_rphy(hw, M88E1000_PHY_SPEC_CTRL, &phy_data);
	if (ret_val)
		return ret_val;

	phy_data &= ~M88E1000_PSCR_AUTO_X_MODE;
	ret_val = e1e_wphy(hw, M88E1000_PHY_SPEC_CTRL, phy_data);
	if (ret_val)
		return ret_val;

	e_dbg("M88E1000 PSCR: %X\n", phy_data);

	ret_val = e1e_rphy(hw, MII_BMCR, &phy_data);
	if (ret_val)
		return ret_val;

	e1000e_phy_force_speed_duplex_setup(hw, &phy_data);

	ret_val = e1e_wphy(hw, MII_BMCR, phy_data);
	if (ret_val)
		return ret_val;

	/* Reset the phy to commit changes. */
	if (hw->phy.ops.commit) {
		ret_val = hw->phy.ops.commit(hw);
		if (ret_val)
			return ret_val;
	}

	if (phy->autoneg_wait_to_complete) {
		e_dbg("Waiting for forced speed/duplex link on M88 phy.\n");

		ret_val = e1000e_phy_has_link_generic(hw, PHY_FORCE_LIMIT,
						     100000, &link);
		if (ret_val)
			return ret_val;

		if (!link) {
			if (hw->phy.type != e1000_phy_m88) {
				e_dbg("Link taking longer than expected.\n");
			} else {
				/* We didn't get link.
				 * Reset the DSP and cross our fingers.
				 */
				ret_val = e1e_wphy(hw, M88E1000_PHY_PAGE_SELECT,
						   0x001d);
				if (ret_val)
					return ret_val;
				ret_val = e1000e_phy_reset_dsp(hw);
				if (ret_val)
					return ret_val;
			}
		}

		/* Try once more */
		ret_val = e1000e_phy_has_link_generic(hw, PHY_FORCE_LIMIT,
						     100000, &link);
		if (ret_val)
			return ret_val;
	}

	if (hw->phy.type != e1000_phy_m88)
		return 0;

	ret_val = e1e_rphy(hw, M88E1000_EXT_PHY_SPEC_CTRL, &phy_data);
	if (ret_val)
		return ret_val;

	/* Resetting the phy means we need to re-force TX_CLK in the
	 * Extended PHY Specific Control Register to 25MHz clock from
	 * the reset value of 2.5MHz.
	 */
	phy_data |= M88E1000_EPSCR_TX_CLK_25;
	ret_val = e1e_wphy(hw, M88E1000_EXT_PHY_SPEC_CTRL, phy_data);
	if (ret_val)
		return ret_val;

	/* In addition, we must re-enable CRS on Tx for both half and full
	 * duplex.
	 */
	ret_val = e1e_rphy(hw, M88E1000_PHY_SPEC_CTRL, &phy_data);
	if (ret_val)
		return ret_val;

	phy_data |= M88E1000_PSCR_ASSERT_CRS_ON_TX;
	ret_val = e1e_wphy(hw, M88E1000_PHY_SPEC_CTRL, phy_data);

	return ret_val;
}