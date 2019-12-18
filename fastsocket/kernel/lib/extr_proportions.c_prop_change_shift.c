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
typedef  int u64 ;
struct prop_descriptor {int index; int /*<<< orphan*/  mutex; TYPE_1__* pg; } ;
struct TYPE_2__ {int shift; int /*<<< orphan*/  events; } ;

/* Variables and functions */
 int PROP_MAX_SHIFT ; 
 int /*<<< orphan*/  local_irq_restore (unsigned long) ; 
 int /*<<< orphan*/  local_irq_save (unsigned long) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  percpu_counter_set (int /*<<< orphan*/ *,int) ; 
 int percpu_counter_sum (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  smp_wmb () ; 
 int /*<<< orphan*/  synchronize_rcu () ; 

void prop_change_shift(struct prop_descriptor *pd, int shift)
{
	int index;
	int offset;
	u64 events;
	unsigned long flags;

	if (shift > PROP_MAX_SHIFT)
		shift = PROP_MAX_SHIFT;

	mutex_lock(&pd->mutex);

	index = pd->index ^ 1;
	offset = pd->pg[pd->index].shift - shift;
	if (!offset)
		goto out;

	pd->pg[index].shift = shift;

	local_irq_save(flags);
	events = percpu_counter_sum(&pd->pg[pd->index].events);
	if (offset < 0)
		events <<= -offset;
	else
		events >>= offset;
	percpu_counter_set(&pd->pg[index].events, events);

	/*
	 * ensure the new pg is fully written before the switch
	 */
	smp_wmb();
	pd->index = index;
	local_irq_restore(flags);

	synchronize_rcu();

out:
	mutex_unlock(&pd->mutex);
}