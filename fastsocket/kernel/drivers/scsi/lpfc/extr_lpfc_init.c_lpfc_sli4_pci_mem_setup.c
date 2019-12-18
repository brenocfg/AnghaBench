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
typedef  scalar_t__ uint32_t ;
struct pci_dev {int /*<<< orphan*/  dev; } ;
struct TYPE_4__ {int /*<<< orphan*/  word0; } ;
struct TYPE_3__ {void* conf_regs_memmap_p; void* ctrl_regs_memmap_p; void* drbl_regs_memmap_p; TYPE_2__ sli_intf; } ;
struct lpfc_hba {TYPE_1__ sli4_hba; void* pci_bar2_map; void* pci_bar1_map; void* pci_bar0_map; struct pci_dev* pcidev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_BIT_MASK (int) ; 
 int ENODEV ; 
 int /*<<< orphan*/  KERN_ERR ; 
 int /*<<< orphan*/  LOG_INIT ; 
 int /*<<< orphan*/  LPFC_SLI_INTF ; 
 scalar_t__ LPFC_SLI_INTF_IF_TYPE_0 ; 
 scalar_t__ LPFC_SLI_INTF_IF_TYPE_2 ; 
 scalar_t__ LPFC_SLI_INTF_VALID ; 
 int /*<<< orphan*/  LPFC_VF0 ; 
 scalar_t__ bf_get (int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  dev_printk (int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*) ; 
 void* ioremap (void*,unsigned long) ; 
 int /*<<< orphan*/  iounmap (void*) ; 
 int /*<<< orphan*/  lpfc_printf_log (struct lpfc_hba*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lpfc_sli4_bar0_register_memmap (struct lpfc_hba*,scalar_t__) ; 
 int /*<<< orphan*/  lpfc_sli4_bar1_register_memmap (struct lpfc_hba*) ; 
 int lpfc_sli4_bar2_register_memmap (struct lpfc_hba*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lpfc_sli_intf_if_type ; 
 int /*<<< orphan*/  lpfc_sli_intf_valid ; 
 scalar_t__ pci_read_config_dword (struct pci_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 unsigned long pci_resource_len (struct pci_dev*,int) ; 
 void* pci_resource_start (struct pci_dev*,int) ; 
 scalar_t__ pci_set_dma_mask (struct pci_dev*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
lpfc_sli4_pci_mem_setup(struct lpfc_hba *phba)
{
	struct pci_dev *pdev;
	unsigned long bar0map_len, bar1map_len, bar2map_len;
	int error = -ENODEV;
	uint32_t if_type;

	/* Obtain PCI device reference */
	if (!phba->pcidev)
		return error;
	else
		pdev = phba->pcidev;

	/* Set the device DMA mask size */
	if (pci_set_dma_mask(pdev, DMA_BIT_MASK(64)) != 0)
		if (pci_set_dma_mask(pdev, DMA_BIT_MASK(32)) != 0)
			return error;

	/*
	 * The BARs and register set definitions and offset locations are
	 * dependent on the if_type.
	 */
	if (pci_read_config_dword(pdev, LPFC_SLI_INTF,
				  &phba->sli4_hba.sli_intf.word0)) {
		return error;
	}

	/* There is no SLI3 failback for SLI4 devices. */
	if (bf_get(lpfc_sli_intf_valid, &phba->sli4_hba.sli_intf) !=
	    LPFC_SLI_INTF_VALID) {
		lpfc_printf_log(phba, KERN_ERR, LOG_INIT,
				"2894 SLI_INTF reg contents invalid "
				"sli_intf reg 0x%x\n",
				phba->sli4_hba.sli_intf.word0);
		return error;
	}

	if_type = bf_get(lpfc_sli_intf_if_type, &phba->sli4_hba.sli_intf);
	/*
	 * Get the bus address of SLI4 device Bar regions and the
	 * number of bytes required by each mapping. The mapping of the
	 * particular PCI BARs regions is dependent on the type of
	 * SLI4 device.
	 */
	if (pci_resource_start(pdev, 0)) {
		phba->pci_bar0_map = pci_resource_start(pdev, 0);
		bar0map_len = pci_resource_len(pdev, 0);

		/*
		 * Map SLI4 PCI Config Space Register base to a kernel virtual
		 * addr
		 */
		phba->sli4_hba.conf_regs_memmap_p =
			ioremap(phba->pci_bar0_map, bar0map_len);
		if (!phba->sli4_hba.conf_regs_memmap_p) {
			dev_printk(KERN_ERR, &pdev->dev,
				   "ioremap failed for SLI4 PCI config "
				   "registers.\n");
			goto out;
		}
		/* Set up BAR0 PCI config space register memory map */
		lpfc_sli4_bar0_register_memmap(phba, if_type);
	} else {
		phba->pci_bar0_map = pci_resource_start(pdev, 1);
		bar0map_len = pci_resource_len(pdev, 1);
		if (if_type == LPFC_SLI_INTF_IF_TYPE_2) {
			dev_printk(KERN_ERR, &pdev->dev,
			   "FATAL - No BAR0 mapping for SLI4, if_type 2\n");
			goto out;
		}
		phba->sli4_hba.conf_regs_memmap_p =
				ioremap(phba->pci_bar0_map, bar0map_len);
		if (!phba->sli4_hba.conf_regs_memmap_p) {
			dev_printk(KERN_ERR, &pdev->dev,
				"ioremap failed for SLI4 PCI config "
				"registers.\n");
				goto out;
		}
		lpfc_sli4_bar0_register_memmap(phba, if_type);
	}

	if ((if_type == LPFC_SLI_INTF_IF_TYPE_0) &&
	    (pci_resource_start(pdev, 2))) {
		/*
		 * Map SLI4 if type 0 HBA Control Register base to a kernel
		 * virtual address and setup the registers.
		 */
		phba->pci_bar1_map = pci_resource_start(pdev, 2);
		bar1map_len = pci_resource_len(pdev, 2);
		phba->sli4_hba.ctrl_regs_memmap_p =
				ioremap(phba->pci_bar1_map, bar1map_len);
		if (!phba->sli4_hba.ctrl_regs_memmap_p) {
			dev_printk(KERN_ERR, &pdev->dev,
			   "ioremap failed for SLI4 HBA control registers.\n");
			goto out_iounmap_conf;
		}
		lpfc_sli4_bar1_register_memmap(phba);
	}

	if ((if_type == LPFC_SLI_INTF_IF_TYPE_0) &&
	    (pci_resource_start(pdev, 4))) {
		/*
		 * Map SLI4 if type 0 HBA Doorbell Register base to a kernel
		 * virtual address and setup the registers.
		 */
		phba->pci_bar2_map = pci_resource_start(pdev, 4);
		bar2map_len = pci_resource_len(pdev, 4);
		phba->sli4_hba.drbl_regs_memmap_p =
				ioremap(phba->pci_bar2_map, bar2map_len);
		if (!phba->sli4_hba.drbl_regs_memmap_p) {
			dev_printk(KERN_ERR, &pdev->dev,
			   "ioremap failed for SLI4 HBA doorbell registers.\n");
			goto out_iounmap_ctrl;
		}
		error = lpfc_sli4_bar2_register_memmap(phba, LPFC_VF0);
		if (error)
			goto out_iounmap_all;
	}

	return 0;

out_iounmap_all:
	iounmap(phba->sli4_hba.drbl_regs_memmap_p);
out_iounmap_ctrl:
	iounmap(phba->sli4_hba.ctrl_regs_memmap_p);
out_iounmap_conf:
	iounmap(phba->sli4_hba.conf_regs_memmap_p);
out:
	return error;
}