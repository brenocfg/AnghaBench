#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int (* wql_callback_func ) (struct waitq*,void*,struct waitq_link*) ;
typedef  scalar_t__ uint64_t ;
struct waitq {scalar_t__ waitq_set_id; } ;
struct waitq_set {scalar_t__ wqset_id; struct waitq wqset_q; } ;
struct TYPE_6__ {scalar_t__ id; } ;
struct TYPE_5__ {struct waitq_set* wql_set; } ;
struct TYPE_4__ {scalar_t__ left_setid; scalar_t__ right_setid; } ;
struct waitq_link {TYPE_3__ wql_setid; TYPE_2__ wql_wqs; TYPE_1__ wql_link; } ;

/* Variables and functions */
 int LINK_WALK_FULL_DAG ; 
 int LINK_WALK_FULL_DAG_UNLOCKED ; 
 int WQL_ALL ; 
 int WQL_LINK ; 
 int WQL_WQS ; 
 int WQ_ITERATE_CONTINUE ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  waitq_irq_safe (struct waitq*) ; 
 scalar_t__ waitq_set_is_valid (struct waitq_set*) ; 
 int /*<<< orphan*/  waitq_set_lock (struct waitq_set*) ; 
 int /*<<< orphan*/  waitq_set_unlock (struct waitq_set*) ; 
 struct waitq_link* wql_get_link (scalar_t__) ; 
 int /*<<< orphan*/  wql_put_link (struct waitq_link*) ; 
 int wql_type (struct waitq_link*) ; 

__attribute__((used)) static __attribute__((noinline))
int walk_waitq_links(int walk_type, struct waitq *waitq,
		     uint64_t setid, int link_type,
		     void *ctx, wql_callback_func cb)
{
	struct waitq_link *link;
	uint64_t nextid;
	int wqltype;

	link = wql_get_link(setid);

	/* invalid link */
	if (!link)
		return WQ_ITERATE_CONTINUE;

	setid = nextid = 0;
	wqltype = wql_type(link);
	if (wqltype == WQL_LINK) {
		setid  = link->wql_link.left_setid;
		nextid = link->wql_link.right_setid;
	}

	/*
	 * Make the callback only on specified link_type (or all links)
	 * Note that after the callback, the link object may be
	 * invalid. The only valid thing we can do is put our
	 * reference to it (which may put it back on the free list)
	 */
	if (link_type == WQL_ALL || link_type == wqltype) {
		/* allow the callback to early-out */
		int ret = cb(waitq, ctx, link);
		if (ret != WQ_ITERATE_CONTINUE) {
			wql_put_link(link);
			return ret;
		}
	}

	if (wqltype == WQL_WQS &&
	    (walk_type == LINK_WALK_FULL_DAG ||
	     walk_type == LINK_WALK_FULL_DAG_UNLOCKED)) {
		/*
		 * Recurse down any sets to which this wait queue set was
		 * added.  We do this just before we put our reference to
		 * the link object (which may free it).
		 */
		struct waitq_set *wqset = link->wql_wqs.wql_set;
		int ret = WQ_ITERATE_CONTINUE;
		int should_unlock = 0;
		uint64_t wqset_setid = 0;

		if (waitq_set_is_valid(wqset) && walk_type == LINK_WALK_FULL_DAG) {
			assert(!waitq_irq_safe(&wqset->wqset_q));
			waitq_set_lock(wqset);
			should_unlock = 1;
		}

		/*
		 * verify the linked waitq set as it could have been
		 * invalidated before we grabbed the lock!
		 */
		if (wqset->wqset_id != link->wql_setid.id) {
			/* This is the bottom of the tree: just get out */
			if (should_unlock) {
				waitq_set_unlock(wqset);
			}
			wql_put_link(link);
			return WQ_ITERATE_CONTINUE;
		}

		wqset_setid = wqset->wqset_q.waitq_set_id;

		if (wqset_setid > 0)
			ret = walk_waitq_links(walk_type, &wqset->wqset_q,
					       wqset_setid, link_type, ctx, cb);
		if (should_unlock) {
			waitq_set_unlock(wqset);
		}
		if (ret != WQ_ITERATE_CONTINUE) {
			wql_put_link(link);
			return ret;
		}
	}

	wql_put_link(link);

	/* recurse down left side of the tree */
	if (setid) {
		int ret = walk_waitq_links(walk_type, waitq, setid, link_type, ctx, cb);
		if (ret != WQ_ITERATE_CONTINUE)
			return ret;
	}

	/* recurse down right side of the tree */
	if (nextid)
		return walk_waitq_links(walk_type, waitq, nextid, link_type, ctx, cb);

	return WQ_ITERATE_CONTINUE;
}