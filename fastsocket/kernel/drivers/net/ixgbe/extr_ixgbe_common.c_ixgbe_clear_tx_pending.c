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
struct TYPE_2__ {int flags; } ;
struct ixgbe_hw {TYPE_1__ mac; } ;

/* Variables and functions */
 int IXGBE_FLAGS_DOUBLE_RESET_REQUIRED ; 
 int /*<<< orphan*/  IXGBE_GCR_EXT ; 
 int IXGBE_GCR_EXT_BUFFERS_CLEAR ; 
 int /*<<< orphan*/  IXGBE_HLREG0 ; 
 int IXGBE_HLREG0_LPBK ; 
 int IXGBE_READ_REG (struct ixgbe_hw*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IXGBE_WRITE_FLUSH (struct ixgbe_hw*) ; 
 int /*<<< orphan*/  IXGBE_WRITE_REG (struct ixgbe_hw*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  udelay (int) ; 

void ixgbe_clear_tx_pending(struct ixgbe_hw *hw)
{
	u32 gcr_ext, hlreg0;

	/*
	 * If double reset is not requested then all transactions should
	 * already be clear and as such there is no work to do
	 */
	if (!(hw->mac.flags & IXGBE_FLAGS_DOUBLE_RESET_REQUIRED))
		return;

	/*
	 * Set loopback enable to prevent any transmits from being sent
	 * should the link come up.  This assumes that the RXCTRL.RXEN bit
	 * has already been cleared.
	 */
	hlreg0 = IXGBE_READ_REG(hw, IXGBE_HLREG0);
	IXGBE_WRITE_REG(hw, IXGBE_HLREG0, hlreg0 | IXGBE_HLREG0_LPBK);

	/* initiate cleaning flow for buffers in the PCIe transaction layer */
	gcr_ext = IXGBE_READ_REG(hw, IXGBE_GCR_EXT);
	IXGBE_WRITE_REG(hw, IXGBE_GCR_EXT,
			gcr_ext | IXGBE_GCR_EXT_BUFFERS_CLEAR);

	/* Flush all writes and allow 20usec for all transactions to clear */
	IXGBE_WRITE_FLUSH(hw);
	udelay(20);

	/* restore previous register values */
	IXGBE_WRITE_REG(hw, IXGBE_GCR_EXT, gcr_ext);
	IXGBE_WRITE_REG(hw, IXGBE_HLREG0, hlreg0);
}