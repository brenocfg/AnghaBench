#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint64_t ;
struct TYPE_4__ {scalar_t__ id; } ;
struct TYPE_3__ {scalar_t__ right_setid; scalar_t__ left_setid; } ;
struct waitq_link {TYPE_2__ wql_setid; TYPE_1__ wql_link; } ;
struct waitq {scalar_t__ waitq_set_id; } ;
typedef  scalar_t__ kern_return_t ;

/* Variables and functions */
 scalar_t__ KERN_ALREADY_IN_SET ; 
 scalar_t__ KERN_SUCCESS ; 
 int /*<<< orphan*/  LINK_WALK_ONE_LEVEL ; 
 int /*<<< orphan*/  WQL_ALL ; 
 scalar_t__ WQSET_NOT_LINKED ; 
 scalar_t__ WQ_ITERATE_FOUND ; 
 int /*<<< orphan*/  assert (int) ; 
 int waitq_held (struct waitq*) ; 
 int /*<<< orphan*/  waitq_inset_cb ; 
 scalar_t__ walk_waitq_links (int /*<<< orphan*/ ,struct waitq*,scalar_t__,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ) ; 
 struct waitq_link* wql_get_link (scalar_t__) ; 
 int /*<<< orphan*/  wql_mkvalid (struct waitq_link*) ; 
 int /*<<< orphan*/  wql_put_link (struct waitq_link*) ; 

__attribute__((used)) static kern_return_t waitq_link_internal(struct waitq *waitq,
					 uint64_t setid, struct waitq_link *link)
{
	struct waitq_link *qlink;
	kern_return_t kr;

	assert(waitq_held(waitq));
	assert(setid != 0);
	assert(setid != WQSET_NOT_LINKED);

	/*
	 * If the waitq_set_id field is empty, then this waitq is not
	 * a member of any other set. All we have to do is update the
	 * field.
	 */
	if (!waitq->waitq_set_id) {
		waitq->waitq_set_id = setid;
		return KERN_SUCCESS;
	}

	qlink = wql_get_link(waitq->waitq_set_id);
	if (!qlink) {
		/*
		 * The set to which this wait queue belonged has been
		 * destroyed / invalidated. We can re-use the waitq field.
		 */
		waitq->waitq_set_id = setid;
		return KERN_SUCCESS;
	}
	wql_put_link(qlink);

	/*
	 * Check to see if it's already a member of the set.
	 *
	 * TODO: check for cycles!
	 */
	kr = walk_waitq_links(LINK_WALK_ONE_LEVEL, waitq, waitq->waitq_set_id,
			      WQL_ALL, (void *)&setid, waitq_inset_cb);
	if (kr == WQ_ITERATE_FOUND)
		return KERN_ALREADY_IN_SET;

	/*
	 * This wait queue is a member of at least one set already,
	 * and _not_ a member of the given set. Use our previously
	 * allocated link object, and hook it up to the wait queue.
	 * Note that it's possible that one or more of the wait queue sets to
	 * which the wait queue belongs was invalidated before we allocated
	 * this link object. That's OK because the next time we use that
	 * object we'll just ignore it.
	 */
	link->wql_link.left_setid = setid;
	link->wql_link.right_setid = waitq->waitq_set_id;
	wql_mkvalid(link);

	waitq->waitq_set_id = link->wql_setid.id;

	return KERN_SUCCESS;
}