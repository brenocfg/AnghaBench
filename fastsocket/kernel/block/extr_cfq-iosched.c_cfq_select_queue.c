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
struct cfq_queue {TYPE_1__* cfqg; scalar_t__ dispatched; int /*<<< orphan*/  new_cfqq; int /*<<< orphan*/  sort_list; } ;
struct cfq_data {scalar_t__ cfq_group_idle; int /*<<< orphan*/  idle_slice_timer; int /*<<< orphan*/  rq_queued; struct cfq_queue* active_queue; } ;
struct TYPE_2__ {int nr_cfqq; scalar_t__ dispatched; } ;

/* Variables and functions */
 scalar_t__ RB_EMPTY_ROOT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cfq_cfqq_must_dispatch (struct cfq_queue*) ; 
 scalar_t__ cfq_cfqq_wait_busy (struct cfq_queue*) ; 
 int /*<<< orphan*/  cfq_choose_cfqg (struct cfq_data*) ; 
 struct cfq_queue* cfq_close_cooperator (struct cfq_data*,struct cfq_queue*) ; 
 struct cfq_queue* cfq_set_active_queue (struct cfq_data*,struct cfq_queue*) ; 
 int /*<<< orphan*/  cfq_setup_merge (struct cfq_queue*,struct cfq_queue*) ; 
 scalar_t__ cfq_should_idle (struct cfq_data*,struct cfq_queue*) ; 
 int /*<<< orphan*/  cfq_slice_expired (struct cfq_data*,int /*<<< orphan*/ ) ; 
 scalar_t__ cfq_slice_used (struct cfq_queue*) ; 
 scalar_t__ timer_pending (int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct cfq_queue *cfq_select_queue(struct cfq_data *cfqd)
{
	struct cfq_queue *cfqq, *new_cfqq = NULL;

	cfqq = cfqd->active_queue;
	if (!cfqq)
		goto new_queue;

	if (!cfqd->rq_queued)
		return NULL;

	/*
	 * We were waiting for group to get backlogged. Expire the queue
	 */
	if (cfq_cfqq_wait_busy(cfqq) && !RB_EMPTY_ROOT(&cfqq->sort_list))
		goto expire;

	/*
	 * The active queue has run out of time, expire it and select new.
	 */
	if (cfq_slice_used(cfqq) && !cfq_cfqq_must_dispatch(cfqq)) {
		/*
		 * If slice had not expired at the completion of last request
		 * we might not have turned on wait_busy flag. Don't expire
		 * the queue yet. Allow the group to get backlogged.
		 *
		 * The very fact that we have used the slice, that means we
		 * have been idling all along on this queue and it should be
		 * ok to wait for this request to complete.
		 */
		if (cfqq->cfqg->nr_cfqq == 1 && RB_EMPTY_ROOT(&cfqq->sort_list)
		    && cfqq->dispatched && cfq_should_idle(cfqd, cfqq)) {
			cfqq = NULL;
			goto keep_queue;
		} else
			goto check_group_idle;
	}

	/*
	 * The active queue has requests and isn't expired, allow it to
	 * dispatch.
	 */
	if (!RB_EMPTY_ROOT(&cfqq->sort_list))
		goto keep_queue;

	/*
	 * If another queue has a request waiting within our mean seek
	 * distance, let it run.  The expire code will check for close
	 * cooperators and put the close queue at the front of the service
	 * tree.  If possible, merge the expiring queue with the new cfqq.
	 */
	new_cfqq = cfq_close_cooperator(cfqd, cfqq);
	if (new_cfqq) {
		if (!cfqq->new_cfqq)
			cfq_setup_merge(cfqq, new_cfqq);
		goto expire;
	}

	/*
	 * No requests pending. If the active queue still has requests in
	 * flight or is idling for a new request, allow either of these
	 * conditions to happen (or time out) before selecting a new queue.
	 */
	if (timer_pending(&cfqd->idle_slice_timer)) {
		cfqq = NULL;
		goto keep_queue;
	}

	if (cfqq->dispatched && cfq_should_idle(cfqd, cfqq)) {
		cfqq = NULL;
		goto keep_queue;
	}

	/*
	 * If group idle is enabled and there are requests dispatched from
	 * this group, wait for requests to complete.
	 */
check_group_idle:
	if (cfqd->cfq_group_idle && cfqq->cfqg->nr_cfqq == 1
	    && cfqq->cfqg->dispatched) {
		cfqq = NULL;
		goto keep_queue;
	}

expire:
	cfq_slice_expired(cfqd, 0);
new_queue:
	/*
	 * Current queue expired. Check if we have to switch to a new
	 * service tree
	 */
	if (!new_cfqq)
		cfq_choose_cfqg(cfqd);

	cfqq = cfq_set_active_queue(cfqd, new_cfqq);
keep_queue:
	return cfqq;
}