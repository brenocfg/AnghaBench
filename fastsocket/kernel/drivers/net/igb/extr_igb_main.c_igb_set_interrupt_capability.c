#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct msix_entry {int dummy; } ;
struct e1000_hw {int dummy; } ;
struct igb_adapter {int num_rx_queues; int rss_queues; int num_tx_queues; int flags; int num_q_vectors; TYPE_1__* pdev; scalar_t__ vfs_allocated_count; int /*<<< orphan*/ * vf_data; struct e1000_hw hw; TYPE_2__* msix_entries; } ;
struct TYPE_7__ {int entry; } ;
struct TYPE_6__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  E1000_IOVCTL ; 
 int /*<<< orphan*/  E1000_IOVCTL_REUSE_VFQ ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int IGB_FLAG_HAS_MSI ; 
 int IGB_FLAG_QUEUE_PAIRS ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  igb_reset_interrupt_capability (struct igb_adapter*) ; 
 TYPE_2__* kcalloc (int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  pci_disable_sriov (TYPE_1__*) ; 
 int /*<<< orphan*/  pci_enable_msi (TYPE_1__*) ; 
 int pci_enable_msix (TYPE_1__*,TYPE_2__*,int) ; 
 int /*<<< orphan*/  wr32 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wrfl () ; 

__attribute__((used)) static void igb_set_interrupt_capability(struct igb_adapter *adapter, bool msix)
{
	int err;
	int numvecs, i;

	if (!msix)
		goto msi_only;

	/* Number of supported queues. */
	adapter->num_rx_queues = adapter->rss_queues;
	if (adapter->vfs_allocated_count)
		adapter->num_tx_queues = 1;
	else
		adapter->num_tx_queues = adapter->rss_queues;

	/* start with one vector for every Rx queue */
	numvecs = adapter->num_rx_queues;

	/* if Tx handler is separate add 1 for every Tx queue */
	if (!(adapter->flags & IGB_FLAG_QUEUE_PAIRS))
		numvecs += adapter->num_tx_queues;

	/* store the number of vectors reserved for queues */
	adapter->num_q_vectors = numvecs;

	/* add 1 vector for link status interrupts */
	numvecs++;
	adapter->msix_entries = kcalloc(numvecs, sizeof(struct msix_entry),
					GFP_KERNEL);

	if (!adapter->msix_entries)
		goto msi_only;

	for (i = 0; i < numvecs; i++)
		adapter->msix_entries[i].entry = i;

	err = pci_enable_msix(adapter->pdev,
			      adapter->msix_entries,
			      numvecs);
	if (err == 0)
		return;

	igb_reset_interrupt_capability(adapter);

	/* If we can't do MSI-X, try MSI */
msi_only:
#ifdef CONFIG_PCI_IOV
	/* disable SR-IOV for non MSI-X configurations */
	if (adapter->vf_data) {
		struct e1000_hw *hw = &adapter->hw;
		/* disable iov and allow time for transactions to clear */
		pci_disable_sriov(adapter->pdev);
		msleep(500);

		kfree(adapter->vf_data);
		adapter->vf_data = NULL;
		wr32(E1000_IOVCTL, E1000_IOVCTL_REUSE_VFQ);
		wrfl();
		msleep(100);
		dev_info(&adapter->pdev->dev, "IOV Disabled\n");
	}
#endif
	adapter->vfs_allocated_count = 0;
	adapter->rss_queues = 1;
	adapter->flags |= IGB_FLAG_QUEUE_PAIRS;
	adapter->num_rx_queues = 1;
	adapter->num_tx_queues = 1;
	adapter->num_q_vectors = 1;
	if (!pci_enable_msi(adapter->pdev))
		adapter->flags |= IGB_FLAG_HAS_MSI;
}