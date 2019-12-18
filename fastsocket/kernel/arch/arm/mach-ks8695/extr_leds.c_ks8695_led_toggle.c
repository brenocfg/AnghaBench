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

/* Variables and functions */
 unsigned long gpio_get_value (unsigned int) ; 
 int /*<<< orphan*/  ks8695_led_off (unsigned int) ; 
 int /*<<< orphan*/  ks8695_led_on (unsigned int) ; 

__attribute__((used)) static inline void ks8695_led_toggle(unsigned int led)
{
	unsigned long is_off = gpio_get_value(led);
	if (is_off)
		ks8695_led_on(led);
	else
		ks8695_led_off(led);
}