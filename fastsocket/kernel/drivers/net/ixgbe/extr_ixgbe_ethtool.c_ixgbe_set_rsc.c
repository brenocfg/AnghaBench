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
struct ixgbe_ring {int dummy; } ;
struct ixgbe_adapter {int num_rx_queues; int flags2; struct ixgbe_ring** rx_ring; } ;

/* Variables and functions */
 int IXGBE_FLAG2_RSC_ENABLED ; 
 int /*<<< orphan*/  ixgbe_clear_rscctl (struct ixgbe_adapter*,struct ixgbe_ring*) ; 
 int /*<<< orphan*/  ixgbe_configure_rscctl (struct ixgbe_adapter*,struct ixgbe_ring*) ; 
 int /*<<< orphan*/  set_ring_rsc_enabled (struct ixgbe_ring*) ; 

__attribute__((used)) static void ixgbe_set_rsc(struct ixgbe_adapter *adapter)
{
	int i;

	for (i = 0; i < adapter->num_rx_queues; i++) {
		struct ixgbe_ring *ring = adapter->rx_ring[i];
		if (adapter->flags2 & IXGBE_FLAG2_RSC_ENABLED) {
			set_ring_rsc_enabled(ring);
			ixgbe_configure_rscctl(adapter, ring);
		} else {
			ixgbe_clear_rscctl(adapter, ring);
		}
	}
}