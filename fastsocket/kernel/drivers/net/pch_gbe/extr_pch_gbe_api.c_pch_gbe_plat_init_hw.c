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
struct pch_gbe_hw {int dummy; } ;
typedef  scalar_t__ s32 ;

/* Variables and functions */
 scalar_t__ pch_gbe_phy_get_id (struct pch_gbe_hw*) ; 
 int /*<<< orphan*/  pch_gbe_phy_init_setting (struct pch_gbe_hw*) ; 
 int /*<<< orphan*/  pch_gbe_phy_set_rgmii (struct pch_gbe_hw*) ; 
 int /*<<< orphan*/  pr_err (char*) ; 

__attribute__((used)) static s32 pch_gbe_plat_init_hw(struct pch_gbe_hw *hw)
{
	s32 ret_val;

	ret_val = pch_gbe_phy_get_id(hw);
	if (ret_val) {
		pr_err("pch_gbe_phy_get_id error\n");
		return ret_val;
	}
	pch_gbe_phy_init_setting(hw);
	/* Setup Mac interface option RGMII */
#ifdef PCH_GBE_MAC_IFOP_RGMII
	pch_gbe_phy_set_rgmii(hw);
#endif
	return ret_val;
}