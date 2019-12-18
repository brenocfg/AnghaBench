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
typedef  int /*<<< orphan*/  u32 ;
struct usb_hcd {int /*<<< orphan*/  regs; int /*<<< orphan*/  rsrc_len; int /*<<< orphan*/  rsrc_start; } ;
struct ssb_ohci_device {int /*<<< orphan*/  enable_flags; } ;
struct TYPE_2__ {scalar_t__ coreid; } ;
struct ssb_device {int /*<<< orphan*/  irq; int /*<<< orphan*/  dev; TYPE_1__ id; } ;

/* Variables and functions */
 int ENOMEM ; 
 int IRQF_DISABLED ; 
 int IRQF_SHARED ; 
 int /*<<< orphan*/  SSB_ADMATCH0 ; 
 scalar_t__ SSB_DEV_USB11_HOSTDEV ; 
 int /*<<< orphan*/  SSB_OHCI_TMSLOW_HOSTMODE ; 
 int /*<<< orphan*/  dev_name (int /*<<< orphan*/ ) ; 
 struct ssb_ohci_device* hcd_to_ssb_ohci (struct usb_hcd*) ; 
 int /*<<< orphan*/  ioremap_nocache (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iounmap (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ssb_admatch_base (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ssb_admatch_size (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ssb_device_disable (struct ssb_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ssb_device_enable (struct ssb_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ssb_ohci_hc_driver ; 
 int /*<<< orphan*/  ssb_read32 (struct ssb_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ssb_set_drvdata (struct ssb_device*,struct usb_hcd*) ; 
 int usb_add_hcd (struct usb_hcd*,int /*<<< orphan*/ ,int) ; 
 struct usb_hcd* usb_create_hcd (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_put_hcd (struct usb_hcd*) ; 

__attribute__((used)) static int ssb_ohci_attach(struct ssb_device *dev)
{
	struct ssb_ohci_device *ohcidev;
	struct usb_hcd *hcd;
	int err = -ENOMEM;
	u32 tmp, flags = 0;

	if (dev->id.coreid == SSB_DEV_USB11_HOSTDEV)
		flags |= SSB_OHCI_TMSLOW_HOSTMODE;

	ssb_device_enable(dev, flags);

	hcd = usb_create_hcd(&ssb_ohci_hc_driver, dev->dev,
			dev_name(dev->dev));
	if (!hcd)
		goto err_dev_disable;
	ohcidev = hcd_to_ssb_ohci(hcd);
	ohcidev->enable_flags = flags;

	tmp = ssb_read32(dev, SSB_ADMATCH0);
	hcd->rsrc_start = ssb_admatch_base(tmp);
	hcd->rsrc_len = ssb_admatch_size(tmp);
	hcd->regs = ioremap_nocache(hcd->rsrc_start, hcd->rsrc_len);
	if (!hcd->regs)
		goto err_put_hcd;
	err = usb_add_hcd(hcd, dev->irq, IRQF_DISABLED | IRQF_SHARED);
	if (err)
		goto err_iounmap;

	ssb_set_drvdata(dev, hcd);

	return err;

err_iounmap:
	iounmap(hcd->regs);
err_put_hcd:
	usb_put_hcd(hcd);
err_dev_disable:
	ssb_device_disable(dev, flags);
	return err;
}