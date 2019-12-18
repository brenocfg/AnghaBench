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
struct igb_ring {int reg_idx; int /*<<< orphan*/  netdev; int /*<<< orphan*/ * dev; int /*<<< orphan*/  count; } ;
struct e1000_hw {int dummy; } ;
struct igb_adapter {int vfs_allocated_count; int /*<<< orphan*/  netdev; TYPE_1__* pdev; struct e1000_hw hw; struct igb_ring test_rx_ring; struct igb_ring test_tx_ring; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  E1000_MRQC ; 
 int /*<<< orphan*/  IGB_DEFAULT_RXD ; 
 int /*<<< orphan*/  IGB_DEFAULT_TXD ; 
 int /*<<< orphan*/  igb_alloc_rx_buffers (struct igb_ring*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  igb_configure_rx_ring (struct igb_adapter*,struct igb_ring*) ; 
 int /*<<< orphan*/  igb_configure_tx_ring (struct igb_adapter*,struct igb_ring*) ; 
 int /*<<< orphan*/  igb_desc_unused (struct igb_ring*) ; 
 int /*<<< orphan*/  igb_free_desc_rings (struct igb_adapter*) ; 
 int /*<<< orphan*/  igb_setup_rctl (struct igb_adapter*) ; 
 scalar_t__ igb_setup_rx_resources (struct igb_ring*) ; 
 int /*<<< orphan*/  igb_setup_tctl (struct igb_adapter*) ; 
 scalar_t__ igb_setup_tx_resources (struct igb_ring*) ; 
 int /*<<< orphan*/  wr32 (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int igb_setup_desc_rings(struct igb_adapter *adapter)
{
	struct igb_ring *tx_ring = &adapter->test_tx_ring;
	struct igb_ring *rx_ring = &adapter->test_rx_ring;
	struct e1000_hw *hw = &adapter->hw;
	int ret_val;

	/* Setup Tx descriptor ring and Tx buffers */
	tx_ring->count = IGB_DEFAULT_TXD;
	tx_ring->dev = &adapter->pdev->dev;
	tx_ring->netdev = adapter->netdev;
	tx_ring->reg_idx = adapter->vfs_allocated_count;

	if (igb_setup_tx_resources(tx_ring)) {
		ret_val = 1;
		goto err_nomem;
	}

	igb_setup_tctl(adapter);
	igb_configure_tx_ring(adapter, tx_ring);

	/* Setup Rx descriptor ring and Rx buffers */
	rx_ring->count = IGB_DEFAULT_RXD;
	rx_ring->dev = &adapter->pdev->dev;
	rx_ring->netdev = adapter->netdev;
	rx_ring->reg_idx = adapter->vfs_allocated_count;

	if (igb_setup_rx_resources(rx_ring)) {
		ret_val = 3;
		goto err_nomem;
	}

	/* set the default queue to queue 0 of PF */
	wr32(E1000_MRQC, adapter->vfs_allocated_count << 3);

	/* enable receive ring */
	igb_setup_rctl(adapter);
	igb_configure_rx_ring(adapter, rx_ring);

	igb_alloc_rx_buffers(rx_ring, igb_desc_unused(rx_ring));

	return 0;

err_nomem:
	igb_free_desc_rings(adapter);
	return ret_val;
}