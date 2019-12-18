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
 int /*<<< orphan*/  device_init_wakeup (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gpio_direction_output (scalar_t__,int) ; 
 int /*<<< orphan*/  gpio_free (scalar_t__) ; 
 int /*<<< orphan*/  platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  usb_hcd_at91_remove (int /*<<< orphan*/ ,struct platform_device*) ; 

__attribute__((used)) static int ohci_hcd_at91_drv_remove(struct platform_device *pdev)
{
	struct at91_usbh_data	*pdata = pdev->dev.platform_data;
	int			i;

	if (pdata) {
		for (i = 0; i < ARRAY_SIZE(pdata->vbus_pin); i++) {
			if (pdata->vbus_pin[i] <= 0)
				continue;
			gpio_direction_output(pdata->vbus_pin[i], 1);
			gpio_free(pdata->vbus_pin[i]);
		}
	}

	device_init_wakeup(&pdev->dev, 0);
	usb_hcd_at91_remove(platform_get_drvdata(pdev), pdev);
	return 0;
}