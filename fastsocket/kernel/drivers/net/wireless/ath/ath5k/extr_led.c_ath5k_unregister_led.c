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
struct ath5k_led {int /*<<< orphan*/ * ah; int /*<<< orphan*/  led_dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  ath5k_led_off (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  led_classdev_unregister (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
ath5k_unregister_led(struct ath5k_led *led)
{
	if (!led->ah)
		return;
	led_classdev_unregister(&led->led_dev);
	ath5k_led_off(led->ah);
	led->ah = NULL;
}