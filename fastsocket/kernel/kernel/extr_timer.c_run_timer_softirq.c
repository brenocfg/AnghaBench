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
struct tvec_base {int /*<<< orphan*/  timer_jiffies; } ;
struct softirq_action {int dummy; } ;

/* Variables and functions */
 struct tvec_base* __get_cpu_var (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __run_timers (struct tvec_base*) ; 
 int /*<<< orphan*/  hrtimer_run_pending () ; 
 int /*<<< orphan*/  jiffies ; 
 scalar_t__ time_after_eq (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tvec_bases ; 

__attribute__((used)) static void run_timer_softirq(struct softirq_action *h)
{
	struct tvec_base *base = __get_cpu_var(tvec_bases);

	hrtimer_run_pending();

	if (time_after_eq(jiffies, base->timer_jiffies))
		__run_timers(base);
}