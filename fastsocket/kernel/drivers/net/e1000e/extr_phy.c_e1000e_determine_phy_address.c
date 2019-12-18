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
typedef  scalar_t__ u32 ;
struct TYPE_2__ {int id; scalar_t__ addr; } ;
struct e1000_hw {TYPE_1__ phy; } ;
typedef  int /*<<< orphan*/  s32 ;
typedef  enum e1000_phy_type { ____Placeholder_e1000_phy_type } e1000_phy_type ;

/* Variables and functions */
 int /*<<< orphan*/  E1000_ERR_PHY_TYPE ; 
 scalar_t__ E1000_MAX_PHY_ADDR ; 
 int e1000_phy_unknown ; 
 int /*<<< orphan*/  e1000e_get_phy_id (struct e1000_hw*) ; 
 int e1000e_get_phy_type_from_id (int) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

s32 e1000e_determine_phy_address(struct e1000_hw *hw)
{
	u32 phy_addr = 0;
	u32 i;
	enum e1000_phy_type phy_type = e1000_phy_unknown;

	hw->phy.id = phy_type;

	for (phy_addr = 0; phy_addr < E1000_MAX_PHY_ADDR; phy_addr++) {
		hw->phy.addr = phy_addr;
		i = 0;

		do {
			e1000e_get_phy_id(hw);
			phy_type = e1000e_get_phy_type_from_id(hw->phy.id);

			/* If phy_type is valid, break - we found our
			 * PHY address
			 */
			if (phy_type != e1000_phy_unknown)
				return 0;

			usleep_range(1000, 2000);
			i++;
		} while (i < 10);
	}

	return -E1000_ERR_PHY_TYPE;
}