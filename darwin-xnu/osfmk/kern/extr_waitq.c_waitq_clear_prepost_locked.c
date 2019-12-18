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
typedef  scalar_t__ uint64_t ;
struct TYPE_2__ {scalar_t__ id; } ;
struct wq_prepost {TYPE_1__ wqp_prepostid; } ;
struct waitq {scalar_t__ waitq_prepost_id; } ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  delay (int) ; 
 int /*<<< orphan*/  disable_preemption () ; 
 int /*<<< orphan*/  enable_preemption () ; 
 int /*<<< orphan*/  waitq_irq_safe (struct waitq*) ; 
 int /*<<< orphan*/  waitq_lock (struct waitq*) ; 
 int /*<<< orphan*/  waitq_unlock (struct waitq*) ; 
 struct wq_prepost* wq_prepost_get (scalar_t__) ; 
 int /*<<< orphan*/  wq_prepost_invalidate (struct wq_prepost*) ; 
 int /*<<< orphan*/  wq_prepost_put (struct wq_prepost*) ; 
 int /*<<< orphan*/  wqdbg_v (char*,scalar_t__,scalar_t__) ; 
 scalar_t__ wqp_refcnt (struct wq_prepost*) ; 

int waitq_clear_prepost_locked(struct waitq *waitq)
{
	struct wq_prepost *wqp;
	int dropped_lock = 0;

	assert(!waitq_irq_safe(waitq));

	if (waitq->waitq_prepost_id == 0)
		return 0;

	wqp = wq_prepost_get(waitq->waitq_prepost_id);
	waitq->waitq_prepost_id = 0;
	if (wqp) {
		uint64_t wqp_id = wqp->wqp_prepostid.id;
		wqdbg_v("invalidate prepost 0x%llx (refcnt:%d)",
			wqp->wqp_prepostid.id, wqp_refcnt(wqp));
		wq_prepost_invalidate(wqp);
		while (wqp_refcnt(wqp) > 1) {

			/*
			 * Some other thread must have raced us to grab a link
			 * object reference before we invalidated it. This
			 * means that they are probably trying to access the
			 * waitq to which the prepost object points. We need
			 * to wait here until the other thread drops their
			 * reference. We know that no one else can get a
			 * reference (the object has been invalidated), and
			 * that prepost references are short-lived (dropped on
			 * a call to wq_prepost_put). We also know that no one
			 * blocks while holding a reference therefore the
			 * other reference holder must be on-core. We'll just
			 * sit and wait for the other reference to be dropped.
			 */
			disable_preemption();

			waitq_unlock(waitq);
			dropped_lock = 1;
			/*
			 * don't yield here, just spin and assume the other
			 * consumer is already on core...
			 */
			delay(1);

			waitq_lock(waitq);

			enable_preemption();
		}
		if (wqp_refcnt(wqp) > 0 && wqp->wqp_prepostid.id == wqp_id)
			wq_prepost_put(wqp);
	}

	return dropped_lock;
}