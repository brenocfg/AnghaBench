#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct task_struct {int flags; struct reclaim_state* reclaim_state; } ;
struct reclaim_state {int /*<<< orphan*/  reclaimed_slab; } ;
struct cpumask {int dummy; } ;
struct TYPE_5__ {unsigned long kswapd_max_order; int /*<<< orphan*/  node_id; int /*<<< orphan*/  kswapd_wait; } ;
typedef  TYPE_1__ pg_data_t ;

/* Variables and functions */
 int /*<<< orphan*/  DEFINE_WAIT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int HZ ; 
 int /*<<< orphan*/  KSWAPD_HIGH_WMARK_HIT_QUICKLY ; 
 int /*<<< orphan*/  KSWAPD_LOW_WMARK_HIT_QUICKLY ; 
 int PF_KSWAPD ; 
 int PF_MEMALLOC ; 
 int PF_SWAPWRITE ; 
 int /*<<< orphan*/  TASK_INTERRUPTIBLE ; 
 int /*<<< orphan*/  balance_pgdat (TYPE_1__*,unsigned long) ; 
 int /*<<< orphan*/  calculate_normal_threshold ; 
 int /*<<< orphan*/  calculate_pressure_threshold ; 
 int /*<<< orphan*/  count_vm_event (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpumask_empty (struct cpumask const*) ; 
 struct cpumask* cpumask_of_node (int /*<<< orphan*/ ) ; 
 struct task_struct* current ; 
 int /*<<< orphan*/  finish_wait (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  freezing (struct task_struct*) ; 
 int /*<<< orphan*/  lockdep_set_current_reclaim_state (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  prepare_to_wait (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  schedule () ; 
 long schedule_timeout (int) ; 
 int /*<<< orphan*/  set_cpus_allowed_ptr (struct task_struct*,struct cpumask const*) ; 
 int /*<<< orphan*/  set_freezable () ; 
 int /*<<< orphan*/  set_pgdat_percpu_threshold (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sleeping_prematurely (TYPE_1__*,unsigned long,long) ; 
 int /*<<< orphan*/  trace_mm_vmscan_kswapd_sleep (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trace_mm_vmscan_kswapd_wake (int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  try_to_freeze () ; 
 int /*<<< orphan*/  wait ; 

__attribute__((used)) static int kswapd(void *p)
{
	unsigned long order;
	pg_data_t *pgdat = (pg_data_t*)p;
	struct task_struct *tsk = current;
	DEFINE_WAIT(wait);
	struct reclaim_state reclaim_state = {
		.reclaimed_slab = 0,
	};
	const struct cpumask *cpumask = cpumask_of_node(pgdat->node_id);

	lockdep_set_current_reclaim_state(GFP_KERNEL);

	if (!cpumask_empty(cpumask))
		set_cpus_allowed_ptr(tsk, cpumask);
	current->reclaim_state = &reclaim_state;

	/*
	 * Tell the memory management that we're a "memory allocator",
	 * and that if we need more memory we should get access to it
	 * regardless (see "__alloc_pages()"). "kswapd" should
	 * never get caught in the normal page freeing logic.
	 *
	 * (Kswapd normally doesn't need memory anyway, but sometimes
	 * you need a small amount of memory in order to be able to
	 * page out something else, and this flag essentially protects
	 * us from recursively trying to free more memory as we're
	 * trying to free the first piece of memory in the first place).
	 */
	tsk->flags |= PF_MEMALLOC | PF_SWAPWRITE | PF_KSWAPD;
	set_freezable();

	order = 0;
	for ( ; ; ) {
		unsigned long new_order;

		prepare_to_wait(&pgdat->kswapd_wait, &wait, TASK_INTERRUPTIBLE);
		new_order = pgdat->kswapd_max_order;
		pgdat->kswapd_max_order = 0;
		if (order < new_order) {
			/*
			 * Don't sleep if someone wants a larger 'order'
			 * allocation
			 */
			order = new_order;
		} else {
			if (!freezing(current)) {
				long remaining = 0;

				/* Try to sleep for a short interval */
				if (!sleeping_prematurely(pgdat, order, remaining)) {
					remaining = schedule_timeout(HZ/10);
					finish_wait(&pgdat->kswapd_wait, &wait);
					prepare_to_wait(&pgdat->kswapd_wait, &wait, TASK_INTERRUPTIBLE);
				}

				/*
				 * After a short sleep, check if it was a
				 * premature sleep. If not, then go fully
				 * to sleep until explicitly woken up
				 */
				if (!sleeping_prematurely(pgdat, order, remaining)) {
					trace_mm_vmscan_kswapd_sleep(pgdat->node_id);

					/*
					 * vmstat counters are not perfectly
					 * accurate and the estimated value
					 * for counters such as NR_FREE_PAGES
					 * can deviate from the true value by
					 * nr_online_cpus * threshold. To
					 * avoid the zone watermarks being
					 * breached while under pressure, we
					 * reduce the per-cpu vmstat threshold
					 * while kswapd is awake and restore
					 * them before going back to sleep.
					 */
					set_pgdat_percpu_threshold(pgdat,
						calculate_normal_threshold);

					schedule();
					set_pgdat_percpu_threshold(pgdat,
						calculate_pressure_threshold);
				} else {
					if (remaining)
						count_vm_event(KSWAPD_LOW_WMARK_HIT_QUICKLY);
					else
						count_vm_event(KSWAPD_HIGH_WMARK_HIT_QUICKLY);
				}
			}

			order = pgdat->kswapd_max_order;
		}
		finish_wait(&pgdat->kswapd_wait, &wait);

		if (!try_to_freeze()) {
			/* We can speed up thawing tasks if we don't call
			 * balance_pgdat after returning from the refrigerator
			 */
			trace_mm_vmscan_kswapd_wake(pgdat->node_id, order);
			balance_pgdat(pgdat, order);
		}
	}
	return 0;
}