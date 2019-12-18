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
struct locomo_dev {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int led_classdev_register (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  led_classdev_unregister (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  locomo_led0 ; 
 int /*<<< orphan*/  locomo_led1 ; 

__attribute__((used)) static int locomoled_probe(struct locomo_dev *ldev)
{
	int ret;

	ret = led_classdev_register(&ldev->dev, &locomo_led0);
	if (ret < 0)
		return ret;

	ret = led_classdev_register(&ldev->dev, &locomo_led1);
	if (ret < 0)
		led_classdev_unregister(&locomo_led0);

	return ret;
}