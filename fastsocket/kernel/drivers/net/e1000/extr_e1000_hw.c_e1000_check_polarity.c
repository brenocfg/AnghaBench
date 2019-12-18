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
typedef  int u16 ;
struct e1000_hw {scalar_t__ phy_type; } ;
typedef  scalar_t__ s32 ;
typedef  int /*<<< orphan*/  e1000_rev_polarity ;

/* Variables and functions */
 scalar_t__ E1000_SUCCESS ; 
 int /*<<< orphan*/  IGP01E1000_PHY_PCS_INIT_REG ; 
 int IGP01E1000_PHY_POLARITY_MASK ; 
 int /*<<< orphan*/  IGP01E1000_PHY_PORT_STATUS ; 
 int IGP01E1000_PSSR_POLARITY_REVERSED ; 
 int IGP01E1000_PSSR_SPEED_1000MBPS ; 
 int IGP01E1000_PSSR_SPEED_MASK ; 
 int /*<<< orphan*/  M88E1000_PHY_SPEC_STATUS ; 
 int M88E1000_PSSR_REV_POLARITY ; 
 int M88E1000_PSSR_REV_POLARITY_SHIFT ; 
 scalar_t__ e1000_phy_igp ; 
 scalar_t__ e1000_phy_m88 ; 
 scalar_t__ e1000_read_phy_reg (struct e1000_hw*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  e1000_rev_polarity_normal ; 
 int /*<<< orphan*/  e1000_rev_polarity_reversed ; 
 int /*<<< orphan*/  e_dbg (char*) ; 

__attribute__((used)) static s32 e1000_check_polarity(struct e1000_hw *hw,
				e1000_rev_polarity *polarity)
{
	s32 ret_val;
	u16 phy_data;

	e_dbg("e1000_check_polarity");

	if (hw->phy_type == e1000_phy_m88) {
		/* return the Polarity bit in the Status register. */
		ret_val = e1000_read_phy_reg(hw, M88E1000_PHY_SPEC_STATUS,
					     &phy_data);
		if (ret_val)
			return ret_val;
		*polarity = ((phy_data & M88E1000_PSSR_REV_POLARITY) >>
			     M88E1000_PSSR_REV_POLARITY_SHIFT) ?
		    e1000_rev_polarity_reversed : e1000_rev_polarity_normal;

	} else if (hw->phy_type == e1000_phy_igp) {
		/* Read the Status register to check the speed */
		ret_val = e1000_read_phy_reg(hw, IGP01E1000_PHY_PORT_STATUS,
					     &phy_data);
		if (ret_val)
			return ret_val;

		/* If speed is 1000 Mbps, must read the IGP01E1000_PHY_PCS_INIT_REG to
		 * find the polarity status */
		if ((phy_data & IGP01E1000_PSSR_SPEED_MASK) ==
		    IGP01E1000_PSSR_SPEED_1000MBPS) {

			/* Read the GIG initialization PCS register (0x00B4) */
			ret_val =
			    e1000_read_phy_reg(hw, IGP01E1000_PHY_PCS_INIT_REG,
					       &phy_data);
			if (ret_val)
				return ret_val;

			/* Check the polarity bits */
			*polarity = (phy_data & IGP01E1000_PHY_POLARITY_MASK) ?
			    e1000_rev_polarity_reversed :
			    e1000_rev_polarity_normal;
		} else {
			/* For 10 Mbps, read the polarity bit in the status register. (for
			 * 100 Mbps this bit is always 0) */
			*polarity =
			    (phy_data & IGP01E1000_PSSR_POLARITY_REVERSED) ?
			    e1000_rev_polarity_reversed :
			    e1000_rev_polarity_normal;
		}
	}
	return E1000_SUCCESS;
}