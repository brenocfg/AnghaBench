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
struct waitq {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  disable_preemption () ; 
 int /*<<< orphan*/  enable_preemption () ; 
 int /*<<< orphan*/  waitq_irq_safe (struct waitq*) ; 
 int /*<<< orphan*/  waitq_lock (struct waitq*) ; 
 int /*<<< orphan*/  waitq_unlock (struct waitq*) ; 
 int /*<<< orphan*/  waitq_valid (struct waitq*) ; 
 struct wq_prepost* wq_prepost_get (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wq_prepost_put (struct wq_prepost*) ; 

struct waitq *waitq_lock_by_prepost_id(uint64_t wqp_id)
{
	struct waitq *wq = NULL;
	struct wq_prepost *wqp;

	disable_preemption();
	wqp = wq_prepost_get(wqp_id);
	if (wqp) {
		wq = wqp->wqp_wq.wqp_wq_ptr;

		assert(!waitq_irq_safe(wq));

		waitq_lock(wq);
		wq_prepost_put(wqp);

		if (!waitq_valid(wq)) {
			/* someone already tore down this waitq! */
			waitq_unlock(wq);
			enable_preemption();
			return NULL;
		}
	}
	enable_preemption();
	return wq;
}