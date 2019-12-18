#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int b_flags; int /*<<< orphan*/  b_list; TYPE_1__* b_target; } ;
typedef  TYPE_2__ xfs_buf_t ;
typedef  int /*<<< orphan*/  spinlock_t ;
struct TYPE_6__ {int /*<<< orphan*/  bt_delwrite_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int XBF_DELWRI ; 
 int /*<<< orphan*/  _RET_IP_ ; 
 int _XBF_DELWRI_Q ; 
 int /*<<< orphan*/  list_del_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  trace_xfs_buf_delwri_dequeue (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xfs_buf_rele (TYPE_2__*) ; 

void
xfs_buf_delwri_dequeue(
	xfs_buf_t		*bp)
{
	spinlock_t		*dwlk = &bp->b_target->bt_delwrite_lock;
	int			dequeued = 0;

	spin_lock(dwlk);
	if ((bp->b_flags & XBF_DELWRI) && !list_empty(&bp->b_list)) {
		ASSERT(bp->b_flags & _XBF_DELWRI_Q);
		list_del_init(&bp->b_list);
		dequeued = 1;
	}
	bp->b_flags &= ~(XBF_DELWRI|_XBF_DELWRI_Q);
	spin_unlock(dwlk);

	if (dequeued)
		xfs_buf_rele(bp);

	trace_xfs_buf_delwri_dequeue(bp, _RET_IP_);
}