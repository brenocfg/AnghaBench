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
struct usb_hcd {TYPE_1__* driver; } ;
struct pci_dev {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* shutdown ) (struct usb_hcd*) ;} ;

/* Variables and functions */
 struct usb_hcd* pci_get_drvdata (struct pci_dev*) ; 
 int /*<<< orphan*/  stub1 (struct usb_hcd*) ; 

void usb_hcd_pci_shutdown(struct pci_dev *dev)
{
	struct usb_hcd		*hcd;

	hcd = pci_get_drvdata(dev);
	if (!hcd)
		return;

	if (hcd->driver->shutdown)
		hcd->driver->shutdown(hcd);
}