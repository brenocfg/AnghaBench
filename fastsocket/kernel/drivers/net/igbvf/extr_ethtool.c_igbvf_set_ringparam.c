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
typedef  scalar_t__ u32 ;
struct net_device {int dummy; } ;
struct igbvf_ring {scalar_t__ count; } ;
struct igbvf_adapter {int /*<<< orphan*/  state; struct igbvf_ring* rx_ring; struct igbvf_ring* tx_ring; int /*<<< orphan*/  netdev; } ;
struct ethtool_ringparam {int /*<<< orphan*/  tx_pending; int /*<<< orphan*/  rx_pending; scalar_t__ rx_jumbo_pending; scalar_t__ rx_mini_pending; } ;

/* Variables and functions */
 scalar_t__ ALIGN (scalar_t__,int /*<<< orphan*/ ) ; 
 int EINVAL ; 
 int ENOMEM ; 
 scalar_t__ IGBVF_MAX_RXD ; 
 scalar_t__ IGBVF_MAX_TXD ; 
 scalar_t__ IGBVF_MIN_RXD ; 
 scalar_t__ IGBVF_MIN_TXD ; 
 int /*<<< orphan*/  REQ_RX_DESCRIPTOR_MULTIPLE ; 
 int /*<<< orphan*/  REQ_TX_DESCRIPTOR_MULTIPLE ; 
 int /*<<< orphan*/  __IGBVF_RESETTING ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  igbvf_down (struct igbvf_adapter*) ; 
 int /*<<< orphan*/  igbvf_free_rx_resources (struct igbvf_ring*) ; 
 int /*<<< orphan*/  igbvf_free_tx_resources (struct igbvf_ring*) ; 
 int igbvf_setup_rx_resources (struct igbvf_adapter*,struct igbvf_ring*) ; 
 int igbvf_setup_tx_resources (struct igbvf_adapter*,struct igbvf_ring*) ; 
 int /*<<< orphan*/  igbvf_up (struct igbvf_adapter*) ; 
 scalar_t__ max (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  memcpy (struct igbvf_ring*,struct igbvf_ring*,int) ; 
 scalar_t__ min (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  msleep (int) ; 
 struct igbvf_adapter* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_running (int /*<<< orphan*/ ) ; 
 scalar_t__ test_and_set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vfree (struct igbvf_ring*) ; 
 struct igbvf_ring* vmalloc (int) ; 

__attribute__((used)) static int igbvf_set_ringparam(struct net_device *netdev,
                               struct ethtool_ringparam *ring)
{
	struct igbvf_adapter *adapter = netdev_priv(netdev);
	struct igbvf_ring *temp_ring;
	int err = 0;
	u32 new_rx_count, new_tx_count;

	if ((ring->rx_mini_pending) || (ring->rx_jumbo_pending))
		return -EINVAL;

	new_rx_count = max(ring->rx_pending, (u32)IGBVF_MIN_RXD);
	new_rx_count = min(new_rx_count, (u32)IGBVF_MAX_RXD);
	new_rx_count = ALIGN(new_rx_count, REQ_RX_DESCRIPTOR_MULTIPLE);

	new_tx_count = max(ring->tx_pending, (u32)IGBVF_MIN_TXD);
	new_tx_count = min(new_tx_count, (u32)IGBVF_MAX_TXD);
	new_tx_count = ALIGN(new_tx_count, REQ_TX_DESCRIPTOR_MULTIPLE);

	if ((new_tx_count == adapter->tx_ring->count) &&
	    (new_rx_count == adapter->rx_ring->count)) {
		/* nothing to do */
		return 0;
	}

	while (test_and_set_bit(__IGBVF_RESETTING, &adapter->state))
		msleep(1);

	if (!netif_running(adapter->netdev)) {
		adapter->tx_ring->count = new_tx_count;
		adapter->rx_ring->count = new_rx_count;
		goto clear_reset;
	}

	temp_ring = vmalloc(sizeof(struct igbvf_ring));
	if (!temp_ring) {
		err = -ENOMEM;
		goto clear_reset;
	}

	igbvf_down(adapter);

	/*
	 * We can't just free everything and then setup again,
	 * because the ISRs in MSI-X mode get passed pointers
	 * to the tx and rx ring structs.
	 */
	if (new_tx_count != adapter->tx_ring->count) {
		memcpy(temp_ring, adapter->tx_ring, sizeof(struct igbvf_ring));

		temp_ring->count = new_tx_count;
		err = igbvf_setup_tx_resources(adapter, temp_ring);
		if (err)
			goto err_setup;

		igbvf_free_tx_resources(adapter->tx_ring);

		memcpy(adapter->tx_ring, temp_ring, sizeof(struct igbvf_ring));
	}

	if (new_rx_count != adapter->rx_ring->count) {
		memcpy(temp_ring, adapter->rx_ring, sizeof(struct igbvf_ring));

		temp_ring->count = new_rx_count;
		err = igbvf_setup_rx_resources(adapter, temp_ring);
		if (err)
			goto err_setup;

		igbvf_free_rx_resources(adapter->rx_ring);

		memcpy(adapter->rx_ring, temp_ring,sizeof(struct igbvf_ring));
	}
err_setup:
	igbvf_up(adapter);
	vfree(temp_ring);
clear_reset:
	clear_bit(__IGBVF_RESETTING, &adapter->state);
	return err;
}