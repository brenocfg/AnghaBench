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
struct clock_event_device {int shift; void* min_delta_ns; void* max_delta_ns; int /*<<< orphan*/  mult; } ;
struct sh_cmt_priv {int rate; int max_match_value; struct clock_event_device ced; } ;

/* Variables and functions */
 int /*<<< orphan*/  FLAG_CLOCKEVENT ; 
 int HZ ; 
 int /*<<< orphan*/  NSEC_PER_SEC ; 
 void* clockevent_delta2ns (int,struct clock_event_device*) ; 
 int /*<<< orphan*/  div_sc (int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  sh_cmt_set_next (struct sh_cmt_priv*,int) ; 
 int /*<<< orphan*/  sh_cmt_start (struct sh_cmt_priv*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void sh_cmt_clock_event_start(struct sh_cmt_priv *p, int periodic)
{
	struct clock_event_device *ced = &p->ced;

	sh_cmt_start(p, FLAG_CLOCKEVENT);

	/* TODO: calculate good shift from rate and counter bit width */

	ced->shift = 32;
	ced->mult = div_sc(p->rate, NSEC_PER_SEC, ced->shift);
	ced->max_delta_ns = clockevent_delta2ns(p->max_match_value, ced);
	ced->min_delta_ns = clockevent_delta2ns(0x1f, ced);

	if (periodic)
		sh_cmt_set_next(p, (p->rate + HZ/2) / HZ);
	else
		sh_cmt_set_next(p, p->max_match_value);
}