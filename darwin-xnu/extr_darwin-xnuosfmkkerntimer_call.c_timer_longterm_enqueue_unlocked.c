#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_8__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint64_t ;
typedef  int uint32_t ;
struct TYPE_10__ {scalar_t__ interval; scalar_t__ deadline; scalar_t__ preempted; TYPE_3__* call; } ;
struct TYPE_11__ {TYPE_1__ threshold; int /*<<< orphan*/  enqueues; } ;
typedef  TYPE_2__ timer_longterm_t ;
typedef  TYPE_3__* timer_call_t ;
typedef  int /*<<< orphan*/  timer_call_param_t ;
typedef  int /*<<< orphan*/  mpqueue_head_t ;
typedef  scalar_t__ boolean_t ;
struct TYPE_13__ {int /*<<< orphan*/  param1; scalar_t__ deadline; } ;
struct TYPE_12__ {int flags; int /*<<< orphan*/  lock; scalar_t__ soft_deadline; scalar_t__ ttd; } ;

/* Variables and functions */
 scalar_t__ FALSE ; 
 TYPE_8__* TCE (TYPE_3__*) ; 
 int TIMER_CALL_LOCAL ; 
 scalar_t__ TIMER_LONGTERM_NONE ; 
 scalar_t__ TRUE ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  master_cpu ; 
 int /*<<< orphan*/  ml_get_interrupts_enabled () ; 
 int /*<<< orphan*/  simple_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  simple_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * timer_call_dequeue_unlocked (TYPE_3__*) ; 
 int /*<<< orphan*/  timer_call_entry_enqueue_tail (TYPE_3__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  timer_call_nosync_cpu (int /*<<< orphan*/ ,void (*) (void*),void*) ; 
 TYPE_2__ timer_longterm ; 
 int /*<<< orphan*/ * timer_longterm_queue ; 
 scalar_t__ timer_longterm_update ; 
 int /*<<< orphan*/  timer_queue_lock_spin (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  timer_queue_unlock (int /*<<< orphan*/ *) ; 

mpqueue_head_t *
timer_longterm_enqueue_unlocked(timer_call_t	call,
				uint64_t	now,
				uint64_t	deadline,
				mpqueue_head_t	**old_queue,
				uint64_t	soft_deadline,
				uint64_t	ttd,
				timer_call_param_t	param1,
				uint32_t	callout_flags)
{
	timer_longterm_t	*tlp = &timer_longterm;
	boolean_t		update_required = FALSE;
	uint64_t		longterm_threshold;

	longterm_threshold = now + tlp->threshold.interval;

	/*
	 * Return NULL without doing anything if:
	 *  - this timer is local, or
	 *  - the longterm mechanism is disabled, or
	 *  - this deadline is too short.
	 */
	if ((callout_flags & TIMER_CALL_LOCAL) != 0 ||
	    (tlp->threshold.interval == TIMER_LONGTERM_NONE) ||
		(deadline <= longterm_threshold))
		return NULL;

	/*
 	 * Remove timer from its current queue, if any.
	 */
	*old_queue = timer_call_dequeue_unlocked(call);

	/*
	 * Lock the longterm queue, queue timer and determine
	 * whether an update is necessary.
	 */
	assert(!ml_get_interrupts_enabled());
	simple_lock(&call->lock);
	timer_queue_lock_spin(timer_longterm_queue);
	TCE(call)->deadline = deadline;
	TCE(call)->param1 = param1;
	call->ttd = ttd;
	call->soft_deadline = soft_deadline;
	call->flags = callout_flags;
	timer_call_entry_enqueue_tail(call, timer_longterm_queue);
	
	tlp->enqueues++;

	/*
	 * We'll need to update the currently set threshold timer
	 * if the new deadline is sooner and no sooner update is in flight.
	 */ 
	if (deadline < tlp->threshold.deadline &&
	    deadline < tlp->threshold.preempted) {
		tlp->threshold.preempted = deadline;
		tlp->threshold.call = call;
		update_required = TRUE;
	}
	timer_queue_unlock(timer_longterm_queue);
	simple_unlock(&call->lock);
	
	if (update_required) {
		/*
		 * Note: this call expects that calling the master cpu
		 * alone does not involve locking the topo lock.
		 */
		timer_call_nosync_cpu(
			master_cpu,
			(void (*)(void *)) timer_longterm_update,
			(void *)tlp);
	}

	return timer_longterm_queue;
}