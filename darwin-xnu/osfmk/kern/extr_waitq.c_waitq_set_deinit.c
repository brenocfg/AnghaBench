#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint64_t ;
struct TYPE_5__ {scalar_t__ waitq_eventmask; scalar_t__ waitq_isvalid; scalar_t__ waitq_prepost; scalar_t__ waitq_fifo; } ;
struct waitq_set {scalar_t__ wqset_id; scalar_t__ wqset_prepost_id; TYPE_2__ wqset_q; } ;
struct TYPE_4__ {scalar_t__ id; } ;
struct waitq_link {TYPE_1__ wql_setid; } ;

/* Variables and functions */
 scalar_t__ WQL_WQS ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  delay (int) ; 
 int /*<<< orphan*/  panic (char*,struct waitq_set*) ; 
 int /*<<< orphan*/  waitq_irq_safe (TYPE_2__*) ; 
 int /*<<< orphan*/  waitq_set_lock (struct waitq_set*) ; 
 int /*<<< orphan*/  waitq_set_unlock (struct waitq_set*) ; 
 int /*<<< orphan*/  waitq_unlink_all_unlock (TYPE_2__*) ; 
 scalar_t__ waitqs_is_linked (struct waitq_set*) ; 
 int /*<<< orphan*/  waitqs_is_set (struct waitq_set*) ; 
 int /*<<< orphan*/  wq_prepost_iterate (scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct waitq_link* wql_get_link (scalar_t__) ; 
 int /*<<< orphan*/  wql_invalidate (struct waitq_link*) ; 
 int /*<<< orphan*/  wql_put_link (struct waitq_link*) ; 
 int wql_refcnt (struct waitq_link*) ; 
 scalar_t__ wql_type (struct waitq_link*) ; 
 int /*<<< orphan*/  wqset_clear_prepost_chain_cb ; 

void waitq_set_deinit(struct waitq_set *wqset)
{
	struct waitq_link *link = NULL;
	uint64_t set_id, prepost_id;

	if (!waitqs_is_set(wqset))
		panic("trying to de-initialize an invalid wqset @%p", wqset);

	assert(!waitq_irq_safe(&wqset->wqset_q));

	waitq_set_lock(wqset);

	set_id = wqset->wqset_id;

	if (waitqs_is_linked(wqset) || set_id == 0) {

		/* grab the set's link object */
		link = wql_get_link(set_id);
		if (link) {
			wql_invalidate(link);
		}
		/* someone raced us to deinit */
		if (!link || wqset->wqset_id != set_id || set_id != link->wql_setid.id) {
			if (link) {
				wql_put_link(link);
			}
			waitq_set_unlock(wqset);
			return;
		}

		/* the link should be a valid link object at this point */
		assert(link != NULL && wql_type(link) == WQL_WQS);

		wqset->wqset_id = 0;
	}

	/*
	 * This set may have a lot of preposts, or may have been a member of
	 * many other sets. To minimize spinlock hold times, we clear out the
	 * waitq set data structure under the lock-hold, but don't clear any
	 * table objects. We keep handles to the prepost and set linkage
	 * objects and free those outside the critical section.
	 */
	prepost_id = 0;
	if (wqset->wqset_q.waitq_prepost && wqset->wqset_prepost_id) {
		assert(link != NULL);
		prepost_id = wqset->wqset_prepost_id;
	}
	/* else { TODO: notify kqueue subsystem? } */
	wqset->wqset_prepost_id = 0;

	wqset->wqset_q.waitq_fifo = 0;
	wqset->wqset_q.waitq_prepost = 0;
	wqset->wqset_q.waitq_isvalid = 0;

	/* don't clear the 'waitq_irq' bit: it's used in locking! */
	wqset->wqset_q.waitq_eventmask = 0;

	waitq_unlink_all_unlock(&wqset->wqset_q);
	/* wqset->wqset_q unlocked and set links deallocated */


	if (link) {
		/*
		 * walk_waitq_links may race with us for access to the waitq set.
		 * If walk_waitq_links has a reference to the set, then we should wait
		 * until the link's refcount goes to 1 (our reference) before we exit
		 * this function. That way we ensure that the waitq set memory will
		 * remain valid even though it's been cleared out.
		 */
		while (wql_refcnt(link) > 1)
			delay(1);
		wql_put_link(link);
	}

	/* drop / unlink all the prepost table objects */
	/* JMM - can this happen before the delay? */
	if (prepost_id)
		(void)wq_prepost_iterate(prepost_id, NULL,
					 wqset_clear_prepost_chain_cb);
}