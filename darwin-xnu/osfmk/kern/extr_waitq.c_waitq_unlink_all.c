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
struct waitq {int dummy; } ;
typedef  int /*<<< orphan*/  kern_return_t ;

/* Variables and functions */
 int /*<<< orphan*/  KERN_SUCCESS ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  panic (char*,struct waitq*) ; 
 int /*<<< orphan*/  waitq_irq_safe (struct waitq*) ; 
 int /*<<< orphan*/  waitq_lock (struct waitq*) ; 
 int /*<<< orphan*/  waitq_unlink_all_unlock (struct waitq*) ; 
 int /*<<< orphan*/  waitq_unlock (struct waitq*) ; 
 int /*<<< orphan*/  waitq_valid (struct waitq*) ; 

kern_return_t waitq_unlink_all(struct waitq *waitq)
{
	kern_return_t kr = KERN_SUCCESS;

	if (!waitq_valid(waitq))
		panic("Invalid waitq: %p", waitq);

	assert(!waitq_irq_safe(waitq));
	waitq_lock(waitq);
	if (!waitq_valid(waitq)) {
		waitq_unlock(waitq);
		return KERN_SUCCESS;
	}

	kr = waitq_unlink_all_unlock(waitq);
	/* waitq unlocked and set links deallocated */

	return kr;
}