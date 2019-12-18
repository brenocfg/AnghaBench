#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct TYPE_7__ {int /*<<< orphan*/  (* release_swfw_sync ) (struct e1000_hw*,int /*<<< orphan*/ ) ;scalar_t__ (* acquire_swfw_sync ) (struct e1000_hw*,int /*<<< orphan*/ ) ;} ;
struct TYPE_8__ {scalar_t__ type; TYPE_3__ ops; } ;
struct TYPE_5__ {int global_device_reset; } ;
struct TYPE_6__ {TYPE_1__ _82575; } ;
struct e1000_hw {TYPE_4__ mac; TYPE_2__ dev_spec; } ;
typedef  scalar_t__ s32 ;

/* Variables and functions */
 int /*<<< orphan*/  E1000_CTRL ; 
 int E1000_CTRL_DEV_RST ; 
 int E1000_CTRL_RST ; 
 int /*<<< orphan*/  E1000_ICR ; 
 int /*<<< orphan*/  E1000_IMC ; 
 int /*<<< orphan*/  E1000_RCTL ; 
 int /*<<< orphan*/  E1000_STATUS ; 
 int E1000_STAT_DEV_RST_SET ; 
 int /*<<< orphan*/  E1000_SW_SYNCH_MB ; 
 int /*<<< orphan*/  E1000_TCTL ; 
 int E1000_TCTL_PSP ; 
 scalar_t__ e1000_82580 ; 
 int /*<<< orphan*/  hw_dbg (char*) ; 
 scalar_t__ igb_check_alt_mac_addr (struct e1000_hw*) ; 
 scalar_t__ igb_disable_pcie_master (struct e1000_hw*) ; 
 scalar_t__ igb_get_auto_rd_done (struct e1000_hw*) ; 
 scalar_t__ igb_reset_mdicnfg_82580 (struct e1000_hw*) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int rd32 (int /*<<< orphan*/ ) ; 
 scalar_t__ stub1 (struct e1000_hw*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (struct e1000_hw*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wr32 (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  wrfl () ; 

__attribute__((used)) static s32 igb_reset_hw_82580(struct e1000_hw *hw)
{
	s32 ret_val = 0;
	/* BH SW mailbox bit in SW_FW_SYNC */
	u16 swmbsw_mask = E1000_SW_SYNCH_MB;
	u32 ctrl;
	bool global_device_reset = hw->dev_spec._82575.global_device_reset;

	hw->dev_spec._82575.global_device_reset = false;

	/* due to hw errata, global device reset doesn't always
	 * work on 82580
	 */
	if (hw->mac.type == e1000_82580)
		global_device_reset = false;

	/* Get current control state. */
	ctrl = rd32(E1000_CTRL);

	/* Prevent the PCI-E bus from sticking if there is no TLP connection
	 * on the last TLP read/write transaction when MAC is reset.
	 */
	ret_val = igb_disable_pcie_master(hw);
	if (ret_val)
		hw_dbg("PCI-E Master disable polling has failed.\n");

	hw_dbg("Masking off all interrupts\n");
	wr32(E1000_IMC, 0xffffffff);
	wr32(E1000_RCTL, 0);
	wr32(E1000_TCTL, E1000_TCTL_PSP);
	wrfl();

	msleep(10);

	/* Determine whether or not a global dev reset is requested */
	if (global_device_reset &&
		hw->mac.ops.acquire_swfw_sync(hw, swmbsw_mask))
			global_device_reset = false;

	if (global_device_reset &&
		!(rd32(E1000_STATUS) & E1000_STAT_DEV_RST_SET))
		ctrl |= E1000_CTRL_DEV_RST;
	else
		ctrl |= E1000_CTRL_RST;

	wr32(E1000_CTRL, ctrl);
	wrfl();

	/* Add delay to insure DEV_RST has time to complete */
	if (global_device_reset)
		msleep(5);

	ret_val = igb_get_auto_rd_done(hw);
	if (ret_val) {
		/* When auto config read does not complete, do not
		 * return with an error. This can happen in situations
		 * where there is no eeprom and prevents getting link.
		 */
		hw_dbg("Auto Read Done did not complete\n");
	}

	/* clear global device reset status bit */
	wr32(E1000_STATUS, E1000_STAT_DEV_RST_SET);

	/* Clear any pending interrupt events. */
	wr32(E1000_IMC, 0xffffffff);
	rd32(E1000_ICR);

	ret_val = igb_reset_mdicnfg_82580(hw);
	if (ret_val)
		hw_dbg("Could not reset MDICNFG based on EEPROM\n");

	/* Install any alternate MAC address into RAR0 */
	ret_val = igb_check_alt_mac_addr(hw);

	/* Release semaphore */
	if (global_device_reset)
		hw->mac.ops.release_swfw_sync(hw, swmbsw_mask);

	return ret_val;
}