#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  wait_timeout_urgency_t ;
typedef  scalar_t__ wait_result_t ;
typedef  int /*<<< orphan*/  wait_interrupt_t ;
typedef  int /*<<< orphan*/  uint64_t ;
typedef  TYPE_1__* thread_t ;
struct waitq_set {int dummy; } ;
struct waitq {uintptr_t waitq_eventmask; int /*<<< orphan*/  waitq_fifo; } ;
typedef  int /*<<< orphan*/  spl_t ;
typedef  struct waitq* event64_t ;
typedef  int /*<<< orphan*/  boolean_t ;
struct TYPE_8__ {scalar_t__ sched_pri; int options; int /*<<< orphan*/  wait_timer_is_set; int /*<<< orphan*/  wait_timer_active; int /*<<< orphan*/  wait_timer; struct waitq* waitq; struct waitq* wait_event; scalar_t__ wait_result; int /*<<< orphan*/  started; } ;

/* Variables and functions */
 scalar_t__ BASEPRI_REALTIME ; 
 int /*<<< orphan*/  FALSE ; 
 struct waitq* NO_EVENT64 ; 
 scalar_t__ THREAD_AWAKENED ; 
 scalar_t__ THREAD_WAITING ; 
 int TH_OPT_VMPRIV ; 
 int /*<<< orphan*/  TRUE ; 
 int WQ_ITERATE_FOUND ; 
 uintptr_t _CAST_TO_EVENT_MASK (struct waitq*) ; 
 int /*<<< orphan*/  assert (int) ; 
 TYPE_1__* current_thread () ; 
 int /*<<< orphan*/  panic (char*,struct waitq*) ; 
 int /*<<< orphan*/  prepost_exists_cb ; 
 int /*<<< orphan*/  splsched () ; 
 int /*<<< orphan*/  splx (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  thread_lock (TYPE_1__*) ; 
 scalar_t__ thread_mark_wait_locked (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  thread_unlock (TYPE_1__*) ; 
 int /*<<< orphan*/  timer_call_enter_with_leeway (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  turnstile_recompute_priority_locked (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  turnstile_update_inheritor_locked (int /*<<< orphan*/ ) ; 
 struct waitq* waitq_get_safeq (struct waitq*) ; 
 int /*<<< orphan*/  waitq_irq_safe (struct waitq*) ; 
 scalar_t__ waitq_is_global (struct waitq*) ; 
 scalar_t__ waitq_is_set (struct waitq*) ; 
 scalar_t__ waitq_is_turnstile_queue (struct waitq*) ; 
 int /*<<< orphan*/  waitq_lock (struct waitq*) ; 
 scalar_t__ waitq_set_maybe_preposted (struct waitq_set*) ; 
 int /*<<< orphan*/  waitq_stats_count_wait (struct waitq*) ; 
 int /*<<< orphan*/  waitq_thread_insert (struct waitq*,TYPE_1__*,int) ; 
 int /*<<< orphan*/  waitq_to_turnstile (struct waitq*) ; 
 int /*<<< orphan*/  waitq_unlock (struct waitq*) ; 
 int wq_prepost_foreach_locked (struct waitq_set*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

wait_result_t waitq_assert_wait64_locked(struct waitq *waitq,
					  event64_t wait_event,
					  wait_interrupt_t interruptible,
					  wait_timeout_urgency_t urgency,
					  uint64_t deadline,
					  uint64_t leeway,
					  thread_t thread)
{
	wait_result_t wait_result;
	int realtime = 0;
	struct waitq *safeq;
	uintptr_t eventmask;
	spl_t s;


	/*
	 * Warning: Do _not_ place debugging print statements here.
	 *          The waitq is locked!
	 */
	assert(!thread->started || thread == current_thread());

	if (thread->waitq != NULL)
		panic("thread already waiting on %p", thread->waitq);

	if (waitq_is_set(waitq)) {
		struct waitq_set *wqset = (struct waitq_set *)waitq;
		/*
		 * early-out if the thread is waiting on a wait queue set
		 * that has already been pre-posted.
		 */
		if (wait_event == NO_EVENT64 && waitq_set_maybe_preposted(wqset)) {
			int ret;
			/*
			 * Run through the list of potential preposts. Because
			 * this is a hot path, we short-circuit the iteration
			 * if we find just one prepost object.
			 */
			ret = wq_prepost_foreach_locked(wqset, NULL,
							prepost_exists_cb);
			if (ret == WQ_ITERATE_FOUND) {
				s = splsched();
				thread_lock(thread);
				thread->wait_result = THREAD_AWAKENED;
				thread_unlock(thread);
				splx(s);
				return THREAD_AWAKENED;
			}
		}
	}

	s = splsched();

	/*
	 * If already dealing with an irq safe wait queue, we are all set.
	 * Otherwise, determine a global queue to use and lock it.
	 */
	if (!waitq_irq_safe(waitq)) {
		safeq = waitq_get_safeq(waitq);
		eventmask = _CAST_TO_EVENT_MASK(waitq);
		waitq_lock(safeq);
	} else {
		safeq = waitq;
		eventmask = _CAST_TO_EVENT_MASK(wait_event);
	}

	/* lock the thread now that we have the irq-safe waitq locked */
	thread_lock(thread);

	/*
	 * Realtime threads get priority for wait queue placements.
	 * This allows wait_queue_wakeup_one to prefer a waiting
	 * realtime thread, similar in principle to performing
	 * a wait_queue_wakeup_all and allowing scheduler prioritization
	 * to run the realtime thread, but without causing the
	 * lock contention of that scenario.
	 */
	if (thread->sched_pri >= BASEPRI_REALTIME)
		realtime = 1;

	/*
	 * This is the extent to which we currently take scheduling attributes
	 * into account.  If the thread is vm priviledged, we stick it at
	 * the front of the queue.  Later, these queues will honor the policy
	 * value set at waitq_init time.
	 */
	wait_result = thread_mark_wait_locked(thread, interruptible);
	/* thread->wait_result has been set */
	if (wait_result == THREAD_WAITING) {
		
		if (!safeq->waitq_fifo
		    || (thread->options & TH_OPT_VMPRIV) || realtime)
			waitq_thread_insert(safeq, thread, false);
		else
			waitq_thread_insert(safeq, thread, true);

		/* mark the event and real waitq, even if enqueued on a global safeq */
		thread->wait_event = wait_event;
		thread->waitq = waitq;

		if (deadline != 0) {
			boolean_t act;

			act = timer_call_enter_with_leeway(&thread->wait_timer,
							   NULL,
							   deadline, leeway,
							   urgency, FALSE);
			if (!act)
				thread->wait_timer_active++;
			thread->wait_timer_is_set = TRUE;
		}

		if (waitq_is_global(safeq))
			safeq->waitq_eventmask |= eventmask;

		waitq_stats_count_wait(waitq);
	}

	/* unlock the thread */
	thread_unlock(thread);

	/* update the inheritor's thread priority if the waitq is embedded in turnstile */
	if (waitq_is_turnstile_queue(safeq) && wait_result == THREAD_WAITING) {
		turnstile_recompute_priority_locked(waitq_to_turnstile(safeq));
		turnstile_update_inheritor_locked(waitq_to_turnstile(safeq));
	}

	/* unlock the safeq if we locked it here */
	if (safeq != waitq) {
		waitq_unlock(safeq);
	}

	splx(s);

	return wait_result;
}