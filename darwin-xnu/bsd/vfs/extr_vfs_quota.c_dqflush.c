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
struct vnode {int dummy; } ;
struct TYPE_4__ {struct dquot* le_next; } ;
struct dquot {TYPE_1__* dq_qfile; scalar_t__ dq_cnt; TYPE_2__ dq_hash; } ;
struct dqhash {struct dquot* lh_first; } ;
struct TYPE_3__ {struct vnode* qf_vp; } ;

/* Variables and functions */
 int /*<<< orphan*/  LIST_REMOVE (struct dquot*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dq_hash ; 
 int /*<<< orphan*/  dq_list_lock () ; 
 int /*<<< orphan*/  dq_list_unlock () ; 
 size_t dqhash ; 
 struct dqhash* dqhashtbl ; 
 int /*<<< orphan*/  dqisinitialized () ; 
 int /*<<< orphan*/  panic (char*) ; 

void
dqflush(struct vnode *vp)
{
	struct dquot *dq, *nextdq;
	struct dqhash *dqh;

	if (!dqisinitialized())
		return;

	/*
	 * Move all dquot's that used to refer to this quota
	 * file off their hash chains (they will eventually
	 * fall off the head of the free list and be re-used).
	 */
	dq_list_lock();

	for (dqh = &dqhashtbl[dqhash]; dqh >= dqhashtbl; dqh--) {
		for (dq = dqh->lh_first; dq; dq = nextdq) {
			nextdq = dq->dq_hash.le_next;
			if (dq->dq_qfile->qf_vp != vp)
				continue;
			if (dq->dq_cnt)
				panic("dqflush: stray dquot");
			LIST_REMOVE(dq, dq_hash);
			dq->dq_qfile = NULL;
		}
	}
	dq_list_unlock();
}