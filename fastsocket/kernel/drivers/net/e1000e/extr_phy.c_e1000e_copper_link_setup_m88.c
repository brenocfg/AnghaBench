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
struct e1000_phy_info {scalar_t__ type; int mdix; scalar_t__ id; int revision; TYPE_1__ ops; scalar_t__ disable_polarity_correction; } ;
struct e1000_hw {struct e1000_phy_info phy; } ;
typedef  scalar_t__ s32 ;

/* Variables and functions */
 scalar_t__ BME1000_E_PHY_ID_R2 ; 
 int BME1000_PSCR_ENABLE_DOWNSHIFT ; 
 int E1000_REVISION_4 ; 
 int I82578_EPSCR_DOWNSHIFT_COUNTER_MASK ; 
 int I82578_EPSCR_DOWNSHIFT_ENABLE ; 
 int M88E1000_EPSCR_MASTER_DOWNSHIFT_1X ; 
 int M88E1000_EPSCR_MASTER_DOWNSHIFT_MASK ; 
 int M88E1000_EPSCR_SLAVE_DOWNSHIFT_1X ; 
 int M88E1000_EPSCR_SLAVE_DOWNSHIFT_MASK ; 
 int M88E1000_EPSCR_TX_CLK_25 ; 
 int M88E1000_EXT_PHY_SPEC_CTRL ; 
 int M88E1000_PHY_SPEC_CTRL ; 
 int M88E1000_PSCR_ASSERT_CRS_ON_TX ; 
 int M88E1000_PSCR_AUTO_X_1000T ; 
 int M88E1000_PSCR_AUTO_X_MODE ; 
 int M88E1000_PSCR_MDIX_MANUAL_MODE ; 
 int M88E1000_PSCR_MDI_MANUAL_MODE ; 
 int M88E1000_PSCR_POLARITY_REVERSAL ; 
 scalar_t__ M88E1111_I_PHY_ID ; 
 int M88EC018_EPSCR_DOWNSHIFT_COUNTER_5X ; 
 int M88EC018_EPSCR_DOWNSHIFT_COUNTER_MASK ; 
 scalar_t__ e1000_phy_82578 ; 
 scalar_t__ e1000_phy_bm ; 
 scalar_t__ e1000_phy_m88 ; 
 scalar_t__ e1e_rphy (struct e1000_hw*,int,int*) ; 
 scalar_t__ e1e_wphy (struct e1000_hw*,int,int) ; 
 int /*<<< orphan*/  e_dbg (char*) ; 
 scalar_t__ stub1 (struct e1000_hw*) ; 
 scalar_t__ stub2 (struct e1000_hw*) ; 

