#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_23__   TYPE_3__ ;
typedef  struct TYPE_22__   TYPE_2__ ;
typedef  struct TYPE_21__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  xfs_trans_t ;
struct TYPE_22__ {int m_flags; } ;
typedef  TYPE_2__ xfs_mount_t ;
struct TYPE_21__ {scalar_t__ di_nlink; int di_flags; int /*<<< orphan*/  di_mode; } ;
struct TYPE_23__ {int /*<<< orphan*/  i_ino; TYPE_1__ i_d; TYPE_2__* i_mount; } ;
typedef  TYPE_3__ xfs_inode_t ;
typedef  int /*<<< orphan*/  xfs_fsblock_t ;
typedef  int /*<<< orphan*/  xfs_bmap_free_t ;
struct xfs_name {int /*<<< orphan*/  len; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int /*<<< orphan*/  EIO ; 
 int /*<<< orphan*/  EMLINK ; 
 int ENOSPC ; 
 int /*<<< orphan*/  EXDEV ; 
 int /*<<< orphan*/  S_ISDIR (int /*<<< orphan*/ ) ; 
 int XFS_DIFLAG_PROJINHERIT ; 
 int XFS_ERROR (int /*<<< orphan*/ ) ; 
 scalar_t__ XFS_FORCED_SHUTDOWN (TYPE_2__*) ; 
 int XFS_ICHGTIME_CHG ; 
 int XFS_ICHGTIME_MOD ; 
 int /*<<< orphan*/  XFS_ILOCK_EXCL ; 
 int /*<<< orphan*/  XFS_ILOG_CORE ; 
 int /*<<< orphan*/  XFS_LINK_LOG_COUNT ; 
 int /*<<< orphan*/  XFS_LINK_LOG_RES (TYPE_2__*) ; 
 int XFS_LINK_SPACE_RES (TYPE_2__*,int /*<<< orphan*/ ) ; 
 scalar_t__ XFS_MAXLINK ; 
 int XFS_MOUNT_DIRSYNC ; 
 int XFS_MOUNT_WSYNC ; 
 int XFS_TRANS_ABORT ; 
 int /*<<< orphan*/  XFS_TRANS_LINK ; 
 int /*<<< orphan*/  XFS_TRANS_PERM_LOG_RES ; 
 int XFS_TRANS_RELEASE_LOG_RES ; 
 int /*<<< orphan*/  trace_xfs_link (TYPE_3__*,struct xfs_name*) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  xfs_bmap_cancel (int /*<<< orphan*/ *) ; 
 int xfs_bmap_finish (int /*<<< orphan*/ **,int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  xfs_bmap_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int xfs_bumplink (int /*<<< orphan*/ *,TYPE_3__*) ; 
 int xfs_dir_canenter (int /*<<< orphan*/ *,TYPE_3__*,struct xfs_name*,int) ; 
 int xfs_dir_createname (int /*<<< orphan*/ *,TYPE_3__*,struct xfs_name*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 scalar_t__ xfs_get_projid (TYPE_3__*) ; 
 int /*<<< orphan*/  xfs_lock_two_inodes (TYPE_3__*,TYPE_3__*,int /*<<< orphan*/ ) ; 
 int xfs_qm_dqattach (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * xfs_trans_alloc (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xfs_trans_cancel (int /*<<< orphan*/ *,int) ; 
 int xfs_trans_commit (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  xfs_trans_ichgtime (int /*<<< orphan*/ *,TYPE_3__*,int) ; 
 int /*<<< orphan*/  xfs_trans_ijoin_ref (int /*<<< orphan*/ *,TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xfs_trans_log_inode (int /*<<< orphan*/ *,TYPE_3__*,int /*<<< orphan*/ ) ; 
 int xfs_trans_reserve (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xfs_trans_set_sync (int /*<<< orphan*/ *) ; 

int
xfs_link(
	xfs_inode_t		*tdp,
	xfs_inode_t		*sip,
	struct xfs_name		*target_name)
{
	xfs_mount_t		*mp = tdp->i_mount;
	xfs_trans_t		*tp;
	int			error;
	xfs_bmap_free_t         free_list;
	xfs_fsblock_t           first_block;
	int			cancel_flags;
	int			committed;
	int			resblks;

	trace_xfs_link(tdp, target_name);

	ASSERT(!S_ISDIR(sip->i_d.di_mode));

	if (XFS_FORCED_SHUTDOWN(mp))
		return XFS_ERROR(EIO);

	error = xfs_qm_dqattach(sip, 0);
	if (error)
		goto std_return;

	error = xfs_qm_dqattach(tdp, 0);
	if (error)
		goto std_return;

	tp = xfs_trans_alloc(mp, XFS_TRANS_LINK);
	cancel_flags = XFS_TRANS_RELEASE_LOG_RES;
	resblks = XFS_LINK_SPACE_RES(mp, target_name->len);
	error = xfs_trans_reserve(tp, resblks, XFS_LINK_LOG_RES(mp), 0,
			XFS_TRANS_PERM_LOG_RES, XFS_LINK_LOG_COUNT);
	if (error == ENOSPC) {
		resblks = 0;
		error = xfs_trans_reserve(tp, 0, XFS_LINK_LOG_RES(mp), 0,
				XFS_TRANS_PERM_LOG_RES, XFS_LINK_LOG_COUNT);
	}
	if (error) {
		cancel_flags = 0;
		goto error_return;
	}

	xfs_lock_two_inodes(sip, tdp, XFS_ILOCK_EXCL);

	xfs_trans_ijoin_ref(tp, sip, XFS_ILOCK_EXCL);
	xfs_trans_ijoin_ref(tp, tdp, XFS_ILOCK_EXCL);

	/*
	 * If the source has too many links, we can't make any more to it.
	 */
	if (sip->i_d.di_nlink >= XFS_MAXLINK) {
		error = XFS_ERROR(EMLINK);
		goto error_return;
	}

	/*
	 * If we are using project inheritance, we only allow hard link
	 * creation in our tree when the project IDs are the same; else
	 * the tree quota mechanism could be circumvented.
	 */
	if (unlikely((tdp->i_d.di_flags & XFS_DIFLAG_PROJINHERIT) &&
		     (xfs_get_projid(tdp) != xfs_get_projid(sip)))) {
		error = XFS_ERROR(EXDEV);
		goto error_return;
	}

	error = xfs_dir_canenter(tp, tdp, target_name, resblks);
	if (error)
		goto error_return;

	xfs_bmap_init(&free_list, &first_block);

	error = xfs_dir_createname(tp, tdp, target_name, sip->i_ino,
					&first_block, &free_list, resblks);
	if (error)
		goto abort_return;
	xfs_trans_ichgtime(tp, tdp, XFS_ICHGTIME_MOD | XFS_ICHGTIME_CHG);
	xfs_trans_log_inode(tp, tdp, XFS_ILOG_CORE);

	error = xfs_bumplink(tp, sip);
	if (error)
		goto abort_return;

	/*
	 * If this is a synchronous mount, make sure that the
	 * link transaction goes to disk before returning to
	 * the user.
	 */
	if (mp->m_flags & (XFS_MOUNT_WSYNC|XFS_MOUNT_DIRSYNC)) {
		xfs_trans_set_sync(tp);
	}

	error = xfs_bmap_finish (&tp, &free_list, &committed);
	if (error) {
		xfs_bmap_cancel(&free_list);
		goto abort_return;
	}

	return xfs_trans_commit(tp, XFS_TRANS_RELEASE_LOG_RES);

 abort_return:
	cancel_flags |= XFS_TRANS_ABORT;
 error_return:
	xfs_trans_cancel(tp, cancel_flags);
 std_return:
	return error;
}