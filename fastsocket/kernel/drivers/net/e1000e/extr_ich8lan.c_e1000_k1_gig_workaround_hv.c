#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int u16 ;
struct TYPE_9__ {int /*<<< orphan*/  (* release ) (struct e1000_hw*) ;scalar_t__ (* acquire ) (struct e1000_hw*) ;} ;
struct TYPE_10__ {scalar_t__ type; TYPE_4__ ops; } ;
struct TYPE_8__ {scalar_t__ type; } ;
struct TYPE_6__ {int nvm_k1_enabled; } ;
struct TYPE_7__ {TYPE_1__ ich8lan; } ;
struct e1000_hw {TYPE_5__ phy; TYPE_3__ mac; TYPE_2__ dev_spec; } ;
typedef  scalar_t__ s32 ;

/* Variables and functions */
 int /*<<< orphan*/  BM_CS_STATUS ; 
 int BM_CS_STATUS_LINK_UP ; 
 int BM_CS_STATUS_RESOLVED ; 
 int BM_CS_STATUS_SPEED_1000 ; 
 int BM_CS_STATUS_SPEED_MASK ; 
 int /*<<< orphan*/  HV_M_STATUS ; 
 int HV_M_STATUS_AUTONEG_COMPLETE ; 
 int HV_M_STATUS_LINK_UP ; 
 int HV_M_STATUS_SPEED_1000 ; 
 int HV_M_STATUS_SPEED_MASK ; 
 int /*<<< orphan*/  PHY_REG (int,int) ; 
 scalar_t__ e1000_configure_k1_ich8lan (struct e1000_hw*,int) ; 
 scalar_t__ e1000_pchlan ; 
 scalar_t__ e1000_phy_82577 ; 
 scalar_t__ e1000_phy_82578 ; 
 scalar_t__ e1e_rphy_locked (struct e1000_hw*,int /*<<< orphan*/ ,int*) ; 
 scalar_t__ e1e_wphy_locked (struct e1000_hw*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ stub1 (struct e1000_hw*) ; 
 int /*<<< orphan*/  stub2 (struct e1000_hw*) ; 

__attribute__((used)) static s32 e1000_k1_gig_workaround_hv(struct e1000_hw *hw, bool link)
{
	s32 ret_val = 0;
	u16 status_reg = 0;
	bool k1_enable = hw->dev_spec.ich8lan.nvm_k1_enabled;

	if (hw->mac.type != e1000_pchlan)
		return 0;

	/* Wrap the whole flow with the sw flag */
	ret_val = hw->phy.ops.acquire(hw);
	if (ret_val)
		return ret_val;

	/* Disable K1 when link is 1Gbps, otherwise use the NVM setting */
	if (link) {
		if (hw->phy.type == e1000_phy_82578) {
			ret_val = e1e_rphy_locked(hw, BM_CS_STATUS,
						  &status_reg);
			if (ret_val)
				goto release;

			status_reg &= (BM_CS_STATUS_LINK_UP |
				       BM_CS_STATUS_RESOLVED |
				       BM_CS_STATUS_SPEED_MASK);

			if (status_reg == (BM_CS_STATUS_LINK_UP |
					   BM_CS_STATUS_RESOLVED |
					   BM_CS_STATUS_SPEED_1000))
				k1_enable = false;
		}

		if (hw->phy.type == e1000_phy_82577) {
			ret_val = e1e_rphy_locked(hw, HV_M_STATUS, &status_reg);
			if (ret_val)
				goto release;

			status_reg &= (HV_M_STATUS_LINK_UP |
				       HV_M_STATUS_AUTONEG_COMPLETE |
				       HV_M_STATUS_SPEED_MASK);

			if (status_reg == (HV_M_STATUS_LINK_UP |
					   HV_M_STATUS_AUTONEG_COMPLETE |
					   HV_M_STATUS_SPEED_1000))
				k1_enable = false;
		}

		/* Link stall fix for link up */
		ret_val = e1e_wphy_locked(hw, PHY_REG(770, 19), 0x0100);
		if (ret_val)
			goto release;

	} else {
		/* Link stall fix for link down */
		ret_val = e1e_wphy_locked(hw, PHY_REG(770, 19), 0x4100);
		if (ret_val)
			goto release;
	}

	ret_val = e1000_configure_k1_ich8lan(hw, k1_enable);

release:
	hw->phy.ops.release(hw);

	return ret_val;
}