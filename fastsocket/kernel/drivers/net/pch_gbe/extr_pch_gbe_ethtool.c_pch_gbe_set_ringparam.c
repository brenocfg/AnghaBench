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
struct pch_gbe_tx_ring {void* count; } ;
struct pch_gbe_rx_ring {void* count; } ;
struct pch_gbe_adapter {int /*<<< orphan*/  netdev; struct pch_gbe_tx_ring* tx_ring; struct pch_gbe_tx_ring* rx_ring; } ;
struct net_device {int dummy; } ;
struct ethtool_ringparam {int /*<<< orphan*/  tx_pending; int /*<<< orphan*/  rx_pending; scalar_t__ rx_jumbo_pending; scalar_t__ rx_mini_pending; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  PCH_GBE_MAX_RXD ; 
 int /*<<< orphan*/  PCH_GBE_MIN_RXD ; 
 int /*<<< orphan*/  PCH_GBE_RX_DESC_MULTIPLE ; 
 int /*<<< orphan*/  PCH_GBE_TX_DESC_MULTIPLE ; 
 void* clamp_val (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct pch_gbe_tx_ring*) ; 
 struct pch_gbe_tx_ring* kzalloc (int,int /*<<< orphan*/ ) ; 
 struct pch_gbe_adapter* netdev_priv (struct net_device*) ; 
 scalar_t__ netif_running (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pch_gbe_down (struct pch_gbe_adapter*) ; 
 int /*<<< orphan*/  pch_gbe_free_rx_resources (struct pch_gbe_adapter*,struct pch_gbe_tx_ring*) ; 
 int /*<<< orphan*/  pch_gbe_free_tx_resources (struct pch_gbe_adapter*,struct pch_gbe_tx_ring*) ; 
 int pch_gbe_setup_rx_resources (struct pch_gbe_adapter*,struct pch_gbe_tx_ring*) ; 
 int pch_gbe_setup_tx_resources (struct pch_gbe_adapter*,struct pch_gbe_tx_ring*) ; 
 int pch_gbe_up (struct pch_gbe_adapter*) ; 
 void* roundup (void*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int pch_gbe_set_ringparam(struct net_device *netdev,
					struct ethtool_ringparam *ring)
{
	struct pch_gbe_adapter *adapter = netdev_priv(netdev);
	struct pch_gbe_tx_ring *txdr, *tx_old;
	struct pch_gbe_rx_ring *rxdr, *rx_old;
	int tx_ring_size, rx_ring_size;
	int err = 0;

	if ((ring->rx_mini_pending) || (ring->rx_jumbo_pending))
		return -EINVAL;
	tx_ring_size = (int)sizeof(struct pch_gbe_tx_ring);
	rx_ring_size = (int)sizeof(struct pch_gbe_rx_ring);

	if ((netif_running(adapter->netdev)))
		pch_gbe_down(adapter);
	tx_old = adapter->tx_ring;
	rx_old = adapter->rx_ring;

	txdr = kzalloc(tx_ring_size, GFP_KERNEL);
	if (!txdr) {
		err = -ENOMEM;
		goto err_alloc_tx;
	}
	rxdr = kzalloc(rx_ring_size, GFP_KERNEL);
	if (!rxdr) {
		err = -ENOMEM;
		goto err_alloc_rx;
	}
	adapter->tx_ring = txdr;
	adapter->rx_ring = rxdr;

	rxdr->count =
		clamp_val(ring->rx_pending, PCH_GBE_MIN_RXD, PCH_GBE_MAX_RXD);
	rxdr->count = roundup(rxdr->count, PCH_GBE_RX_DESC_MULTIPLE);

	txdr->count =
		clamp_val(ring->tx_pending, PCH_GBE_MIN_RXD, PCH_GBE_MAX_RXD);
	txdr->count = roundup(txdr->count, PCH_GBE_TX_DESC_MULTIPLE);

	if ((netif_running(adapter->netdev))) {
		/* Try to get new resources before deleting old */
		err = pch_gbe_setup_rx_resources(adapter, adapter->rx_ring);
		if (err)
			goto err_setup_rx;
		err = pch_gbe_setup_tx_resources(adapter, adapter->tx_ring);
		if (err)
			goto err_setup_tx;
		/* save the new, restore the old in order to free it,
		 * then restore the new back again */
#ifdef RINGFREE
		adapter->rx_ring = rx_old;
		adapter->tx_ring = tx_old;
		pch_gbe_free_rx_resources(adapter, adapter->rx_ring);
		pch_gbe_free_tx_resources(adapter, adapter->tx_ring);
		kfree(tx_old);
		kfree(rx_old);
		adapter->rx_ring = rxdr;
		adapter->tx_ring = txdr;
#else
		pch_gbe_free_rx_resources(adapter, rx_old);
		pch_gbe_free_tx_resources(adapter, tx_old);
		kfree(tx_old);
		kfree(rx_old);
		adapter->rx_ring = rxdr;
		adapter->tx_ring = txdr;
#endif
		err = pch_gbe_up(adapter);
	}
	return err;

err_setup_tx:
	pch_gbe_free_rx_resources(adapter, adapter->rx_ring);
err_setup_rx:
	adapter->rx_ring = rx_old;
	adapter->tx_ring = tx_old;
	kfree(rxdr);
err_alloc_rx:
	kfree(txdr);
err_alloc_tx:
	if (netif_running(adapter->netdev))
		pch_gbe_up(adapter);
	return err;
}