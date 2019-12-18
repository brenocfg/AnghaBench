#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct iwl_trans_pcie {TYPE_1__* pci_dev; int /*<<< orphan*/  hw_base; } ;
struct iwl_trans {int /*<<< orphan*/  dev_cmd_pool; } ;
struct TYPE_4__ {int /*<<< orphan*/  irq; } ;

/* Variables and functions */
 struct iwl_trans_pcie* IWL_TRANS_GET_PCIE_TRANS (struct iwl_trans*) ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct iwl_trans*) ; 
 int /*<<< orphan*/  iounmap (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iwl_pcie_free_ict (struct iwl_trans*) ; 
 int /*<<< orphan*/  iwl_pcie_rx_free (struct iwl_trans*) ; 
 int /*<<< orphan*/  iwl_pcie_tx_free (struct iwl_trans*) ; 
 int /*<<< orphan*/  kfree (struct iwl_trans*) ; 
 int /*<<< orphan*/  kmem_cache_destroy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_disable_device (TYPE_1__*) ; 
 int /*<<< orphan*/  pci_disable_msi (TYPE_1__*) ; 
 int /*<<< orphan*/  pci_release_regions (TYPE_1__*) ; 
 int /*<<< orphan*/  synchronize_irq (int /*<<< orphan*/ ) ; 

void iwl_trans_pcie_free(struct iwl_trans *trans)
{
	struct iwl_trans_pcie *trans_pcie = IWL_TRANS_GET_PCIE_TRANS(trans);

	synchronize_irq(trans_pcie->pci_dev->irq);

	iwl_pcie_tx_free(trans);
	iwl_pcie_rx_free(trans);

	free_irq(trans_pcie->pci_dev->irq, trans);
	iwl_pcie_free_ict(trans);

	pci_disable_msi(trans_pcie->pci_dev);
	iounmap(trans_pcie->hw_base);
	pci_release_regions(trans_pcie->pci_dev);
	pci_disable_device(trans_pcie->pci_dev);
	kmem_cache_destroy(trans->dev_cmd_pool);

	kfree(trans);
}