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
struct clock_event_device {int shift; int min_delta_ns; int /*<<< orphan*/  max_delta_ns; int /*<<< orphan*/  mult; } ;
struct sh_tmu_priv {int rate; int periodic; struct clock_event_device ced; } ;

/* Variables and functions */
 int HZ ; 
 int /*<<< orphan*/  NSEC_PER_SEC ; 
 int /*<<< orphan*/  clockevent_delta2ns (int,struct clock_event_device*) ; 
 int /*<<< orphan*/  div_sc (int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  sh_tmu_enable (struct sh_tmu_priv*) ; 
 int /*<<< orphan*/  sh_tmu_set_next (struct sh_tmu_priv*,int,int) ; 

__attribute__((used)) static void sh_tmu_clock_event_start(struct sh_tmu_priv *p, int periodic)
{
	struct clock_event_device *ced = &p->ced;

	sh_tmu_enable(p);

	/* TODO: calculate good shift from rate and counter bit width */

	ced->shift = 32;
	ced->mult = div_sc(p->rate, NSEC_PER_SEC, ced->shift);
	ced->max_delta_ns = clockevent_delta2ns(0xffffffff, ced);
	ced->min_delta_ns = 5000;

	if (periodic) {
		p->periodic = (p->rate + HZ/2) / HZ;
		sh_tmu_set_next(p, p->periodic, 1);
	}
}