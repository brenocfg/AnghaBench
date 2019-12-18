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
struct vmxnet3_intr {int type; scalar_t__ num_intrs; TYPE_1__* msix_entries; } ;
struct vmxnet3_adapter {int num_tx_queues; int num_rx_queues; int /*<<< orphan*/ * netdev; TYPE_2__* pdev; int /*<<< orphan*/ * rx_queue; int /*<<< orphan*/  share_intr; int /*<<< orphan*/ * tx_queue; struct vmxnet3_intr intr; } ;
struct TYPE_4__ {int /*<<< orphan*/  irq; } ;
struct TYPE_3__ {int /*<<< orphan*/  vector; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG () ; 
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  VMXNET3_INTR_BUDDYSHARE ; 
 int /*<<< orphan*/  VMXNET3_INTR_TXSHARE ; 
 int VMXNET3_IT_AUTO ; 
#define  VMXNET3_IT_INTX 130 
#define  VMXNET3_IT_MSI 129 
#define  VMXNET3_IT_MSIX 128 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
vmxnet3_free_irqs(struct vmxnet3_adapter *adapter)
{
	struct vmxnet3_intr *intr = &adapter->intr;
	BUG_ON(intr->type == VMXNET3_IT_AUTO || intr->num_intrs <= 0);

	switch (intr->type) {
#ifdef CONFIG_PCI_MSI
	case VMXNET3_IT_MSIX:
	{
		int i, vector = 0;

		if (adapter->share_intr != VMXNET3_INTR_BUDDYSHARE) {
			for (i = 0; i < adapter->num_tx_queues; i++) {
				free_irq(intr->msix_entries[vector++].vector,
					 &(adapter->tx_queue[i]));
				if (adapter->share_intr == VMXNET3_INTR_TXSHARE)
					break;
			}
		}

		for (i = 0; i < adapter->num_rx_queues; i++) {
			free_irq(intr->msix_entries[vector++].vector,
				 &(adapter->rx_queue[i]));
		}

		free_irq(intr->msix_entries[vector].vector,
			 adapter->netdev);
		BUG_ON(vector >= intr->num_intrs);
		break;
	}
#endif
	case VMXNET3_IT_MSI:
		free_irq(adapter->pdev->irq, adapter->netdev);
		break;
	case VMXNET3_IT_INTX:
		free_irq(adapter->pdev->irq, adapter->netdev);
		break;
	default:
		BUG();
	}
}