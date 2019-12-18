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

/* Variables and functions */
 int /*<<< orphan*/  clk_disable (scalar_t__) ; 
 int /*<<< orphan*/  clk_put (scalar_t__) ; 
 scalar_t__ mxc_ahb_clk ; 
 scalar_t__ mxc_usb_clk ; 

void fsl_udc_clk_release(void)
{
	if (mxc_usb_clk) {
		clk_disable(mxc_usb_clk);
		clk_put(mxc_usb_clk);
	}
	clk_disable(mxc_ahb_clk);
	clk_put(mxc_ahb_clk);
}