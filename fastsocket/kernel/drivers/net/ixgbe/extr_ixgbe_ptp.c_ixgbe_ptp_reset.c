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
struct ixgbe_hw {int dummy; } ;
struct ixgbe_adapter {int /*<<< orphan*/  tmreg_lock; int /*<<< orphan*/  cc; int /*<<< orphan*/  tc; struct ixgbe_hw hw; } ;

/* Variables and functions */
 int /*<<< orphan*/  IXGBE_SYSTIMH ; 
 int /*<<< orphan*/  IXGBE_SYSTIML ; 
 int /*<<< orphan*/  IXGBE_WRITE_FLUSH (struct ixgbe_hw*) ; 
 int /*<<< orphan*/  IXGBE_WRITE_REG (struct ixgbe_hw*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ixgbe_ptp_setup_sdp (struct ixgbe_adapter*) ; 
 int /*<<< orphan*/  ixgbe_ptp_start_cyclecounter (struct ixgbe_adapter*) ; 
 int /*<<< orphan*/  ktime_get_real () ; 
 int /*<<< orphan*/  ktime_to_ns (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  timecounter_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void ixgbe_ptp_reset(struct ixgbe_adapter *adapter)
{
	struct ixgbe_hw *hw = &adapter->hw;
	unsigned long flags;

	/* set SYSTIME registers to 0 just in case */
	IXGBE_WRITE_REG(hw, IXGBE_SYSTIML, 0x00000000);
	IXGBE_WRITE_REG(hw, IXGBE_SYSTIMH, 0x00000000);
	IXGBE_WRITE_FLUSH(hw);

	ixgbe_ptp_start_cyclecounter(adapter);

	spin_lock_irqsave(&adapter->tmreg_lock, flags);

	/* reset the ns time counter */
	timecounter_init(&adapter->tc, &adapter->cc,
			 ktime_to_ns(ktime_get_real()));

	spin_unlock_irqrestore(&adapter->tmreg_lock, flags);

	/*
	 * Now that the shift has been calculated and the systime
	 * registers reset, (re-)enable the Clock out feature
	 */
	ixgbe_ptp_setup_sdp(adapter);
}