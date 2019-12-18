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
struct usb_hcd {void* rsrc_len; void* rsrc_start; int /*<<< orphan*/ * regs; } ;
struct pci_device_id {scalar_t__ driver_data; } ;
struct pci_dev {int irq; int /*<<< orphan*/  dev; int /*<<< orphan*/  current_state; } ;
struct hc_driver {int flags; int /*<<< orphan*/  description; } ;

/* Variables and functions */
 int EBUSY ; 
 int EFAULT ; 
 int EINVAL ; 
 int ENODEV ; 
 int ENOMEM ; 
 int HCD_MASK ; 
 int HCD_MEMORY ; 
 int HCD_USB3 ; 
 int IORESOURCE_IO ; 
 int IRQF_DISABLED ; 
 int IRQF_SHARED ; 
 int /*<<< orphan*/  PCI_D0 ; 
 int PCI_ROM_RESOURCE ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/ * ioremap_nocache (void*,void*) ; 
 int /*<<< orphan*/  iounmap (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pci_disable_device (struct pci_dev*) ; 
 scalar_t__ pci_enable_device (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_name (struct pci_dev*) ; 
 int pci_resource_flags (struct pci_dev*,int) ; 
 void* pci_resource_len (struct pci_dev*,int) ; 
 void* pci_resource_start (struct pci_dev*,int) ; 
 int /*<<< orphan*/  pci_set_master (struct pci_dev*) ; 
 int /*<<< orphan*/  release_mem_region (void*,void*) ; 
 int /*<<< orphan*/  release_region (void*,void*) ; 
 int /*<<< orphan*/  request_mem_region (void*,void*,int /*<<< orphan*/ ) ; 
 scalar_t__ request_region (void*,void*,int /*<<< orphan*/ ) ; 
 int usb_add_hcd (struct usb_hcd*,int,int) ; 
 struct usb_hcd* usb_create_hcd (struct hc_driver*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ usb_disabled () ; 
 int /*<<< orphan*/  usb_put_hcd (struct usb_hcd*) ; 

int usb_hcd_pci_probe(struct pci_dev *dev, const struct pci_device_id *id)
{
	struct hc_driver	*driver;
	struct usb_hcd		*hcd;
	int			retval;
	int			hcd_irq = 0;

	if (usb_disabled())
		return -ENODEV;

	if (!id)
		return -EINVAL;
	driver = (struct hc_driver *)id->driver_data;
	if (!driver)
		return -EINVAL;

	if (pci_enable_device(dev) < 0)
		return -ENODEV;
	dev->current_state = PCI_D0;

	/*
	 * The xHCI driver has its own irq management
	 * make sure irq setup is not touched for xhci in generic hcd code
	 */
	if ((driver->flags & HCD_MASK) != HCD_USB3) {
		if (!dev->irq) {
			dev_err(&dev->dev,
			"Found HC with no IRQ. Check BIOS/PCI %s setup!\n",
				pci_name(dev));
			retval = -ENODEV;
			goto err1;
		}
		hcd_irq = dev->irq;
	}

	hcd = usb_create_hcd(driver, &dev->dev, pci_name(dev));
	if (!hcd) {
		retval = -ENOMEM;
		goto err1;
	}

	if (driver->flags & HCD_MEMORY) {
		/* EHCI, OHCI */
		hcd->rsrc_start = pci_resource_start(dev, 0);
		hcd->rsrc_len = pci_resource_len(dev, 0);
		if (!request_mem_region(hcd->rsrc_start, hcd->rsrc_len,
				driver->description)) {
			dev_dbg(&dev->dev, "controller already in use\n");
			retval = -EBUSY;
			goto err2;
		}
		hcd->regs = ioremap_nocache(hcd->rsrc_start, hcd->rsrc_len);
		if (hcd->regs == NULL) {
			dev_dbg(&dev->dev, "error mapping memory\n");
			retval = -EFAULT;
			goto err3;
		}

	} else {
		/* UHCI */
		int	region;

		for (region = 0; region < PCI_ROM_RESOURCE; region++) {
			if (!(pci_resource_flags(dev, region) &
					IORESOURCE_IO))
				continue;

			hcd->rsrc_start = pci_resource_start(dev, region);
			hcd->rsrc_len = pci_resource_len(dev, region);
			if (request_region(hcd->rsrc_start, hcd->rsrc_len,
					driver->description))
				break;
		}
		if (region == PCI_ROM_RESOURCE) {
			dev_dbg(&dev->dev, "no i/o regions available\n");
			retval = -EBUSY;
			goto err1;
		}
	}

	pci_set_master(dev);

	retval = usb_add_hcd(hcd, hcd_irq, IRQF_DISABLED | IRQF_SHARED);
	if (retval != 0)
		goto err4;
	return retval;

 err4:
	if (driver->flags & HCD_MEMORY) {
		iounmap(hcd->regs);
 err3:
		release_mem_region(hcd->rsrc_start, hcd->rsrc_len);
	} else
		release_region(hcd->rsrc_start, hcd->rsrc_len);
 err2:
	usb_put_hcd(hcd);
 err1:
	pci_disable_device(dev);
	dev_err(&dev->dev, "init %s fail, %d\n", pci_name(dev), retval);
	return retval;
}