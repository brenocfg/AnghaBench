#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  ring; } ;
struct TYPE_4__ {int /*<<< orphan*/  ring; } ;
struct ixgbevf_adapter {int num_msix_vectors; struct ixgbevf_adapter** q_vector; TYPE_3__* msix_entries; TYPE_2__ tx; TYPE_1__ rx; } ;
struct TYPE_6__ {int /*<<< orphan*/  vector; } ;

/* Variables and functions */
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct ixgbevf_adapter*) ; 
 int /*<<< orphan*/  ixgbevf_reset_q_vectors (struct ixgbevf_adapter*) ; 

__attribute__((used)) static void ixgbevf_free_irq(struct ixgbevf_adapter *adapter)
{
	int i, q_vectors;

	q_vectors = adapter->num_msix_vectors;
	i = q_vectors - 1;

	free_irq(adapter->msix_entries[i].vector, adapter);
	i--;

	for (; i >= 0; i--) {
		/* free only the irqs that were actually requested */
		if (!adapter->q_vector[i]->rx.ring &&
		    !adapter->q_vector[i]->tx.ring)
			continue;

		free_irq(adapter->msix_entries[i].vector,
			 adapter->q_vector[i]);
	}

	ixgbevf_reset_q_vectors(adapter);
}