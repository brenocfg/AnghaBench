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
struct led_timer {int /*<<< orphan*/  list; int /*<<< orphan*/  blink_timer; } ;
struct led_classdev {int /*<<< orphan*/  node; int /*<<< orphan*/  dev; int /*<<< orphan*/  trigger_lock; scalar_t__ trigger; } ;

/* Variables and functions */
 int /*<<< orphan*/  del_timer_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_attr_brightness ; 
 int /*<<< orphan*/  dev_attr_max_brightness ; 
 int /*<<< orphan*/  dev_attr_trigger ; 
 int /*<<< orphan*/  device_remove_file (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  device_unregister (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  down_write (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct led_timer*) ; 
 struct led_timer* led_get_timer (struct led_classdev*) ; 
 int /*<<< orphan*/  led_lock ; 
 int /*<<< orphan*/  led_trigger_set (struct led_classdev*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  leds_list_lock ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  up_write (int /*<<< orphan*/ *) ; 

void led_classdev_unregister(struct led_classdev *led_cdev)
{
	struct led_timer *led = led_get_timer(led_cdev);
	unsigned long flags;

	if (led) {
		del_timer_sync(&led->blink_timer);
		spin_lock_irqsave(&led_lock, flags);
		list_del(&led->list);
		spin_unlock_irqrestore(&led_lock, flags);
		kfree(led);
	}

	device_remove_file(led_cdev->dev, &dev_attr_max_brightness);
	device_remove_file(led_cdev->dev, &dev_attr_brightness);
#ifdef CONFIG_LEDS_TRIGGERS
	device_remove_file(led_cdev->dev, &dev_attr_trigger);
	down_write(&led_cdev->trigger_lock);
	if (led_cdev->trigger)
		led_trigger_set(led_cdev, NULL);
	up_write(&led_cdev->trigger_lock);
#endif

	device_unregister(led_cdev->dev);

	down_write(&leds_list_lock);
	list_del(&led_cdev->node);
	up_write(&leds_list_lock);
}