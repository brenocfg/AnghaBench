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
struct timer_trig_data {int /*<<< orphan*/  timer; } ;
struct led_classdev {int /*<<< orphan*/  (* blink_set ) (struct led_classdev*,unsigned long*,unsigned long*) ;int /*<<< orphan*/  dev; struct timer_trig_data* trigger_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  del_timer_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_attr_delay_off ; 
 int /*<<< orphan*/  dev_attr_delay_on ; 
 int /*<<< orphan*/  device_remove_file (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct timer_trig_data*) ; 
 int /*<<< orphan*/  stub1 (struct led_classdev*,unsigned long*,unsigned long*) ; 

__attribute__((used)) static void timer_trig_deactivate(struct led_classdev *led_cdev)
{
	struct timer_trig_data *timer_data = led_cdev->trigger_data;
	unsigned long on = 0, off = 0;

	if (timer_data) {
		device_remove_file(led_cdev->dev, &dev_attr_delay_on);
		device_remove_file(led_cdev->dev, &dev_attr_delay_off);
		del_timer_sync(&timer_data->timer);
		kfree(timer_data);
	}

	/* If there is hardware support for blinking, stop it */
	if (led_cdev->blink_set)
		led_cdev->blink_set(led_cdev, &on, &off);
}