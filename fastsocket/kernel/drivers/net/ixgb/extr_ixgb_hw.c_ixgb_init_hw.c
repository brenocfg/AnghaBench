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
struct ixgb_hw {int adapter_stopped; int /*<<< orphan*/  curr_mac_addr; int /*<<< orphan*/  phy_type; int /*<<< orphan*/  device_id; } ;

/* Variables and functions */
 int /*<<< orphan*/  CTRL1 ; 
 int /*<<< orphan*/  DEBUGFUNC (char*) ; 
 int /*<<< orphan*/  DEBUGOUT (char*) ; 
 int /*<<< orphan*/  IXGB_CTRL1_EE_RST ; 
 int /*<<< orphan*/  IXGB_DELAY_AFTER_EE_RESET ; 
 scalar_t__ IXGB_MC_TBL_SIZE ; 
 int /*<<< orphan*/  IXGB_WRITE_REG (struct ixgb_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IXGB_WRITE_REG_ARRAY (struct ixgb_hw*,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IXGB_WRITE_REG_IO (struct ixgb_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MTA ; 
 int /*<<< orphan*/  ixgb_check_for_link (struct ixgb_hw*) ; 
 int /*<<< orphan*/  ixgb_clear_hw_cntrs (struct ixgb_hw*) ; 
 int /*<<< orphan*/  ixgb_clear_vfta (struct ixgb_hw*) ; 
 int /*<<< orphan*/  ixgb_get_bus_info (struct ixgb_hw*) ; 
 int /*<<< orphan*/  ixgb_get_ee_device_id (struct ixgb_hw*) ; 
 int /*<<< orphan*/  ixgb_get_eeprom_data (struct ixgb_hw*) ; 
 int /*<<< orphan*/  ixgb_identify_phy (struct ixgb_hw*) ; 
 int /*<<< orphan*/  ixgb_init_rx_addrs (struct ixgb_hw*) ; 
 scalar_t__ ixgb_mac_reset (struct ixgb_hw*) ; 
 int ixgb_setup_fc (struct ixgb_hw*) ; 
 int /*<<< orphan*/  mac_addr_valid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msleep (int /*<<< orphan*/ ) ; 

bool
ixgb_init_hw(struct ixgb_hw *hw)
{
	u32 i;
	u32 ctrl_reg;
	bool status;

	DEBUGFUNC("ixgb_init_hw");

	/* Issue a global reset to the MAC.  This will reset the chip's
	 * transmit, receive, DMA, and link units.  It will not effect
	 * the current PCI configuration.  The global reset bit is self-
	 * clearing, and should clear within a microsecond.
	 */
	DEBUGOUT("Issuing a global reset to MAC\n");

	ctrl_reg = ixgb_mac_reset(hw);

	DEBUGOUT("Issuing an EE reset to MAC\n");
#ifdef HP_ZX1
	/* Workaround for 82597EX reset errata */
	IXGB_WRITE_REG_IO(hw, CTRL1, IXGB_CTRL1_EE_RST);
#else
	IXGB_WRITE_REG(hw, CTRL1, IXGB_CTRL1_EE_RST);
#endif

	/* Delay a few ms just to allow the reset to complete */
	msleep(IXGB_DELAY_AFTER_EE_RESET);

	if (!ixgb_get_eeprom_data(hw))
		return false;

	/* Use the device id to determine the type of phy/transceiver. */
	hw->device_id = ixgb_get_ee_device_id(hw);
	hw->phy_type = ixgb_identify_phy(hw);

	/* Setup the receive addresses.
	 * Receive Address Registers (RARs 0 - 15).
	 */
	ixgb_init_rx_addrs(hw);

	/*
	 * Check that a valid MAC address has been set.
	 * If it is not valid, we fail hardware init.
	 */
	if (!mac_addr_valid(hw->curr_mac_addr)) {
		DEBUGOUT("MAC address invalid after ixgb_init_rx_addrs\n");
		return(false);
	}

	/* tell the routines in this file they can access hardware again */
	hw->adapter_stopped = false;

	/* Fill in the bus_info structure */
	ixgb_get_bus_info(hw);

	/* Zero out the Multicast HASH table */
	DEBUGOUT("Zeroing the MTA\n");
	for (i = 0; i < IXGB_MC_TBL_SIZE; i++)
		IXGB_WRITE_REG_ARRAY(hw, MTA, i, 0);

	/* Zero out the VLAN Filter Table Array */
	ixgb_clear_vfta(hw);

	/* Zero all of the hardware counters */
	ixgb_clear_hw_cntrs(hw);

	/* Call a subroutine to setup flow control. */
	status = ixgb_setup_fc(hw);

	/* 82597EX errata: Call check-for-link in case lane deskew is locked */
	ixgb_check_for_link(hw);

	return (status);
}