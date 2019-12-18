#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_27__   TYPE_5__ ;
typedef  struct TYPE_26__   TYPE_4__ ;
typedef  struct TYPE_25__   TYPE_3__ ;
typedef  struct TYPE_24__   TYPE_2__ ;
typedef  struct TYPE_23__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  xfs_mru_cache_t ;
struct TYPE_24__ {int sb_agcount; } ;
struct TYPE_25__ {int m_flags; int m_agfrotor; TYPE_2__ m_sb; int /*<<< orphan*/ * m_filestream; } ;
typedef  TYPE_3__ xfs_mount_t ;
struct TYPE_23__ {int di_mode; } ;
struct TYPE_26__ {int /*<<< orphan*/  i_ino; TYPE_3__* i_mount; TYPE_1__ i_d; } ;
typedef  TYPE_4__ xfs_inode_t ;
typedef  int xfs_agnumber_t ;
struct TYPE_27__ {int ag; TYPE_4__* ip; } ;
typedef  TYPE_5__ fstrm_item_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int EINVAL ; 
 int NULLAGNUMBER ; 
 int S_IFDIR ; 
 int S_IFREG ; 
 int /*<<< orphan*/  TRACE_ASSOCIATE (TYPE_3__*,TYPE_4__*,TYPE_4__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRACE_LOOKUP (TYPE_3__*,TYPE_4__*,TYPE_4__*,int,int /*<<< orphan*/ ) ; 
 int XFS_INO_TO_AGNO (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XFS_IOLOCK_EXCL ; 
 int XFS_MOUNT_32BITINODES ; 
 int _xfs_filestream_pick_ag (TYPE_3__*,int,int*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int _xfs_filestream_update_ag (TYPE_4__*,TYPE_4__*,int) ; 
 int /*<<< orphan*/  xfs_filestream_peek_ag (TYPE_3__*,int) ; 
 int /*<<< orphan*/  xfs_filestream_put_ag (TYPE_3__*,int) ; 
 int /*<<< orphan*/  xfs_ilock_nowait (TYPE_4__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xfs_iunlock (TYPE_4__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xfs_mru_cache_done (int /*<<< orphan*/ *) ; 
 TYPE_5__* xfs_mru_cache_lookup (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int xfs_rotorstep ; 

int
xfs_filestream_associate(
	xfs_inode_t	*pip,
	xfs_inode_t	*ip)
{
	xfs_mount_t	*mp;
	xfs_mru_cache_t	*cache;
	fstrm_item_t	*item;
	xfs_agnumber_t	ag, rotorstep, startag;
	int		err = 0;

	ASSERT(pip->i_d.di_mode & S_IFDIR);
	ASSERT(ip->i_d.di_mode & S_IFREG);
	if (!(pip->i_d.di_mode & S_IFDIR) || !(ip->i_d.di_mode & S_IFREG))
		return -EINVAL;

	mp = pip->i_mount;
	cache = mp->m_filestream;

	/*
	 * We have a problem, Houston.
	 *
	 * Taking the iolock here violates inode locking order - we already
	 * hold the ilock. Hence if we block getting this lock we may never
	 * wake. Unfortunately, that means if we can't get the lock, we're
	 * screwed in terms of getting a stream association - we can't spin
	 * waiting for the lock because someone else is waiting on the lock we
	 * hold and we cannot drop that as we are in a transaction here.
	 *
	 * Lucky for us, this inversion is not a problem because it's a
	 * directory inode that we are trying to lock here.
	 *
	 * So, if we can't get the iolock without sleeping then just give up
	 */
	if (!xfs_ilock_nowait(pip, XFS_IOLOCK_EXCL))
		return 1;

	/* If the parent directory is already in the cache, use its AG. */
	item = xfs_mru_cache_lookup(cache, pip->i_ino);
	if (item) {
		ASSERT(item->ip == pip);
		ag = item->ag;
		xfs_mru_cache_done(cache);

		TRACE_LOOKUP(mp, pip, pip, ag, xfs_filestream_peek_ag(mp, ag));
		err = _xfs_filestream_update_ag(ip, pip, ag);

		goto exit;
	}

	/*
	 * Set the starting AG using the rotor for inode32, otherwise
	 * use the directory inode's AG.
	 */
	if (mp->m_flags & XFS_MOUNT_32BITINODES) {
		rotorstep = xfs_rotorstep;
		startag = (mp->m_agfrotor / rotorstep) % mp->m_sb.sb_agcount;
		mp->m_agfrotor = (mp->m_agfrotor + 1) %
		                 (mp->m_sb.sb_agcount * rotorstep);
	} else
		startag = XFS_INO_TO_AGNO(mp, pip->i_ino);

	/* Pick a new AG for the parent inode starting at startag. */
	err = _xfs_filestream_pick_ag(mp, startag, &ag, 0, 0);
	if (err || ag == NULLAGNUMBER)
		goto exit_did_pick;

	/* Associate the parent inode with the AG. */
	err = _xfs_filestream_update_ag(pip, NULL, ag);
	if (err)
		goto exit_did_pick;

	/* Associate the file inode with the AG. */
	err = _xfs_filestream_update_ag(ip, pip, ag);
	if (err)
		goto exit_did_pick;

	TRACE_ASSOCIATE(mp, ip, pip, ag, xfs_filestream_peek_ag(mp, ag));

exit_did_pick:
	/*
	 * If _xfs_filestream_pick_ag() returned a valid AG, remove the
	 * reference it took on it, since the file and directory will have taken
	 * their own now if they were successfully cached.
	 */
	if (ag != NULLAGNUMBER)
		xfs_filestream_put_ag(mp, ag);

exit:
	xfs_iunlock(pip, XFS_IOLOCK_EXCL);
	return -err;
}