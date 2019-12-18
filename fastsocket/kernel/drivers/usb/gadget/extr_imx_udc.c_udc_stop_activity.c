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
struct usb_gadget_driver {int /*<<< orphan*/  (* disconnect ) (TYPE_1__*) ;} ;
struct TYPE_2__ {scalar_t__ speed; } ;
struct imx_udc_struct {TYPE_1__ gadget; scalar_t__ alt; scalar_t__ intf; scalar_t__ cfg; struct imx_ep_struct* imx_ep; } ;
struct imx_ep_struct {int stopped; } ;

/* Variables and functions */
 int /*<<< orphan*/  ESHUTDOWN ; 
 int IMX_USB_NB_EP ; 
 scalar_t__ USB_SPEED_UNKNOWN ; 
 int /*<<< orphan*/  imx_ep_irq_disable (struct imx_ep_struct*) ; 
 int /*<<< orphan*/  imx_flush (struct imx_ep_struct*) ; 
 int /*<<< orphan*/  nuke (struct imx_ep_struct*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (TYPE_1__*) ; 

__attribute__((used)) static void udc_stop_activity(struct imx_udc_struct *imx_usb,
					struct usb_gadget_driver *driver)
{
	struct imx_ep_struct *imx_ep;
	int i;

	if (imx_usb->gadget.speed == USB_SPEED_UNKNOWN)
		driver = NULL;

	/* prevent new request submissions, kill any outstanding requests  */
	for (i = 1; i < IMX_USB_NB_EP; i++) {
		imx_ep = &imx_usb->imx_ep[i];
		imx_flush(imx_ep);
		imx_ep->stopped = 1;
		imx_ep_irq_disable(imx_ep);
		nuke(imx_ep, -ESHUTDOWN);
	}

	imx_usb->cfg = 0;
	imx_usb->intf = 0;
	imx_usb->alt = 0;

	if (driver)
		driver->disconnect(&imx_usb->gadget);
}