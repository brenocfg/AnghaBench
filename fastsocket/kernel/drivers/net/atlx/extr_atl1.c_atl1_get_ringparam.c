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
struct ethtool_ringparam {scalar_t__ rx_jumbo_pending; scalar_t__ rx_mini_pending; int /*<<< orphan*/  tx_pending; int /*<<< orphan*/  rx_pending; scalar_t__ rx_jumbo_max_pending; scalar_t__ rx_mini_max_pending; int /*<<< orphan*/  tx_max_pending; int /*<<< orphan*/  rx_max_pending; } ;
struct atl1_tpd_ring {int /*<<< orphan*/  count; } ;
struct atl1_rfd_ring {int /*<<< orphan*/  count; } ;
struct atl1_adapter {struct atl1_rfd_ring rfd_ring; struct atl1_tpd_ring tpd_ring; } ;

/* Variables and functions */
 int /*<<< orphan*/  ATL1_MAX_RFD ; 
 int /*<<< orphan*/  ATL1_MAX_TPD ; 
 struct atl1_adapter* netdev_priv (struct net_device*) ; 

__attribute__((used)) static void atl1_get_ringparam(struct net_device *netdev,
	struct ethtool_ringparam *ring)
{
	struct atl1_adapter *adapter = netdev_priv(netdev);
	struct atl1_tpd_ring *txdr = &adapter->tpd_ring;
	struct atl1_rfd_ring *rxdr = &adapter->rfd_ring;

	ring->rx_max_pending = ATL1_MAX_RFD;
	ring->tx_max_pending = ATL1_MAX_TPD;
	ring->rx_mini_max_pending = 0;
	ring->rx_jumbo_max_pending = 0;
	ring->rx_pending = rxdr->count;
	ring->tx_pending = txdr->count;
	ring->rx_mini_pending = 0;
	ring->rx_jumbo_pending = 0;
}