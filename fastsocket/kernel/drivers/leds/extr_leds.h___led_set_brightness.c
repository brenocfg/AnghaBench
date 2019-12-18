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
struct led_classdev {int max_brightness; int brightness; int flags; int /*<<< orphan*/  (* brightness_set ) (struct led_classdev*,int) ;} ;
typedef  enum led_brightness { ____Placeholder_led_brightness } led_brightness ;

/* Variables and functions */
 int LED_SUSPENDED ; 
 int /*<<< orphan*/  stub1 (struct led_classdev*,int) ; 

__attribute__((used)) static inline void __led_set_brightness(struct led_classdev *led_cdev,
					enum led_brightness value)
{
	if (value > led_cdev->max_brightness)
		value = led_cdev->max_brightness;
	led_cdev->brightness = value;
	if (!(led_cdev->flags & LED_SUSPENDED))
		led_cdev->brightness_set(led_cdev, value);
}