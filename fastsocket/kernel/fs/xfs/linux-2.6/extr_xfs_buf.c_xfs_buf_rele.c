#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int b_flags; int /*<<< orphan*/  b_rbnode; int /*<<< orphan*/  b_lru_ref; int /*<<< orphan*/  b_hold; int /*<<< orphan*/  b_lru; struct xfs_perag* b_pag; } ;
typedef  TYPE_1__ xfs_buf_t ;
struct xfs_perag {int /*<<< orphan*/  pag_buf_lock; int /*<<< orphan*/  pag_buf_tree; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int RB_EMPTY_NODE (int /*<<< orphan*/ *) ; 
 int XBF_DELWRI ; 
 int XBF_STALE ; 
 int /*<<< orphan*/  _RET_IP_ ; 
 int _XBF_DELWRI_Q ; 
 scalar_t__ atomic_dec_and_lock (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ atomic_dec_and_test (int /*<<< orphan*/ *) ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 int list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rb_erase (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  trace_xfs_buf_rele (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xfs_buf_free (TYPE_1__*) ; 
 int /*<<< orphan*/  xfs_buf_lru_add (TYPE_1__*) ; 
 int /*<<< orphan*/  xfs_buf_lru_del (TYPE_1__*) ; 
 int /*<<< orphan*/  xfs_perag_put (struct xfs_perag*) ; 

void
xfs_buf_rele(
	xfs_buf_t		*bp)
{
	struct xfs_perag	*pag = bp->b_pag;

	trace_xfs_buf_rele(bp, _RET_IP_);

	if (!pag) {
		ASSERT(list_empty(&bp->b_lru));
		ASSERT(RB_EMPTY_NODE(&bp->b_rbnode));
		if (atomic_dec_and_test(&bp->b_hold))
			xfs_buf_free(bp);
		return;
	}

	ASSERT(!RB_EMPTY_NODE(&bp->b_rbnode));

	ASSERT(atomic_read(&bp->b_hold) > 0);
	if (atomic_dec_and_lock(&bp->b_hold, &pag->pag_buf_lock)) {
		if (!(bp->b_flags & XBF_STALE) &&
			   atomic_read(&bp->b_lru_ref)) {
			xfs_buf_lru_add(bp);
			spin_unlock(&pag->pag_buf_lock);
		} else {
			xfs_buf_lru_del(bp);
			ASSERT(!(bp->b_flags & (XBF_DELWRI|_XBF_DELWRI_Q)));
			rb_erase(&bp->b_rbnode, &pag->pag_buf_tree);
			spin_unlock(&pag->pag_buf_lock);
			xfs_perag_put(pag);
			xfs_buf_free(bp);
		}
	}
}