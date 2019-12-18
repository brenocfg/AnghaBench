#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_25__   TYPE_3__ ;
typedef  struct TYPE_24__   TYPE_2__ ;
typedef  struct TYPE_23__   TYPE_1__ ;
typedef  struct TYPE_22__   TYPE_17__ ;
typedef  struct TYPE_21__   TYPE_12__ ;

/* Type definitions */
typedef  TYPE_2__* timer_call_t ;
struct TYPE_25__ {int /*<<< orphan*/  earliest_soft_deadline; int /*<<< orphan*/  head; } ;
typedef  TYPE_3__ mpqueue_head_t ;
struct TYPE_23__ {TYPE_2__* lock_data; } ;
struct TYPE_21__ {TYPE_1__ interlock; } ;
struct TYPE_24__ {int flags; TYPE_12__ lock; } ;
struct TYPE_22__ {scalar_t__ deadline; TYPE_2__* queue; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBG (char*,TYPE_3__*,TYPE_3__*) ; 
 int DBG_FUNC_NONE ; 
 int DECR_TIMER_ASYNC_DEQ ; 
 int /*<<< orphan*/  KDEBUG_TRACE ; 
 TYPE_17__* TCE (TYPE_2__*) ; 
 TYPE_2__* TIMER_CALL (int /*<<< orphan*/ ) ; 
 int TIMER_CALL_LOCAL ; 
 int /*<<< orphan*/  TIMER_KDEBUG_TRACE (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UINT64_MAX ; 
 int /*<<< orphan*/  VM_KERNEL_UNSLIDE_OR_PERM (TYPE_2__*) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  ml_get_interrupts_enabled () ; 
 int /*<<< orphan*/  qe (TYPE_2__*) ; 
 scalar_t__ queue_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  queue_end (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  queue_first (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  queue_next (int /*<<< orphan*/ ) ; 
 scalar_t__ serverperfmode ; 
 int /*<<< orphan*/  simple_lock_try (TYPE_12__*) ; 
 int /*<<< orphan*/  simple_unlock (TYPE_12__*) ; 
 int /*<<< orphan*/  timer_call_entry_dequeue (TYPE_2__*) ; 
 int /*<<< orphan*/  timer_call_entry_dequeue_async (TYPE_2__*) ; 
 int /*<<< orphan*/  timer_call_entry_enqueue_deadline (TYPE_2__*,TYPE_3__*,scalar_t__) ; 
 int /*<<< orphan*/  timer_queue_lock_spin (TYPE_3__*) ; 
 int /*<<< orphan*/  timer_queue_migrate_lock_skips ; 
 int /*<<< orphan*/  timer_queue_unlock (TYPE_3__*) ; 

int
timer_queue_migrate(mpqueue_head_t *queue_from, mpqueue_head_t *queue_to)
{
	timer_call_t	call;
	timer_call_t	head_to;
	int		timers_migrated = 0;

	DBG("timer_queue_migrate(%p,%p)\n", queue_from, queue_to);

	assert(!ml_get_interrupts_enabled());
	assert(queue_from != queue_to);

	if (serverperfmode) {
		/*
		 * if we're running a high end server
		 * avoid migrations... they add latency
		 * and don't save us power under typical
		 * server workloads
		 */
		return -4;
	}

	/*
	 * Take both local (from) and target (to) timer queue locks while
	 * moving the timers from the local queue to the target processor.
	 * We assume that the target is always the boot processor.
	 * But only move if all of the following is true:
	 *  - the target queue is non-empty
	 *  - the local queue is non-empty
	 *  - the local queue's first deadline is later than the target's
	 *  - the local queue contains no non-migrateable "local" call
	 * so that we need not have the target resync.
	 */

        timer_queue_lock_spin(queue_to);

	head_to = TIMER_CALL(queue_first(&queue_to->head));
	if (queue_empty(&queue_to->head)) {
		timers_migrated = -1;
		goto abort1;
	}

        timer_queue_lock_spin(queue_from);

	if (queue_empty(&queue_from->head)) {
		timers_migrated = -2;
		goto abort2;
	}

	call = TIMER_CALL(queue_first(&queue_from->head));
	if (TCE(call)->deadline < TCE(head_to)->deadline) {
		timers_migrated = 0;
		goto abort2;
	}

	/* perform scan for non-migratable timers */
	do {
		if (call->flags & TIMER_CALL_LOCAL) {
			timers_migrated = -3;
			goto abort2;
		}
		call = TIMER_CALL(queue_next(qe(call)));
	} while (!queue_end(&queue_from->head, qe(call)));

	/* migration loop itself -- both queues are locked */
	while (!queue_empty(&queue_from->head)) {
		call = TIMER_CALL(queue_first(&queue_from->head));
		if (!simple_lock_try(&call->lock)) {
			/* case (2b) lock order inversion, dequeue only */
#ifdef TIMER_ASSERT
			TIMER_KDEBUG_TRACE(KDEBUG_TRACE, 
				DECR_TIMER_ASYNC_DEQ | DBG_FUNC_NONE,
				VM_KERNEL_UNSLIDE_OR_PERM(call),
				VM_KERNEL_UNSLIDE_OR_PERM(TCE(call)->queue),
				VM_KERNEL_UNSLIDE_OR_PERM(call->lock.interlock.lock_data),
				0x2b, 0);
#endif
			timer_queue_migrate_lock_skips++;
			timer_call_entry_dequeue_async(call);
			continue;
		}
		timer_call_entry_dequeue(call);
		timer_call_entry_enqueue_deadline(
			call, queue_to, TCE(call)->deadline);
		timers_migrated++;
		simple_unlock(&call->lock);
	}
	queue_from->earliest_soft_deadline = UINT64_MAX;
abort2:
       	timer_queue_unlock(queue_from);
abort1:
       	timer_queue_unlock(queue_to);

	return timers_migrated;
}