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
typedef  int u32 ;
struct clocksource {int mult; int maxadj; int /*<<< orphan*/  max_idle_ns; int /*<<< orphan*/  shift; } ;

/* Variables and functions */
 int MAX_UPDATE_LENGTH ; 
 int NSEC_PER_SEC ; 
 int /*<<< orphan*/  clocks_calc_mult_shift (int*,int /*<<< orphan*/ *,int,int,int) ; 
 int /*<<< orphan*/  clocksource_enqueue (struct clocksource*) ; 
 int /*<<< orphan*/  clocksource_enqueue_watchdog (struct clocksource*) ; 
 void* clocksource_max_adjustment (struct clocksource*) ; 
 int /*<<< orphan*/  clocksource_max_deferment (struct clocksource*) ; 
 int /*<<< orphan*/  clocksource_mutex ; 
 int /*<<< orphan*/  clocksource_select () ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

int __clocksource_register_scale(struct clocksource *cs, u32 scale, u32 freq)
{

	/*
	 * Ideally we want to use  some of the limits used in
	 * clocksource_max_deferment, to provide a more informed
	 * MAX_UPDATE_LENGTH. But for now this just gets the
	 * register interface working properly.
	 */
	clocks_calc_mult_shift(&cs->mult, &cs->shift, freq,
				      NSEC_PER_SEC/scale,
				      MAX_UPDATE_LENGTH*scale);

	/*
	 * for clocksources that have large mults, to avoid overflow.
	 * Since mult may be adjusted by ntp, add an safety extra margin
	 *
	 */
	cs->maxadj = clocksource_max_adjustment(cs);
	while ((cs->mult + cs->maxadj < cs->mult)
		|| (cs->mult - cs->maxadj > cs->mult)) {
		cs->mult >>= 1;
		cs->shift--;
		cs->maxadj = clocksource_max_adjustment(cs);
	}

	cs->max_idle_ns = clocksource_max_deferment(cs);

	mutex_lock(&clocksource_mutex);
	clocksource_enqueue(cs);
	clocksource_enqueue_watchdog(cs);
	clocksource_select();
	mutex_unlock(&clocksource_mutex);
	return 0;
}