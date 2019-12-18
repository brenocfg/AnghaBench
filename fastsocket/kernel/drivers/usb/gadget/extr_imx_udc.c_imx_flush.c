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
struct imx_udc_struct {scalar_t__ base; } ;
struct imx_ep_struct {struct imx_udc_struct* imx_usb; } ;

/* Variables and functions */
 int EPSTAT_FLUSH ; 
 int /*<<< orphan*/  EP_NO (struct imx_ep_struct*) ; 
 scalar_t__ USB_EP_STAT (int /*<<< orphan*/ ) ; 
 int __raw_readl (scalar_t__) ; 
 int /*<<< orphan*/  __raw_writel (int,scalar_t__) ; 

void imx_flush(struct imx_ep_struct *imx_ep)
{
	struct imx_udc_struct *imx_usb = imx_ep->imx_usb;

	int temp = __raw_readl(imx_usb->base + USB_EP_STAT(EP_NO(imx_ep)));
	__raw_writel(temp | EPSTAT_FLUSH,
		imx_usb->base + USB_EP_STAT(EP_NO(imx_ep)));
}