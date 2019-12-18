#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  int u64 ;
struct hrtimer {TYPE_2__* base; } ;
typedef  int s64 ;
struct TYPE_13__ {scalar_t__ tv64; } ;
typedef  TYPE_3__ ktime_t ;
struct TYPE_11__ {scalar_t__ tv64; } ;
struct TYPE_12__ {TYPE_1__ resolution; } ;

/* Variables and functions */
 int /*<<< orphan*/  hrtimer_add_expires (struct hrtimer*,TYPE_3__) ; 
 int /*<<< orphan*/  hrtimer_add_expires_ns (struct hrtimer*,int) ; 
 int /*<<< orphan*/  hrtimer_get_expires (struct hrtimer*) ; 
 scalar_t__ hrtimer_get_expires_tv64 (struct hrtimer*) ; 
 int ktime_divns (TYPE_3__,int) ; 
 TYPE_3__ ktime_sub (TYPE_3__,int /*<<< orphan*/ ) ; 
 int ktime_to_ns (TYPE_3__) ; 
 scalar_t__ unlikely (int) ; 

u64 hrtimer_forward(struct hrtimer *timer, ktime_t now, ktime_t interval)
{
	u64 orun = 1;
	ktime_t delta;

	delta = ktime_sub(now, hrtimer_get_expires(timer));

	if (delta.tv64 < 0)
		return 0;

	if (interval.tv64 < timer->base->resolution.tv64)
		interval.tv64 = timer->base->resolution.tv64;

	if (unlikely(delta.tv64 >= interval.tv64)) {
		s64 incr = ktime_to_ns(interval);

		orun = ktime_divns(delta, incr);
		hrtimer_add_expires_ns(timer, incr * orun);
		if (hrtimer_get_expires_tv64(timer) > now.tv64)
			return orun;
		/*
		 * This (and the ktime_add() below) is the
		 * correction for exact:
		 */
		orun++;
	}
	hrtimer_add_expires(timer, interval);

	return orun;
}