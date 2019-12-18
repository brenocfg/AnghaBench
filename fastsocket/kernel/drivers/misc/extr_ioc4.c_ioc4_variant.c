#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct pci_dev {int /*<<< orphan*/  devfn; TYPE_3__* bus; } ;
struct ioc4_driver_data {TYPE_2__* idd_pdev; } ;
struct TYPE_6__ {scalar_t__ number; } ;
struct TYPE_5__ {TYPE_1__* bus; } ;
struct TYPE_4__ {scalar_t__ number; } ;

/* Variables and functions */
 unsigned int IOC4_VARIANT_IO10 ; 
 unsigned int IOC4_VARIANT_IO9 ; 
 unsigned int IOC4_VARIANT_PCI_RT ; 
 int /*<<< orphan*/  PCI_DEVICE_ID_QLOGIC_ISP12160 ; 
 int /*<<< orphan*/  PCI_DEVICE_ID_VITESSE_VSC7174 ; 
 int PCI_SLOT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PCI_VENDOR_ID_QLOGIC ; 
 int /*<<< orphan*/  PCI_VENDOR_ID_VITESSE ; 
 int /*<<< orphan*/  pci_dev_put (struct pci_dev*) ; 
 struct pci_dev* pci_get_device (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct pci_dev*) ; 

__attribute__((used)) static unsigned int
ioc4_variant(struct ioc4_driver_data *idd)
{
	struct pci_dev *pdev = NULL;
	int found = 0;

	/* IO9: Look for a QLogic ISP 12160 at the same bus and slot 3. */
	do {
		pdev = pci_get_device(PCI_VENDOR_ID_QLOGIC,
				      PCI_DEVICE_ID_QLOGIC_ISP12160, pdev);
		if (pdev &&
		    idd->idd_pdev->bus->number == pdev->bus->number &&
		    3 == PCI_SLOT(pdev->devfn))
			found = 1;
	} while (pdev && !found);
	if (NULL != pdev) {
		pci_dev_put(pdev);
		return IOC4_VARIANT_IO9;
	}

	/* IO10: Look for a Vitesse VSC 7174 at the same bus and slot 3. */
	pdev = NULL;
	do {
		pdev = pci_get_device(PCI_VENDOR_ID_VITESSE,
				      PCI_DEVICE_ID_VITESSE_VSC7174, pdev);
		if (pdev &&
		    idd->idd_pdev->bus->number == pdev->bus->number &&
		    3 == PCI_SLOT(pdev->devfn))
			found = 1;
	} while (pdev && !found);
	if (NULL != pdev) {
		pci_dev_put(pdev);
		return IOC4_VARIANT_IO10;
	}

	/* PCI-RT: No SCSI/SATA controller will be present */
	return IOC4_VARIANT_PCI_RT;
}