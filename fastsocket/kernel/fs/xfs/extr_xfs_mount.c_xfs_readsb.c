#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {unsigned int sb_sectsize; } ;
struct TYPE_9__ {int /*<<< orphan*/ * m_sb_bp; TYPE_3__ m_sb; int /*<<< orphan*/ * m_ddev_targp; } ;
typedef  TYPE_1__ xfs_mount_t ;
typedef  int /*<<< orphan*/  xfs_buf_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int /*<<< orphan*/ ) ; 
 int EIO ; 
 int ENOSYS ; 
 int /*<<< orphan*/  XFS_BUF_TO_SBP (int /*<<< orphan*/ *) ; 
 int XFS_MFSI_QUIET ; 
 int /*<<< orphan*/  XFS_SB_DADDR ; 
 int /*<<< orphan*/ * xfs_buf_read_uncached (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xfs_buf_relse (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xfs_buf_unlock (int /*<<< orphan*/ *) ; 
 unsigned int xfs_getsize_buftarg (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xfs_icsb_reinit_counters (TYPE_1__*) ; 
 int xfs_mount_validate_sb (TYPE_1__*,TYPE_3__*,int) ; 
 int /*<<< orphan*/  xfs_sb_from_disk (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xfs_warn (TYPE_1__*,char*,...) ; 

int
xfs_readsb(xfs_mount_t *mp, int flags)
{
	unsigned int	sector_size;
	xfs_buf_t	*bp;
	int		error;
	int		loud = !(flags & XFS_MFSI_QUIET);

	ASSERT(mp->m_sb_bp == NULL);
	ASSERT(mp->m_ddev_targp != NULL);

	/*
	 * Allocate a (locked) buffer to hold the superblock.
	 * This will be kept around at all times to optimize
	 * access to the superblock.
	 */
	sector_size = xfs_getsize_buftarg(mp->m_ddev_targp);

reread:
	bp = xfs_buf_read_uncached(mp, mp->m_ddev_targp,
					XFS_SB_DADDR, sector_size, 0);
	if (!bp) {
		if (loud)
			xfs_warn(mp, "SB buffer read failed");
		return EIO;
	}

	/*
	 * Initialize the mount structure from the superblock.
	 * But first do some basic consistency checking.
	 */
	xfs_sb_from_disk(&mp->m_sb, XFS_BUF_TO_SBP(bp));
	error = xfs_mount_validate_sb(mp, &(mp->m_sb), flags);
	if (error) {
		if (loud)
			xfs_warn(mp, "SB validate failed");
		goto release_buf;
	}

	/*
	 * We must be able to do sector-sized and sector-aligned IO.
	 */
	if (sector_size > mp->m_sb.sb_sectsize) {
		if (loud)
			xfs_warn(mp, "device supports %u byte sectors (not %u)",
				sector_size, mp->m_sb.sb_sectsize);
		error = ENOSYS;
		goto release_buf;
	}

	/*
	 * If device sector size is smaller than the superblock size,
	 * re-read the superblock so the buffer is correctly sized.
	 */
	if (sector_size < mp->m_sb.sb_sectsize) {
		xfs_buf_relse(bp);
		sector_size = mp->m_sb.sb_sectsize;
		goto reread;
	}

	/* Initialize per-cpu counters */
	xfs_icsb_reinit_counters(mp);

	mp->m_sb_bp = bp;
	xfs_buf_unlock(bp);
	return 0;

release_buf:
	xfs_buf_relse(bp);
	return error;
}