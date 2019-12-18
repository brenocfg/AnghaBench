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
struct ethtool_ringparam {int /*<<< orphan*/  tx_pending; int /*<<< orphan*/  rx_pending; void* tx_max_pending; void* rx_max_pending; } ;
struct efx_nic {int /*<<< orphan*/  txq_entries; int /*<<< orphan*/  rxq_entries; } ;

/* Variables and functions */
 void* EFX_MAX_DMAQ_SIZE ; 
 struct efx_nic* netdev_priv (struct net_device*) ; 

__attribute__((used)) static void efx_ethtool_get_ringparam(struct net_device *net_dev,
				      struct ethtool_ringparam *ring)
{
	struct efx_nic *efx = netdev_priv(net_dev);

	ring->rx_max_pending = EFX_MAX_DMAQ_SIZE;
	ring->tx_max_pending = EFX_MAX_DMAQ_SIZE;
	ring->rx_pending = efx->rxq_entries;
	ring->tx_pending = efx->txq_entries;
}