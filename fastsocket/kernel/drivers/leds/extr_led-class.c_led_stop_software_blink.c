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
struct led_timer {scalar_t__ blink_delay_off; scalar_t__ blink_delay_on; int /*<<< orphan*/  blink_timer; } ;

/* Variables and functions */
 int /*<<< orphan*/  del_timer_sync (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void led_stop_software_blink(struct led_timer *led)
{
	del_timer_sync(&led->blink_timer);
	led->blink_delay_on = 0;
	led->blink_delay_off = 0;
}