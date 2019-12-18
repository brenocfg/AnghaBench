#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct ixgbevf_ring {int queue_index; int reg_idx; int /*<<< orphan*/  netdev; int /*<<< orphan*/ * dev; int /*<<< orphan*/  count; } ;
struct ixgbe_hw {int dummy; } ;
struct ixgbevf_adapter {unsigned int num_rx_queues; struct ixgbevf_ring* rx_ring; int /*<<< orphan*/  netdev; TYPE_2__* pdev; int /*<<< orphan*/  rx_ring_count; TYPE_1__* tx_ring; int /*<<< orphan*/  mbx_lock; struct ixgbe_hw hw; } ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;
struct TYPE_3__ {unsigned int reg_idx; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int ixgbevf_get_queues (struct ixgbe_hw*,unsigned int*,unsigned int*) ; 
 struct ixgbevf_ring* kcalloc (unsigned int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct ixgbevf_ring*) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ixgbevf_setup_queues(struct ixgbevf_adapter *adapter)
{
	struct ixgbe_hw *hw = &adapter->hw;
	struct ixgbevf_ring *rx_ring;
	unsigned int def_q = 0;
	unsigned int num_tcs = 0;
	unsigned int num_rx_queues = 1;
	int err, i;

	spin_lock_bh(&adapter->mbx_lock);

	/* fetch queue configuration from the PF */
	err = ixgbevf_get_queues(hw, &num_tcs, &def_q);

	spin_unlock_bh(&adapter->mbx_lock);

	if (err)
		return err;

	if (num_tcs > 1) {
		/* update default Tx ring register index */
		adapter->tx_ring[0].reg_idx = def_q;

		/* we need as many queues as traffic classes */
		num_rx_queues = num_tcs;
	}

	/* nothing to do if we have the correct number of queues */
	if (adapter->num_rx_queues == num_rx_queues)
		return 0;

	/* allocate new rings */
	rx_ring = kcalloc(num_rx_queues,
			  sizeof(struct ixgbevf_ring), GFP_KERNEL);
	if (!rx_ring)
		return -ENOMEM;

	/* setup ring fields */
	for (i = 0; i < num_rx_queues; i++) {
		rx_ring[i].count = adapter->rx_ring_count;
		rx_ring[i].queue_index = i;
		rx_ring[i].reg_idx = i;
		rx_ring[i].dev = &adapter->pdev->dev;
		rx_ring[i].netdev = adapter->netdev;
	}

	/* free the existing ring and queues */
	adapter->num_rx_queues = 0;
	kfree(adapter->rx_ring);

	/* move new rings into position on the adapter struct */
	adapter->rx_ring = rx_ring;
	adapter->num_rx_queues = num_rx_queues;

	return 0;
}