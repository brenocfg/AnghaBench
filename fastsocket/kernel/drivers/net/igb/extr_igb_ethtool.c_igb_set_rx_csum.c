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
typedef  scalar_t__ u32 ;
struct net_device {int dummy; } ;
struct igb_adapter {int num_rx_queues; TYPE_1__** rx_ring; } ;
struct TYPE_2__ {int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  IGB_RING_FLAG_RX_CSUM ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct igb_adapter* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int igb_set_rx_csum(struct net_device *netdev, u32 data)
{
	struct igb_adapter *adapter = netdev_priv(netdev);
	int i;

	for (i = 0; i < adapter->num_rx_queues; i++) {
		if (data)
			set_bit(IGB_RING_FLAG_RX_CSUM,
				&adapter->rx_ring[i]->flags);
		else
			clear_bit(IGB_RING_FLAG_RX_CSUM,
				  &adapter->rx_ring[i]->flags);
	}

	return 0;
}