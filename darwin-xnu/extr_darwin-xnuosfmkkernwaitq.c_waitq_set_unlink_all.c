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
struct waitq_set {int /*<<< orphan*/  wqset_q; } ;
typedef  int /*<<< orphan*/  kern_return_t ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  waitq_irq_safe (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  waitq_set_lock (struct waitq_set*) ; 
 int /*<<< orphan*/  waitq_set_unlink_all_unlock (struct waitq_set*) ; 
 int waitqs_is_set (struct waitq_set*) ; 

kern_return_t waitq_set_unlink_all(struct waitq_set *wqset)
{
	assert(waitqs_is_set(wqset));
	assert(!waitq_irq_safe(&wqset->wqset_q));

	waitq_set_lock(wqset);
	return waitq_set_unlink_all_unlock(wqset);
	/* wqset unlocked and set links and preposts deallocated */
}