s32 e1000e_copper_link_setup_m88(struct e1000_hw *hw)
{
	struct e1000_phy_info *phy = &hw->phy;
	s32 ret_val;
	u16 phy_data;

	/* Enable CRS on Tx. This must be set for half-duplex operation. */
	ret_val = e1e_rphy(hw, M88E1000_PHY_SPEC_CTRL, &phy_data);
	if (ret_val)
		return ret_val;

	/* For BM PHY this bit is downshift enable */
	if (phy->type != e1000_phy_bm)
		phy_data |= M88E1000_PSCR_ASSERT_CRS_ON_TX;

	/* Options:
	 *   MDI/MDI-X = 0 (default)
	 *   0 - Auto for all speeds
	 *   1 - MDI mode
	 *   2 - MDI-X mode
	 *   3 - Auto for 1000Base-T only (MDI-X for 10/100Base-T modes)
	 */
	phy_data &= ~M88E1000_PSCR_AUTO_X_MODE;

	switch (phy->mdix) {
	case 1:
		phy_data |= M88E1000_PSCR_MDI_MANUAL_MODE;
		break;
	case 2:
		phy_data |= M88E1000_PSCR_MDIX_MANUAL_MODE;
		break;
	case 3:
		phy_data |= M88E1000_PSCR_AUTO_X_1000T;
		break;
	case 0:
	default:
		phy_data |= M88E1000_PSCR_AUTO_X_MODE;
		break;
	}

	/* Options:
	 *   disable_polarity_correction = 0 (default)
	 *       Automatic Correction for Reversed Cable Polarity
	 *   0 - Disabled
	 *   1 - Enabled
	 */
	phy_data &= ~M88E1000_PSCR_POLARITY_REVERSAL;
	if (phy->disable_polarity_correction)
		phy_data |= M88E1000_PSCR_POLARITY_REVERSAL;

	/* Enable downshift on BM (disabled by default) */
	if (phy->type == e1000_phy_bm) {
		/* For 82574/82583, first disable then enable downshift */
		if (phy->id == BME1000_E_PHY_ID_R2) {
			phy_data &= ~BME1000_PSCR_ENABLE_DOWNSHIFT;
			ret_val = e1e_wphy(hw, M88E1000_PHY_SPEC_CTRL,
					   phy_data);
			if (ret_val)
				return ret_val;
			/* Commit the changes. */
			ret_val = phy->ops.commit(hw);
			if (ret_val) {
				e_dbg("Error committing the PHY changes\n");
				return ret_val;
			}
		}

		phy_data |= BME1000_PSCR_ENABLE_DOWNSHIFT;
	}

	ret_val = e1e_wphy(hw, M88E1000_PHY_SPEC_CTRL, phy_data);
	if (ret_val)
		return ret_val;

	if ((phy->type == e1000_phy_m88) &&
	    (phy->revision < E1000_REVISION_4) &&
	    (phy->id != BME1000_E_PHY_ID_R2)) {
		/* Force TX_CLK in the Extended PHY Specific Control Register
		 * to 25MHz clock.
		 */
		ret_val = e1e_rphy(hw, M88E1000_EXT_PHY_SPEC_CTRL, &phy_data);
		if (ret_val)
			return ret_val;

		phy_data |= M88E1000_EPSCR_TX_CLK_25;

		if ((phy->revision == 2) && (phy->id == M88E1111_I_PHY_ID)) {
			/* 82573L PHY - set the downshift counter to 5x. */
			phy_data &= ~M88EC018_EPSCR_DOWNSHIFT_COUNTER_MASK;
			phy_data |= M88EC018_EPSCR_DOWNSHIFT_COUNTER_5X;
		} else {
			/* Configure Master and Slave downshift values */
			phy_data &= ~(M88E1000_EPSCR_MASTER_DOWNSHIFT_MASK |
				      M88E1000_EPSCR_SLAVE_DOWNSHIFT_MASK);
			phy_data |= (M88E1000_EPSCR_MASTER_DOWNSHIFT_1X |
				     M88E1000_EPSCR_SLAVE_DOWNSHIFT_1X);
		}
		ret_val = e1e_wphy(hw, M88E1000_EXT_PHY_SPEC_CTRL, phy_data);
		if (ret_val)
			return ret_val;
	}

	if ((phy->type == e1000_phy_bm) && (phy->id == BME1000_E_PHY_ID_R2)) {
		/* Set PHY page 0, register 29 to 0x0003 */
		ret_val = e1e_wphy(hw, 29, 0x0003);
		if (ret_val)
			return ret_val;

		/* Set PHY page 0, register 30 to 0x0000 */
		ret_val = e1e_wphy(hw, 30, 0x0000);
		if (ret_val)
			return ret_val;
	}

	/* Commit the changes. */
	if (phy->ops.commit) {
		ret_val = phy->ops.commit(hw);
		if (ret_val) {
			e_dbg("Error committing the PHY changes\n");
			return ret_val;
		}
	}

	if (phy->type == e1000_phy_82578) {
		ret_val = e1e_rphy(hw, M88E1000_EXT_PHY_SPEC_CTRL, &phy_data);
		if (ret_val)
			return ret_val;

		/* 82578 PHY - set the downshift count to 1x. */
		phy_data |= I82578_EPSCR_DOWNSHIFT_ENABLE;
		phy_data &= ~I82578_EPSCR_DOWNSHIFT_COUNTER_MASK;
		ret_val = e1e_wphy(hw, M88E1000_EXT_PHY_SPEC_CTRL, phy_data);
		if (ret_val)
			return ret_val;
	}

	return 0;
}