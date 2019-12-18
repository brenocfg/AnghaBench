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
typedef  int u32 ;
typedef  int u16 ;
struct TYPE_10__ {scalar_t__ type; } ;
struct TYPE_8__ {scalar_t__ (* get_cfg_done ) (struct e1000_hw*) ;int /*<<< orphan*/  (* check_reset_block ) (struct e1000_hw*) ;} ;
struct TYPE_9__ {TYPE_3__ ops; } ;
struct e1000_dev_spec_ich8lan {int nvm_k1_enabled; } ;
struct TYPE_6__ {struct e1000_dev_spec_ich8lan ich8lan; } ;
struct e1000_hw {TYPE_5__ mac; TYPE_4__ phy; TYPE_2__* adapter; TYPE_1__ dev_spec; } ;
typedef  scalar_t__ s32 ;
struct TYPE_7__ {int /*<<< orphan*/  state; } ;

/* Variables and functions */
 int /*<<< orphan*/  CRC_OFFSET ; 
 int /*<<< orphan*/  CTRL ; 
 int E1000_CTRL_PHY_RST ; 
 int E1000_CTRL_RST ; 
 int E1000_FEXTNVM3_PHY_CFG_COUNTER_50MSEC ; 
 int E1000_FEXTNVM3_PHY_CFG_COUNTER_MASK ; 
 int E1000_ICH_FWSM_FW_VALID ; 
 int E1000_KABGTXD_BGSQLBIAS ; 
 int /*<<< orphan*/  E1000_NVM_K1_CONFIG ; 
 int E1000_NVM_K1_ENABLE ; 
 int E1000_PBA_8K ; 
 int E1000_PBS_16K ; 
 int E1000_TCTL_PSP ; 
 int /*<<< orphan*/  FEXTNVM3 ; 
 int /*<<< orphan*/  FWSM ; 
 int /*<<< orphan*/  ICR ; 
 int /*<<< orphan*/  IMC ; 
 int /*<<< orphan*/  KABGTXD ; 
 int /*<<< orphan*/  PBA ; 
 int /*<<< orphan*/  PBS ; 
 int /*<<< orphan*/  RCTL ; 
 int /*<<< orphan*/  TCTL ; 
 int /*<<< orphan*/  __E1000_ACCESS_SHARED_RESOURCE ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ e1000_acquire_swflag_ich8lan (struct e1000_hw*) ; 
 int /*<<< orphan*/  e1000_gate_hw_phy_config_ich8lan (struct e1000_hw*,int) ; 
 scalar_t__ e1000_ich8lan ; 
 scalar_t__ e1000_pch2lan ; 
 scalar_t__ e1000_pchlan ; 
 scalar_t__ e1000_post_phy_reset_ich8lan (struct e1000_hw*) ; 
 scalar_t__ e1000_read_nvm (struct e1000_hw*,int /*<<< orphan*/ ,int,int*) ; 
 scalar_t__ e1000e_disable_pcie_master (struct e1000_hw*) ; 
 int /*<<< orphan*/  e1e_flush () ; 
 int /*<<< orphan*/  e_dbg (char*) ; 
 int er32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ew32 (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  stub1 (struct e1000_hw*) ; 
 scalar_t__ stub2 (struct e1000_hw*) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

__attribute__((used)) static s32 e1000_reset_hw_ich8lan(struct e1000_hw *hw)
{
	struct e1000_dev_spec_ich8lan *dev_spec = &hw->dev_spec.ich8lan;
	u16 kum_cfg;
	u32 ctrl, reg;
	s32 ret_val;

	/* Prevent the PCI-E bus from sticking if there is no TLP connection
	 * on the last TLP read/write transaction when MAC is reset.
	 */
	ret_val = e1000e_disable_pcie_master(hw);
	if (ret_val)
		e_dbg("PCI-E Master disable polling has failed.\n");

	e_dbg("Masking off all interrupts\n");
	ew32(IMC, 0xffffffff);

	/* Disable the Transmit and Receive units.  Then delay to allow
	 * any pending transactions to complete before we hit the MAC
	 * with the global reset.
	 */
	ew32(RCTL, 0);
	ew32(TCTL, E1000_TCTL_PSP);
	e1e_flush();

	usleep_range(10000, 20000);

	/* Workaround for ICH8 bit corruption issue in FIFO memory */
	if (hw->mac.type == e1000_ich8lan) {
		/* Set Tx and Rx buffer allocation to 8k apiece. */
		ew32(PBA, E1000_PBA_8K);
		/* Set Packet Buffer Size to 16k. */
		ew32(PBS, E1000_PBS_16K);
	}

	if (hw->mac.type == e1000_pchlan) {
		/* Save the NVM K1 bit setting */
		ret_val = e1000_read_nvm(hw, E1000_NVM_K1_CONFIG, 1, &kum_cfg);
		if (ret_val)
			return ret_val;

		if (kum_cfg & E1000_NVM_K1_ENABLE)
			dev_spec->nvm_k1_enabled = true;
		else
			dev_spec->nvm_k1_enabled = false;
	}

	ctrl = er32(CTRL);

	if (!hw->phy.ops.check_reset_block(hw)) {
		/* Full-chip reset requires MAC and PHY reset at the same
		 * time to make sure the interface between MAC and the
		 * external PHY is reset.
		 */
		ctrl |= E1000_CTRL_PHY_RST;

		/* Gate automatic PHY configuration by hardware on
		 * non-managed 82579
		 */
		if ((hw->mac.type == e1000_pch2lan) &&
		    !(er32(FWSM) & E1000_ICH_FWSM_FW_VALID))
			e1000_gate_hw_phy_config_ich8lan(hw, true);
	}
	ret_val = e1000_acquire_swflag_ich8lan(hw);
	e_dbg("Issuing a global reset to ich8lan\n");
	ew32(CTRL, (ctrl | E1000_CTRL_RST));
	/* cannot issue a flush here because it hangs the hardware */
	msleep(20);

	/* Set Phy Config Counter to 50msec */
	if (hw->mac.type == e1000_pch2lan) {
		reg = er32(FEXTNVM3);
		reg &= ~E1000_FEXTNVM3_PHY_CFG_COUNTER_MASK;
		reg |= E1000_FEXTNVM3_PHY_CFG_COUNTER_50MSEC;
		ew32(FEXTNVM3, reg);
	}

	if (!ret_val)
		clear_bit(__E1000_ACCESS_SHARED_RESOURCE, &hw->adapter->state);

	if (ctrl & E1000_CTRL_PHY_RST) {
		ret_val = hw->phy.ops.get_cfg_done(hw);
		if (ret_val)
			return ret_val;

		ret_val = e1000_post_phy_reset_ich8lan(hw);
		if (ret_val)
			return ret_val;
	}

	/* For PCH, this write will make sure that any noise
	 * will be detected as a CRC error and be dropped rather than show up
	 * as a bad packet to the DMA engine.
	 */
	if (hw->mac.type == e1000_pchlan)
		ew32(CRC_OFFSET, 0x65656565);

	ew32(IMC, 0xffffffff);
	er32(ICR);

	reg = er32(KABGTXD);
	reg |= E1000_KABGTXD_BGSQLBIAS;
	ew32(KABGTXD, reg);

	return 0;
}