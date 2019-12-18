#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct TYPE_6__ {int type; int /*<<< orphan*/  serdes_link_state; } ;
struct TYPE_5__ {scalar_t__ media_type; } ;
struct TYPE_4__ {scalar_t__ type; } ;
struct e1000_hw {TYPE_3__ mac; TYPE_2__ phy; TYPE_1__ nvm; } ;
typedef  scalar_t__ s32 ;

/* Variables and functions */
 int /*<<< orphan*/  CTRL ; 
 int /*<<< orphan*/  CTRL_EXT ; 
 int E1000_CTRL_EXT_EE_RST ; 
 int E1000_CTRL_RST ; 
 int E1000_EECD_GNT ; 
 int E1000_EECD_REQ ; 
 int E1000_TCTL_EN ; 
 int /*<<< orphan*/  EECD ; 
 int /*<<< orphan*/  ICR ; 
 int /*<<< orphan*/  IMC ; 
 int /*<<< orphan*/  RCTL ; 
 int /*<<< orphan*/  TCTL ; 
#define  e1000_82571 132 
#define  e1000_82572 131 
#define  e1000_82573 130 
#define  e1000_82574 129 
#define  e1000_82583 128 
 scalar_t__ e1000_check_alt_mac_addr_generic (struct e1000_hw*) ; 
 scalar_t__ e1000_get_hw_semaphore_82573 (struct e1000_hw*) ; 
 scalar_t__ e1000_get_hw_semaphore_82574 (struct e1000_hw*) ; 
 scalar_t__ e1000_media_type_internal_serdes ; 
 scalar_t__ e1000_nvm_flash_hw ; 
 int /*<<< orphan*/  e1000_put_hw_semaphore_82574 (struct e1000_hw*) ; 
 int /*<<< orphan*/  e1000_serdes_link_down ; 
 scalar_t__ e1000e_disable_pcie_master (struct e1000_hw*) ; 
 scalar_t__ e1000e_get_auto_rd_done (struct e1000_hw*) ; 
 int /*<<< orphan*/  e1000e_set_laa_state_82571 (struct e1000_hw*,int) ; 
 int /*<<< orphan*/  e1e_flush () ; 
 int /*<<< orphan*/  e_dbg (char*) ; 
 int er32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ew32 (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

__attribute__((used)) static s32 e1000_reset_hw_82571(struct e1000_hw *hw)
{
	u32 ctrl, ctrl_ext, eecd, tctl;
	s32 ret_val;

	/* Prevent the PCI-E bus from sticking if there is no TLP connection
	 * on the last TLP read/write transaction when MAC is reset.
	 */
	ret_val = e1000e_disable_pcie_master(hw);
	if (ret_val)
		e_dbg("PCI-E Master disable polling has failed.\n");

	e_dbg("Masking off all interrupts\n");
	ew32(IMC, 0xffffffff);

	ew32(RCTL, 0);
	tctl = er32(TCTL);
	tctl &= ~E1000_TCTL_EN;
	ew32(TCTL, tctl);
	e1e_flush();

	usleep_range(10000, 20000);

	/* Must acquire the MDIO ownership before MAC reset.
	 * Ownership defaults to firmware after a reset.
	 */
	switch (hw->mac.type) {
	case e1000_82573:
		ret_val = e1000_get_hw_semaphore_82573(hw);
		break;
	case e1000_82574:
	case e1000_82583:
		ret_val = e1000_get_hw_semaphore_82574(hw);
		break;
	default:
		break;
	}

	ctrl = er32(CTRL);

	e_dbg("Issuing a global reset to MAC\n");
	ew32(CTRL, ctrl | E1000_CTRL_RST);

	/* Must release MDIO ownership and mutex after MAC reset. */
	switch (hw->mac.type) {
	case e1000_82574:
	case e1000_82583:
		/* Release mutex only if the hw semaphore is acquired */
		if (!ret_val)
			e1000_put_hw_semaphore_82574(hw);
		break;
	default:
		break;
	}

	if (hw->nvm.type == e1000_nvm_flash_hw) {
		usleep_range(10, 20);
		ctrl_ext = er32(CTRL_EXT);
		ctrl_ext |= E1000_CTRL_EXT_EE_RST;
		ew32(CTRL_EXT, ctrl_ext);
		e1e_flush();
	}

	ret_val = e1000e_get_auto_rd_done(hw);
	if (ret_val)
		/* We don't want to continue accessing MAC registers. */
		return ret_val;

	/* Phy configuration from NVM just starts after EECD_AUTO_RD is set.
	 * Need to wait for Phy configuration completion before accessing
	 * NVM and Phy.
	 */

	switch (hw->mac.type) {
	case e1000_82571:
	case e1000_82572:
		/* REQ and GNT bits need to be cleared when using AUTO_RD
		 * to access the EEPROM.
		 */
		eecd = er32(EECD);
		eecd &= ~(E1000_EECD_REQ | E1000_EECD_GNT);
		ew32(EECD, eecd);
		break;
	case e1000_82573:
	case e1000_82574:
	case e1000_82583:
		msleep(25);
		break;
	default:
		break;
	}

	/* Clear any pending interrupt events. */
	ew32(IMC, 0xffffffff);
	er32(ICR);

	if (hw->mac.type == e1000_82571) {
		/* Install any alternate MAC address into RAR0 */
		ret_val = e1000_check_alt_mac_addr_generic(hw);
		if (ret_val)
			return ret_val;

		e1000e_set_laa_state_82571(hw, true);
	}

	/* Reinitialize the 82571 serdes link state machine */
	if (hw->phy.media_type == e1000_media_type_internal_serdes)
		hw->mac.serdes_link_state = e1000_serdes_link_down;

	return 0;
}