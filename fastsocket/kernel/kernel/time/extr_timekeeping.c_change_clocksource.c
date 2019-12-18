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
struct clocksource {scalar_t__ (* enable ) (struct clocksource*) ;int /*<<< orphan*/  (* disable ) (struct clocksource*) ;} ;
struct TYPE_2__ {int /*<<< orphan*/  lock; struct clocksource* clock; } ;

/* Variables and functions */
 scalar_t__ stub1 (struct clocksource*) ; 
 int /*<<< orphan*/  stub2 (struct clocksource*) ; 
 TYPE_1__ timekeeper ; 
 int /*<<< orphan*/  timekeeper_setup_internals (struct clocksource*) ; 
 int /*<<< orphan*/  timekeeping_forward_now () ; 
 int /*<<< orphan*/  timekeeping_update (int) ; 
 int /*<<< orphan*/  write_seqlock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  write_sequnlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int change_clocksource(void *data)
{
	struct clocksource *new, *old;
	unsigned long flags;

	new = (struct clocksource *) data;

	write_seqlock_irqsave(&timekeeper.lock, flags);

	timekeeping_forward_now();
	if (!new->enable || new->enable(new) == 0) {
		old = timekeeper.clock;
		timekeeper_setup_internals(new);
		if (old->disable)
			old->disable(old);
	}
	timekeeping_update(true);

	write_sequnlock_irqrestore(&timekeeper.lock, flags);

	return 0;
}