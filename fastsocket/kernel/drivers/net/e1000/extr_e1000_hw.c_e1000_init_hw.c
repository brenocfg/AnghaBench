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
struct e1000_hw {int mac_type; int pci_cmd_word; scalar_t__ device_id; int /*<<< orphan*/  bus_type; scalar_t__ dma_fairness; } ;
typedef  scalar_t__ s32 ;

/* Variables and functions */
 int /*<<< orphan*/  CTRL ; 
 int /*<<< orphan*/  CTRL_EXT ; 
 scalar_t__ E1000_CTRL_EXT_RO_DIS ; 
 scalar_t__ E1000_CTRL_PRIOR ; 
 scalar_t__ E1000_DEV_ID_82546GB_QUAD_COPPER ; 
 scalar_t__ E1000_DEV_ID_82546GB_QUAD_COPPER_KSP3 ; 
 scalar_t__ E1000_MC_TBL_SIZE ; 
 scalar_t__ E1000_RCTL_RST ; 
 scalar_t__ E1000_TXDCTL_FULL_TX_DESC_WB ; 
 scalar_t__ E1000_TXDCTL_WTHRESH ; 
 int /*<<< orphan*/  E1000_WRITE_FLUSH () ; 
 int /*<<< orphan*/  E1000_WRITE_REG_ARRAY (struct e1000_hw*,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MTA ; 
 int PCI_COMMAND_INVALIDATE ; 
 int /*<<< orphan*/  RCTL ; 
 int /*<<< orphan*/  TXDCTL ; 
 int /*<<< orphan*/  VET ; 
 int e1000_82542_rev2_0 ; 
 int e1000_82543 ; 
 int e1000_82544 ; 
#define  e1000_82545_rev_3 129 
#define  e1000_82546_rev_3 128 
 int /*<<< orphan*/  e1000_bus_type_pcix ; 
 int /*<<< orphan*/  e1000_clear_hw_cntrs (struct e1000_hw*) ; 
 int /*<<< orphan*/  e1000_clear_vfta (struct e1000_hw*) ; 
 scalar_t__ e1000_id_led_init (struct e1000_hw*) ; 
 int /*<<< orphan*/  e1000_init_rx_addrs (struct e1000_hw*) ; 
 int /*<<< orphan*/  e1000_pci_clear_mwi (struct e1000_hw*) ; 
 int /*<<< orphan*/  e1000_pci_set_mwi (struct e1000_hw*) ; 
 int e1000_pcix_get_mmrbc (struct e1000_hw*) ; 
 int /*<<< orphan*/  e1000_pcix_set_mmrbc (struct e1000_hw*,int) ; 
 int /*<<< orphan*/  e1000_set_media_type (struct e1000_hw*) ; 
 scalar_t__ e1000_setup_link (struct e1000_hw*) ; 
 int /*<<< orphan*/  e_dbg (char*) ; 
 scalar_t__ er32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ew32 (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  msleep (int) ; 

s32 e1000_init_hw(struct e1000_hw *hw)
{
	u32 ctrl;
	u32 i;
	s32 ret_val;
	u32 mta_size;
	u32 ctrl_ext;

	e_dbg("e1000_init_hw");

	/* Initialize Identification LED */
	ret_val = e1000_id_led_init(hw);
	if (ret_val) {
		e_dbg("Error Initializing Identification LED\n");
		return ret_val;
	}

	/* Set the media type and TBI compatibility */
	e1000_set_media_type(hw);

	/* Disabling VLAN filtering. */
	e_dbg("Initializing the IEEE VLAN\n");
	if (hw->mac_type < e1000_82545_rev_3)
		ew32(VET, 0);
	e1000_clear_vfta(hw);

	/* For 82542 (rev 2.0), disable MWI and put the receiver into reset */
	if (hw->mac_type == e1000_82542_rev2_0) {
		e_dbg("Disabling MWI on 82542 rev 2.0\n");
		e1000_pci_clear_mwi(hw);
		ew32(RCTL, E1000_RCTL_RST);
		E1000_WRITE_FLUSH();
		msleep(5);
	}

	/* Setup the receive address. This involves initializing all of the Receive
	 * Address Registers (RARs 0 - 15).
	 */
	e1000_init_rx_addrs(hw);

	/* For 82542 (rev 2.0), take the receiver out of reset and enable MWI */
	if (hw->mac_type == e1000_82542_rev2_0) {
		ew32(RCTL, 0);
		E1000_WRITE_FLUSH();
		msleep(1);
		if (hw->pci_cmd_word & PCI_COMMAND_INVALIDATE)
			e1000_pci_set_mwi(hw);
	}

	/* Zero out the Multicast HASH table */
	e_dbg("Zeroing the MTA\n");
	mta_size = E1000_MC_TBL_SIZE;
	for (i = 0; i < mta_size; i++) {
		E1000_WRITE_REG_ARRAY(hw, MTA, i, 0);
		/* use write flush to prevent Memory Write Block (MWB) from
		 * occurring when accessing our register space */
		E1000_WRITE_FLUSH();
	}

	/* Set the PCI priority bit correctly in the CTRL register.  This
	 * determines if the adapter gives priority to receives, or if it
	 * gives equal priority to transmits and receives.  Valid only on
	 * 82542 and 82543 silicon.
	 */
	if (hw->dma_fairness && hw->mac_type <= e1000_82543) {
		ctrl = er32(CTRL);
		ew32(CTRL, ctrl | E1000_CTRL_PRIOR);
	}

	switch (hw->mac_type) {
	case e1000_82545_rev_3:
	case e1000_82546_rev_3:
		break;
	default:
		/* Workaround for PCI-X problem when BIOS sets MMRBC incorrectly. */
		if (hw->bus_type == e1000_bus_type_pcix
		    && e1000_pcix_get_mmrbc(hw) > 2048)
			e1000_pcix_set_mmrbc(hw, 2048);
		break;
	}

	/* Call a subroutine to configure the link and setup flow control. */
	ret_val = e1000_setup_link(hw);

	/* Set the transmit descriptor write-back policy */
	if (hw->mac_type > e1000_82544) {
		ctrl = er32(TXDCTL);
		ctrl =
		    (ctrl & ~E1000_TXDCTL_WTHRESH) |
		    E1000_TXDCTL_FULL_TX_DESC_WB;
		ew32(TXDCTL, ctrl);
	}

	/* Clear all of the statistics registers (clear on read).  It is
	 * important that we do this after we have tried to establish link
	 * because the symbol error count will increment wildly if there
	 * is no link.
	 */
	e1000_clear_hw_cntrs(hw);

	if (hw->device_id == E1000_DEV_ID_82546GB_QUAD_COPPER ||
	    hw->device_id == E1000_DEV_ID_82546GB_QUAD_COPPER_KSP3) {
		ctrl_ext = er32(CTRL_EXT);
		/* Relaxed ordering must be disabled to avoid a parity
		 * error crash in a PCI slot. */
		ctrl_ext |= E1000_CTRL_EXT_RO_DIS;
		ew32(CTRL_EXT, ctrl_ext);
	}

	return ret_val;
}