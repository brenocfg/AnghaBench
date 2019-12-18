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
struct TYPE_2__ {struct fsl_usb2_platform_data* platform_data; } ;
struct platform_device {TYPE_1__ dev; } ;
struct fsl_usb2_platform_data {scalar_t__ phy_mode; } ;

/* Variables and functions */
 scalar_t__ FSL_USB2_PHY_ULPI ; 
 int /*<<< orphan*/  clk_disable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  clk_put (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * mxc_usb_clk ; 

void fsl_udc_clk_finalize(struct platform_device *pdev)
{
	struct fsl_usb2_platform_data *pdata = pdev->dev.platform_data;

	/* ULPI transceivers don't need usbpll */
	if (pdata->phy_mode == FSL_USB2_PHY_ULPI) {
		clk_disable(mxc_usb_clk);
		clk_put(mxc_usb_clk);
		mxc_usb_clk = NULL;
	}
}