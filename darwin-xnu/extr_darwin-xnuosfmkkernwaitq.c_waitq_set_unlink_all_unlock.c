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
typedef  scalar_t__ uint64_t ;
struct TYPE_6__ {scalar_t__ waitq_prepost; } ;
struct waitq_set {TYPE_3__ wqset_q; scalar_t__ wqset_prepost_id; int /*<<< orphan*/  wqset_id; } ;
struct TYPE_5__ {int /*<<< orphan*/  id; } ;
struct TYPE_4__ {struct waitq_set* wql_set; } ;
struct waitq_link {TYPE_2__ wql_setid; TYPE_1__ wql_wqs; } ;
typedef  int /*<<< orphan*/  kern_return_t ;

/* Variables and functions */
 int /*<<< orphan*/  KERN_SUCCESS ; 
 int /*<<< orphan*/  WQL_WQS ; 
 int /*<<< orphan*/  waitq_set_unlock (struct waitq_set*) ; 
 int /*<<< orphan*/  waitq_unlink_all_unlock (TYPE_3__*) ; 
 scalar_t__ waitqs_is_linked (struct waitq_set*) ; 
 int /*<<< orphan*/  wq_prepost_iterate (scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wqdbg_v (char*,int /*<<< orphan*/ ) ; 
 struct waitq_link* wql_get_link (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wql_invalidate (struct waitq_link*) ; 
 int /*<<< orphan*/  wql_mkvalid (struct waitq_link*) ; 
 int /*<<< orphan*/  wql_put_link (struct waitq_link*) ; 
 int /*<<< orphan*/  wql_realloc_link (struct waitq_link*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wqset_clear_prepost_chain_cb ; 

kern_return_t waitq_set_unlink_all_unlock(struct waitq_set *wqset)
{
	struct waitq_link *link;
	uint64_t prepost_id;

	wqdbg_v("unlink all queues from set 0x%llx", wqset->wqset_id);

	/*
	 * This operation does not require interaction with any of the set's
	 * constituent wait queues. All we have to do is invalidate the SetID
	 */

	if (waitqs_is_linked(wqset)){

		/* invalidate and re-alloc the link object first */
		link = wql_get_link(wqset->wqset_id);

		/* we may have raced with a waitq_set_deinit: handle this */
		if (!link) {
			waitq_set_unlock(wqset);
			return KERN_SUCCESS;
		}

		wql_invalidate(link);

		/* re-alloc the object to get a new generation ID */
		wql_realloc_link(link, WQL_WQS);
		link->wql_wqs.wql_set = wqset;

		wqset->wqset_id = link->wql_setid.id;
		wql_mkvalid(link);
		wql_put_link(link);
	}

	/* clear any preposts attached to this set */
	prepost_id = 0;
	if (wqset->wqset_q.waitq_prepost && wqset->wqset_prepost_id)
		prepost_id = wqset->wqset_prepost_id;
	/* else { TODO: notify kqueue subsystem? } */
	wqset->wqset_prepost_id = 0;

	/*
	 * clear set linkage and prepost object associated with this set:
	 * waitq sets may prepost to other sets if, for example, they are
	 * associated with a kqueue which is in a select set.
	 *
	 * This releases all the set link objects
	 * (links to other sets to which this set was previously added)
	 */
	waitq_unlink_all_unlock(&wqset->wqset_q);
	/* wqset->wqset_q unlocked */

	/* drop / unlink all the prepost table objects */
	if (prepost_id)
		(void)wq_prepost_iterate(prepost_id, NULL,
					 wqset_clear_prepost_chain_cb);

	return KERN_SUCCESS;
}