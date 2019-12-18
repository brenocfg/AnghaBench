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
struct xt_led_info_internal {int /*<<< orphan*/  netfilter_led_trigger; } ;
struct xt_led_info {struct xt_led_info_internal* internal_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  LED_OFF ; 
 int /*<<< orphan*/  led_trigger_event (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void led_timeout_callback(unsigned long data)
{
	struct xt_led_info *ledinfo = (struct xt_led_info *)data;
	struct xt_led_info_internal *ledinternal = ledinfo->internal_data;

	led_trigger_event(&ledinternal->netfilter_led_trigger, LED_OFF);
}