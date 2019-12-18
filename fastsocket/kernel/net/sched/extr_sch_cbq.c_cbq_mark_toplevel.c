#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct cbq_sched_data {int toplevel; scalar_t__ now_rt; scalar_t__ now; } ;
struct cbq_class {int level; scalar_t__ undertime; struct cbq_class* borrow; TYPE_1__* q; } ;
typedef  scalar_t__ psched_time_t ;
typedef  scalar_t__ psched_tdiff_t ;
struct TYPE_2__ {int flags; } ;

/* Variables and functions */
 int TCQ_F_THROTTLED ; 
 scalar_t__ psched_get_time () ; 

__attribute__((used)) static void
cbq_mark_toplevel(struct cbq_sched_data *q, struct cbq_class *cl)
{
	int toplevel = q->toplevel;

	if (toplevel > cl->level && !(cl->q->flags&TCQ_F_THROTTLED)) {
		psched_time_t now;
		psched_tdiff_t incr;

		now = psched_get_time();
		incr = now - q->now_rt;
		now = q->now + incr;

		do {
			if (cl->undertime < now) {
				q->toplevel = cl->level;
				return;
			}
		} while ((cl=cl->borrow) != NULL && toplevel > cl->level);
	}
}