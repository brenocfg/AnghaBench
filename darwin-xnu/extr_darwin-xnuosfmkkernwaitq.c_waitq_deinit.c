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
struct waitq {scalar_t__ waitq_isvalid; } ;
typedef  int /*<<< orphan*/  spl_t ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  splsched () ; 
 int /*<<< orphan*/  splx (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  waitq_empty (struct waitq*) ; 
 scalar_t__ waitq_irq_safe (struct waitq*) ; 
 int /*<<< orphan*/  waitq_is_queue (struct waitq*) ; 
 int /*<<< orphan*/  waitq_lock (struct waitq*) ; 
 int /*<<< orphan*/  waitq_unlink_all_unlock (struct waitq*) ; 
 int /*<<< orphan*/  waitq_unlock (struct waitq*) ; 
 int /*<<< orphan*/  waitq_valid (struct waitq*) ; 

void waitq_deinit(struct waitq *waitq)
{
	spl_t s;

	if (!waitq || !waitq_is_queue(waitq))
		return;

	if (waitq_irq_safe(waitq))
		s = splsched();
	waitq_lock(waitq);
	if (!waitq_valid(waitq)) {
		waitq_unlock(waitq);
		if (waitq_irq_safe(waitq))
			splx(s);
		return;
	}

	waitq->waitq_isvalid = 0;

	if (!waitq_irq_safe(waitq)) {
		waitq_unlink_all_unlock(waitq);
		/* waitq unlocked and set links deallocated */
	} else {
		waitq_unlock(waitq);
		splx(s);
	}

	assert(waitq_empty(waitq));
}