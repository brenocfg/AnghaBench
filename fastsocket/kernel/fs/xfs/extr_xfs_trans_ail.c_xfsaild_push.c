#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_3__ ;
typedef  struct TYPE_17__   TYPE_2__ ;
typedef  struct TYPE_16__   TYPE_1__ ;

/* Type definitions */
struct TYPE_17__ {TYPE_1__* m_ddev_targp; int /*<<< orphan*/  m_log; } ;
typedef  TYPE_2__ xfs_mount_t ;
typedef  scalar_t__ xfs_lsn_t ;
struct TYPE_18__ {scalar_t__ li_lsn; } ;
typedef  TYPE_3__ xfs_log_item_t ;
struct xfs_ail_cursor {int dummy; } ;
struct xfs_ail {scalar_t__ xa_target; scalar_t__ xa_log_flush; int /*<<< orphan*/  xa_lock; int /*<<< orphan*/  xa_ail; struct xfs_ail_cursor xa_cursors; TYPE_2__* xa_mount; } ;
struct TYPE_16__ {int /*<<< orphan*/  bt_task; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IOP_PUSH (TYPE_3__*) ; 
 int /*<<< orphan*/  IOP_PUSHBUF (TYPE_3__*) ; 
 int IOP_TRYLOCK (TYPE_3__*) ; 
 scalar_t__ XFS_FORCED_SHUTDOWN (TYPE_2__*) ; 
#define  XFS_ITEM_LOCKED 131 
#define  XFS_ITEM_PINNED 130 
#define  XFS_ITEM_PUSHBUF 129 
#define  XFS_ITEM_SUCCESS 128 
 int /*<<< orphan*/  XFS_LOG_SYNC ; 
 scalar_t__ XFS_LSN_CMP (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  XFS_STATS_INC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  trace_xfs_ail_locked (TYPE_3__*) ; 
 int /*<<< orphan*/  trace_xfs_ail_pinned (TYPE_3__*) ; 
 int /*<<< orphan*/  trace_xfs_ail_push (TYPE_3__*) ; 
 int /*<<< orphan*/  trace_xfs_ail_pushbuf (TYPE_3__*) ; 
 int /*<<< orphan*/  trace_xfs_ail_pushbuf_pinned (TYPE_3__*) ; 
 int /*<<< orphan*/  wake_up_process (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xfs_log_force (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xfs_trans_ail_cursor_done (struct xfs_ail*,struct xfs_ail_cursor*) ; 
 TYPE_3__* xfs_trans_ail_cursor_first (struct xfs_ail*,struct xfs_ail_cursor*,scalar_t__) ; 
 int /*<<< orphan*/  xfs_trans_ail_cursor_init (struct xfs_ail*,struct xfs_ail_cursor*) ; 
 TYPE_3__* xfs_trans_ail_cursor_next (struct xfs_ail*,struct xfs_ail_cursor*) ; 
 int /*<<< orphan*/  xs_push_ail ; 
 int /*<<< orphan*/  xs_push_ail_flush ; 
 int /*<<< orphan*/  xs_push_ail_locked ; 
 int /*<<< orphan*/  xs_push_ail_pinned ; 
 int /*<<< orphan*/  xs_push_ail_pushbuf ; 
 int /*<<< orphan*/  xs_push_ail_success ; 

long
xfsaild_push(
	struct xfs_ail	*ailp,
	xfs_lsn_t	*last_lsn)
{
	long		tout = 10;
	xfs_lsn_t	last_pushed_lsn = *last_lsn;
	xfs_lsn_t	target;
	xfs_lsn_t	lsn;
	xfs_log_item_t	*lip;
	int		flush_log, count, stuck;
	xfs_mount_t	*mp = ailp->xa_mount;
	struct xfs_ail_cursor	*cur = &ailp->xa_cursors;
	int		push_xfsbufd = 0;

	/*
	 * If last time we ran we encountered pinned items, force the log first
	 * and wait for it before pushing again.
	 */
	spin_lock(&ailp->xa_lock);
	if (last_pushed_lsn == 0 && ailp->xa_log_flush &&
	    !list_empty(&ailp->xa_ail)) {
		ailp->xa_log_flush = 0;
		spin_unlock(&ailp->xa_lock);
		XFS_STATS_INC(xs_push_ail_flush);
		xfs_log_force(mp, XFS_LOG_SYNC);
		spin_lock(&ailp->xa_lock);
	}

	target = ailp->xa_target;
	xfs_trans_ail_cursor_init(ailp, cur);
	lip = xfs_trans_ail_cursor_first(ailp, cur, *last_lsn);
	if (!lip || XFS_FORCED_SHUTDOWN(mp)) {
		/*
		 * AIL is empty or our push has reached the end.
		 */
		xfs_trans_ail_cursor_done(ailp, cur);
		spin_unlock(&ailp->xa_lock);
		*last_lsn = 0;
		tout = 50;
		return tout;
	}

	XFS_STATS_INC(xs_push_ail);

	/*
	 * While the item we are looking at is below the given threshold
	 * try to flush it out. We'd like not to stop until we've at least
	 * tried to push on everything in the AIL with an LSN less than
	 * the given threshold.
	 *
	 * However, we will stop after a certain number of pushes and wait
	 * for a reduced timeout to fire before pushing further. This
	 * prevents use from spinning when we can't do anything or there is
	 * lots of contention on the AIL lists.
	 */
	lsn = lip->li_lsn;
	flush_log = stuck = count = 0;
	while ((XFS_LSN_CMP(lip->li_lsn, target) <= 0)) {
		int	lock_result;
		/*
		 * If we can lock the item without sleeping, unlock the AIL
		 * lock and flush the item.  Then re-grab the AIL lock so we
		 * can look for the next item on the AIL. List changes are
		 * handled by the AIL lookup functions internally
		 *
		 * If we can't lock the item, either its holder will flush it
		 * or it is already being flushed or it is being relogged.  In
		 * any of these case it is being taken care of and we can just
		 * skip to the next item in the list.
		 */
		lock_result = IOP_TRYLOCK(lip);
		spin_unlock(&ailp->xa_lock);
		switch (lock_result) {
		case XFS_ITEM_SUCCESS:
			XFS_STATS_INC(xs_push_ail_success);
			trace_xfs_ail_push(lip);

			IOP_PUSH(lip);
			last_pushed_lsn = lsn;
			break;

		case XFS_ITEM_PUSHBUF:
			XFS_STATS_INC(xs_push_ail_pushbuf);
			trace_xfs_ail_pushbuf(lip);

			if (!IOP_PUSHBUF(lip)) {
				trace_xfs_ail_pushbuf_pinned(lip);
				stuck++;
				ailp->xa_log_flush++;
			} else {
				last_pushed_lsn = lsn;
			}
			push_xfsbufd = 1;
			break;

		case XFS_ITEM_PINNED:
			XFS_STATS_INC(xs_push_ail_pinned);
			trace_xfs_ail_pinned(lip);

			stuck++;
			ailp->xa_log_flush++;
			break;

		case XFS_ITEM_LOCKED:
			XFS_STATS_INC(xs_push_ail_locked);
			trace_xfs_ail_locked(lip);
			stuck++;
			break;

		default:
			ASSERT(0);
			break;
		}

		spin_lock(&ailp->xa_lock);
		/* should we bother continuing? */
		if (XFS_FORCED_SHUTDOWN(mp))
			break;
		ASSERT(mp->m_log);

		count++;

		/*
		 * Are there too many items we can't do anything with?
		 * If we we are skipping too many items because we can't flush
		 * them or they are already being flushed, we back off and
		 * given them time to complete whatever operation is being
		 * done. i.e. remove pressure from the AIL while we can't make
		 * progress so traversals don't slow down further inserts and
		 * removals to/from the AIL.
		 *
		 * The value of 100 is an arbitrary magic number based on
		 * observation.
		 */
		if (stuck > 100)
			break;

		lip = xfs_trans_ail_cursor_next(ailp, cur);
		if (lip == NULL)
			break;
		lsn = lip->li_lsn;
	}
	xfs_trans_ail_cursor_done(ailp, cur);
	spin_unlock(&ailp->xa_lock);

	if (push_xfsbufd) {
		/* we've got delayed write buffers to flush */
		wake_up_process(mp->m_ddev_targp->bt_task);
	}

	if (!count) {
		/* We're past our target or empty, so idle */
		last_pushed_lsn = 0;
		ailp->xa_log_flush = 0;

		tout = 50;
	} else if (XFS_LSN_CMP(lsn, target) >= 0) {
		/*
		 * We reached the target so wait a bit longer for I/O to
		 * complete and remove pushed items from the AIL before we
		 * start the next scan from the start of the AIL.
		 */
		tout = 50;
		last_pushed_lsn = 0;
	} else if ((stuck * 100) / count > 90) {
		/*
		 * Either there is a lot of contention on the AIL or we
		 * are stuck due to operations in progress. "Stuck" in this
		 * case is defined as >90% of the items we tried to push
		 * were stuck.
		 *
		 * Backoff a bit more to allow some I/O to complete before
		 * restarting from the start of the AIL. This prevents us
		 * from spinning on the same items, and if they are pinned will
		 * all the restart to issue a log force to unpin the stuck
		 * items.
		 */
		tout = 20;
		last_pushed_lsn = 0;
	}

	*last_lsn = last_pushed_lsn;
	return tout;
}