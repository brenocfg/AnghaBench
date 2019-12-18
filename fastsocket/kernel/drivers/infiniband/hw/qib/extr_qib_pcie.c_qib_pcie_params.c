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
typedef  int u32 ;
typedef  int u16 ;
struct qib_msix_entry {int dummy; } ;
struct qib_devdata {int lbus_width; int lbus_speed; int /*<<< orphan*/  lbus_info; int /*<<< orphan*/  pcidev; } ;

/* Variables and functions */
 int /*<<< orphan*/  PCI_CAP_ID_MSI ; 
 int /*<<< orphan*/  PCI_CAP_ID_MSIX ; 
 int /*<<< orphan*/  PCI_EXP_LNKSTA ; 
 int pci_find_capability (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_is_pcie (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pcie_capability_read_word (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  qib_dev_err (struct qib_devdata*,char*,...) ; 
 int /*<<< orphan*/  qib_enable_intx (int /*<<< orphan*/ ) ; 
 int qib_msi_setup (struct qib_devdata*,int) ; 
 int /*<<< orphan*/  qib_msix_setup (struct qib_devdata*,int,int*,struct qib_msix_entry*) ; 
 int /*<<< orphan*/  qib_tune_pcie_caps (struct qib_devdata*) ; 
 int /*<<< orphan*/  qib_tune_pcie_coalesce (struct qib_devdata*) ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ ,int,char*,int,int) ; 

int qib_pcie_params(struct qib_devdata *dd, u32 minw, u32 *nent,
		    struct qib_msix_entry *entry)
{
	u16 linkstat, speed;
	int pos = 0, ret = 1;

	if (!pci_is_pcie(dd->pcidev)) {
		qib_dev_err(dd, "Can't find PCI Express capability!\n");
		/* set up something... */
		dd->lbus_width = 1;
		dd->lbus_speed = 2500; /* Gen1, 2.5GHz */
		goto bail;
	}

	pos = pci_find_capability(dd->pcidev, PCI_CAP_ID_MSIX);
	if (nent && *nent && pos) {
		qib_msix_setup(dd, pos, nent, entry);
		ret = 0; /* did it, either MSIx or INTx */
	} else {
		pos = pci_find_capability(dd->pcidev, PCI_CAP_ID_MSI);
		if (pos)
			ret = qib_msi_setup(dd, pos);
		else
			qib_dev_err(dd, "No PCI MSI or MSIx capability!\n");
	}
	if (!pos)
		qib_enable_intx(dd->pcidev);

	pcie_capability_read_word(dd->pcidev, PCI_EXP_LNKSTA, &linkstat);
	/*
	 * speed is bits 0-3, linkwidth is bits 4-8
	 * no defines for them in headers
	 */
	speed = linkstat & 0xf;
	linkstat >>= 4;
	linkstat &= 0x1f;
	dd->lbus_width = linkstat;

	switch (speed) {
	case 1:
		dd->lbus_speed = 2500; /* Gen1, 2.5GHz */
		break;
	case 2:
		dd->lbus_speed = 5000; /* Gen1, 5GHz */
		break;
	default: /* not defined, assume gen1 */
		dd->lbus_speed = 2500;
		break;
	}

	/*
	 * Check against expected pcie width and complain if "wrong"
	 * on first initialization, not afterwards (i.e., reset).
	 */
	if (minw && linkstat < minw)
		qib_dev_err(dd,
			    "PCIe width %u (x%u HCA), performance reduced\n",
			    linkstat, minw);

	qib_tune_pcie_caps(dd);

	qib_tune_pcie_coalesce(dd);

bail:
	/* fill in string, even on errors */
	snprintf(dd->lbus_info, sizeof(dd->lbus_info),
		 "PCIe,%uMHz,x%u\n", dd->lbus_speed, dd->lbus_width);
	return ret;
}