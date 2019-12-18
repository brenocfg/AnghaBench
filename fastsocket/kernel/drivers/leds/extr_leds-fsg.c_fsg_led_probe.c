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
struct platform_device {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  IXP4XX_EXP_BUS_BASE (int) ; 
 int /*<<< orphan*/  fsg_ring_led ; 
 int /*<<< orphan*/  fsg_sata_led ; 
 int /*<<< orphan*/  fsg_sync_led ; 
 int /*<<< orphan*/  fsg_usb_led ; 
 int /*<<< orphan*/  fsg_wan_led ; 
 int /*<<< orphan*/  fsg_wlan_led ; 
 scalar_t__ ioremap (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  iounmap (int*) ; 
 int* latch_address ; 
 int latch_value ; 
 int led_classdev_register (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  led_classdev_unregister (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int fsg_led_probe(struct platform_device *pdev)
{
	int ret;

	/* Map the LED chip select address space */
	latch_address = (unsigned short *) ioremap(IXP4XX_EXP_BUS_BASE(2), 512);
	if (!latch_address) {
		ret = -ENOMEM;
		goto failremap;
	}

	latch_value = 0xffff;
	*latch_address = latch_value;

	ret = led_classdev_register(&pdev->dev, &fsg_wlan_led);
	if (ret < 0)
		goto failwlan;

	ret = led_classdev_register(&pdev->dev, &fsg_wan_led);
	if (ret < 0)
		goto failwan;

	ret = led_classdev_register(&pdev->dev, &fsg_sata_led);
	if (ret < 0)
		goto failsata;

	ret = led_classdev_register(&pdev->dev, &fsg_usb_led);
	if (ret < 0)
		goto failusb;

	ret = led_classdev_register(&pdev->dev, &fsg_sync_led);
	if (ret < 0)
		goto failsync;

	ret = led_classdev_register(&pdev->dev, &fsg_ring_led);
	if (ret < 0)
		goto failring;

	return ret;

 failring:
	led_classdev_unregister(&fsg_sync_led);
 failsync:
	led_classdev_unregister(&fsg_usb_led);
 failusb:
	led_classdev_unregister(&fsg_sata_led);
 failsata:
	led_classdev_unregister(&fsg_wan_led);
 failwan:
	led_classdev_unregister(&fsg_wlan_led);
 failwlan:
	iounmap(latch_address);
 failremap:

	return ret;
}