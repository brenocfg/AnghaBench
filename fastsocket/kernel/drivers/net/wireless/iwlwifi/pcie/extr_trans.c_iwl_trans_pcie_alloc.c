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
typedef  int u16 ;
struct pci_device_id {int dummy; } ;
struct pci_dev {int device; int subsystem_device; int /*<<< orphan*/  irq; int /*<<< orphan*/  dev; } ;
struct iwl_trans_pcie {int /*<<< orphan*/  inta_mask; int /*<<< orphan*/  wait_command_queue; struct pci_dev* pci_dev; int /*<<< orphan*/  hw_base; int /*<<< orphan*/  ucode_write_waitq; int /*<<< orphan*/  reg_lock; int /*<<< orphan*/  irq_lock; struct iwl_trans* trans; } ;
struct iwl_trans {int hw_id; int /*<<< orphan*/  dev_cmd_pool; scalar_t__ dev_cmd_headroom; int /*<<< orphan*/  dev_cmd_pool_name; int /*<<< orphan*/ * dev; int /*<<< orphan*/  hw_id_str; int /*<<< orphan*/  hw_rev; struct iwl_cfg const* cfg; int /*<<< orphan*/ * ops; } ;
struct iwl_device_cmd {int dummy; } ;
struct iwl_cfg {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CSR_HW_REV ; 
 int /*<<< orphan*/  CSR_INI_SET_MASK ; 
 int /*<<< orphan*/  DMA_BIT_MASK (int) ; 
 int /*<<< orphan*/  DRV_NAME ; 
 int ENODEV ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IRQF_SHARED ; 
 int /*<<< orphan*/  IWL_ERR (struct iwl_trans*,char*,int /*<<< orphan*/ ) ; 
 struct iwl_trans_pcie* IWL_TRANS_GET_PCIE_TRANS (struct iwl_trans*) ; 
 int PCIE_LINK_STATE_CLKPM ; 
 int PCIE_LINK_STATE_L0S ; 
 int PCIE_LINK_STATE_L1 ; 
 int /*<<< orphan*/  PCI_CFG_RETRY_TIMEOUT ; 
 int /*<<< orphan*/  PCI_COMMAND ; 
 int PCI_COMMAND_INTX_DISABLE ; 
 int /*<<< orphan*/  SLAB_HWCACHE_ALIGN ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,...) ; 
 char* dev_name (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  init_waitqueue_head (int /*<<< orphan*/ *) ; 
 scalar_t__ iwl_pcie_alloc_ict (struct iwl_trans*) ; 
 int /*<<< orphan*/  iwl_pcie_free_ict (struct iwl_trans*) ; 
 int /*<<< orphan*/  iwl_pcie_irq_handler ; 
 int /*<<< orphan*/  iwl_pcie_isr_ict ; 
 int /*<<< orphan*/  iwl_read32 (struct iwl_trans*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct iwl_trans*) ; 
 int /*<<< orphan*/  kmem_cache_create (int /*<<< orphan*/ ,scalar_t__,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kmem_cache_destroy (int /*<<< orphan*/ ) ; 
 struct iwl_trans* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_disable_device (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_disable_link_state (struct pci_dev*,int) ; 
 int /*<<< orphan*/  pci_disable_msi (struct pci_dev*) ; 
 scalar_t__ pci_enable_device (struct pci_dev*) ; 
 int pci_enable_msi (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_ioremap_bar (struct pci_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_read_config_word (struct pci_dev*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  pci_release_regions (struct pci_dev*) ; 
 int pci_request_regions (struct pci_dev*,int /*<<< orphan*/ ) ; 
 int pci_set_consistent_dma_mask (struct pci_dev*,int /*<<< orphan*/ ) ; 
 int pci_set_dma_mask (struct pci_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_set_master (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_write_config_byte (struct pci_dev*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pci_write_config_word (struct pci_dev*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ request_threaded_irq (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct iwl_trans*) ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ ,int,char*,...) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  trans_lockdep_init (struct iwl_trans*) ; 
 int /*<<< orphan*/  trans_ops_pcie ; 

struct iwl_trans *iwl_trans_pcie_alloc(struct pci_dev *pdev,
				       const struct pci_device_id *ent,
				       const struct iwl_cfg *cfg)
{
	struct iwl_trans_pcie *trans_pcie;
	struct iwl_trans *trans;
	u16 pci_cmd;
	int err;

	trans = kzalloc(sizeof(struct iwl_trans) +
			sizeof(struct iwl_trans_pcie), GFP_KERNEL);

	if (!trans)
		return NULL;

	trans_pcie = IWL_TRANS_GET_PCIE_TRANS(trans);

	trans->ops = &trans_ops_pcie;
	trans->cfg = cfg;
	trans_lockdep_init(trans);
	trans_pcie->trans = trans;
	spin_lock_init(&trans_pcie->irq_lock);
	spin_lock_init(&trans_pcie->reg_lock);
	init_waitqueue_head(&trans_pcie->ucode_write_waitq);

	if (pci_enable_device(pdev)) {
		err = -ENODEV;
		goto out_no_pci;
	}

	/* W/A - seems to solve weird behavior. We need to remove this if we
	 * don't want to stay in L1 all the time. This wastes a lot of power */
	pci_disable_link_state(pdev, PCIE_LINK_STATE_L0S | PCIE_LINK_STATE_L1 |
			       PCIE_LINK_STATE_CLKPM);

	pci_set_master(pdev);

	err = pci_set_dma_mask(pdev, DMA_BIT_MASK(36));
	if (!err)
		err = pci_set_consistent_dma_mask(pdev, DMA_BIT_MASK(36));
	if (err) {
		err = pci_set_dma_mask(pdev, DMA_BIT_MASK(32));
		if (!err)
			err = pci_set_consistent_dma_mask(pdev,
							  DMA_BIT_MASK(32));
		/* both attempts failed: */
		if (err) {
			dev_err(&pdev->dev, "No suitable DMA available\n");
			goto out_pci_disable_device;
		}
	}

	err = pci_request_regions(pdev, DRV_NAME);
	if (err) {
		dev_err(&pdev->dev, "pci_request_regions failed\n");
		goto out_pci_disable_device;
	}

	trans_pcie->hw_base = pci_ioremap_bar(pdev, 0);
	if (!trans_pcie->hw_base) {
		dev_err(&pdev->dev, "pci_ioremap_bar failed\n");
		err = -ENODEV;
		goto out_pci_release_regions;
	}

	/* We disable the RETRY_TIMEOUT register (0x41) to keep
	 * PCI Tx retries from interfering with C3 CPU state */
	pci_write_config_byte(pdev, PCI_CFG_RETRY_TIMEOUT, 0x00);

	err = pci_enable_msi(pdev);
	if (err) {
		dev_err(&pdev->dev, "pci_enable_msi failed(0X%x)\n", err);
		/* enable rfkill interrupt: hw bug w/a */
		pci_read_config_word(pdev, PCI_COMMAND, &pci_cmd);
		if (pci_cmd & PCI_COMMAND_INTX_DISABLE) {
			pci_cmd &= ~PCI_COMMAND_INTX_DISABLE;
			pci_write_config_word(pdev, PCI_COMMAND, pci_cmd);
		}
	}

	trans->dev = &pdev->dev;
	trans_pcie->pci_dev = pdev;
	trans->hw_rev = iwl_read32(trans, CSR_HW_REV);
	trans->hw_id = (pdev->device << 16) + pdev->subsystem_device;
	snprintf(trans->hw_id_str, sizeof(trans->hw_id_str),
		 "PCI ID: 0x%04X:0x%04X", pdev->device, pdev->subsystem_device);

	/* Initialize the wait queue for commands */
	init_waitqueue_head(&trans_pcie->wait_command_queue);

	snprintf(trans->dev_cmd_pool_name, sizeof(trans->dev_cmd_pool_name),
		 "iwl_cmd_pool:%s", dev_name(trans->dev));

	trans->dev_cmd_headroom = 0;
	trans->dev_cmd_pool =
		kmem_cache_create(trans->dev_cmd_pool_name,
				  sizeof(struct iwl_device_cmd)
				  + trans->dev_cmd_headroom,
				  sizeof(void *),
				  SLAB_HWCACHE_ALIGN,
				  NULL);

	if (!trans->dev_cmd_pool)
		goto out_pci_disable_msi;

	trans_pcie->inta_mask = CSR_INI_SET_MASK;

	if (iwl_pcie_alloc_ict(trans))
		goto out_free_cmd_pool;

	if (request_threaded_irq(pdev->irq, iwl_pcie_isr_ict,
				 iwl_pcie_irq_handler,
				 IRQF_SHARED, DRV_NAME, trans)) {
		IWL_ERR(trans, "Error allocating IRQ %d\n", pdev->irq);
		goto out_free_ict;
	}

	return trans;

out_free_ict:
	iwl_pcie_free_ict(trans);
out_free_cmd_pool:
	kmem_cache_destroy(trans->dev_cmd_pool);
out_pci_disable_msi:
	pci_disable_msi(pdev);
out_pci_release_regions:
	pci_release_regions(pdev);
out_pci_disable_device:
	pci_disable_device(pdev);
out_no_pci:
	kfree(trans);
	return NULL;
}