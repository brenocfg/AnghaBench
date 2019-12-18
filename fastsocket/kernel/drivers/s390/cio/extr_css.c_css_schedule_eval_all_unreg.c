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
struct idset {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  __unset_registered ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  bus_for_each_dev (int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct idset*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cio_work_q ; 
 int /*<<< orphan*/  css_bus_type ; 
 int /*<<< orphan*/  css_eval_scheduled ; 
 int /*<<< orphan*/  css_schedule_eval_all () ; 
 int /*<<< orphan*/  idset_add_set (int /*<<< orphan*/ ,struct idset*) ; 
 int /*<<< orphan*/  idset_fill (struct idset*) ; 
 int /*<<< orphan*/  idset_free (struct idset*) ; 
 struct idset* idset_sch_new () ; 
 int /*<<< orphan*/  queue_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  slow_path_work ; 
 int /*<<< orphan*/  slow_subchannel_lock ; 
 int /*<<< orphan*/  slow_subchannel_set ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

void css_schedule_eval_all_unreg(void)
{
	unsigned long flags;
	struct idset *unreg_set;

	/* Find unregistered subchannels. */
	unreg_set = idset_sch_new();
	if (!unreg_set) {
		/* Fallback. */
		css_schedule_eval_all();
		return;
	}
	idset_fill(unreg_set);
	bus_for_each_dev(&css_bus_type, NULL, unreg_set, __unset_registered);
	/* Apply to slow_subchannel_set. */
	spin_lock_irqsave(&slow_subchannel_lock, flags);
	idset_add_set(slow_subchannel_set, unreg_set);
	atomic_set(&css_eval_scheduled, 1);
	queue_work(cio_work_q, &slow_path_work);
	spin_unlock_irqrestore(&slow_subchannel_lock, flags);
	idset_free(unreg_set);
}