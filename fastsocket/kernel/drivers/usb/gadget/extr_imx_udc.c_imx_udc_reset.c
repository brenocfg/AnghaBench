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

/* Variables and functions */
 int DADR_CFG ; 
 int ENAB_RST ; 
 scalar_t__ USB_DADR ; 
 scalar_t__ USB_ENAB ; 
 int __raw_readl (scalar_t__) ; 
 int /*<<< orphan*/  __raw_writel (int,scalar_t__) ; 

void imx_udc_reset(struct imx_udc_struct *imx_usb)
{
	int temp = __raw_readl(imx_usb->base + USB_ENAB);

	/* set RST bit */
	__raw_writel(temp | ENAB_RST, imx_usb->base + USB_ENAB);

	/* wait RST bit to clear */
	do {} while (__raw_readl(imx_usb->base + USB_ENAB) & ENAB_RST);

	/* wait CFG bit to assert */
	do {} while (!(__raw_readl(imx_usb->base + USB_DADR) & DADR_CFG));

	/* udc module is now ready */
}