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
struct pci_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  PCI_CAP_ID_MSI ; 
 int /*<<< orphan*/  PCI_CAP_ID_MSIX ; 
 scalar_t__ PCI_COMMAND ; 
 int PCI_COMMAND_INTX_DISABLE ; 
 scalar_t__ PCI_MSIX_FLAGS ; 
 int PCI_MSIX_FLAGS_ENABLE ; 
 scalar_t__ PCI_MSI_FLAGS ; 
 int PCI_MSI_FLAGS_ENABLE ; 
 int pci_find_capability (struct pci_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_read_config_word (struct pci_dev*,scalar_t__,int*) ; 
 int /*<<< orphan*/  pci_write_config_word (struct pci_dev*,scalar_t__,int) ; 

void qib_enable_intx(struct pci_dev *pdev)
{
	u16 cw, new;
	int pos;

	/* first, turn on INTx */
	pci_read_config_word(pdev, PCI_COMMAND, &cw);
	new = cw & ~PCI_COMMAND_INTX_DISABLE;
	if (new != cw)
		pci_write_config_word(pdev, PCI_COMMAND, new);

	pos = pci_find_capability(pdev, PCI_CAP_ID_MSI);
	if (pos) {
		/* then turn off MSI */
		pci_read_config_word(pdev, pos + PCI_MSI_FLAGS, &cw);
		new = cw & ~PCI_MSI_FLAGS_ENABLE;
		if (new != cw)
			pci_write_config_word(pdev, pos + PCI_MSI_FLAGS, new);
	}
	pos = pci_find_capability(pdev, PCI_CAP_ID_MSIX);
	if (pos) {
		/* then turn off MSIx */
		pci_read_config_word(pdev, pos + PCI_MSIX_FLAGS, &cw);
		new = cw & ~PCI_MSIX_FLAGS_ENABLE;
		if (new != cw)
			pci_write_config_word(pdev, pos + PCI_MSIX_FLAGS, new);
	}
}