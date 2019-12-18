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
struct TYPE_2__ {scalar_t__ (* read_reg ) (struct e1000_hw*,int,int*) ;} ;
struct e1000_phy_info {int /*<<< orphan*/  cable_polarity; TYPE_1__ ops; } ;
struct e1000_hw {struct e1000_phy_info phy; } ;
typedef  scalar_t__ s32 ;

/* Variables and functions */
 int IGP01E1000_PHY_PCS_INIT_REG ; 
 int IGP01E1000_PHY_POLARITY_MASK ; 
 int IGP01E1000_PHY_PORT_STATUS ; 
 int IGP01E1000_PSSR_POLARITY_REVERSED ; 
 int IGP01E1000_PSSR_SPEED_1000MBPS ; 
 int IGP01E1000_PSSR_SPEED_MASK ; 
 int /*<<< orphan*/  e1000_rev_polarity_normal ; 
 int /*<<< orphan*/  e1000_rev_polarity_reversed ; 
 scalar_t__ stub1 (struct e1000_hw*,int,int*) ; 
 scalar_t__ stub2 (struct e1000_hw*,int,int*) ; 

__attribute__((used)) static s32 igb_check_polarity_igp(struct e1000_hw *hw)
{
	struct e1000_phy_info *phy = &hw->phy;
	s32 ret_val;
	u16 data, offset, mask;

	/* Polarity is determined based on the speed of
	 * our connection.
	 */
	ret_val = phy->ops.read_reg(hw, IGP01E1000_PHY_PORT_STATUS, &data);
	if (ret_val)
		goto out;

	if ((data & IGP01E1000_PSSR_SPEED_MASK) ==
	    IGP01E1000_PSSR_SPEED_1000MBPS) {
		offset	= IGP01E1000_PHY_PCS_INIT_REG;
		mask	= IGP01E1000_PHY_POLARITY_MASK;
	} else {
		/* This really only applies to 10Mbps since
		 * there is no polarity for 100Mbps (always 0).
		 */
		offset	= IGP01E1000_PHY_PORT_STATUS;
		mask	= IGP01E1000_PSSR_POLARITY_REVERSED;
	}

	ret_val = phy->ops.read_reg(hw, offset, &data);

	if (!ret_val)
		phy->cable_polarity = (data & mask)
				      ? e1000_rev_polarity_reversed
				      : e1000_rev_polarity_normal;

out:
	return ret_val;
}