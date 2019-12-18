#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_24__   TYPE_3__ ;
typedef  struct TYPE_23__   TYPE_2__ ;
typedef  struct TYPE_22__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  xfs_trans_t ;
struct TYPE_23__ {int m_flags; } ;
typedef  TYPE_2__ xfs_mount_t ;
struct TYPE_22__ {int di_nlink; int /*<<< orphan*/  di_mode; } ;
struct TYPE_24__ {int /*<<< orphan*/  i_ino; TYPE_1__ i_d; TYPE_2__* i_mount; } ;
typedef  TYPE_3__ xfs_inode_t ;
typedef  int /*<<< orphan*/  xfs_fsblock_t ;
typedef  int /*<<< orphan*/  xfs_bmap_free_t ;
typedef  scalar_t__ uint ;
struct xfs_name {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int /*<<< orphan*/  EIO ; 
 int ENOENT ; 
 int ENOSPC ; 
 int /*<<< orphan*/  ENOTEMPTY ; 
 int S_ISDIR (int /*<<< orphan*/ ) ; 
 scalar_t__ XFS_DEFAULT_LOG_COUNT ; 
 int XFS_ERROR (int /*<<< orphan*/ ) ; 
 scalar_t__ XFS_FORCED_SHUTDOWN (TYPE_2__*) ; 
 int XFS_ICHGTIME_CHG ; 
 int XFS_ICHGTIME_MOD ; 
 int /*<<< orphan*/  XFS_ILOCK_EXCL ; 
 int /*<<< orphan*/  XFS_ILOG_CORE ; 
 int XFS_MOUNT_DIRSYNC ; 
 int XFS_MOUNT_WSYNC ; 
 scalar_t__ XFS_REMOVE_LOG_COUNT ; 
 int /*<<< orphan*/  XFS_REMOVE_LOG_RES (TYPE_2__*) ; 
 scalar_t__ XFS_REMOVE_SPACE_RES (TYPE_2__*) ; 
 int XFS_TRANS_ABORT ; 
 int /*<<< orphan*/  XFS_TRANS_PERM_LOG_RES ; 
 int XFS_TRANS_RELEASE_LOG_RES ; 
 int /*<<< orphan*/  XFS_TRANS_REMOVE ; 
 int /*<<< orphan*/  XFS_TRANS_RMDIR ; 
 int /*<<< orphan*/  trace_xfs_remove (TYPE_3__*,struct xfs_name*) ; 
 int /*<<< orphan*/  xfs_bmap_cancel (int /*<<< orphan*/ *) ; 
 int xfs_bmap_finish (int /*<<< orphan*/ **,int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  xfs_bmap_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xfs_dir_isempty (TYPE_3__*) ; 
 int xfs_dir_removename (int /*<<< orphan*/ *,TYPE_3__*,struct xfs_name*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,scalar_t__) ; 
 int xfs_droplink (int /*<<< orphan*/ *,TYPE_3__*) ; 
 int /*<<< orphan*/  xfs_filestream_deassociate (TYPE_3__*) ; 
 scalar_t__ xfs_inode_is_filestream (TYPE_3__*) ; 
 int /*<<< orphan*/  xfs_lock_two_inodes (TYPE_3__*,TYPE_3__*,int /*<<< orphan*/ ) ; 
 int xfs_qm_dqattach (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * xfs_trans_alloc (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xfs_trans_cancel (int /*<<< orphan*/ *,int) ; 
 int xfs_trans_commit (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  xfs_trans_ichgtime (int /*<<< orphan*/ *,TYPE_3__*,int) ; 
 int /*<<< orphan*/  xfs_trans_ijoin_ref (int /*<<< orphan*/ *,TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xfs_trans_log_inode (int /*<<< orphan*/ *,TYPE_3__*,int /*<<< orphan*/ ) ; 
 int xfs_trans_reserve (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  xfs_trans_set_sync (int /*<<< orphan*/ *) ; 

int
xfs_remove(
	xfs_inode_t             *dp,
	struct xfs_name		*name,
	xfs_inode_t		*ip)
{
	xfs_mount_t		*mp = dp->i_mount;
	xfs_trans_t             *tp = NULL;
	int			is_dir = S_ISDIR(ip->i_d.di_mode);
	int                     error = 0;
	xfs_bmap_free_t         free_list;
	xfs_fsblock_t           first_block;
	int			cancel_flags;
	int			committed;
	int			link_zero;
	uint			resblks;
	uint			log_count;

	trace_xfs_remove(dp, name);

	if (XFS_FORCED_SHUTDOWN(mp))
		return XFS_ERROR(EIO);

	error = xfs_qm_dqattach(dp, 0);
	if (error)
		goto std_return;

	error = xfs_qm_dqattach(ip, 0);
	if (error)
		goto std_return;

	if (is_dir) {
		tp = xfs_trans_alloc(mp, XFS_TRANS_RMDIR);
		log_count = XFS_DEFAULT_LOG_COUNT;
	} else {
		tp = xfs_trans_alloc(mp, XFS_TRANS_REMOVE);
		log_count = XFS_REMOVE_LOG_COUNT;
	}
	cancel_flags = XFS_TRANS_RELEASE_LOG_RES;

	/*
	 * We try to get the real space reservation first,
	 * allowing for directory btree deletion(s) implying
	 * possible bmap insert(s).  If we can't get the space
	 * reservation then we use 0 instead, and avoid the bmap
	 * btree insert(s) in the directory code by, if the bmap
	 * insert tries to happen, instead trimming the LAST
	 * block from the directory.
	 */
	resblks = XFS_REMOVE_SPACE_RES(mp);
	error = xfs_trans_reserve(tp, resblks, XFS_REMOVE_LOG_RES(mp), 0,
				  XFS_TRANS_PERM_LOG_RES, log_count);
	if (error == ENOSPC) {
		resblks = 0;
		error = xfs_trans_reserve(tp, 0, XFS_REMOVE_LOG_RES(mp), 0,
					  XFS_TRANS_PERM_LOG_RES, log_count);
	}
	if (error) {
		ASSERT(error != ENOSPC);
		cancel_flags = 0;
		goto out_trans_cancel;
	}

	xfs_lock_two_inodes(dp, ip, XFS_ILOCK_EXCL);

	xfs_trans_ijoin_ref(tp, dp, XFS_ILOCK_EXCL);
	xfs_trans_ijoin_ref(tp, ip, XFS_ILOCK_EXCL);

	/*
	 * If we're removing a directory perform some additional validation.
	 */
	cancel_flags |= XFS_TRANS_ABORT;
	if (is_dir) {
		ASSERT(ip->i_d.di_nlink >= 2);
		if (ip->i_d.di_nlink != 2) {
			error = XFS_ERROR(ENOTEMPTY);
			goto out_trans_cancel;
		}
		if (!xfs_dir_isempty(ip)) {
			error = XFS_ERROR(ENOTEMPTY);
			goto out_trans_cancel;
		}

		/* Drop the link from ip's "..".  */
		error = xfs_droplink(tp, dp);
		if (error)
			goto out_trans_cancel;

		/* Drop the "." link from ip to self.  */
		error = xfs_droplink(tp, ip);
		if (error)
			goto out_trans_cancel;
	} else {
		/*
		 * When removing a non-directory we need to log the parent
		 * inode here.  For a directory this is done implicitly
		 * by the xfs_droplink call for the ".." entry.
		 */
		xfs_trans_log_inode(tp, dp, XFS_ILOG_CORE);
	}
	xfs_trans_ichgtime(tp, dp, XFS_ICHGTIME_MOD | XFS_ICHGTIME_CHG);

	/* Drop the link from dp to ip. */
	error = xfs_droplink(tp, ip);
	if (error)
		goto out_trans_cancel;

	/* Determine if this is the last link while the inode is locked */
	link_zero = (ip->i_d.di_nlink == 0);

	xfs_bmap_init(&free_list, &first_block);
	error = xfs_dir_removename(tp, dp, name, ip->i_ino,
					&first_block, &free_list, resblks);
	if (error) {
		ASSERT(error != ENOENT);
		goto out_bmap_cancel;
	}

	/*
	 * If this is a synchronous mount, make sure that the
	 * remove transaction goes to disk before returning to
	 * the user.
	 */
	if (mp->m_flags & (XFS_MOUNT_WSYNC|XFS_MOUNT_DIRSYNC))
		xfs_trans_set_sync(tp);

	error = xfs_bmap_finish(&tp, &free_list, &committed);
	if (error)
		goto out_bmap_cancel;

	error = xfs_trans_commit(tp, XFS_TRANS_RELEASE_LOG_RES);
	if (error)
		goto std_return;

	/*
	 * If we are using filestreams, kill the stream association.
	 * If the file is still open it may get a new one but that
	 * will get killed on last close in xfs_close() so we don't
	 * have to worry about that.
	 */
	if (!is_dir && link_zero && xfs_inode_is_filestream(ip))
		xfs_filestream_deassociate(ip);

	return 0;

 out_bmap_cancel:
	xfs_bmap_cancel(&free_list);
 out_trans_cancel:
	xfs_trans_cancel(tp, cancel_flags);
 std_return:
	return error;
}