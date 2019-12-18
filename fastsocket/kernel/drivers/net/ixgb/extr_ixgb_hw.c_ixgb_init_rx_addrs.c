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
struct ixgb_hw {int /*<<< orphan*/ * curr_mac_addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUGFUNC (char*) ; 
 int /*<<< orphan*/  DEBUGOUT (char*) ; 
 int /*<<< orphan*/  DEBUGOUT3 (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int IXGB_RAR_ENTRIES ; 
 int /*<<< orphan*/  IXGB_WRITE_REG_ARRAY (struct ixgb_hw*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RA ; 
 int /*<<< orphan*/  ixgb_get_ee_mac_addr (struct ixgb_hw*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ixgb_rar_set (struct ixgb_hw*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mac_addr_valid (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
ixgb_init_rx_addrs(struct ixgb_hw *hw)
{
	u32 i;

	DEBUGFUNC("ixgb_init_rx_addrs");

	/*
	 * If the current mac address is valid, assume it is a software override
	 * to the permanent address.
	 * Otherwise, use the permanent address from the eeprom.
	 */
	if (!mac_addr_valid(hw->curr_mac_addr)) {

		/* Get the MAC address from the eeprom for later reference */
		ixgb_get_ee_mac_addr(hw, hw->curr_mac_addr);

		DEBUGOUT3(" Keeping Permanent MAC Addr =%.2X %.2X %.2X ",
			  hw->curr_mac_addr[0],
			  hw->curr_mac_addr[1], hw->curr_mac_addr[2]);
		DEBUGOUT3("%.2X %.2X %.2X\n",
			  hw->curr_mac_addr[3],
			  hw->curr_mac_addr[4], hw->curr_mac_addr[5]);
	} else {

		/* Setup the receive address. */
		DEBUGOUT("Overriding MAC Address in RAR[0]\n");
		DEBUGOUT3(" New MAC Addr =%.2X %.2X %.2X ",
			  hw->curr_mac_addr[0],
			  hw->curr_mac_addr[1], hw->curr_mac_addr[2]);
		DEBUGOUT3("%.2X %.2X %.2X\n",
			  hw->curr_mac_addr[3],
			  hw->curr_mac_addr[4], hw->curr_mac_addr[5]);

		ixgb_rar_set(hw, hw->curr_mac_addr, 0);
	}

	/* Zero out the other 15 receive addresses. */
	DEBUGOUT("Clearing RAR[1-15]\n");
	for (i = 1; i < IXGB_RAR_ENTRIES; i++) {
		/* Write high reg first to disable the AV bit first */
		IXGB_WRITE_REG_ARRAY(hw, RA, ((i << 1) + 1), 0);
		IXGB_WRITE_REG_ARRAY(hw, RA, (i << 1), 0);
	}

	return;
}