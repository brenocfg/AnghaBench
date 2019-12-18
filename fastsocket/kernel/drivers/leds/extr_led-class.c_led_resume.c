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
struct led_classdev {int flags; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int LED_CORE_SUSPENDRESUME ; 
 struct led_classdev* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  led_classdev_resume (struct led_classdev*) ; 

__attribute__((used)) static int led_resume(struct device *dev)
{
	struct led_classdev *led_cdev = dev_get_drvdata(dev);

	if (led_cdev->flags & LED_CORE_SUSPENDRESUME)
		led_classdev_resume(led_cdev);

	return 0;
}