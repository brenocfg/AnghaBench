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
struct ixgbe_ring {scalar_t__ next_to_use; scalar_t__ next_to_clean; } ;
struct ixgbe_adapter {int num_tx_queues; int /*<<< orphan*/  flags2; struct ixgbe_ring** tx_ring; int /*<<< orphan*/  netdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  IXGBE_FLAG2_RESET_REQUESTED ; 
 int /*<<< orphan*/  drv ; 
 int /*<<< orphan*/  e_warn (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  netif_carrier_ok (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ixgbe_watchdog_flush_tx(struct ixgbe_adapter *adapter)
{
	int i;
	int some_tx_pending = 0;

	if (!netif_carrier_ok(adapter->netdev)) {
		for (i = 0; i < adapter->num_tx_queues; i++) {
			struct ixgbe_ring *tx_ring = adapter->tx_ring[i];
			if (tx_ring->next_to_use != tx_ring->next_to_clean) {
				some_tx_pending = 1;
				break;
			}
		}

		if (some_tx_pending) {
			/* We've lost link, so the controller stops DMA,
			 * but we've got queued Tx work that's never going
			 * to get done, so reset controller to flush Tx.
			 * (Do the reset outside of interrupt context).
			 */
			e_warn(drv, "initiating reset to clear Tx work after link loss\n");
			adapter->flags2 |= IXGBE_FLAG2_RESET_REQUESTED;
		}
	}
}