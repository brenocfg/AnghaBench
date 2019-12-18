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
 int /*<<< orphan*/  led_classdev_unregister (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wrap_error_led ; 
 int /*<<< orphan*/  wrap_extra_led ; 
 int /*<<< orphan*/  wrap_power_led ; 

__attribute__((used)) static int wrap_led_remove(struct platform_device *pdev)
{
	led_classdev_unregister(&wrap_power_led);
	led_classdev_unregister(&wrap_error_led);
	led_classdev_unregister(&wrap_extra_led);
	return 0;
}