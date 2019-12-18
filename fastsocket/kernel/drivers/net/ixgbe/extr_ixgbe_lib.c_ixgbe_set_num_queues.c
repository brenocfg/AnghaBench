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
struct ixgbe_adapter {int num_rx_queues; int num_tx_queues; int num_rx_pools; int num_rx_queues_per_pool; } ;

/* Variables and functions */
 scalar_t__ ixgbe_set_dcb_queues (struct ixgbe_adapter*) ; 
 scalar_t__ ixgbe_set_dcb_sriov_queues (struct ixgbe_adapter*) ; 
 int /*<<< orphan*/  ixgbe_set_rss_queues (struct ixgbe_adapter*) ; 
 scalar_t__ ixgbe_set_sriov_queues (struct ixgbe_adapter*) ; 

__attribute__((used)) static void ixgbe_set_num_queues(struct ixgbe_adapter *adapter)
{
	/* Start with base case */
	adapter->num_rx_queues = 1;
	adapter->num_tx_queues = 1;
	adapter->num_rx_pools = adapter->num_rx_queues;
	adapter->num_rx_queues_per_pool = 1;

#ifdef CONFIG_IXGBE_DCB
	if (ixgbe_set_dcb_sriov_queues(adapter))
		return;

	if (ixgbe_set_dcb_queues(adapter))
		return;

#endif
	if (ixgbe_set_sriov_queues(adapter))
		return;

	ixgbe_set_rss_queues(adapter);
}