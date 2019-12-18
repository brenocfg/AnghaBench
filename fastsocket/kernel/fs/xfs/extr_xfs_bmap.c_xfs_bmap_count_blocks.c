#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_19__   TYPE_4__ ;
typedef  struct TYPE_18__   TYPE_3__ ;
typedef  struct TYPE_17__   TYPE_2__ ;
typedef  struct TYPE_16__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  xfs_trans_t ;
struct TYPE_16__ {scalar_t__ sb_agcount; scalar_t__ sb_agblocks; } ;
struct TYPE_17__ {TYPE_1__ m_sb; } ;
typedef  TYPE_2__ xfs_mount_t ;
struct TYPE_18__ {TYPE_2__* i_mount; } ;
typedef  TYPE_3__ xfs_inode_t ;
struct TYPE_19__ {int if_bytes; int /*<<< orphan*/  if_broot_bytes; struct xfs_btree_block* if_broot; } ;
typedef  TYPE_4__ xfs_ifork_t ;
typedef  scalar_t__ xfs_fsblock_t ;
typedef  int /*<<< orphan*/  xfs_bmbt_rec_t ;
typedef  int uint ;
struct xfs_btree_block {int /*<<< orphan*/  bb_level; } ;
typedef  int /*<<< orphan*/  __be64 ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int /*<<< orphan*/  EFSCORRUPTED ; 
 scalar_t__ NULLDFSBNO ; 
 scalar_t__ NULLFSBLOCK ; 
 int /*<<< orphan*/ * XFS_BMAP_BROOT_PTR_ADDR (TYPE_2__*,struct xfs_btree_block*,int,int /*<<< orphan*/ ) ; 
 scalar_t__ XFS_DINODE_FMT_EXTENTS ; 
 int /*<<< orphan*/  XFS_ERRLEVEL_LOW ; 
 int XFS_ERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XFS_ERROR_REPORT (char*,int /*<<< orphan*/ ,TYPE_2__*) ; 
 scalar_t__ XFS_FSB_TO_AGBNO (TYPE_2__*,scalar_t__) ; 
 scalar_t__ XFS_FSB_TO_AGNO (TYPE_2__*,scalar_t__) ; 
 scalar_t__ XFS_IFORK_FORMAT (TYPE_3__*,int) ; 
 TYPE_4__* XFS_IFORK_PTR (TYPE_3__*,int) ; 
 int be16_to_cpu (int /*<<< orphan*/ ) ; 
 scalar_t__ be64_to_cpu (int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  xfs_bmap_count_leaves (TYPE_4__*,int /*<<< orphan*/ ,int,int*) ; 
 scalar_t__ xfs_bmap_count_tree (TYPE_2__*,int /*<<< orphan*/ *,TYPE_4__*,scalar_t__,int,int*) ; 

int						/* error */
xfs_bmap_count_blocks(
	xfs_trans_t		*tp,		/* transaction pointer */
	xfs_inode_t		*ip,		/* incore inode */
	int			whichfork,	/* data or attr fork */
	int			*count)		/* out: count of blocks */
{
	struct xfs_btree_block	*block;	/* current btree block */
	xfs_fsblock_t		bno;	/* block # of "block" */
	xfs_ifork_t		*ifp;	/* fork structure */
	int			level;	/* btree level, for checking */
	xfs_mount_t		*mp;	/* file system mount structure */
	__be64			*pp;	/* pointer to block address */

	bno = NULLFSBLOCK;
	mp = ip->i_mount;
	ifp = XFS_IFORK_PTR(ip, whichfork);
	if ( XFS_IFORK_FORMAT(ip, whichfork) == XFS_DINODE_FMT_EXTENTS ) {
		xfs_bmap_count_leaves(ifp, 0,
			ifp->if_bytes / (uint)sizeof(xfs_bmbt_rec_t),
			count);
		return 0;
	}

	/*
	 * Root level must use BMAP_BROOT_PTR_ADDR macro to get ptr out.
	 */
	block = ifp->if_broot;
	level = be16_to_cpu(block->bb_level);
	ASSERT(level > 0);
	pp = XFS_BMAP_BROOT_PTR_ADDR(mp, block, 1, ifp->if_broot_bytes);
	bno = be64_to_cpu(*pp);
	ASSERT(bno != NULLDFSBNO);
	ASSERT(XFS_FSB_TO_AGNO(mp, bno) < mp->m_sb.sb_agcount);
	ASSERT(XFS_FSB_TO_AGBNO(mp, bno) < mp->m_sb.sb_agblocks);

	if (unlikely(xfs_bmap_count_tree(mp, tp, ifp, bno, level, count) < 0)) {
		XFS_ERROR_REPORT("xfs_bmap_count_blocks(2)", XFS_ERRLEVEL_LOW,
				 mp);
		return XFS_ERROR(EFSCORRUPTED);
	}

	return 0;
}