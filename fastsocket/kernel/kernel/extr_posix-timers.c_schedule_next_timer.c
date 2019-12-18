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
struct TYPE_8__ {scalar_t__ tv64; } ;
struct hrtimer {TYPE_1__* base; } ;
struct TYPE_6__ {TYPE_4__ interval; struct hrtimer timer; } ;
struct TYPE_7__ {TYPE_2__ real; } ;
struct k_itimer {unsigned int it_overrun; unsigned int it_overrun_last; int /*<<< orphan*/  it_requeue_pending; TYPE_3__ it; } ;
struct TYPE_5__ {int /*<<< orphan*/  (* get_time ) () ;} ;

/* Variables and functions */
 scalar_t__ hrtimer_forward (struct hrtimer*,int /*<<< orphan*/ ,TYPE_4__) ; 
 int /*<<< orphan*/  hrtimer_restart (struct hrtimer*) ; 
 int /*<<< orphan*/  stub1 () ; 

__attribute__((used)) static void schedule_next_timer(struct k_itimer *timr)
{
	struct hrtimer *timer = &timr->it.real.timer;

	if (timr->it.real.interval.tv64 == 0)
		return;

	timr->it_overrun += (unsigned int) hrtimer_forward(timer,
						timer->base->get_time(),
						timr->it.real.interval);

	timr->it_overrun_last = timr->it_overrun;
	timr->it_overrun = -1;
	++timr->it_requeue_pending;
	hrtimer_restart(timer);
}