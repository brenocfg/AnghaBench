#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {unsigned long data; scalar_t__ expires; int /*<<< orphan*/  function; } ;
struct qib_pportdata {unsigned int* led_override_vals; int led_override_timeoff; int /*<<< orphan*/  led_override_timer_active; TYPE_1__ led_override_timer; struct qib_devdata* dd; } ;
struct qib_devdata {int flags; } ;

/* Variables and functions */
 int HZ ; 
 unsigned int LED_OVER_FREQ_MASK ; 
 unsigned int LED_OVER_FREQ_SHIFT ; 
 int QIB_INITTED ; 
 int /*<<< orphan*/  add_timer (TYPE_1__*) ; 
 int /*<<< orphan*/  atomic_dec (int /*<<< orphan*/ *) ; 
 int atomic_inc_return (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  init_timer (TYPE_1__*) ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  mod_timer (TYPE_1__*,scalar_t__) ; 
 int /*<<< orphan*/  qib_run_led_override ; 

void qib_set_led_override(struct qib_pportdata *ppd, unsigned int val)
{
	struct qib_devdata *dd = ppd->dd;
	int timeoff, freq;

	if (!(dd->flags & QIB_INITTED))
		return;

	/* First check if we are blinking. If not, use 1HZ polling */
	timeoff = HZ;
	freq = (val & LED_OVER_FREQ_MASK) >> LED_OVER_FREQ_SHIFT;

	if (freq) {
		/* For blink, set each phase from one nybble of val */
		ppd->led_override_vals[0] = val & 0xF;
		ppd->led_override_vals[1] = (val >> 4) & 0xF;
		timeoff = (HZ << 4)/freq;
	} else {
		/* Non-blink set both phases the same. */
		ppd->led_override_vals[0] = val & 0xF;
		ppd->led_override_vals[1] = val & 0xF;
	}
	ppd->led_override_timeoff = timeoff;

	/*
	 * If the timer has not already been started, do so. Use a "quick"
	 * timeout so the function will be called soon, to look at our request.
	 */
	if (atomic_inc_return(&ppd->led_override_timer_active) == 1) {
		/* Need to start timer */
		init_timer(&ppd->led_override_timer);
		ppd->led_override_timer.function = qib_run_led_override;
		ppd->led_override_timer.data = (unsigned long) ppd;
		ppd->led_override_timer.expires = jiffies + 1;
		add_timer(&ppd->led_override_timer);
	} else {
		if (ppd->led_override_vals[0] || ppd->led_override_vals[1])
			mod_timer(&ppd->led_override_timer, jiffies + 1);
		atomic_dec(&ppd->led_override_timer_active);
	}
}