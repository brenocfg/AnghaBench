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
typedef  scalar_t__ u16 ;
struct pci_dev {scalar_t__ vendor; scalar_t__ device; } ;
struct bcma_device {TYPE_1__* bus; } ;
struct TYPE_2__ {struct pci_dev* host_pci; } ;

/* Variables and functions */
 scalar_t__ BCM4313_D11N2G_ID ; 
 scalar_t__ BCM43224_CHIP_ID ; 
 scalar_t__ BCM43224_D11N_ID ; 
 scalar_t__ BCM43224_D11N_ID_VEN1 ; 
 scalar_t__ BCM43225_D11N2G_ID ; 
 scalar_t__ BCM43236_D11N2G_ID ; 
 scalar_t__ BCM43236_D11N_ID ; 
 scalar_t__ PCI_VENDOR_ID_BROADCOM ; 
 int /*<<< orphan*/  pr_err (char*,scalar_t__) ; 

__attribute__((used)) static bool brcms_c_chipmatch_pci(struct bcma_device *core)
{
	struct pci_dev *pcidev = core->bus->host_pci;
	u16 vendor = pcidev->vendor;
	u16 device = pcidev->device;

	if (vendor != PCI_VENDOR_ID_BROADCOM) {
		pr_err("unknown vendor id %04x\n", vendor);
		return false;
	}

	if (device == BCM43224_D11N_ID_VEN1 || device == BCM43224_CHIP_ID)
		return true;
	if ((device == BCM43224_D11N_ID) || (device == BCM43225_D11N2G_ID))
		return true;
	if (device == BCM4313_D11N2G_ID)
		return true;
	if ((device == BCM43236_D11N_ID) || (device == BCM43236_D11N2G_ID))
		return true;

	pr_err("unknown device id %04x\n", device);
	return false;
}