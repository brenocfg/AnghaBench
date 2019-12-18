#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {struct fsl_usb2_platform_data* platform_data; } ;
struct platform_device {TYPE_1__ dev; } ;
struct fsl_usb2_platform_data {scalar_t__ phy_mode; } ;

/* Variables and functions */
 scalar_t__ FSL_USB2_PHY_ULPI ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ *) ; 
 int PTR_ERR (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  clk_disable (int /*<<< orphan*/ *) ; 
 int clk_enable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * clk_get (TYPE_1__*,char*) ; 
 unsigned long clk_get_rate (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  clk_put (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_err (TYPE_1__*,char*,...) ; 
 int /*<<< orphan*/ * mxc_ahb_clk ; 
 int /*<<< orphan*/ * mxc_usb_clk ; 

int fsl_udc_clk_init(struct platform_device *pdev)
{
	struct fsl_usb2_platform_data *pdata;
	unsigned long freq;
	int ret;

	pdata = pdev->dev.platform_data;

	mxc_ahb_clk = clk_get(&pdev->dev, "usb_ahb");
	if (IS_ERR(mxc_ahb_clk))
		return PTR_ERR(mxc_ahb_clk);

	ret = clk_enable(mxc_ahb_clk);
	if (ret < 0) {
		dev_err(&pdev->dev, "clk_enable(\"usb_ahb\") failed\n");
		goto eenahb;
	}

	/* make sure USB_CLK is running at 60 MHz +/- 1000 Hz */
	mxc_usb_clk = clk_get(&pdev->dev, "usb");
	if (IS_ERR(mxc_usb_clk)) {
		dev_err(&pdev->dev, "clk_get(\"usb\") failed\n");
		ret = PTR_ERR(mxc_usb_clk);
		goto egusb;
	}

	freq = clk_get_rate(mxc_usb_clk);
	if (pdata->phy_mode != FSL_USB2_PHY_ULPI &&
	    (freq < 59999000 || freq > 60001000)) {
		dev_err(&pdev->dev, "USB_CLK=%lu, should be 60MHz\n", freq);
		goto eclkrate;
	}

	ret = clk_enable(mxc_usb_clk);
	if (ret < 0) {
		dev_err(&pdev->dev, "clk_enable(\"usb_clk\") failed\n");
		goto eenusb;
	}

	return 0;

eenusb:
eclkrate:
	clk_put(mxc_usb_clk);
	mxc_usb_clk = NULL;
egusb:
	clk_disable(mxc_ahb_clk);
eenahb:
	clk_put(mxc_ahb_clk);
	return ret;
}