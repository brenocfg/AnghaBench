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
struct pci_dev {int /*<<< orphan*/  devfn; TYPE_1__* bus; } ;
struct device {int dummy; } ;
struct acpi_device_info {int valid; scalar_t__ address; } ;
typedef  int /*<<< orphan*/  acpi_status ;
typedef  scalar_t__ acpi_integer ;
typedef  scalar_t__ acpi_handle ;
struct TYPE_2__ {unsigned int number; } ;

/* Variables and functions */
 scalar_t__ ACPI_FAILURE (int /*<<< orphan*/ ) ; 
 int ACPI_VALID_ADR ; 
 int /*<<< orphan*/  DEBPRINT (char*,...) ; 
 scalar_t__ DEVICE_ACPI_HANDLE (struct device*) ; 
 int ENODEV ; 
 unsigned int PCI_FUNC (int /*<<< orphan*/ ) ; 
 unsigned int PCI_SLOT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  acpi_get_object_info (scalar_t__,struct acpi_device_info**) ; 
 int /*<<< orphan*/  kfree (struct acpi_device_info*) ; 
 struct pci_dev* to_pci_dev (struct device*) ; 

__attribute__((used)) static int ide_get_dev_handle(struct device *dev, acpi_handle *handle,
			       acpi_integer *pcidevfn)
{
	struct pci_dev *pdev = to_pci_dev(dev);
	unsigned int bus, devnum, func;
	acpi_integer addr;
	acpi_handle dev_handle;
	acpi_status status;
	struct acpi_device_info	*dinfo = NULL;
	int ret = -ENODEV;

	bus = pdev->bus->number;
	devnum = PCI_SLOT(pdev->devfn);
	func = PCI_FUNC(pdev->devfn);
	/* ACPI _ADR encoding for PCI bus: */
	addr = (acpi_integer)(devnum << 16 | func);

	DEBPRINT("ENTER: pci %02x:%02x.%01x\n", bus, devnum, func);

	dev_handle = DEVICE_ACPI_HANDLE(dev);
	if (!dev_handle) {
		DEBPRINT("no acpi handle for device\n");
		goto err;
	}

	status = acpi_get_object_info(dev_handle, &dinfo);
	if (ACPI_FAILURE(status)) {
		DEBPRINT("get_object_info for device failed\n");
		goto err;
	}
	if (dinfo && (dinfo->valid & ACPI_VALID_ADR) &&
	    dinfo->address == addr) {
		*pcidevfn = addr;
		*handle = dev_handle;
	} else {
		DEBPRINT("get_object_info for device has wrong "
			" address: %llu, should be %u\n",
			dinfo ? (unsigned long long)dinfo->address : -1ULL,
			(unsigned int)addr);
		goto err;
	}

	DEBPRINT("for dev=0x%x.%x, addr=0x%llx, *handle=0x%p\n",
		 devnum, func, (unsigned long long)addr, *handle);
	ret = 0;
err:
	kfree(dinfo);
	return ret;
}