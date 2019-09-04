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
typedef  scalar_t__ uint64_t ;
struct waitq_set {scalar_t__ wqset_id; } ;
struct waitq {scalar_t__ waitq_set_id; } ;
typedef  scalar_t__ kern_return_t ;
typedef  int boolean_t ;

/* Variables and functions */
 int FALSE ; 
 int /*<<< orphan*/  LINK_WALK_ONE_LEVEL ; 
 int TRUE ; 
 int /*<<< orphan*/  WQL_ALL ; 
 scalar_t__ WQ_ITERATE_FOUND ; 
 scalar_t__ WQ_ITERATE_SUCCESS ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  panic (char*,struct waitq*) ; 
 int /*<<< orphan*/  waitq_inset_cb ; 
 int /*<<< orphan*/  waitq_irq_safe (struct waitq*) ; 
 int /*<<< orphan*/  waitq_lock (struct waitq*) ; 
 int /*<<< orphan*/  waitq_unlock (struct waitq*) ; 
 int /*<<< orphan*/  waitq_valid (struct waitq*) ; 
 int /*<<< orphan*/  waitqs_is_linked (struct waitq_set*) ; 
 int /*<<< orphan*/  waitqs_is_set (struct waitq_set*) ; 
 scalar_t__ walk_waitq_links (int /*<<< orphan*/ ,struct waitq*,scalar_t__,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ) ; 

boolean_t waitq_member(struct waitq *waitq, struct waitq_set *wqset)
{
	kern_return_t kr = WQ_ITERATE_SUCCESS;
	uint64_t setid;

	if (!waitq_valid(waitq))
		panic("Invalid waitq: %p", waitq);
	assert(!waitq_irq_safe(waitq));

	if (!waitqs_is_set(wqset))
		return FALSE;

	waitq_lock(waitq);

	if (!waitqs_is_linked(wqset))
                goto out_unlock;

	setid = wqset->wqset_id;

	/* fast path: most waitqs are members of only 1 set */
	if (waitq->waitq_set_id == setid) {
		waitq_unlock(waitq);
		return TRUE;
	}

	/* walk the link table and look for the Set ID of wqset */
	kr = walk_waitq_links(LINK_WALK_ONE_LEVEL, waitq, waitq->waitq_set_id,
			      WQL_ALL, (void *)&setid, waitq_inset_cb);

out_unlock:
	waitq_unlock(waitq);
	return (kr == WQ_ITERATE_FOUND);
}