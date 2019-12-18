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
struct TYPE_2__ {struct at91_usbh_data* platform_data; } ;
struct platform_device {TYPE_1__ dev; } ;
struct at91_usbh_data {scalar_t__* vbus_pin; } ;

/* Variables and functions */
 int ARRAY_SIZE (scalar_t__*) ; 
 int /*<<< orphan*/  device_init_wakeup (TYPE_1__*,int) ; 
 int /*<<< orphan*/  gpio_direction_output (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gpio_request (scalar_t__,char*) ; 
 int /*<<< orphan*/  ohci_at91_hc_driver ; 
 int usb_hcd_at91_probe (int /*<<< orphan*/ *,struct platform_device*) ; 

__attribute__((used)) static int ohci_hcd_at91_drv_probe(struct platform_device *pdev)
{
	struct at91_usbh_data	*pdata = pdev->dev.platform_data;
	int			i;

	if (pdata) {
		/* REVISIT make the driver support per-port power switching,
		 * and also overcurrent detection.  Here we assume the ports
		 * are always powered while this driver is active, and use
		 * active-low power switches.
		 */
		for (i = 0; i < ARRAY_SIZE(pdata->vbus_pin); i++) {
			if (pdata->vbus_pin[i] <= 0)
				continue;
			gpio_request(pdata->vbus_pin[i], "ohci_vbus");
			gpio_direction_output(pdata->vbus_pin[i], 0);
		}
	}

	device_init_wakeup(&pdev->dev, 1);
	return usb_hcd_at91_probe(&ohci_at91_hc_driver, pdev);
}