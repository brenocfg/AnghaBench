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
struct acpi_device {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  work; int /*<<< orphan*/  led_classdev; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  flush_work (int /*<<< orphan*/ *) ; 
 TYPE_1__ hpled_led ; 
 int /*<<< orphan*/  led_classdev_unregister (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lis3_dev ; 
 int /*<<< orphan*/  lis3lv02d_joystick_disable () ; 
 int /*<<< orphan*/  lis3lv02d_poweroff (int /*<<< orphan*/ *) ; 
 int lis3lv02d_remove_fs (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int lis3lv02d_remove(struct acpi_device *device, int type)
{
	if (!device)
		return -EINVAL;

	lis3lv02d_joystick_disable();
	lis3lv02d_poweroff(&lis3_dev);

	led_classdev_unregister(&hpled_led.led_classdev);
	flush_work(&hpled_led.work);

	return lis3lv02d_remove_fs(&lis3_dev);
}