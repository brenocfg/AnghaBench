#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct usb_hcd {scalar_t__ rsrc_len; scalar_t__ rsrc_start; int /*<<< orphan*/  regs; } ;
struct TYPE_6__ {int /*<<< orphan*/  platform_data; } ;
struct platform_device {TYPE_1__* resource; TYPE_2__ dev; } ;
struct hc_driver {int dummy; } ;
struct TYPE_5__ {scalar_t__ start; scalar_t__ end; } ;

/* Variables and functions */
 int EBUSY ; 
 int ENOENT ; 
 int ENOMEM ; 
 int /*<<< orphan*/  IRQF_DISABLED ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clk ; 
 int /*<<< orphan*/  clk_get (TYPE_2__*,char*) ; 
 int /*<<< orphan*/  clk_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (TYPE_2__*,char*) ; 
 int /*<<< orphan*/  hcd_name ; 
 int /*<<< orphan*/  hcd_to_ohci (struct usb_hcd*) ; 
 int /*<<< orphan*/  ioremap (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  iounmap (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ohci_hcd_init (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  release_mem_region (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  request_mem_region (scalar_t__,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  s3c2410_start_hc (struct platform_device*,struct usb_hcd*) ; 
 int /*<<< orphan*/  s3c2410_stop_hc (struct platform_device*) ; 
 int /*<<< orphan*/  s3c2410_usb_set_power (int /*<<< orphan*/ ,int,int) ; 
 int usb_add_hcd (struct usb_hcd*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_clk ; 
 struct usb_hcd* usb_create_hcd (struct hc_driver const*,TYPE_2__*,char*) ; 
 int /*<<< orphan*/  usb_put_hcd (struct usb_hcd*) ; 

__attribute__((used)) static int usb_hcd_s3c2410_probe (const struct hc_driver *driver,
				  struct platform_device *dev)
{
	struct usb_hcd *hcd = NULL;
	int retval;

	s3c2410_usb_set_power(dev->dev.platform_data, 1, 1);
	s3c2410_usb_set_power(dev->dev.platform_data, 2, 1);

	hcd = usb_create_hcd(driver, &dev->dev, "s3c24xx");
	if (hcd == NULL)
		return -ENOMEM;

	hcd->rsrc_start = dev->resource[0].start;
	hcd->rsrc_len   = dev->resource[0].end - dev->resource[0].start + 1;

	if (!request_mem_region(hcd->rsrc_start, hcd->rsrc_len, hcd_name)) {
		dev_err(&dev->dev, "request_mem_region failed\n");
		retval = -EBUSY;
		goto err_put;
	}

	clk = clk_get(&dev->dev, "usb-host");
	if (IS_ERR(clk)) {
		dev_err(&dev->dev, "cannot get usb-host clock\n");
		retval = -ENOENT;
		goto err_mem;
	}

	usb_clk = clk_get(&dev->dev, "usb-bus-host");
	if (IS_ERR(usb_clk)) {
		dev_err(&dev->dev, "cannot get usb-bus-host clock\n");
		retval = -ENOENT;
		goto err_clk;
	}

	s3c2410_start_hc(dev, hcd);

	hcd->regs = ioremap(hcd->rsrc_start, hcd->rsrc_len);
	if (!hcd->regs) {
		dev_err(&dev->dev, "ioremap failed\n");
		retval = -ENOMEM;
		goto err_ioremap;
	}

	ohci_hcd_init(hcd_to_ohci(hcd));

	retval = usb_add_hcd(hcd, dev->resource[1].start, IRQF_DISABLED);
	if (retval != 0)
		goto err_ioremap;

	return 0;

 err_ioremap:
	s3c2410_stop_hc(dev);
	iounmap(hcd->regs);
	clk_put(usb_clk);

 err_clk:
	clk_put(clk);

 err_mem:
	release_mem_region(hcd->rsrc_start, hcd->rsrc_len);

 err_put:
	usb_put_hcd(hcd);
	return retval;
}