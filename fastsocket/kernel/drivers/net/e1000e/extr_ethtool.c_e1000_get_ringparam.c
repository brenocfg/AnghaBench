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
struct net_device {int dummy; } ;
struct ethtool_ringparam {int /*<<< orphan*/  tx_pending; int /*<<< orphan*/  rx_pending; int /*<<< orphan*/  tx_max_pending; int /*<<< orphan*/  rx_max_pending; } ;
struct e1000_adapter {int /*<<< orphan*/  tx_ring_count; int /*<<< orphan*/  rx_ring_count; } ;

/* Variables and functions */
 int /*<<< orphan*/  E1000_MAX_RXD ; 
 int /*<<< orphan*/  E1000_MAX_TXD ; 
 struct e1000_adapter* netdev_priv (struct net_device*) ; 

__attribute__((used)) static void e1000_get_ringparam(struct net_device *netdev,
				struct ethtool_ringparam *ring)
{
	struct e1000_adapter *adapter = netdev_priv(netdev);

	ring->rx_max_pending = E1000_MAX_RXD;
	ring->tx_max_pending = E1000_MAX_TXD;
	ring->rx_pending = adapter->rx_ring_count;
	ring->tx_pending = adapter->tx_ring_count;
}