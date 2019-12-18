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
struct xfs_buftarg {int /*<<< orphan*/  bt_lru_lock; int /*<<< orphan*/  bt_lru_nr; } ;
struct xfs_buf {int b_lru_flags; int /*<<< orphan*/  b_hold; int /*<<< orphan*/  b_lru; struct xfs_buftarg* b_target; int /*<<< orphan*/  b_lru_ref; int /*<<< orphan*/  b_flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int /*<<< orphan*/  XBF_STALE ; 
 int _XBF_LRU_DISPOSE ; 
 int /*<<< orphan*/  atomic_dec (int /*<<< orphan*/ *) ; 
 int atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_del_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

void
xfs_buf_stale(
	struct xfs_buf	*bp)
{
	bp->b_flags |= XBF_STALE;
	atomic_set(&(bp)->b_lru_ref, 0);
	if (!list_empty(&bp->b_lru)) {
		struct xfs_buftarg *btp = bp->b_target;

		spin_lock(&btp->bt_lru_lock);
		if (!list_empty(&bp->b_lru) &&
		    !(bp->b_lru_flags & _XBF_LRU_DISPOSE)) {
			list_del_init(&bp->b_lru);
			btp->bt_lru_nr--;
			atomic_dec(&bp->b_hold);
		}
		spin_unlock(&btp->bt_lru_lock);
	}
	ASSERT(atomic_read(&bp->b_hold) >= 1);
}