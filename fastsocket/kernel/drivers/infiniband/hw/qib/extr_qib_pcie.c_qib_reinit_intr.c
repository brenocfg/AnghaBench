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
struct qib_devdata {int msi_data; int flags; int /*<<< orphan*/  pcidev; int /*<<< orphan*/  msi_hi; int /*<<< orphan*/  msi_lo; } ;

/* Variables and functions */
 int /*<<< orphan*/  PCI_CAP_ID_MSI ; 
 scalar_t__ PCI_MSI_ADDRESS_HI ; 
 scalar_t__ PCI_MSI_ADDRESS_LO ; 
 int PCI_MSI_FLAGS ; 
 int PCI_MSI_FLAGS_64BIT ; 
 int PCI_MSI_FLAGS_ENABLE ; 
 int QIB_HAS_INTX ; 
 int pci_find_capability (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_read_config_word (int /*<<< orphan*/ ,int,int*) ; 
 int /*<<< orphan*/  pci_set_master (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_write_config_dword (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_write_config_word (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  qib_dev_err (struct qib_devdata*,char*) ; 
 int /*<<< orphan*/  qib_enable_intx (int /*<<< orphan*/ ) ; 

int qib_reinit_intr(struct qib_devdata *dd)
{
	int pos;
	u16 control;
	int ret = 0;

	/* If we aren't using MSI, don't restore it */
	if (!dd->msi_lo)
		goto bail;

	pos = pci_find_capability(dd->pcidev, PCI_CAP_ID_MSI);
	if (!pos) {
		qib_dev_err(dd,
			"Can't find MSI capability, can't restore MSI settings\n");
		ret = 0;
		/* nothing special for MSIx, just MSI */
		goto bail;
	}
	pci_write_config_dword(dd->pcidev, pos + PCI_MSI_ADDRESS_LO,
			       dd->msi_lo);
	pci_write_config_dword(dd->pcidev, pos + PCI_MSI_ADDRESS_HI,
			       dd->msi_hi);
	pci_read_config_word(dd->pcidev, pos + PCI_MSI_FLAGS, &control);
	if (!(control & PCI_MSI_FLAGS_ENABLE)) {
		control |= PCI_MSI_FLAGS_ENABLE;
		pci_write_config_word(dd->pcidev, pos + PCI_MSI_FLAGS,
				      control);
	}
	/* now rewrite the data (vector) info */
	pci_write_config_word(dd->pcidev, pos +
			      ((control & PCI_MSI_FLAGS_64BIT) ? 12 : 8),
			      dd->msi_data);
	ret = 1;
bail:
	if (!ret && (dd->flags & QIB_HAS_INTX)) {
		qib_enable_intx(dd->pcidev);
		ret = 1;
	}

	/* and now set the pci master bit again */
	pci_set_master(dd->pcidev);

	return ret;
}