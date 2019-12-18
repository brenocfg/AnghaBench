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
 int /*<<< orphan*/  INT_MAX ; 
 int /*<<< orphan*/  LED_OFF ; 
 scalar_t__ ide_activity ; 
 scalar_t__ ide_lastactivity ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  led_trigger_event (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ledtrig_ide ; 
 int /*<<< orphan*/  ledtrig_ide_timer ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ msecs_to_jiffies (int) ; 

__attribute__((used)) static void ledtrig_ide_timerfunc(unsigned long data)
{
	if (ide_lastactivity != ide_activity) {
		ide_lastactivity = ide_activity;
		/* INT_MAX will set each LED to its maximum brightness */
		led_trigger_event(ledtrig_ide, INT_MAX);
		mod_timer(&ledtrig_ide_timer, jiffies + msecs_to_jiffies(10));
	} else {
		led_trigger_event(ledtrig_ide, LED_OFF);
	}
}