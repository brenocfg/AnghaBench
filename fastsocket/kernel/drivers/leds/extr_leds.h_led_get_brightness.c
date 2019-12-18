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
struct led_classdev {int brightness; } ;

/* Variables and functions */

__attribute__((used)) static inline int led_get_brightness(struct led_classdev *led_cdev)
{
	return led_cdev->brightness;
}