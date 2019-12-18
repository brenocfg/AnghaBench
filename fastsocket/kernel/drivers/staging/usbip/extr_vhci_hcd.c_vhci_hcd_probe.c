#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct usb_hcd {int dummy; } ;
struct TYPE_4__ {scalar_t__ dma_mask; } ;
struct platform_device {TYPE_1__ dev; int /*<<< orphan*/  id; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  dev_info (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  dev_name (TYPE_1__*) ; 
 int /*<<< orphan*/ * hcd_to_vhci (struct usb_hcd*) ; 
 int /*<<< orphan*/ * the_controller ; 
 int usb_add_hcd (struct usb_hcd*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct usb_hcd* usb_create_hcd (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_put_hcd (struct usb_hcd*) ; 
 int /*<<< orphan*/  usbip_dbg_vhci_hc (char*,...) ; 
 int /*<<< orphan*/  usbip_uerr (char*,...) ; 
 int /*<<< orphan*/  usbip_uinfo (char*) ; 
 int /*<<< orphan*/  vhci_hc_driver ; 

__attribute__((used)) static int vhci_hcd_probe(struct platform_device *pdev)
{
	struct usb_hcd		*hcd;
	int			ret;

	usbip_uinfo("proving...\n");

	usbip_dbg_vhci_hc("name %s id %d\n", pdev->name, pdev->id);

	/* will be removed */
	if (pdev->dev.dma_mask) {
		dev_info(&pdev->dev, "vhci_hcd DMA not supported\n");
		return -EINVAL;
	}

	/*
	 * Allocate and initialize hcd.
	 * Our private data is also allocated automatically.
	 */
	hcd = usb_create_hcd(&vhci_hc_driver, &pdev->dev, dev_name(&pdev->dev));
	if (!hcd) {
		usbip_uerr("create hcd failed\n");
		return -ENOMEM;
	}


	/* this is private data for vhci_hcd */
	the_controller = hcd_to_vhci(hcd);

	/*
	 * Finish generic HCD structure initialization and register.
	 * Call the driver's reset() and start() routines.
	 */
	ret = usb_add_hcd(hcd, 0, 0);
	if (ret != 0) {
		usbip_uerr("usb_add_hcd failed %d\n", ret);
		usb_put_hcd(hcd);
		the_controller = NULL;
		return ret;
	}


	usbip_dbg_vhci_hc("bye\n");
	return 0;
}