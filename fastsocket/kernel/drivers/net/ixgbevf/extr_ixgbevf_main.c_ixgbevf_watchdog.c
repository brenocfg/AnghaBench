#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct TYPE_4__ {scalar_t__ ring; } ;
struct TYPE_3__ {scalar_t__ ring; } ;
struct ixgbevf_q_vector {TYPE_2__ tx; TYPE_1__ rx; } ;
struct ixgbe_hw {int dummy; } ;
struct ixgbevf_adapter {int num_msix_vectors; int /*<<< orphan*/  watchdog_task; struct ixgbevf_q_vector** q_vector; int /*<<< orphan*/  state; struct ixgbe_hw hw; } ;

/* Variables and functions */
 int /*<<< orphan*/  IXGBE_VTEICS ; 
 int /*<<< orphan*/  IXGBE_WRITE_REG (struct ixgbe_hw*,int /*<<< orphan*/ ,int) ; 
 int NON_Q_VECTORS ; 
 int /*<<< orphan*/  __IXGBEVF_DOWN ; 
 int /*<<< orphan*/  schedule_work (int /*<<< orphan*/ *) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void ixgbevf_watchdog(unsigned long data)
{
	struct ixgbevf_adapter *adapter = (struct ixgbevf_adapter *)data;
	struct ixgbe_hw *hw = &adapter->hw;
	u32 eics = 0;
	int i;

	/*
	 * Do the watchdog outside of interrupt context due to the lovely
	 * delays that some of the newer hardware requires
	 */

	if (test_bit(__IXGBEVF_DOWN, &adapter->state))
		goto watchdog_short_circuit;

	/* get one bit for every active tx/rx interrupt vector */
	for (i = 0; i < adapter->num_msix_vectors - NON_Q_VECTORS; i++) {
		struct ixgbevf_q_vector *qv = adapter->q_vector[i];
		if (qv->rx.ring || qv->tx.ring)
			eics |= 1 << i;
	}

	IXGBE_WRITE_REG(hw, IXGBE_VTEICS, eics);

watchdog_short_circuit:
	schedule_work(&adapter->watchdog_task);
}