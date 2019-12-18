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
struct usb_hcd {scalar_t__ rsrc_len; scalar_t__ rsrc_start; int /*<<< orphan*/  regs; } ;
struct TYPE_2__ {scalar_t__ start; scalar_t__ end; } ;
struct sa1111_dev {int /*<<< orphan*/ * irq; int /*<<< orphan*/  mapbase; TYPE_1__ res; int /*<<< orphan*/  dev; } ;
struct hc_driver {int dummy; } ;

/* Variables and functions */
 int EBUSY ; 
 int ENOMEM ; 
 int /*<<< orphan*/  IRQF_DISABLED ; 
 int /*<<< orphan*/  dbg (char*) ; 
 int /*<<< orphan*/  hcd_name ; 
 int /*<<< orphan*/  hcd_to_ohci (struct usb_hcd*) ; 
 int /*<<< orphan*/  ohci_hcd_init (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  release_mem_region (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  request_mem_region (scalar_t__,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sa1111_start_hc (struct sa1111_dev*) ; 
 int /*<<< orphan*/  sa1111_stop_hc (struct sa1111_dev*) ; 
 int usb_add_hcd (struct usb_hcd*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct usb_hcd* usb_create_hcd (struct hc_driver const*,int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  usb_put_hcd (struct usb_hcd*) ; 

int usb_hcd_sa1111_probe (const struct hc_driver *driver,
			  struct sa1111_dev *dev)
{
	struct usb_hcd *hcd;
	int retval;

	hcd = usb_create_hcd (driver, &dev->dev, "sa1111");
	if (!hcd)
		return -ENOMEM;
	hcd->rsrc_start = dev->res.start;
	hcd->rsrc_len = dev->res.end - dev->res.start + 1;

	if (!request_mem_region(hcd->rsrc_start, hcd->rsrc_len, hcd_name)) {
		dbg("request_mem_region failed");
		retval = -EBUSY;
		goto err1;
	}
	hcd->regs = dev->mapbase;

	sa1111_start_hc(dev);
	ohci_hcd_init(hcd_to_ohci(hcd));

	retval = usb_add_hcd(hcd, dev->irq[1], IRQF_DISABLED);
	if (retval == 0)
		return retval;

	sa1111_stop_hc(dev);
	release_mem_region(hcd->rsrc_start, hcd->rsrc_len);
 err1:
	usb_put_hcd(hcd);
	return retval;
}