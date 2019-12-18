#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
union cpu_time_count {scalar_t__ sched; int /*<<< orphan*/  cpu; } ;
struct TYPE_6__ {scalar_t__ sched; int /*<<< orphan*/  cpu; } ;
struct TYPE_5__ {scalar_t__ sched; int /*<<< orphan*/  cpu; } ;
struct TYPE_7__ {TYPE_2__ expires; TYPE_1__ incr; } ;
struct TYPE_8__ {TYPE_3__ cpu; } ;
struct k_itimer {int it_overrun; TYPE_4__ it; int /*<<< orphan*/  it_clock; } ;
typedef  int /*<<< orphan*/  cputime_t ;

/* Variables and functions */
 scalar_t__ CPUCLOCK_SCHED ; 
 scalar_t__ CPUCLOCK_WHICH (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cputime_add (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cputime_halve (int /*<<< orphan*/ ) ; 
 scalar_t__ cputime_lt (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cputime_sub (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void bump_cpu_timer(struct k_itimer *timer,
				  union cpu_time_count now)
{
	int i;

	if (timer->it.cpu.incr.sched == 0)
		return;

	if (CPUCLOCK_WHICH(timer->it_clock) == CPUCLOCK_SCHED) {
		unsigned long long delta, incr;

		if (now.sched < timer->it.cpu.expires.sched)
			return;
		incr = timer->it.cpu.incr.sched;
		delta = now.sched + incr - timer->it.cpu.expires.sched;
		/* Don't use (incr*2 < delta), incr*2 might overflow. */
		for (i = 0; incr < delta - incr; i++)
			incr = incr << 1;
		for (; i >= 0; incr >>= 1, i--) {
			if (delta < incr)
				continue;
			timer->it.cpu.expires.sched += incr;
			timer->it_overrun += 1 << i;
			delta -= incr;
		}
	} else {
		cputime_t delta, incr;

		if (cputime_lt(now.cpu, timer->it.cpu.expires.cpu))
			return;
		incr = timer->it.cpu.incr.cpu;
		delta = cputime_sub(cputime_add(now.cpu, incr),
				    timer->it.cpu.expires.cpu);
		/* Don't use (incr*2 < delta), incr*2 might overflow. */
		for (i = 0; cputime_lt(incr, cputime_sub(delta, incr)); i++)
			     incr = cputime_add(incr, incr);
		for (; i >= 0; incr = cputime_halve(incr), i--) {
			if (cputime_lt(delta, incr))
				continue;
			timer->it.cpu.expires.cpu =
				cputime_add(timer->it.cpu.expires.cpu, incr);
			timer->it_overrun += 1 << i;
			delta = cputime_sub(delta, incr);
		}
	}
}