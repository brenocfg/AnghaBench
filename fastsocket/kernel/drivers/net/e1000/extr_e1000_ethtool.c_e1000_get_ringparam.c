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
struct e1000_tx_ring {int /*<<< orphan*/  count; } ;
struct e1000_rx_ring {int /*<<< orphan*/  count; } ;
struct e1000_hw {scalar_t__ mac_type; } ;
struct e1000_adapter {struct e1000_rx_ring* rx_ring; struct e1000_tx_ring* tx_ring; struct e1000_hw hw; } ;
typedef  scalar_t__ e1000_mac_type ;

/* Variables and functions */
 int /*<<< orphan*/  E1000_MAX_82544_RXD ; 
 int /*<<< orphan*/  E1000_MAX_82544_TXD ; 
 int /*<<< orphan*/  E1000_MAX_RXD ; 
 int /*<<< orphan*/  E1000_MAX_TXD ; 
 scalar_t__ e1000_82544 ; 
 struct e1000_adapter* netdev_priv (struct net_device*) ; 

__attribute__((used)) static void e1000_get_ringparam(struct net_device *netdev,
				struct ethtool_ringparam *ring)
{
	struct e1000_adapter *adapter = netdev_priv(netdev);
	struct e1000_hw *hw = &adapter->hw;
	e1000_mac_type mac_type = hw->mac_type;
	struct e1000_tx_ring *txdr = adapter->tx_ring;
	struct e1000_rx_ring *rxdr = adapter->rx_ring;

	ring->rx_max_pending = (mac_type < e1000_82544) ? E1000_MAX_RXD :
		E1000_MAX_82544_RXD;
	ring->tx_max_pending = (mac_type < e1000_82544) ? E1000_MAX_TXD :
		E1000_MAX_82544_TXD;
	ring->rx_pending = rxdr->count;
	ring->tx_pending = txdr->count;
}