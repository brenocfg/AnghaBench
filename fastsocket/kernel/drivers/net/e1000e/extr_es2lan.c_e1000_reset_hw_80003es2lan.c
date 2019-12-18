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
typedef  int /*<<< orphan*/  u16 ;
struct e1000_hw {int dummy; } ;
typedef  scalar_t__ s32 ;

/* Variables and functions */
 int /*<<< orphan*/  CTRL ; 
 int E1000_CTRL_RST ; 
 int /*<<< orphan*/  E1000_KMRNCTRLSTA_IBIST_DISABLE ; 
 int /*<<< orphan*/  E1000_KMRNCTRLSTA_INBAND_PARAM ; 
 int E1000_TCTL_PSP ; 
 int /*<<< orphan*/  ICR ; 
 int /*<<< orphan*/  IMC ; 
 int /*<<< orphan*/  RCTL ; 
 int /*<<< orphan*/  TCTL ; 
 scalar_t__ e1000_acquire_phy_80003es2lan (struct e1000_hw*) ; 
 scalar_t__ e1000_check_alt_mac_addr_generic (struct e1000_hw*) ; 
 int /*<<< orphan*/  e1000_read_kmrn_reg_80003es2lan (struct e1000_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  e1000_release_phy_80003es2lan (struct e1000_hw*) ; 
 int /*<<< orphan*/  e1000_write_kmrn_reg_80003es2lan (struct e1000_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ e1000e_disable_pcie_master (struct e1000_hw*) ; 
 scalar_t__ e1000e_get_auto_rd_done (struct e1000_hw*) ; 
 int /*<<< orphan*/  e1e_flush () ; 
 int /*<<< orphan*/  e_dbg (char*) ; 
 int er32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ew32 (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

__attribute__((used)) static s32 e1000_reset_hw_80003es2lan(struct e1000_hw *hw)
{
	u32 ctrl;
	s32 ret_val;
	u16 kum_reg_data;

	/* Prevent the PCI-E bus from sticking if there is no TLP connection
	 * on the last TLP read/write transaction when MAC is reset.
	 */
	ret_val = e1000e_disable_pcie_master(hw);
	if (ret_val)
		e_dbg("PCI-E Master disable polling has failed.\n");

	e_dbg("Masking off all interrupts\n");
	ew32(IMC, 0xffffffff);

	ew32(RCTL, 0);
	ew32(TCTL, E1000_TCTL_PSP);
	e1e_flush();

	usleep_range(10000, 20000);

	ctrl = er32(CTRL);

	ret_val = e1000_acquire_phy_80003es2lan(hw);
	if (ret_val)
		return ret_val;

	e_dbg("Issuing a global reset to MAC\n");
	ew32(CTRL, ctrl | E1000_CTRL_RST);
	e1000_release_phy_80003es2lan(hw);

	/* Disable IBIST slave mode (far-end loopback) */
	e1000_read_kmrn_reg_80003es2lan(hw, E1000_KMRNCTRLSTA_INBAND_PARAM,
					&kum_reg_data);
	kum_reg_data |= E1000_KMRNCTRLSTA_IBIST_DISABLE;
	e1000_write_kmrn_reg_80003es2lan(hw, E1000_KMRNCTRLSTA_INBAND_PARAM,
					 kum_reg_data);

	ret_val = e1000e_get_auto_rd_done(hw);
	if (ret_val)
		/* We don't want to continue accessing MAC registers. */
		return ret_val;

	/* Clear any pending interrupt events. */
	ew32(IMC, 0xffffffff);
	er32(ICR);

	return e1000_check_alt_mac_addr_generic(hw);
}