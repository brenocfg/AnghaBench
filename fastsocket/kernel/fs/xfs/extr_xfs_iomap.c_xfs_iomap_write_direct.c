#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_30__   TYPE_4__ ;
typedef  struct TYPE_29__   TYPE_3__ ;
typedef  struct TYPE_28__   TYPE_2__ ;
typedef  struct TYPE_27__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  xfs_ufsize_t ;
typedef  int /*<<< orphan*/  xfs_trans_t ;
typedef  scalar_t__ xfs_off_t ;
struct TYPE_27__ {scalar_t__ sb_rextsize; } ;
struct TYPE_28__ {TYPE_1__ m_sb; } ;
typedef  TYPE_2__ xfs_mount_t ;
struct TYPE_29__ {TYPE_2__* i_mount; } ;
typedef  TYPE_3__ xfs_inode_t ;
typedef  int /*<<< orphan*/  xfs_fsblock_t ;
typedef  scalar_t__ xfs_fileoff_t ;
typedef  scalar_t__ xfs_filblks_t ;
typedef  scalar_t__ xfs_extlen_t ;
struct TYPE_30__ {scalar_t__ br_startblock; scalar_t__ br_startoff; scalar_t__ br_blockcount; } ;
typedef  TYPE_4__ xfs_bmbt_irec_t ;
typedef  int /*<<< orphan*/  xfs_bmap_free_t ;
typedef  scalar_t__ uint ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int ENOSPC ; 
 scalar_t__ HOLESTARTBLOCK ; 
 scalar_t__ MIN (scalar_t__,scalar_t__) ; 
 int XFS_BMAPI_PREALLOC ; 
 int XFS_BMAPI_WRITE ; 
 scalar_t__ XFS_B_TO_FSB (TYPE_2__*,int /*<<< orphan*/ ) ; 
 scalar_t__ XFS_B_TO_FSBT (TYPE_2__*,scalar_t__) ; 
 scalar_t__ XFS_DIOSTRAT_SPACE_RES (TYPE_2__*,scalar_t__) ; 
 int XFS_ERROR (int) ; 
 int /*<<< orphan*/  XFS_ILOCK_EXCL ; 
 scalar_t__ XFS_ISIZE (TYPE_3__*) ; 
 int XFS_IS_REALTIME_INODE (TYPE_3__*) ; 
 int XFS_QMOPT_RES_REGBLKS ; 
 int XFS_QMOPT_RES_RTBLKS ; 
 int XFS_TRANS_ABORT ; 
 int /*<<< orphan*/  XFS_TRANS_DIOSTRAT ; 
 int /*<<< orphan*/  XFS_TRANS_PERM_LOG_RES ; 
 int XFS_TRANS_RELEASE_LOG_RES ; 
 int /*<<< orphan*/  XFS_WRITE_LOG_COUNT ; 
 int /*<<< orphan*/  XFS_WRITE_LOG_RES (TYPE_2__*) ; 
 scalar_t__ do_mod (scalar_t__,scalar_t__) ; 
 scalar_t__ unlikely (int) ; 
 int xfs_alert_fsblock_zero (TYPE_3__*,TYPE_4__*) ; 
 int /*<<< orphan*/  xfs_bmap_cancel (int /*<<< orphan*/ *) ; 
 int xfs_bmap_finish (int /*<<< orphan*/ **,int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  xfs_bmap_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int xfs_bmapi (int /*<<< orphan*/ *,TYPE_3__*,scalar_t__,scalar_t__,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_4__*,int*,int /*<<< orphan*/ *) ; 
 scalar_t__ xfs_get_extsz_hint (TYPE_3__*) ; 
 int /*<<< orphan*/  xfs_ilock (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int xfs_iomap_eof_align_last_fsb (TYPE_2__*,TYPE_3__*,scalar_t__,scalar_t__*) ; 
 int /*<<< orphan*/  xfs_iunlock (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int xfs_qm_dqattach (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * xfs_trans_alloc (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xfs_trans_cancel (int /*<<< orphan*/ *,int) ; 
 int xfs_trans_commit (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  xfs_trans_ijoin (int /*<<< orphan*/ *,TYPE_3__*) ; 
 int xfs_trans_reserve (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int xfs_trans_reserve_quota_nblks (int /*<<< orphan*/ *,TYPE_3__*,scalar_t__,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  xfs_trans_unreserve_quota_nblks (int /*<<< orphan*/ *,TYPE_3__*,scalar_t__,int /*<<< orphan*/ ,int) ; 

int
xfs_iomap_write_direct(
	xfs_inode_t	*ip,
	xfs_off_t	offset,
	size_t		count,
	xfs_bmbt_irec_t *imap,
	int		nmaps)
{
	xfs_mount_t	*mp = ip->i_mount;
	xfs_fileoff_t	offset_fsb;
	xfs_fileoff_t	last_fsb;
	xfs_filblks_t	count_fsb, resaligned;
	xfs_fsblock_t	firstfsb;
	xfs_extlen_t	extsz, temp;
	int		nimaps;
	int		bmapi_flag;
	int		quota_flag;
	int		rt;
	xfs_trans_t	*tp;
	xfs_bmap_free_t free_list;
	uint		qblocks, resblks, resrtextents;
	int		committed;
	int		error;

	error = xfs_qm_dqattach(ip, 0);
	if (error)
		return XFS_ERROR(error);

	rt = XFS_IS_REALTIME_INODE(ip);
	extsz = xfs_get_extsz_hint(ip);

	offset_fsb = XFS_B_TO_FSBT(mp, offset);
	last_fsb = XFS_B_TO_FSB(mp, ((xfs_ufsize_t)(offset + count)));
	if ((offset + count) > XFS_ISIZE(ip)) {
		error = xfs_iomap_eof_align_last_fsb(mp, ip, extsz, &last_fsb);
		if (error)
			return XFS_ERROR(error);
	} else {
		if (nmaps && (imap->br_startblock == HOLESTARTBLOCK))
			last_fsb = MIN(last_fsb, (xfs_fileoff_t)
					imap->br_blockcount +
					imap->br_startoff);
	}
	count_fsb = last_fsb - offset_fsb;
	ASSERT(count_fsb > 0);

	resaligned = count_fsb;
	if (unlikely(extsz)) {
		if ((temp = do_mod(offset_fsb, extsz)))
			resaligned += temp;
		if ((temp = do_mod(resaligned, extsz)))
			resaligned += extsz - temp;
	}

	if (unlikely(rt)) {
		resrtextents = qblocks = resaligned;
		resrtextents /= mp->m_sb.sb_rextsize;
		resblks = XFS_DIOSTRAT_SPACE_RES(mp, 0);
		quota_flag = XFS_QMOPT_RES_RTBLKS;
	} else {
		resrtextents = 0;
		resblks = qblocks = XFS_DIOSTRAT_SPACE_RES(mp, resaligned);
		quota_flag = XFS_QMOPT_RES_REGBLKS;
	}

	/*
	 * Allocate and setup the transaction
	 */
	tp = xfs_trans_alloc(mp, XFS_TRANS_DIOSTRAT);
	error = xfs_trans_reserve(tp, resblks,
			XFS_WRITE_LOG_RES(mp), resrtextents,
			XFS_TRANS_PERM_LOG_RES,
			XFS_WRITE_LOG_COUNT);
	/*
	 * Check for running out of space, note: need lock to return
	 */
	if (error) {
		xfs_trans_cancel(tp, 0);
		return XFS_ERROR(error);
	}

	xfs_ilock(ip, XFS_ILOCK_EXCL);

	error = xfs_trans_reserve_quota_nblks(tp, ip, qblocks, 0, quota_flag);
	if (error)
		goto out_trans_cancel;

	xfs_trans_ijoin(tp, ip);

	bmapi_flag = XFS_BMAPI_WRITE;
	if (offset < XFS_ISIZE(ip) || extsz)
		bmapi_flag |= XFS_BMAPI_PREALLOC;

	/*
	 * Issue the xfs_bmapi() call to allocate the blocks.
	 *
	 * From this point onwards we overwrite the imap pointer that the
	 * caller gave to us.
	 */
	xfs_bmap_init(&free_list, &firstfsb);
	nimaps = 1;
	error = xfs_bmapi(tp, ip, offset_fsb, count_fsb, bmapi_flag,
		&firstfsb, 0, imap, &nimaps, &free_list);
	if (error)
		goto out_bmap_cancel;

	/*
	 * Complete the transaction
	 */
	error = xfs_bmap_finish(&tp, &free_list, &committed);
	if (error)
		goto out_bmap_cancel;
	error = xfs_trans_commit(tp, XFS_TRANS_RELEASE_LOG_RES);
	if (error)
		goto out_unlock;

	/*
	 * Copy any maps to caller's array and return any error.
	 */
	if (nimaps == 0) {
		error = XFS_ERROR(ENOSPC);
		goto out_unlock;
	}

	if (!(imap->br_startblock || XFS_IS_REALTIME_INODE(ip)))
		error = xfs_alert_fsblock_zero(ip, imap);

out_unlock:
	xfs_iunlock(ip, XFS_ILOCK_EXCL);
	return error;

out_bmap_cancel:
	xfs_bmap_cancel(&free_list);
	xfs_trans_unreserve_quota_nblks(tp, ip, qblocks, 0, quota_flag);
out_trans_cancel:
	xfs_trans_cancel(tp, XFS_TRANS_RELEASE_LOG_RES | XFS_TRANS_ABORT);
	goto out_unlock;
}