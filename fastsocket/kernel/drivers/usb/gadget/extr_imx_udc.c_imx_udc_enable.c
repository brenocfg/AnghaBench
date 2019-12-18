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
struct TYPE_2__ {int /*<<< orphan*/  speed; } ;
struct imx_udc_struct {TYPE_1__ gadget; scalar_t__ base; } ;

/* Variables and functions */
 int CTRL_AFE_ENA ; 
 int CTRL_FE_ENA ; 
 scalar_t__ USB_CTRL ; 
 int /*<<< orphan*/  USB_SPEED_FULL ; 
 int __raw_readl (scalar_t__) ; 
 int /*<<< orphan*/  __raw_writel (int,scalar_t__) ; 

void imx_udc_enable(struct imx_udc_struct *imx_usb)
{
	int temp = __raw_readl(imx_usb->base + USB_CTRL);
	__raw_writel(temp | CTRL_FE_ENA | CTRL_AFE_ENA,
						imx_usb->base + USB_CTRL);
	imx_usb->gadget.speed = USB_SPEED_FULL;
}