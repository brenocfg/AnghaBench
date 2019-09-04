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
struct waitq_set {int /*<<< orphan*/  wqset_id; } ;
struct waitq {int dummy; } ;
typedef  int /*<<< orphan*/  kern_return_t ;

/* Variables and functions */
 int /*<<< orphan*/  KERN_INVALID_ARGUMENT ; 
 int /*<<< orphan*/  KERN_SUCCESS ; 
 scalar_t__ VM_KERNEL_UNSLIDE_OR_PERM (struct waitq*) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  waitq_irq_safe (struct waitq*) ; 
 int /*<<< orphan*/  waitq_lock (struct waitq*) ; 
 int /*<<< orphan*/  waitq_unlink_locked (struct waitq*,struct waitq_set*) ; 
 int /*<<< orphan*/  waitq_unlock (struct waitq*) ; 
 int /*<<< orphan*/  waitq_valid (struct waitq*) ; 
 int waitqs_is_set (struct waitq_set*) ; 
 int /*<<< orphan*/  wqdbg_v (char*,void*,int /*<<< orphan*/ ) ; 

kern_return_t waitq_unlink(struct waitq *waitq, struct waitq_set *wqset)
{
	kern_return_t kr = KERN_SUCCESS;

	assert(waitqs_is_set(wqset));

	/*
	 * we allow the waitq to be invalid because the caller may be trying
	 * to clear out old/dirty state
	 */
	if (!waitq_valid(waitq))
		return KERN_INVALID_ARGUMENT;

	wqdbg_v("unlink waitq %p from set 0x%llx",
		(void *)VM_KERNEL_UNSLIDE_OR_PERM(waitq), wqset->wqset_id);

	assert(!waitq_irq_safe(waitq));

	waitq_lock(waitq);

	kr = waitq_unlink_locked(waitq, wqset);

	waitq_unlock(waitq);
	return kr;
}