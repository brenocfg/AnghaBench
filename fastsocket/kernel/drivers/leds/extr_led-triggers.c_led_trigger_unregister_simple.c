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
struct led_trigger {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct led_trigger*) ; 
 int /*<<< orphan*/  led_trigger_unregister (struct led_trigger*) ; 

void led_trigger_unregister_simple(struct led_trigger *trigger)
{
	if (trigger)
		led_trigger_unregister(trigger);
	kfree(trigger);
}