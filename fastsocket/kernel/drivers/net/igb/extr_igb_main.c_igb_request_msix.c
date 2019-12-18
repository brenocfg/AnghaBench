#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct net_device {char* name; } ;
struct TYPE_9__ {TYPE_3__* ring; } ;
struct TYPE_7__ {TYPE_1__* ring; } ;
struct e1000_hw {scalar_t__ hw_addr; } ;
struct igb_q_vector {int num_q_vectors; char* name; struct igb_q_vector** q_vector; TYPE_5__* msix_entries; TYPE_4__ rx; TYPE_2__ tx; scalar_t__ itr_register; struct e1000_hw hw; struct net_device* netdev; } ;
struct igb_adapter {int num_q_vectors; char* name; struct igb_adapter** q_vector; TYPE_5__* msix_entries; TYPE_4__ rx; TYPE_2__ tx; scalar_t__ itr_register; struct e1000_hw hw; struct net_device* netdev; } ;
struct TYPE_10__ {int /*<<< orphan*/  vector; } ;
struct TYPE_8__ {int queue_index; } ;
struct TYPE_6__ {int queue_index; } ;

/* Variables and functions */
 scalar_t__ E1000_EITR (int) ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct igb_q_vector*) ; 
 int /*<<< orphan*/  igb_configure_msix (struct igb_q_vector*) ; 
 int /*<<< orphan*/  igb_msix_other ; 
 int /*<<< orphan*/  igb_msix_ring ; 
 int request_irq (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,struct igb_q_vector*) ; 
 int /*<<< orphan*/  sprintf (char*,char*,char*,...) ; 

__attribute__((used)) static int igb_request_msix(struct igb_adapter *adapter)
{
	struct net_device *netdev = adapter->netdev;
	struct e1000_hw *hw = &adapter->hw;
	int i, err = 0, vector = 0, free_vector = 0;

	err = request_irq(adapter->msix_entries[vector].vector,
			  igb_msix_other, 0, netdev->name, adapter);
	if (err)
		goto err_out;

	for (i = 0; i < adapter->num_q_vectors; i++) {
		struct igb_q_vector *q_vector = adapter->q_vector[i];

		vector++;

		q_vector->itr_register = hw->hw_addr + E1000_EITR(vector);

		if (q_vector->rx.ring && q_vector->tx.ring)
			sprintf(q_vector->name, "%s-TxRx-%u", netdev->name,
				q_vector->rx.ring->queue_index);
		else if (q_vector->tx.ring)
			sprintf(q_vector->name, "%s-tx-%u", netdev->name,
				q_vector->tx.ring->queue_index);
		else if (q_vector->rx.ring)
			sprintf(q_vector->name, "%s-rx-%u", netdev->name,
				q_vector->rx.ring->queue_index);
		else
			sprintf(q_vector->name, "%s-unused", netdev->name);

		err = request_irq(adapter->msix_entries[vector].vector,
				  igb_msix_ring, 0, q_vector->name,
				  q_vector);
		if (err)
			goto err_free;
	}

	igb_configure_msix(adapter);
	return 0;

err_free:
	/* free already assigned IRQs */
	free_irq(adapter->msix_entries[free_vector++].vector, adapter);

	vector--;
	for (i = 0; i < vector; i++) {
		free_irq(adapter->msix_entries[free_vector++].vector,
			 adapter->q_vector[i]);
	}
err_out:
	return err;
}