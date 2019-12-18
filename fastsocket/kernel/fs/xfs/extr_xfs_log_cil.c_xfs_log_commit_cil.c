#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  xfs_lsn_t ;
struct xfs_trans {TYPE_3__* t_ticket; int /*<<< orphan*/  t_commit_lsn; int /*<<< orphan*/  t_busy; } ;
struct xfs_mount {struct log* m_log; } ;
struct xfs_log_vec {int dummy; } ;
struct log {TYPE_2__* l_cilp; int /*<<< orphan*/  l_mp; } ;
struct TYPE_8__ {scalar_t__ t_curr_res; } ;
struct TYPE_7__ {int /*<<< orphan*/  xc_ctx_lock; TYPE_1__* xc_ctx; int /*<<< orphan*/  xc_cil_lock; } ;
struct TYPE_6__ {scalar_t__ space_used; int /*<<< orphan*/  busy_extents; int /*<<< orphan*/  sequence; } ;

/* Variables and functions */
 int XFS_LOG_REL_PERM_RESERV ; 
 int XFS_TRANS_RELEASE_LOG_RES ; 
 scalar_t__ XLOG_CIL_SPACE_LIMIT (struct log*) ; 
 int /*<<< orphan*/  down_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_splice_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  up_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xfs_log_done (struct xfs_mount*,TYPE_3__*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  xfs_trans_free_items (struct xfs_trans*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xfs_trans_unreserve_and_mod_sb (struct xfs_trans*) ; 
 int /*<<< orphan*/  xlog_cil_format_items (struct log*,struct xfs_log_vec*) ; 
 int /*<<< orphan*/  xlog_cil_insert_items (struct log*,struct xfs_log_vec*,TYPE_3__*) ; 
 int /*<<< orphan*/  xlog_cil_push (struct log*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xlog_print_tic_res (int /*<<< orphan*/ ,TYPE_3__*) ; 

void
xfs_log_commit_cil(
	struct xfs_mount	*mp,
	struct xfs_trans	*tp,
	struct xfs_log_vec	*log_vector,
	xfs_lsn_t		*commit_lsn,
	int			flags)
{
	struct log		*log = mp->m_log;
	int			log_flags = 0;
	int			push = 0;

	if (flags & XFS_TRANS_RELEASE_LOG_RES)
		log_flags = XFS_LOG_REL_PERM_RESERV;

	/*
	 * do all the hard work of formatting items (including memory
	 * allocation) outside the CIL context lock. This prevents stalling CIL
	 * pushes when we are low on memory and a transaction commit spends a
	 * lot of time in memory reclaim.
	 */
	xlog_cil_format_items(log, log_vector);

	/* lock out background commit */
	down_read(&log->l_cilp->xc_ctx_lock);
	if (commit_lsn)
		*commit_lsn = log->l_cilp->xc_ctx->sequence;

	xlog_cil_insert_items(log, log_vector, tp->t_ticket);

	/* check we didn't blow the reservation */
	if (tp->t_ticket->t_curr_res < 0)
		xlog_print_tic_res(log->l_mp, tp->t_ticket);

	/* attach the transaction to the CIL if it has any busy extents */
	if (!list_empty(&tp->t_busy)) {
		spin_lock(&log->l_cilp->xc_cil_lock);
		list_splice_init(&tp->t_busy,
					&log->l_cilp->xc_ctx->busy_extents);
		spin_unlock(&log->l_cilp->xc_cil_lock);
	}

	tp->t_commit_lsn = *commit_lsn;
	xfs_log_done(mp, tp->t_ticket, NULL, log_flags);
	xfs_trans_unreserve_and_mod_sb(tp);

	/*
	 * Once all the items of the transaction have been copied to the CIL,
	 * the items can be unlocked and freed.
	 *
	 * This needs to be done before we drop the CIL context lock because we
	 * have to update state in the log items and unlock them before they go
	 * to disk. If we don't, then the CIL checkpoint can race with us and
	 * we can run checkpoint completion before we've updated and unlocked
	 * the log items. This affects (at least) processing of stale buffers,
	 * inodes and EFIs.
	 */
	xfs_trans_free_items(tp, *commit_lsn, 0);

	/* check for background commit before unlock */
	if (log->l_cilp->xc_ctx->space_used > XLOG_CIL_SPACE_LIMIT(log))
		push = 1;

	up_read(&log->l_cilp->xc_ctx_lock);

	/*
	 * We need to push CIL every so often so we don't cache more than we
	 * can fit in the log. The limit really is that a checkpoint can't be
	 * more than half the log (the current checkpoint is not allowed to
	 * overwrite the previous checkpoint), but commit latency and memory
	 * usage limit this to a smaller size in most cases.
	 */
	if (push)
		xlog_cil_push(log, 0);
}