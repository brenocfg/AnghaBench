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
struct xfs_buftarg {int /*<<< orphan*/  bt_delwrite_lock; int /*<<< orphan*/  bt_delwrite_queue; } ;
struct xfs_buf {int b_flags; long b_queuetime; int /*<<< orphan*/  b_list; struct xfs_buftarg* b_target; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int XBF_DELWRI ; 
 int _XBF_DELWRI_Q ; 
 long jiffies ; 
 int /*<<< orphan*/  list_move (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int msecs_to_jiffies (int) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int xfs_buf_age_centisecs ; 

void
xfs_buf_delwri_promote(
	struct xfs_buf	*bp)
{
	struct xfs_buftarg *btp = bp->b_target;
	long		age = xfs_buf_age_centisecs * msecs_to_jiffies(10) + 1;

	ASSERT(bp->b_flags & XBF_DELWRI);
	ASSERT(bp->b_flags & _XBF_DELWRI_Q);

	/*
	 * Check the buffer age before locking the delayed write queue as we
	 * don't need to promote buffers that are already past the flush age.
	 */
	if (bp->b_queuetime < jiffies - age)
		return;
	bp->b_queuetime = jiffies - age;
	spin_lock(&btp->bt_delwrite_lock);
	list_move(&bp->b_list, &btp->bt_delwrite_queue);
	spin_unlock(&btp->bt_delwrite_lock);
}