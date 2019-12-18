#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct TYPE_6__ {int type; int mask_mode; int num_intrs; TYPE_1__* msix_entries; } ;
struct vmxnet3_adapter {scalar_t__ share_intr; int num_tx_queues; int num_rx_queues; TYPE_2__ intr; TYPE_4__* netdev; TYPE_3__* pdev; int /*<<< orphan*/  cmd_lock; } ;
struct TYPE_8__ {int /*<<< orphan*/  dev; } ;
struct TYPE_7__ {int /*<<< orphan*/  dev; } ;
struct TYPE_5__ {int entry; } ;

/* Variables and functions */
 int /*<<< orphan*/  VMXNET3_CMD_GET_CONF_INTR ; 
 scalar_t__ VMXNET3_INTR_BUDDYSHARE ; 
 scalar_t__ VMXNET3_INTR_TXSHARE ; 
 int VMXNET3_IT_AUTO ; 
 int VMXNET3_IT_INTX ; 
 int VMXNET3_IT_MSI ; 
 int VMXNET3_IT_MSIX ; 
 int VMXNET3_LINUX_MIN_MSIX_VECT ; 
 int VMXNET3_READ_BAR1_REG (struct vmxnet3_adapter*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VMXNET3_REG_CMD ; 
 int /*<<< orphan*/  VMXNET3_WRITE_BAR1_REG (struct vmxnet3_adapter*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  netdev_err (TYPE_4__*,char*) ; 
 int pci_enable_msi (TYPE_3__*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int vmxnet3_acquire_msix_vectors (struct vmxnet3_adapter*,int) ; 

__attribute__((used)) static void
vmxnet3_alloc_intr_resources(struct vmxnet3_adapter *adapter)
{
	u32 cfg;
	unsigned long flags;

	/* intr settings */
	spin_lock_irqsave(&adapter->cmd_lock, flags);
	VMXNET3_WRITE_BAR1_REG(adapter, VMXNET3_REG_CMD,
			       VMXNET3_CMD_GET_CONF_INTR);
	cfg = VMXNET3_READ_BAR1_REG(adapter, VMXNET3_REG_CMD);
	spin_unlock_irqrestore(&adapter->cmd_lock, flags);
	adapter->intr.type = cfg & 0x3;
	adapter->intr.mask_mode = (cfg >> 2) & 0x3;

	if (adapter->intr.type == VMXNET3_IT_AUTO) {
		adapter->intr.type = VMXNET3_IT_MSIX;
	}

#ifdef CONFIG_PCI_MSI
	if (adapter->intr.type == VMXNET3_IT_MSIX) {
		int vector, err = 0;

		adapter->intr.num_intrs = (adapter->share_intr ==
					   VMXNET3_INTR_TXSHARE) ? 1 :
					   adapter->num_tx_queues;
		adapter->intr.num_intrs += (adapter->share_intr ==
					   VMXNET3_INTR_BUDDYSHARE) ? 0 :
					   adapter->num_rx_queues;
		adapter->intr.num_intrs += 1;		/* for link event */

		adapter->intr.num_intrs = (adapter->intr.num_intrs >
					   VMXNET3_LINUX_MIN_MSIX_VECT
					   ? adapter->intr.num_intrs :
					   VMXNET3_LINUX_MIN_MSIX_VECT);

		for (vector = 0; vector < adapter->intr.num_intrs; vector++)
			adapter->intr.msix_entries[vector].entry = vector;

		err = vmxnet3_acquire_msix_vectors(adapter,
						   adapter->intr.num_intrs);
		/* If we cannot allocate one MSIx vector per queue
		 * then limit the number of rx queues to 1
		 */
		if (err == VMXNET3_LINUX_MIN_MSIX_VECT) {
			if (adapter->share_intr != VMXNET3_INTR_BUDDYSHARE
			    || adapter->num_rx_queues != 1) {
				adapter->share_intr = VMXNET3_INTR_TXSHARE;
				netdev_err(adapter->netdev,
					   "Number of rx queues : 1\n");
				adapter->num_rx_queues = 1;
				adapter->intr.num_intrs =
						VMXNET3_LINUX_MIN_MSIX_VECT;
			}
			return;
		}
		if (!err)
			return;

		/* If we cannot allocate MSIx vectors use only one rx queue */
		dev_info(&adapter->pdev->dev,
			 "Failed to enable MSI-X, error %d. "
			 "Limiting #rx queues to 1, try MSI.\n", err);

		adapter->intr.type = VMXNET3_IT_MSI;
	}

	if (adapter->intr.type == VMXNET3_IT_MSI) {
		int err;
		err = pci_enable_msi(adapter->pdev);
		if (!err) {
			adapter->num_rx_queues = 1;
			adapter->intr.num_intrs = 1;
			return;
		}
	}
#endif /* CONFIG_PCI_MSI */

	adapter->num_rx_queues = 1;
	dev_info(&adapter->netdev->dev,
		 "Using INTx interrupt, #Rx queues: 1.\n");
	adapter->intr.type = VMXNET3_IT_INTX;

	/* INT-X related setting */
	adapter->intr.num_intrs = 1;
}