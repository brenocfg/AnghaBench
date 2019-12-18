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
struct pci_dev {int subsystem_device; int device; scalar_t__ subsystem_vendor; } ;

/* Variables and functions */
 int ENODEV ; 
#define  PCI_DEVICE_ID_NETMOS_9900 131 
 int PCI_DEVICE_ID_NETMOS_9901 ; 
#define  PCI_DEVICE_ID_NETMOS_9904 130 
#define  PCI_DEVICE_ID_NETMOS_9912 129 
#define  PCI_DEVICE_ID_NETMOS_9922 128 
 scalar_t__ PCI_VENDOR_ID_IBM ; 
 int /*<<< orphan*/  moan_device (char*,struct pci_dev*) ; 
 unsigned int pci_netmos_9900_numports (struct pci_dev*) ; 

__attribute__((used)) static int pci_netmos_init(struct pci_dev *dev)
{
	/* subdevice 0x00PS means <P> parallel, <S> serial */
	unsigned int num_serial = dev->subsystem_device & 0xf;

	if (dev->device == PCI_DEVICE_ID_NETMOS_9901)
		return 0;

	if (dev->subsystem_vendor == PCI_VENDOR_ID_IBM &&
			dev->subsystem_device == 0x0299)
		return 0;

	switch (dev->device) { /* FALLTHROUGH on all */
		case PCI_DEVICE_ID_NETMOS_9904:
		case PCI_DEVICE_ID_NETMOS_9912:
		case PCI_DEVICE_ID_NETMOS_9922:
		case PCI_DEVICE_ID_NETMOS_9900:
			num_serial = pci_netmos_9900_numports(dev);
			break;

		default:
			if (num_serial == 0 ) {
				moan_device("unknown NetMos/Mostech device", dev);
			}
	}

	if (num_serial == 0)
		return -ENODEV;

	return num_serial;
}