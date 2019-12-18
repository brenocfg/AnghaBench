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
struct request {int dummy; } ;
struct io_context {int /*<<< orphan*/  lock; struct as_io_context* aic; } ;
struct as_io_context {scalar_t__ ttime_samples; scalar_t__ ttime_mean; int /*<<< orphan*/  state; int /*<<< orphan*/  nr_dispatched; int /*<<< orphan*/  nr_queued; } ;
struct as_data {int exit_prob; int exit_no_coop; scalar_t__ new_ttime_mean; scalar_t__ antic_expire; scalar_t__ ioc_finished; struct io_context* io_context; } ;

/* Variables and functions */
 int /*<<< orphan*/  AS_TASK_RUNNING ; 
 int /*<<< orphan*/  BUG_ON (int) ; 
 struct io_context* RQ_IOC (struct request*) ; 
 scalar_t__ as_antic_expired (struct as_data*) ; 
 scalar_t__ as_close_req (struct as_data*,struct as_io_context*,struct request*) ; 
 int /*<<< orphan*/  as_update_iohist (struct as_data*,struct as_io_context*,struct request*) ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 scalar_t__ rq_is_sync (struct request*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int as_can_break_anticipation(struct as_data *ad, struct request *rq)
{
	struct io_context *ioc;
	struct as_io_context *aic;

	ioc = ad->io_context;
	BUG_ON(!ioc);
	spin_lock(&ioc->lock);

	if (rq && ioc == RQ_IOC(rq)) {
		/* request from same process */
		spin_unlock(&ioc->lock);
		return 1;
	}

	if (ad->ioc_finished && as_antic_expired(ad)) {
		/*
		 * In this situation status should really be FINISHED,
		 * however the timer hasn't had the chance to run yet.
		 */
		spin_unlock(&ioc->lock);
		return 1;
	}

	aic = ioc->aic;
	if (!aic) {
		spin_unlock(&ioc->lock);
		return 0;
	}

	if (atomic_read(&aic->nr_queued) > 0) {
		/* process has more requests queued */
		spin_unlock(&ioc->lock);
		return 1;
	}

	if (atomic_read(&aic->nr_dispatched) > 0) {
		/* process has more requests dispatched */
		spin_unlock(&ioc->lock);
		return 1;
	}

	if (rq && rq_is_sync(rq) && as_close_req(ad, aic, rq)) {
		/*
		 * Found a close request that is not one of ours.
		 *
		 * This makes close requests from another process update
		 * our IO history. Is generally useful when there are
		 * two or more cooperating processes working in the same
		 * area.
		 */
		if (!test_bit(AS_TASK_RUNNING, &aic->state)) {
			if (aic->ttime_samples == 0)
				ad->exit_prob = (7*ad->exit_prob + 256)/8;

			ad->exit_no_coop = (7*ad->exit_no_coop)/8;
		}

		as_update_iohist(ad, aic, rq);
		spin_unlock(&ioc->lock);
		return 1;
	}

	if (!test_bit(AS_TASK_RUNNING, &aic->state)) {
		/* process anticipated on has exited */
		if (aic->ttime_samples == 0)
			ad->exit_prob = (7*ad->exit_prob + 256)/8;

		if (ad->exit_no_coop > 128) {
			spin_unlock(&ioc->lock);
			return 1;
		}
	}

	if (aic->ttime_samples == 0) {
		if (ad->new_ttime_mean > ad->antic_expire) {
			spin_unlock(&ioc->lock);
			return 1;
		}
		if (ad->exit_prob * ad->exit_no_coop > 128*256) {
			spin_unlock(&ioc->lock);
			return 1;
		}
	} else if (aic->ttime_mean > ad->antic_expire) {
		/* the process thinks too much between requests */
		spin_unlock(&ioc->lock);
		return 1;
	}
	spin_unlock(&ioc->lock);
	return 0;
}