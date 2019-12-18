#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_20__   TYPE_4__ ;
typedef  struct TYPE_19__   TYPE_3__ ;
typedef  struct TYPE_18__   TYPE_2__ ;
typedef  struct TYPE_17__   TYPE_1__ ;
typedef  struct TYPE_16__   TYPE_15__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  thread_t ;
typedef  TYPE_2__* sched_group_t ;
typedef  TYPE_3__* run_queue_t ;
typedef  int /*<<< orphan*/  processor_t ;
typedef  scalar_t__ integer_t ;
typedef  TYPE_4__* entry_queue_t ;
typedef  scalar_t__ boolean_t ;
typedef  int ast_t ;
struct TYPE_20__ {int highq; scalar_t__ count; } ;
struct TYPE_19__ {int highq; scalar_t__ count; } ;
struct TYPE_17__ {scalar_t__ count; scalar_t__ highq; } ;
struct TYPE_18__ {TYPE_1__ runq; } ;
struct TYPE_16__ {TYPE_2__* sched_group; } ;

/* Variables and functions */
 int AST_PREEMPTION ; 
 int DBG_FUNC_NONE ; 
 int /*<<< orphan*/  DBG_MACH_SCHED ; 
 scalar_t__ FALSE ; 
 int /*<<< orphan*/  KDEBUG_TRACE ; 
 int /*<<< orphan*/  KERNEL_DEBUG_CONSTANT_IST (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,scalar_t__,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int MACHDBG_CODE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MACH_MULTIQ_BOUND ; 
 int /*<<< orphan*/  MACH_MULTIQ_DEQUEUE ; 
 int /*<<< orphan*/  MACH_MULTIQ_GLOBAL ; 
 int /*<<< orphan*/  MACH_MULTIQ_GROUP ; 
 int /*<<< orphan*/  SCHED_HEADQ ; 
 int /*<<< orphan*/  THREAD_NULL ; 
 scalar_t__ TRUE ; 
 TYPE_15__* current_thread () ; 
 scalar_t__ deep_drain ; 
 scalar_t__ drain_band_limit ; 
 scalar_t__ drain_ceiling ; 
 scalar_t__ drain_depth_limit ; 
 int /*<<< orphan*/  global_check_entry_queue (TYPE_4__*) ; 
 int /*<<< orphan*/  group_check_run_queue (TYPE_4__*,TYPE_2__*) ; 
 TYPE_3__* multiq_bound_runq (int /*<<< orphan*/ ) ; 
 TYPE_4__* multiq_main_entryq (int /*<<< orphan*/ ) ; 
 scalar_t__ multiq_sanity_check ; 
 int /*<<< orphan*/  run_queue_dequeue (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sched_global_deep_drain_dequeue_thread (TYPE_4__*) ; 
 int /*<<< orphan*/  sched_global_dequeue_thread (TYPE_4__*) ; 
 int /*<<< orphan*/  sched_group_dequeue_thread (TYPE_4__*,TYPE_2__*) ; 

__attribute__((used)) static thread_t
sched_multiq_choose_thread(
                           processor_t      processor,
                           int              priority,
                           ast_t            reason)
{
	entry_queue_t   main_entryq = multiq_main_entryq(processor);
	run_queue_t     bound_runq  = multiq_bound_runq(processor);

	boolean_t choose_bound_runq = FALSE;

	if (bound_runq->highq  < priority &&
	    main_entryq->highq < priority)
		return THREAD_NULL;

	if (bound_runq->count && main_entryq->count) {
		if (bound_runq->highq >= main_entryq->highq) {
			choose_bound_runq = TRUE;
		} else {
			/* Use main runq */
		}
	} else if (bound_runq->count) {
		choose_bound_runq = TRUE;
	} else if (main_entryq->count) {
		/* Use main runq */
	} else {
		return (THREAD_NULL);
	}

	if (choose_bound_runq) {
		KERNEL_DEBUG_CONSTANT_IST(KDEBUG_TRACE,
		    MACHDBG_CODE(DBG_MACH_SCHED, MACH_MULTIQ_DEQUEUE) | DBG_FUNC_NONE,
		    MACH_MULTIQ_BOUND, main_entryq->highq, bound_runq->highq, 0, 0);

		return run_queue_dequeue(bound_runq, SCHED_HEADQ);
	}

	sched_group_t group = current_thread()->sched_group;

#if defined(MULTIQ_SANITY_CHECK)
	if (multiq_sanity_check) {
		global_check_entry_queue(main_entryq);
		group_check_run_queue(main_entryq, group);
	}
#endif

	/*
	 * Determine if we should look at the group or the global queue
	 *
	 * TODO:
	 * Perhaps pass reason as a 'should look inside' argument to choose_thread
	 * Should YIELD AST override drain limit?
	 */
	if (group->runq.count != 0 && (reason & AST_PREEMPTION) == 0) {
		boolean_t favor_group = TRUE;

		integer_t global_pri = main_entryq->highq;
		integer_t group_pri  = group->runq.highq;

		/*
		 * Favor the current group if the group is still the globally highest.
		 *
		 * Otherwise, consider choosing a thread from the current group
		 * even if it's lower priority than the global highest priority.
		 */
		if (global_pri > group_pri) {
			/*
			 * If there's something elsewhere above the depth limit,
			 * don't pick a thread below the limit.
			 */
			if (global_pri > drain_depth_limit && group_pri <= drain_depth_limit)
				favor_group = FALSE;

			/*
			 * If there's something at or above the ceiling,
			 * don't favor the group.
			 */
			if (global_pri >= drain_ceiling)
				favor_group = FALSE;

			/*
			 * Don't go more than X steps below the global highest
			 */
			if ((global_pri - group_pri) >= drain_band_limit)
				favor_group = FALSE;
		}

		if (favor_group) {
			/* Pull from local runq */
			KERNEL_DEBUG_CONSTANT_IST(KDEBUG_TRACE,
			    MACHDBG_CODE(DBG_MACH_SCHED, MACH_MULTIQ_DEQUEUE) | DBG_FUNC_NONE,
			    MACH_MULTIQ_GROUP, global_pri, group_pri, 0, 0);

			return sched_group_dequeue_thread(main_entryq, group);
		}
	}

	KERNEL_DEBUG_CONSTANT_IST(KDEBUG_TRACE,
	    MACHDBG_CODE(DBG_MACH_SCHED, MACH_MULTIQ_DEQUEUE) | DBG_FUNC_NONE,
	    MACH_MULTIQ_GLOBAL, main_entryq->highq, group->runq.highq, 0, 0);

	/* Couldn't pull from local runq, pull from global runq instead */
	if (deep_drain) {
		return sched_global_deep_drain_dequeue_thread(main_entryq);
	} else {
		return sched_global_dequeue_thread(main_entryq);
	}
}