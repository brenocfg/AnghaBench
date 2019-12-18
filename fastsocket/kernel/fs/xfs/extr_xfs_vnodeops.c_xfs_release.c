#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_19__   TYPE_3__ ;
typedef  struct TYPE_18__   TYPE_2__ ;
typedef  struct TYPE_17__   TYPE_1__ ;

/* Type definitions */
struct TYPE_18__ {int m_flags; } ;
typedef  TYPE_2__ xfs_mount_t ;
struct TYPE_17__ {scalar_t__ di_mode; scalar_t__ di_nlink; } ;
struct TYPE_19__ {scalar_t__ i_delayed_blks; TYPE_1__ i_d; TYPE_2__* i_mount; } ;
typedef  TYPE_3__ xfs_inode_t ;

/* Variables and functions */
 int EAGAIN ; 
 int /*<<< orphan*/  FI_NONE ; 
 int /*<<< orphan*/  S_ISREG (scalar_t__) ; 
 int /*<<< orphan*/  VFS_I (TYPE_3__*) ; 
 scalar_t__ VN_DIRTY (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XBF_ASYNC ; 
 int /*<<< orphan*/  XFS_FORCED_SHUTDOWN (TYPE_2__*) ; 
 int /*<<< orphan*/  XFS_FREE_EOF_TRYLOCK ; 
 int /*<<< orphan*/  XFS_IDIRTY_RELEASE ; 
 int /*<<< orphan*/  XFS_ITRUNCATED ; 
 int XFS_MOUNT_RDONLY ; 
 scalar_t__ xfs_can_free_eofblocks (TYPE_3__*,int) ; 
 int /*<<< orphan*/  xfs_filestream_deassociate (TYPE_3__*) ; 
 int /*<<< orphan*/  xfs_flush_pages (TYPE_3__*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int xfs_free_eofblocks (TYPE_2__*,TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xfs_iflags_clear (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xfs_iflags_set (TYPE_3__*,int /*<<< orphan*/ ) ; 
 scalar_t__ xfs_iflags_test (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int xfs_iflags_test_and_clear (TYPE_3__*,int /*<<< orphan*/ ) ; 
 scalar_t__ xfs_inode_is_filestream (TYPE_3__*) ; 

int
xfs_release(
	xfs_inode_t	*ip)
{
	xfs_mount_t	*mp = ip->i_mount;
	int		error;

	if (!S_ISREG(ip->i_d.di_mode) || (ip->i_d.di_mode == 0))
		return 0;

	/* If this is a read-only mount, don't do this (would generate I/O) */
	if (mp->m_flags & XFS_MOUNT_RDONLY)
		return 0;

	if (!XFS_FORCED_SHUTDOWN(mp)) {
		int truncated;

		/*
		 * If we are using filestreams, and we have an unlinked
		 * file that we are processing the last close on, then nothing
		 * will be able to reopen and write to this file. Purge this
		 * inode from the filestreams cache so that it doesn't delay
		 * teardown of the inode.
		 */
		if ((ip->i_d.di_nlink == 0) && xfs_inode_is_filestream(ip))
			xfs_filestream_deassociate(ip);

		/*
		 * If we previously truncated this file and removed old data
		 * in the process, we want to initiate "early" writeout on
		 * the last close.  This is an attempt to combat the notorious
		 * NULL files problem which is particularly noticeable from a
		 * truncate down, buffered (re-)write (delalloc), followed by
		 * a crash.  What we are effectively doing here is
		 * significantly reducing the time window where we'd otherwise
		 * be exposed to that problem.
		 */
		truncated = xfs_iflags_test_and_clear(ip, XFS_ITRUNCATED);
		if (truncated) {
			xfs_iflags_clear(ip, XFS_IDIRTY_RELEASE);
			if (VN_DIRTY(VFS_I(ip)) && ip->i_delayed_blks > 0)
				xfs_flush_pages(ip, 0, -1, XBF_ASYNC, FI_NONE);
		}
	}

	if (ip->i_d.di_nlink == 0)
		return 0;

	if (xfs_can_free_eofblocks(ip, false)) {

		/*
		 * If we can't get the iolock just skip truncating the blocks
		 * past EOF because we could deadlock with the mmap_sem
		 * otherwise.  We'll get another chance to drop them once the
		 * last reference to the inode is dropped, so we'll never leak
		 * blocks permanently.
		 *
		 * Further, check if the inode is being opened, written and
		 * closed frequently and we have delayed allocation blocks
		 * outstanding (e.g. streaming writes from the NFS server),
		 * truncating the blocks past EOF will cause fragmentation to
		 * occur.
		 *
		 * In this case don't do the truncation, either, but we have to
		 * be careful how we detect this case. Blocks beyond EOF show
		 * up as i_delayed_blks even when the inode is clean, so we
		 * need to truncate them away first before checking for a dirty
		 * release. Hence on the first dirty close we will still remove
		 * the speculative allocation, but after that we will leave it
		 * in place.
		 */
		if (xfs_iflags_test(ip, XFS_IDIRTY_RELEASE))
			return 0;

		error = xfs_free_eofblocks(mp, ip,
					   XFS_FREE_EOF_TRYLOCK);
		if (error && error != EAGAIN)
			return error;

		/* delalloc blocks after truncation means it really is dirty */
		if (ip->i_delayed_blks)
			xfs_iflags_set(ip, XFS_IDIRTY_RELEASE);
	}
	return 0;
}