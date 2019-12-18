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
struct TYPE_2__ {unsigned long weight; } ;
struct rq {unsigned long last_load_update_tick; unsigned long* cpu_load; int /*<<< orphan*/  nr_load_updates; TYPE_1__ load; } ;

/* Variables and functions */
 int CPU_LOAD_IDX_MAX ; 
 unsigned long decay_load_missed (unsigned long,unsigned long,int) ; 
 unsigned long jiffies ; 

__attribute__((used)) static void update_cpu_load(struct rq *this_rq)
{
	unsigned long this_load = this_rq->load.weight;
	unsigned long curr_jiffies = jiffies;
	unsigned long pending_updates;
	int i, scale;

	this_rq->nr_load_updates++;

	/* Avoid repeated calls on same jiffy, when moving in and out of idle */
	if (curr_jiffies == this_rq->last_load_update_tick)
		return;

	pending_updates = curr_jiffies - this_rq->last_load_update_tick;
	this_rq->last_load_update_tick = curr_jiffies;

	/* Update our load: */
	this_rq->cpu_load[0] = this_load; /* Fasttrack for idx 0 */
	for (i = 1, scale = 2; i < CPU_LOAD_IDX_MAX; i++, scale += scale) {
		unsigned long old_load, new_load;

		/* scale is effectively 1 << i now, and >> i divides by scale */

		old_load = this_rq->cpu_load[i];
		old_load = decay_load_missed(old_load, pending_updates - 1, i);
		new_load = this_load;
		/*
		 * Round up the averaging division if load is increasing. This
		 * prevents us from getting stuck on 9 if the load is 10, for
		 * example.
		 */
		if (new_load > old_load)
			new_load += scale - 1;

		this_rq->cpu_load[i] = (old_load * (scale - 1) + new_load) >> i;
	}
}