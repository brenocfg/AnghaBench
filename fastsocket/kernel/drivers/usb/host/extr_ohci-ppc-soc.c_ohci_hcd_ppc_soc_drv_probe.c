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
struct platform_device {int dummy; } ;

/* Variables and functions */
 int ENODEV ; 
 int /*<<< orphan*/  ohci_ppc_soc_hc_driver ; 
 scalar_t__ usb_disabled () ; 
 int usb_hcd_ppc_soc_probe (int /*<<< orphan*/ *,struct platform_device*) ; 

__attribute__((used)) static int ohci_hcd_ppc_soc_drv_probe(struct platform_device *pdev)
{
	int ret;

	if (usb_disabled())
		return -ENODEV;

	ret = usb_hcd_ppc_soc_probe(&ohci_ppc_soc_hc_driver, pdev);
	return ret;
}