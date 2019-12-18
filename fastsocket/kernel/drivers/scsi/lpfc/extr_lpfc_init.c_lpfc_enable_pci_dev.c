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
struct pci_dev {int needs_freset; } ;
struct lpfc_hba {struct pci_dev* pcidev; } ;

/* Variables and functions */
 int ENODEV ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 int /*<<< orphan*/  KERN_ERR ; 
 int /*<<< orphan*/  LOG_INIT ; 
 int /*<<< orphan*/  LPFC_DRIVER_NAME ; 
 int /*<<< orphan*/  PCI_CAP_ID_EXP ; 
 int /*<<< orphan*/  lpfc_printf_log (struct lpfc_hba*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  pci_disable_device (struct pci_dev*) ; 
 scalar_t__ pci_enable_device_mem (struct pci_dev*) ; 
 scalar_t__ pci_find_capability (struct pci_dev*,int /*<<< orphan*/ ) ; 
 scalar_t__ pci_request_selected_regions (struct pci_dev*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_save_state (struct pci_dev*) ; 
 int pci_select_bars (struct pci_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_set_master (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_try_set_mwi (struct pci_dev*) ; 

__attribute__((used)) static int
lpfc_enable_pci_dev(struct lpfc_hba *phba)
{
	struct pci_dev *pdev;
	int bars = 0;

	/* Obtain PCI device reference */
	if (!phba->pcidev)
		goto out_error;
	else
		pdev = phba->pcidev;
	/* Select PCI BARs */
	bars = pci_select_bars(pdev, IORESOURCE_MEM);
	/* Enable PCI device */
	if (pci_enable_device_mem(pdev))
		goto out_error;
	/* Request PCI resource for the device */
	if (pci_request_selected_regions(pdev, bars, LPFC_DRIVER_NAME))
		goto out_disable_device;
	/* Set up device as PCI master and save state for EEH */
	pci_set_master(pdev);
	pci_try_set_mwi(pdev);
	pci_save_state(pdev);

	/* PCIe EEH recovery on powerpc platforms needs fundamental reset */
	if (pci_find_capability(pdev, PCI_CAP_ID_EXP))
		pdev->needs_freset = 1;

	return 0;

out_disable_device:
	pci_disable_device(pdev);
out_error:
	lpfc_printf_log(phba, KERN_ERR, LOG_INIT,
			"1401 Failed to enable pci device, bars:x%x\n", bars);
	return -ENODEV;
}