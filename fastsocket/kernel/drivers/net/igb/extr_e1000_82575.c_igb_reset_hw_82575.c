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
struct e1000_hw {int dummy; } ;
typedef  scalar_t__ s32 ;

/* Variables and functions */
 int /*<<< orphan*/  E1000_CTRL ; 
 int E1000_CTRL_RST ; 
 int /*<<< orphan*/  E1000_EECD ; 
 int E1000_EECD_PRES ; 
 int /*<<< orphan*/  E1000_ICR ; 
 int /*<<< orphan*/  E1000_IMC ; 
 int /*<<< orphan*/  E1000_RCTL ; 
 int /*<<< orphan*/  E1000_TCTL ; 
 int E1000_TCTL_PSP ; 
 int /*<<< orphan*/  hw_dbg (char*) ; 
 scalar_t__ igb_check_alt_mac_addr (struct e1000_hw*) ; 
 scalar_t__ igb_disable_pcie_master (struct e1000_hw*) ; 
 scalar_t__ igb_get_auto_rd_done (struct e1000_hw*) ; 
 int /*<<< orphan*/  igb_reset_init_script_82575 (struct e1000_hw*) ; 
 scalar_t__ igb_set_pcie_completion_timeout (struct e1000_hw*) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int rd32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wr32 (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  wrfl () ; 

__attribute__((used)) static s32 igb_reset_hw_82575(struct e1000_hw *hw)
{
	u32 ctrl;
	s32 ret_val;

	/* Prevent the PCI-E bus from sticking if there is no TLP connection
	 * on the last TLP read/write transaction when MAC is reset.
	 */
	ret_val = igb_disable_pcie_master(hw);
	if (ret_val)
		hw_dbg("PCI-E Master disable polling has failed.\n");

	/* set the completion timeout for interface */
	ret_val = igb_set_pcie_completion_timeout(hw);
	if (ret_val) {
		hw_dbg("PCI-E Set completion timeout has failed.\n");
	}

	hw_dbg("Masking off all interrupts\n");
	wr32(E1000_IMC, 0xffffffff);

	wr32(E1000_RCTL, 0);
	wr32(E1000_TCTL, E1000_TCTL_PSP);
	wrfl();

	msleep(10);

	ctrl = rd32(E1000_CTRL);

	hw_dbg("Issuing a global reset to MAC\n");
	wr32(E1000_CTRL, ctrl | E1000_CTRL_RST);

	ret_val = igb_get_auto_rd_done(hw);
	if (ret_val) {
		/* When auto config read does not complete, do not
		 * return with an error. This can happen in situations
		 * where there is no eeprom and prevents getting link.
		 */
		hw_dbg("Auto Read Done did not complete\n");
	}

	/* If EEPROM is not present, run manual init scripts */
	if ((rd32(E1000_EECD) & E1000_EECD_PRES) == 0)
		igb_reset_init_script_82575(hw);

	/* Clear any pending interrupt events. */
	wr32(E1000_IMC, 0xffffffff);
	rd32(E1000_ICR);

	/* Install any alternate MAC address into RAR0 */
	ret_val = igb_check_alt_mac_addr(hw);

	return ret_val;
}