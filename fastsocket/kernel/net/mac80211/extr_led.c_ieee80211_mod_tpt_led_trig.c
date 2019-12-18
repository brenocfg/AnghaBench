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
struct tpt_led_trigger {unsigned int active; int want; } ;
struct ieee80211_local {struct tpt_led_trigger* tpt_led_trigger; } ;

/* Variables and functions */
 int IEEE80211_TPT_LEDTRIG_FL_RADIO ; 
 int /*<<< orphan*/  WARN_ON (unsigned int) ; 
 int /*<<< orphan*/  ieee80211_start_tpt_led_trig (struct ieee80211_local*) ; 
 int /*<<< orphan*/  ieee80211_stop_tpt_led_trig (struct ieee80211_local*) ; 

void ieee80211_mod_tpt_led_trig(struct ieee80211_local *local,
				unsigned int types_on, unsigned int types_off)
{
	struct tpt_led_trigger *tpt_trig = local->tpt_led_trigger;
	bool allowed;

	WARN_ON(types_on & types_off);

	if (!tpt_trig)
		return;

	tpt_trig->active &= ~types_off;
	tpt_trig->active |= types_on;

	/*
	 * Regardless of wanted state, we shouldn't blink when
	 * the radio is disabled -- this can happen due to some
	 * code ordering issues with __ieee80211_recalc_idle()
	 * being called before the radio is started.
	 */
	allowed = tpt_trig->active & IEEE80211_TPT_LEDTRIG_FL_RADIO;

	if (!allowed || !(tpt_trig->active & tpt_trig->want))
		ieee80211_stop_tpt_led_trig(local);
	else
		ieee80211_start_tpt_led_trig(local);
}