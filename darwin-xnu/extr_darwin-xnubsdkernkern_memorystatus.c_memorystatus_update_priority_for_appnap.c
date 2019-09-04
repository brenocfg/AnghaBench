#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint64_t ;
typedef  TYPE_1__* proc_t ;
struct TYPE_9__ {int /*<<< orphan*/  count; int /*<<< orphan*/  list; } ;
typedef  TYPE_2__ memstat_bucket_t ;
typedef  size_t int32_t ;
typedef  scalar_t__ boolean_t ;
struct TYPE_8__ {int p_memstat_state; int p_listflag; size_t p_memstat_effectivepriority; size_t p_memstat_requestedpriority; scalar_t__ p_memstat_idle_start; int /*<<< orphan*/  p_pid; scalar_t__ p_memstat_idle_delta; } ;

/* Variables and functions */
 int /*<<< orphan*/  BSDDBG_CODE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BSD_MEMSTAT_CHANGE_PRIORITY ; 
 int /*<<< orphan*/  DBG_BSD_MEMSTAT ; 
 size_t JETSAM_PRIORITY_IDLE ; 
 int /*<<< orphan*/  KERNEL_DEBUG_CONSTANT (int /*<<< orphan*/ ,int /*<<< orphan*/ ,size_t,size_t,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int P_LIST_EXITED ; 
 int P_MEMSTAT_ERROR ; 
 int P_MEMSTAT_INTERNAL ; 
 int P_MEMSTAT_MANAGED ; 
 int P_MEMSTAT_TERMINATED ; 
 int /*<<< orphan*/  TAILQ_INSERT_TAIL (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TAILQ_REMOVE (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  isApp (TYPE_1__*) ; 
 scalar_t__ mach_absolute_time () ; 
 TYPE_2__* memstat_bucket ; 
 int /*<<< orphan*/  p_memstat_list ; 
 int /*<<< orphan*/  proc_list_lock () ; 
 int /*<<< orphan*/  proc_list_unlock () ; 

int
memorystatus_update_priority_for_appnap(proc_t p, boolean_t is_appnap)
{
#if !CONFIG_JETSAM
	if (!p || (!isApp(p)) || (p->p_memstat_state & (P_MEMSTAT_INTERNAL | P_MEMSTAT_MANAGED))) {
		/*
		 * Ineligible processes OR system processes e.g. launchd.
		 *
		 * We also skip processes that have the P_MEMSTAT_MANAGED bit set, i.e.
		 * they're managed by assertiond. These are iOS apps that have been ported
		 * to macOS. assertiond might be in the process of modifying the app's
		 * priority / memory limit - so it might have the proc_list lock, and then try
		 * to take the task lock. Meanwhile we've entered this function with the task lock
		 * held, and we need the proc_list lock below. So we'll deadlock with assertiond.
		 *
		 * It should be fine to read the P_MEMSTAT_MANAGED bit without the proc_list
		 * lock here, since assertiond only sets this bit on process launch.
		 */
		return -1;
	}

	/*
	 * For macOS only:
	 * We would like to use memorystatus_update() here to move the processes
	 * within the bands. Unfortunately memorystatus_update() calls
	 * memorystatus_update_priority_locked() which uses any band transitions
	 * as an indication to modify ledgers. For that it needs the task lock
	 * and since we came into this function with the task lock held, we'll deadlock.
	 *
	 * Unfortunately we can't completely disable ledger updates  because we still 
	 * need the ledger updates for a subset of processes i.e. daemons.
	 * When all processes on all platforms support memory limits, we can simply call
	 * memorystatus_update().
	 
	 * It also has some logic to deal with 'aging' which, currently, is only applicable
	 * on CONFIG_JETSAM configs. So, till every platform has CONFIG_JETSAM we'll need
	 * to do this explicit band transition.
	 */

	memstat_bucket_t *current_bucket, *new_bucket;
	int32_t	priority = 0;

	proc_list_lock();

	if (((p->p_listflag & P_LIST_EXITED) != 0) ||
	    (p->p_memstat_state & (P_MEMSTAT_ERROR | P_MEMSTAT_TERMINATED))) {
		/*
		 * If the process is on its way out OR
		 * jetsam has alread tried and failed to kill this process,
		 * let's skip the whole jetsam band transition.
		 */
		proc_list_unlock();
		return(0);
	}

	if (is_appnap) {
		current_bucket = &memstat_bucket[p->p_memstat_effectivepriority];
		new_bucket = &memstat_bucket[JETSAM_PRIORITY_IDLE];
		priority = JETSAM_PRIORITY_IDLE;
	} else {
		if (p->p_memstat_effectivepriority != JETSAM_PRIORITY_IDLE) {
			/*
			 * It is possible that someone pulled this process
			 * out of the IDLE band without updating its app-nap
			 * parameters.
			 */
			proc_list_unlock();
			return (0);
		}

		current_bucket = &memstat_bucket[JETSAM_PRIORITY_IDLE];
		new_bucket = &memstat_bucket[p->p_memstat_requestedpriority];
		priority = p->p_memstat_requestedpriority;
	}

	TAILQ_REMOVE(&current_bucket->list, p, p_memstat_list);
	current_bucket->count--;

	TAILQ_INSERT_TAIL(&new_bucket->list, p, p_memstat_list);
	new_bucket->count++;

	/*
	 * Record idle start or idle delta.
	 */
	if (p->p_memstat_effectivepriority == priority) {
		/*	
		 * This process is not transitioning between
		 * jetsam priority buckets.  Do nothing.
		 */
	} else if (p->p_memstat_effectivepriority == JETSAM_PRIORITY_IDLE) {
		uint64_t now;
		/*
		 * Transitioning out of the idle priority bucket.
		 * Record idle delta.
		 */
		assert(p->p_memstat_idle_start != 0);
		now = mach_absolute_time();
		if (now > p->p_memstat_idle_start) {
			p->p_memstat_idle_delta = now - p->p_memstat_idle_start;
		}
	} else if (priority == JETSAM_PRIORITY_IDLE) {
		/*
		 * Transitioning into the idle priority bucket.
		 * Record idle start.
		 */
		p->p_memstat_idle_start = mach_absolute_time();
	}

	KERNEL_DEBUG_CONSTANT(BSDDBG_CODE(DBG_BSD_MEMSTAT, BSD_MEMSTAT_CHANGE_PRIORITY), p->p_pid, priority, p->p_memstat_effectivepriority, 0, 0);

	p->p_memstat_effectivepriority = priority;

	proc_list_unlock();

	return (0);

#else /* !CONFIG_JETSAM */
	#pragma unused(p)
	#pragma unused(is_appnap)
	return -1;
#endif /* !CONFIG_JETSAM */
}