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
struct s3c24xx_gpio_led {int /*<<< orphan*/  cdev; } ;
struct platform_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct s3c24xx_gpio_led*) ; 
 int /*<<< orphan*/  led_classdev_unregister (int /*<<< orphan*/ *) ; 
 struct s3c24xx_gpio_led* pdev_to_gpio (struct platform_device*) ; 

__attribute__((used)) static int s3c24xx_led_remove(struct platform_device *dev)
{
	struct s3c24xx_gpio_led *led = pdev_to_gpio(dev);

	led_classdev_unregister(&led->cdev);
	kfree(led);

	return 0;
}