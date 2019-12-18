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
struct net_device {char* name; } ;
struct msix_entry {int /*<<< orphan*/  vector; } ;
struct TYPE_4__ {scalar_t__ ring; } ;
struct TYPE_3__ {scalar_t__ ring; } ;
struct ixgbevf_q_vector {int num_msix_vectors; char* name; struct ixgbevf_q_vector** q_vector; struct msix_entry* msix_entries; int /*<<< orphan*/  hw; TYPE_2__ tx; TYPE_1__ rx; struct net_device* netdev; } ;
struct ixgbevf_adapter {int num_msix_vectors; char* name; struct ixgbevf_adapter** q_vector; struct msix_entry* msix_entries; int /*<<< orphan*/  hw; TYPE_2__ tx; TYPE_1__ rx; struct net_device* netdev; } ;

/* Variables and functions */
 int NON_Q_VECTORS ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct ixgbevf_q_vector*) ; 
 int /*<<< orphan*/  hw_dbg (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  ixgbevf_msix_clean_rings ; 
 int /*<<< orphan*/  ixgbevf_msix_other ; 
 int request_irq (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,struct ixgbevf_q_vector*) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char*,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ixgbevf_request_msix_irqs(struct ixgbevf_adapter *adapter)
{
	struct net_device *netdev = adapter->netdev;
	int q_vectors = adapter->num_msix_vectors - NON_Q_VECTORS;
	int vector, err;
	int ri = 0, ti = 0;

	for (vector = 0; vector < q_vectors; vector++) {
		struct ixgbevf_q_vector *q_vector = adapter->q_vector[vector];
		struct msix_entry *entry = &adapter->msix_entries[vector];

		if (q_vector->tx.ring && q_vector->rx.ring) {
			snprintf(q_vector->name, sizeof(q_vector->name) - 1,
				 "%s-%s-%d", netdev->name, "TxRx", ri++);
			ti++;
		} else if (q_vector->rx.ring) {
			snprintf(q_vector->name, sizeof(q_vector->name) - 1,
				 "%s-%s-%d", netdev->name, "rx", ri++);
		} else if (q_vector->tx.ring) {
			snprintf(q_vector->name, sizeof(q_vector->name) - 1,
				 "%s-%s-%d", netdev->name, "tx", ti++);
		} else {
			/* skip this unused q_vector */
			continue;
		}
		err = request_irq(entry->vector, &ixgbevf_msix_clean_rings, 0,
				  q_vector->name, q_vector);
		if (err) {
			hw_dbg(&adapter->hw,
			       "request_irq failed for MSIX interrupt "
			       "Error: %d\n", err);
			goto free_queue_irqs;
		}
	}

	err = request_irq(adapter->msix_entries[vector].vector,
			  &ixgbevf_msix_other, 0, netdev->name, adapter);
	if (err) {
		hw_dbg(&adapter->hw,
		       "request_irq for msix_other failed: %d\n", err);
		goto free_queue_irqs;
	}

	return 0;

free_queue_irqs:
	while (vector) {
		vector--;
		free_irq(adapter->msix_entries[vector].vector,
			 adapter->q_vector[vector]);
	}
	/* This failure is non-recoverable - it indicates the system is
	 * out of MSIX vector resources and the VF driver cannot run
	 * without them.  Set the number of msix vectors to zero
	 * indicating that not enough can be allocated.  The error
	 * will be returned to the user indicating device open failed.
	 * Any further attempts to force the driver to open will also
	 * fail.  The only way to recover is to unload the driver and
	 * reload it again.  If the system has recovered some MSIX
	 * vectors then it may succeed.
	 */
	adapter->num_msix_vectors = 0;
	return err;
}