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
struct imx_udc_struct {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  imx_udc_config (struct imx_udc_struct*) ; 
 int /*<<< orphan*/  imx_udc_init_ep (struct imx_udc_struct*) ; 
 int /*<<< orphan*/  imx_udc_init_fifo (struct imx_udc_struct*) ; 
 int /*<<< orphan*/  imx_udc_init_irq (struct imx_udc_struct*) ; 
 int /*<<< orphan*/  imx_udc_reset (struct imx_udc_struct*) ; 

__attribute__((used)) static void imx_udc_init(struct imx_udc_struct *imx_usb)
{
	/* Reset UDC */
	imx_udc_reset(imx_usb);

	/* Download config to enpoint buffer */
	imx_udc_config(imx_usb);

	/* Setup interrups */
	imx_udc_init_irq(imx_usb);

	/* Setup endpoints */
	imx_udc_init_ep(imx_usb);

	/* Setup fifos */
	imx_udc_init_fifo(imx_usb);
}