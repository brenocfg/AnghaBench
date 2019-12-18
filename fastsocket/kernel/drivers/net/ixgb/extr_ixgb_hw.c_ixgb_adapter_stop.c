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
struct ixgb_hw {int adapter_stopped; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUGFUNC (char*) ; 
 int /*<<< orphan*/  DEBUGOUT (char*) ; 
 int /*<<< orphan*/  ICR ; 
 int /*<<< orphan*/  IMC ; 
 int IXGB_CTRL0_RST ; 
 int /*<<< orphan*/  IXGB_DELAY_BEFORE_RESET ; 
 int IXGB_RCTL_RXEN ; 
 int IXGB_READ_REG (struct ixgb_hw*,int /*<<< orphan*/ ) ; 
 int IXGB_TCTL_TXEN ; 
 int /*<<< orphan*/  IXGB_WRITE_REG (struct ixgb_hw*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  RCTL ; 
 int /*<<< orphan*/  TCTL ; 
 int ixgb_mac_reset (struct ixgb_hw*) ; 
 int /*<<< orphan*/  msleep (int /*<<< orphan*/ ) ; 

bool
ixgb_adapter_stop(struct ixgb_hw *hw)
{
	u32 ctrl_reg;
	u32 icr_reg;

	DEBUGFUNC("ixgb_adapter_stop");

	/* If we are stopped or resetting exit gracefully and wait to be
	 * started again before accessing the hardware.
	 */
	if (hw->adapter_stopped) {
		DEBUGOUT("Exiting because the adapter is already stopped!!!\n");
		return false;
	}

	/* Set the Adapter Stopped flag so other driver functions stop
	 * touching the Hardware.
	 */
	hw->adapter_stopped = true;

	/* Clear interrupt mask to stop board from generating interrupts */
	DEBUGOUT("Masking off all interrupts\n");
	IXGB_WRITE_REG(hw, IMC, 0xFFFFFFFF);

	/* Disable the Transmit and Receive units.  Then delay to allow
	 * any pending transactions to complete before we hit the MAC with
	 * the global reset.
	 */
	IXGB_WRITE_REG(hw, RCTL, IXGB_READ_REG(hw, RCTL) & ~IXGB_RCTL_RXEN);
	IXGB_WRITE_REG(hw, TCTL, IXGB_READ_REG(hw, TCTL) & ~IXGB_TCTL_TXEN);
	msleep(IXGB_DELAY_BEFORE_RESET);

	/* Issue a global reset to the MAC.  This will reset the chip's
	 * transmit, receive, DMA, and link units.  It will not effect
	 * the current PCI configuration.  The global reset bit is self-
	 * clearing, and should clear within a microsecond.
	 */
	DEBUGOUT("Issuing a global reset to MAC\n");

	ctrl_reg = ixgb_mac_reset(hw);

	/* Clear interrupt mask to stop board from generating interrupts */
	DEBUGOUT("Masking off all interrupts\n");
	IXGB_WRITE_REG(hw, IMC, 0xffffffff);

	/* Clear any pending interrupt events. */
	icr_reg = IXGB_READ_REG(hw, ICR);

	return (ctrl_reg & IXGB_CTRL0_RST);
}