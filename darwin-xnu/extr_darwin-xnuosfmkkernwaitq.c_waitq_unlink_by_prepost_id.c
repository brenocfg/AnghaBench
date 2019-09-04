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
typedef  int /*<<< orphan*/  uint64_t ;
struct TYPE_2__ {struct waitq* wqp_wq_ptr; } ;
struct wq_prepost {TYPE_1__ wqp_wq; } ;
struct waitq_set {int dummy; } ;
struct waitq {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  disable_preemption () ; 
 int /*<<< orphan*/  enable_preemption () ; 
 int /*<<< orphan*/  waitq_irq_safe (struct waitq*) ; 
 int /*<<< orphan*/  waitq_lock (struct waitq*) ; 
 int /*<<< orphan*/  waitq_unlink_locked (struct waitq*,struct waitq_set*) ; 
 int /*<<< orphan*/  waitq_unlock (struct waitq*) ; 
 int /*<<< orphan*/  waitq_valid (struct waitq*) ; 
 struct wq_prepost* wq_prepost_get (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wq_prepost_put (struct wq_prepost*) ; 

void waitq_unlink_by_prepost_id(uint64_t wqp_id, struct waitq_set *wqset)
{
	struct wq_prepost *wqp;

	disable_preemption();
	wqp = wq_prepost_get(wqp_id);
	if (wqp) {
		struct waitq *wq;

		wq = wqp->wqp_wq.wqp_wq_ptr;

		/*
		 * lock the waitq, then release our prepost ID reference, then
		 * unlink the waitq from the wqset: this ensures that we don't
		 * hold a prepost ID reference during the unlink, but we also
		 * complete the unlink operation atomically to avoid a race
		 * with waitq_unlink[_all].
		 */
		assert(!waitq_irq_safe(wq));

		waitq_lock(wq);
		wq_prepost_put(wqp);

		if (!waitq_valid(wq)) {
			/* someone already tore down this waitq! */
			waitq_unlock(wq);
			enable_preemption();
			return;
		}

		/* this _may_ drop the wq lock, but that's OK */
		waitq_unlink_locked(wq, wqset);

		waitq_unlock(wq);
	}
	enable_preemption();
	return;
}