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
struct lg_cpu {int /*<<< orphan*/  hrt; } ;
typedef  int /*<<< orphan*/  ktime_t ;

/* Variables and functions */
 int /*<<< orphan*/  HRTIMER_MODE_ABS ; 
 int /*<<< orphan*/  hrtimer_cancel (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hrtimer_start (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ktime_add_ns (int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  ktime_get_real () ; 
 scalar_t__ unlikely (int) ; 

void guest_set_clockevent(struct lg_cpu *cpu, unsigned long delta)
{
	ktime_t expires;

	if (unlikely(delta == 0)) {
		/* Clock event device is shutting down. */
		hrtimer_cancel(&cpu->hrt);
		return;
	}

	/*
	 * We use wallclock time here, so the Guest might not be running for
	 * all the time between now and the timer interrupt it asked for.  This
	 * is almost always the right thing to do.
	 */
	expires = ktime_add_ns(ktime_get_real(), delta);
	hrtimer_start(&cpu->hrt, expires, HRTIMER_MODE_ABS);
}