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
struct imx_udc_struct {size_t ep0state; int /*<<< orphan*/  dev; } ;
typedef  enum ep0_state { ____Placeholder_ep0_state } ep0_state ;

/* Variables and functions */
 int /*<<< orphan*/  D_EP0 (int /*<<< orphan*/ ,char*,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * state_name ; 

void ep0_chg_stat(const char *label,
			struct imx_udc_struct *imx_usb, enum ep0_state stat)
{
	D_EP0(imx_usb->dev, "<%s> from %15s to %15s\n",
		label, state_name[imx_usb->ep0state], state_name[stat]);

	if (imx_usb->ep0state == stat)
		return;

	imx_usb->ep0state = stat;
}