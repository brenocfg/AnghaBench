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
struct ixgbevf_adapter {struct ixgbe_hw hw; } ;

/* Variables and functions */
 int /*<<< orphan*/  IXGBE_READ_REG (struct ixgbe_hw*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IXGBE_VTEICR ; 
 int /*<<< orphan*/  ixgbevf_configure (struct ixgbevf_adapter*) ; 
 int /*<<< orphan*/  ixgbevf_irq_enable (struct ixgbevf_adapter*) ; 
 int /*<<< orphan*/  ixgbevf_reset_queues (struct ixgbevf_adapter*) ; 
 int /*<<< orphan*/  ixgbevf_up_complete (struct ixgbevf_adapter*) ; 

void ixgbevf_up(struct ixgbevf_adapter *adapter)
{
	struct ixgbe_hw *hw = &adapter->hw;

	ixgbevf_reset_queues(adapter);

	ixgbevf_configure(adapter);

	ixgbevf_up_complete(adapter);

	/* clear any pending interrupts, may auto mask */
	IXGBE_READ_REG(hw, IXGBE_VTEICR);

	ixgbevf_irq_enable(adapter);
}