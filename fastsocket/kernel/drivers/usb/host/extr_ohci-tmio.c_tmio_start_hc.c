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
struct usb_hcd {unsigned long rsrc_start; int /*<<< orphan*/  irq; } ;
struct tmio_hcd {scalar_t__ ccr; } ;
struct platform_device {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 scalar_t__ CCR_BASE ; 
 scalar_t__ CCR_ILME ; 
 scalar_t__ CCR_INTC ; 
 scalar_t__ CCR_REVID ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,unsigned long,int /*<<< orphan*/ ) ; 
 struct tmio_hcd* hcd_to_tmio (struct usb_hcd*) ; 
 struct usb_hcd* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  tmio_ioread8 (scalar_t__) ; 
 int /*<<< orphan*/  tmio_iowrite16 (unsigned long,scalar_t__) ; 
 int /*<<< orphan*/  tmio_iowrite8 (int,scalar_t__) ; 
 int /*<<< orphan*/  tmio_write_pm (struct platform_device*) ; 

__attribute__((used)) static void tmio_start_hc(struct platform_device *dev)
{
	struct usb_hcd *hcd = platform_get_drvdata(dev);
	struct tmio_hcd *tmio = hcd_to_tmio(hcd);
	unsigned long base = hcd->rsrc_start;

	tmio_write_pm(dev);
	tmio_iowrite16(base, tmio->ccr + CCR_BASE);
	tmio_iowrite16(base >> 16, tmio->ccr + CCR_BASE + 2);
	tmio_iowrite8(1, tmio->ccr + CCR_ILME);
	tmio_iowrite8(2, tmio->ccr + CCR_INTC);

	dev_info(&dev->dev, "revision %d @ 0x%08llx, irq %d\n",
			tmio_ioread8(tmio->ccr + CCR_REVID), hcd->rsrc_start, hcd->irq);
}