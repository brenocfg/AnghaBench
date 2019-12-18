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
 int /*<<< orphan*/  fsg_ring_led ; 
 int /*<<< orphan*/  fsg_sata_led ; 
 int /*<<< orphan*/  fsg_sync_led ; 
 int /*<<< orphan*/  fsg_usb_led ; 
 int /*<<< orphan*/  fsg_wan_led ; 
 int /*<<< orphan*/  fsg_wlan_led ; 
 int /*<<< orphan*/  iounmap (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  latch_address ; 
 int /*<<< orphan*/  led_classdev_unregister (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int fsg_led_remove(struct platform_device *pdev)
{
	led_classdev_unregister(&fsg_wlan_led);
	led_classdev_unregister(&fsg_wan_led);
	led_classdev_unregister(&fsg_sata_led);
	led_classdev_unregister(&fsg_usb_led);
	led_classdev_unregister(&fsg_sync_led);
	led_classdev_unregister(&fsg_ring_led);

	iounmap(latch_address);

	return 0;
}