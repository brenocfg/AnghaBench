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
struct ieee80211_local {int tx_led_counter; int /*<<< orphan*/  tx_led; } ;

/* Variables and functions */
 int /*<<< orphan*/  LED_FULL ; 
 int /*<<< orphan*/  LED_OFF ; 
 int /*<<< orphan*/  led_trigger_event (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int) ; 

void ieee80211_led_tx(struct ieee80211_local *local, int q)
{
	if (unlikely(!local->tx_led))
		return;
	/* not sure how this is supposed to work ... */
	local->tx_led_counter += 2*q-1;
	if (local->tx_led_counter % 2 == 0)
		led_trigger_event(local->tx_led, LED_OFF);
	else
		led_trigger_event(local->tx_led, LED_FULL);
}