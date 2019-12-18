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
struct b43_led {int /*<<< orphan*/ * wl; int /*<<< orphan*/  led_dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  led_classdev_unregister (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void b43_unregister_led(struct b43_led *led)
{
	if (!led->wl)
		return;
	led_classdev_unregister(&led->led_dev);
	led->wl = NULL;
}