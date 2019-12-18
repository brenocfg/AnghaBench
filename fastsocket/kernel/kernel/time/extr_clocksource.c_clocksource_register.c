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
struct clocksource {scalar_t__ maxadj; scalar_t__ mult; int /*<<< orphan*/  name; int /*<<< orphan*/  max_idle_ns; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ONCE (int,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clocksource_enqueue (struct clocksource*) ; 
 int /*<<< orphan*/  clocksource_enqueue_watchdog (struct clocksource*) ; 
 scalar_t__ clocksource_max_adjustment (struct clocksource*) ; 
 int /*<<< orphan*/  clocksource_max_deferment (struct clocksource*) ; 
 int /*<<< orphan*/  clocksource_mutex ; 
 int /*<<< orphan*/  clocksource_select () ; 
 int has_kvm_clock ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strcmp (int /*<<< orphan*/ ,char*) ; 

int clocksource_register(struct clocksource *cs)
{
	/* calculate max adjustment for given mult/shift */
	cs->maxadj = clocksource_max_adjustment(cs);
	WARN_ONCE(cs->mult + cs->maxadj < cs->mult,
		"Clocksource %s might overflow on 11%% adjustment\n",
		cs->name);

	/* calculate max idle time permitted for this clocksource */
	cs->max_idle_ns = clocksource_max_deferment(cs);

	mutex_lock(&clocksource_mutex);
	clocksource_enqueue(cs);
	clocksource_select();
	clocksource_enqueue_watchdog(cs);
	mutex_unlock(&clocksource_mutex);
	if (!strcmp(cs->name, "kvm-clock"))
		has_kvm_clock = 1;
	return 0;
}