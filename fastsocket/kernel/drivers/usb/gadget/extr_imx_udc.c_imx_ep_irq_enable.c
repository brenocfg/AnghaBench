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
struct imx_ep_struct {TYPE_1__* imx_usb; } ;
struct TYPE_2__ {scalar_t__ base; } ;

/* Variables and functions */
 int EPINTR_EOF ; 
 int EPINTR_EOT ; 
 int EP_NO (struct imx_ep_struct*) ; 
 scalar_t__ USB_EP_INTR (int) ; 
 scalar_t__ USB_EP_MASK (int) ; 
 int /*<<< orphan*/  __raw_writel (int,scalar_t__) ; 

void imx_ep_irq_enable(struct imx_ep_struct *imx_ep)
{

	int i = EP_NO(imx_ep);

	__raw_writel(0x1FF, imx_ep->imx_usb->base + USB_EP_MASK(i));
	__raw_writel(0x1FF, imx_ep->imx_usb->base + USB_EP_INTR(i));
	__raw_writel(0x1FF & ~(EPINTR_EOT | EPINTR_EOF),
		imx_ep->imx_usb->base + USB_EP_MASK(i));
}