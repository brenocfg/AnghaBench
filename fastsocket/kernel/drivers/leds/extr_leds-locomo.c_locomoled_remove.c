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
struct locomo_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  led_classdev_unregister (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  locomo_led0 ; 
 int /*<<< orphan*/  locomo_led1 ; 

__attribute__((used)) static int locomoled_remove(struct locomo_dev *dev)
{
	led_classdev_unregister(&locomo_led0);
	led_classdev_unregister(&locomo_led1);
	return 0;
}