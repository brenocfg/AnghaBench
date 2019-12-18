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
typedef  scalar_t__ u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct pch_gbe_phy_info {int /*<<< orphan*/  addr; } ;
struct pch_gbe_hw {struct pch_gbe_phy_info phy; } ;
typedef  int /*<<< orphan*/  s32 ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  PCH_GBE_HAL_MIIM_WRITE ; 
 scalar_t__ PHY_MAX_REG_ADDRESS ; 
 int /*<<< orphan*/  pch_gbe_mac_ctrl_miim (struct pch_gbe_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_err (char*,scalar_t__) ; 

s32 pch_gbe_phy_write_reg_miic(struct pch_gbe_hw *hw, u32 offset, u16 data)
{
	struct pch_gbe_phy_info *phy = &hw->phy;

	if (offset > PHY_MAX_REG_ADDRESS) {
		pr_err("PHY Address %d is out of range\n", offset);
		return -EINVAL;
	}
	pch_gbe_mac_ctrl_miim(hw, phy->addr, PCH_GBE_HAL_MIIM_WRITE,
				 offset, data);
	return 0;
}