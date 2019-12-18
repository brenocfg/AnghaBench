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
struct ixgbevf_ring {int /*<<< orphan*/  queue_index; int /*<<< orphan*/  netdev; } ;
struct ixgbevf_adapter {int /*<<< orphan*/  restart_queue; } ;

/* Variables and functions */
 int EBUSY ; 
 int IXGBE_DESC_UNUSED (struct ixgbevf_ring*) ; 
 scalar_t__ likely (int) ; 
 struct ixgbevf_adapter* netdev_priv (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netif_start_subqueue (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netif_stop_subqueue (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  smp_mb () ; 

__attribute__((used)) static int __ixgbevf_maybe_stop_tx(struct ixgbevf_ring *tx_ring, int size)
{
	struct ixgbevf_adapter *adapter = netdev_priv(tx_ring->netdev);

	netif_stop_subqueue(tx_ring->netdev, tx_ring->queue_index);
	/* Herbert's original patch had:
	 *  smp_mb__after_netif_stop_queue();
	 * but since that doesn't exist yet, just open code it. */
	smp_mb();

	/* We need to check again in a case another CPU has just
	 * made room available. */
	if (likely(IXGBE_DESC_UNUSED(tx_ring) < size))
		return -EBUSY;

	/* A reprieve! - use start_queue because it doesn't call schedule */
	netif_start_subqueue(tx_ring->netdev, tx_ring->queue_index);
	++adapter->restart_queue;
	return 0;
}