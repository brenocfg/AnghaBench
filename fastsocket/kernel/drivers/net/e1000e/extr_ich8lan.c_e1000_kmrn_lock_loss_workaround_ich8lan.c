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
typedef  int u32 ;
typedef  int u16 ;
struct e1000_dev_spec_ich8lan {int /*<<< orphan*/  kmrn_lock_loss_workaround_enabled; } ;
struct TYPE_2__ {struct e1000_dev_spec_ich8lan ich8lan; } ;
struct e1000_hw {TYPE_1__ dev_spec; } ;
typedef  scalar_t__ s32 ;

/* Variables and functions */
 scalar_t__ E1000_ERR_PHY ; 
 int E1000_PHY_CTRL_GBE_DISABLE ; 
 int E1000_PHY_CTRL_NOND0A_GBE_DISABLE ; 
 int /*<<< orphan*/  IGP3_KMRN_DIAG ; 
 int IGP3_KMRN_DIAG_PCS_LOCK_LOSS ; 
 int /*<<< orphan*/  PHY_CTRL ; 
 int /*<<< orphan*/  e1000_phy_hw_reset (struct e1000_hw*) ; 
 int /*<<< orphan*/  e1000e_gig_downshift_workaround_ich8lan (struct e1000_hw*) ; 
 scalar_t__ e1000e_phy_has_link_generic (struct e1000_hw*,int,int /*<<< orphan*/ ,int*) ; 
 scalar_t__ e1e_rphy (struct e1000_hw*,int /*<<< orphan*/ ,int*) ; 
 int er32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ew32 (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mdelay (int) ; 

__attribute__((used)) static s32 e1000_kmrn_lock_loss_workaround_ich8lan(struct e1000_hw *hw)
{
	struct e1000_dev_spec_ich8lan *dev_spec = &hw->dev_spec.ich8lan;
	u32 phy_ctrl;
	s32 ret_val;
	u16 i, data;
	bool link;

	if (!dev_spec->kmrn_lock_loss_workaround_enabled)
		return 0;

	/* Make sure link is up before proceeding.  If not just return.
	 * Attempting this while link is negotiating fouled up link
	 * stability
	 */
	ret_val = e1000e_phy_has_link_generic(hw, 1, 0, &link);
	if (!link)
		return 0;

	for (i = 0; i < 10; i++) {
		/* read once to clear */
		ret_val = e1e_rphy(hw, IGP3_KMRN_DIAG, &data);
		if (ret_val)
			return ret_val;
		/* and again to get new status */
		ret_val = e1e_rphy(hw, IGP3_KMRN_DIAG, &data);
		if (ret_val)
			return ret_val;

		/* check for PCS lock */
		if (!(data & IGP3_KMRN_DIAG_PCS_LOCK_LOSS))
			return 0;

		/* Issue PHY reset */
		e1000_phy_hw_reset(hw);
		mdelay(5);
	}
	/* Disable GigE link negotiation */
	phy_ctrl = er32(PHY_CTRL);
	phy_ctrl |= (E1000_PHY_CTRL_GBE_DISABLE |
		     E1000_PHY_CTRL_NOND0A_GBE_DISABLE);
	ew32(PHY_CTRL, phy_ctrl);

	/* Call gig speed drop workaround on Gig disable before accessing
	 * any PHY registers
	 */
	e1000e_gig_downshift_workaround_ich8lan(hw);

	/* unable to acquire PCS lock */
	return -E1000_ERR_PHY;
}