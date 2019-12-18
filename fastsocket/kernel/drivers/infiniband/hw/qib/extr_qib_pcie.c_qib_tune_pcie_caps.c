#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u16 ;
struct qib_devdata {struct pci_dev* pcidev; } ;
struct pci_dev {TYPE_1__* bus; } ;
struct TYPE_2__ {scalar_t__ parent; struct pci_dev* self; } ;

/* Variables and functions */
 int /*<<< orphan*/  PCI_EXP_DEVCAP ; 
 int PCI_EXP_DEVCAP_PAYLOAD ; 
 int /*<<< orphan*/  PCI_EXP_DEVCTL ; 
 int PCI_EXP_DEVCTL_PAYLOAD ; 
 int PCI_EXP_DEVCTL_READRQ ; 
 int fld2val (int,int) ; 
 int /*<<< orphan*/  pci_is_pcie (struct pci_dev*) ; 
 int /*<<< orphan*/  pcie_capability_read_word (struct pci_dev*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  pcie_capability_write_word (struct pci_dev*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  qib_devinfo (struct pci_dev*,char*) ; 
 int qib_pcie_caps ; 
 int val2fld (int,int) ; 

__attribute__((used)) static int qib_tune_pcie_caps(struct qib_devdata *dd)
{
	int ret = 1; /* Assume the worst */
	struct pci_dev *parent;
	u16 pcaps, pctl, ecaps, ectl;
	int rc_sup, ep_sup;
	int rc_cur, ep_cur;

	/* Find out supported and configured values for parent (root) */
	parent = dd->pcidev->bus->self;
	if (parent->bus->parent) {
		qib_devinfo(dd->pcidev, "Parent not root\n");
		goto bail;
	}

	if (!pci_is_pcie(parent) || !pci_is_pcie(dd->pcidev))
		goto bail;
	pcie_capability_read_word(parent, PCI_EXP_DEVCAP, &pcaps);
	pcie_capability_read_word(parent, PCI_EXP_DEVCTL, &pctl);
	/* Find out supported and configured values for endpoint (us) */
	pcie_capability_read_word(dd->pcidev, PCI_EXP_DEVCAP, &ecaps);
	pcie_capability_read_word(dd->pcidev, PCI_EXP_DEVCTL, &ectl);

	ret = 0;
	/* Find max payload supported by root, endpoint */
	rc_sup = fld2val(pcaps, PCI_EXP_DEVCAP_PAYLOAD);
	ep_sup = fld2val(ecaps, PCI_EXP_DEVCAP_PAYLOAD);
	if (rc_sup > ep_sup)
		rc_sup = ep_sup;

	rc_cur = fld2val(pctl, PCI_EXP_DEVCTL_PAYLOAD);
	ep_cur = fld2val(ectl, PCI_EXP_DEVCTL_PAYLOAD);

	/* If Supported greater than limit in module param, limit it */
	if (rc_sup > (qib_pcie_caps & 7))
		rc_sup = qib_pcie_caps & 7;
	/* If less than (allowed, supported), bump root payload */
	if (rc_sup > rc_cur) {
		rc_cur = rc_sup;
		pctl = (pctl & ~PCI_EXP_DEVCTL_PAYLOAD) |
			val2fld(rc_cur, PCI_EXP_DEVCTL_PAYLOAD);
		pcie_capability_write_word(parent, PCI_EXP_DEVCTL, pctl);
	}
	/* If less than (allowed, supported), bump endpoint payload */
	if (rc_sup > ep_cur) {
		ep_cur = rc_sup;
		ectl = (ectl & ~PCI_EXP_DEVCTL_PAYLOAD) |
			val2fld(ep_cur, PCI_EXP_DEVCTL_PAYLOAD);
		pcie_capability_write_word(dd->pcidev, PCI_EXP_DEVCTL, ectl);
	}

	/*
	 * Now the Read Request size.
	 * No field for max supported, but PCIe spec limits it to 4096,
	 * which is code '5' (log2(4096) - 7)
	 */
	rc_sup = 5;
	if (rc_sup > ((qib_pcie_caps >> 4) & 7))
		rc_sup = (qib_pcie_caps >> 4) & 7;
	rc_cur = fld2val(pctl, PCI_EXP_DEVCTL_READRQ);
	ep_cur = fld2val(ectl, PCI_EXP_DEVCTL_READRQ);

	if (rc_sup > rc_cur) {
		rc_cur = rc_sup;
		pctl = (pctl & ~PCI_EXP_DEVCTL_READRQ) |
			val2fld(rc_cur, PCI_EXP_DEVCTL_READRQ);
		pcie_capability_write_word(parent, PCI_EXP_DEVCTL, pctl);
	}
	if (rc_sup > ep_cur) {
		ep_cur = rc_sup;
		ectl = (ectl & ~PCI_EXP_DEVCTL_READRQ) |
			val2fld(ep_cur, PCI_EXP_DEVCTL_READRQ);
		pcie_capability_write_word(dd->pcidev, PCI_EXP_DEVCTL, ectl);
	}
bail:
	return ret;
}