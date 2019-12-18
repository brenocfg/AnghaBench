#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
struct TYPE_14__ {int sb_agblocks; scalar_t__ sb_dblocks; scalar_t__ sb_imax_pct; } ;
typedef  TYPE_1__ xfs_sb_t ;
struct TYPE_15__ {int pagi_inodeok; int pagf_metadata; int /*<<< orphan*/  pag_buf_tree; int /*<<< orphan*/  pag_buf_lock; int /*<<< orphan*/  pag_ici_root; int /*<<< orphan*/  pag_ici_reclaim_lock; int /*<<< orphan*/  pag_ici_lock; TYPE_3__* pag_mount; scalar_t__ pag_agno; } ;
typedef  TYPE_2__ xfs_perag_t ;
struct TYPE_16__ {int m_flags; int /*<<< orphan*/  m_perag_tree; scalar_t__ m_maxicount; int /*<<< orphan*/  m_perag_lock; TYPE_1__ m_sb; } ;
typedef  TYPE_3__ xfs_mount_t ;
typedef  scalar_t__ xfs_ino_t ;
typedef  scalar_t__ xfs_agnumber_t ;
typedef  int /*<<< orphan*/  xfs_agino_t ;
typedef  scalar_t__ __uint64_t ;

/* Variables and functions */
 int /*<<< orphan*/  BUG () ; 
 int EEXIST ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  GFP_NOFS ; 
 int /*<<< orphan*/  INIT_RADIX_TREE (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  KM_MAYFAIL ; 
 int /*<<< orphan*/  RB_ROOT ; 
 scalar_t__ XFS_AGINO_TO_INO (TYPE_3__*,scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ XFS_MAXINUMBER_32 ; 
 int XFS_MOUNT_32BITINODES ; 
 int XFS_MOUNT_SMALL_INUMS ; 
 int /*<<< orphan*/  XFS_OFFBNO_TO_AGINO (TYPE_3__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  do_div (scalar_t__,int) ; 
 int /*<<< orphan*/  kmem_free (TYPE_2__*) ; 
 TYPE_2__* kmem_zalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 TYPE_2__* radix_tree_delete (int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ radix_tree_insert (int /*<<< orphan*/ *,scalar_t__,TYPE_2__*) ; 
 scalar_t__ radix_tree_preload (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  radix_tree_preload_end () ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 TYPE_2__* xfs_perag_get (TYPE_3__*,scalar_t__) ; 
 int /*<<< orphan*/  xfs_perag_put (TYPE_2__*) ; 

int
xfs_initialize_perag(
	xfs_mount_t	*mp,
	xfs_agnumber_t	agcount,
	xfs_agnumber_t	*maxagi)
{
	xfs_agnumber_t	index, max_metadata;
	xfs_agnumber_t	first_initialised = 0;
	xfs_perag_t	*pag;
	xfs_agino_t	agino;
	xfs_ino_t	ino;
	xfs_sb_t	*sbp = &mp->m_sb;
	int		error = -ENOMEM;

	/*
	 * Walk the current per-ag tree so we don't try to initialise AGs
	 * that already exist (growfs case). Allocate and insert all the
	 * AGs we don't find ready for initialisation.
	 */
	for (index = 0; index < agcount; index++) {
		pag = xfs_perag_get(mp, index);
		if (pag) {
			xfs_perag_put(pag);
			continue;
		}
		if (!first_initialised)
			first_initialised = index;

		pag = kmem_zalloc(sizeof(*pag), KM_MAYFAIL);
		if (!pag)
			goto out_unwind;
		pag->pag_agno = index;
		pag->pag_mount = mp;
		spin_lock_init(&pag->pag_ici_lock);
		mutex_init(&pag->pag_ici_reclaim_lock);
		INIT_RADIX_TREE(&pag->pag_ici_root, GFP_ATOMIC);
		spin_lock_init(&pag->pag_buf_lock);
		pag->pag_buf_tree = RB_ROOT;

		if (radix_tree_preload(GFP_NOFS))
			goto out_unwind;

		spin_lock(&mp->m_perag_lock);
		if (radix_tree_insert(&mp->m_perag_tree, index, pag)) {
			BUG();
			spin_unlock(&mp->m_perag_lock);
			radix_tree_preload_end();
			error = -EEXIST;
			goto out_unwind;
		}
		spin_unlock(&mp->m_perag_lock);
		radix_tree_preload_end();
	}

	/*
	 * If we mount with the inode64 option, or no inode overflows
	 * the legacy 32-bit address space clear the inode32 option.
	 */
	agino = XFS_OFFBNO_TO_AGINO(mp, sbp->sb_agblocks - 1, 0);
	ino = XFS_AGINO_TO_INO(mp, agcount - 1, agino);

	if ((mp->m_flags & XFS_MOUNT_SMALL_INUMS) && ino > XFS_MAXINUMBER_32)
		mp->m_flags |= XFS_MOUNT_32BITINODES;
	else
		mp->m_flags &= ~XFS_MOUNT_32BITINODES;

	if (mp->m_flags & XFS_MOUNT_32BITINODES) {
		/*
		 * Calculate how much should be reserved for inodes to meet
		 * the max inode percentage.
		 */
		if (mp->m_maxicount) {
			__uint64_t	icount;

			icount = sbp->sb_dblocks * sbp->sb_imax_pct;
			do_div(icount, 100);
			icount += sbp->sb_agblocks - 1;
			do_div(icount, sbp->sb_agblocks);
			max_metadata = icount;
		} else {
			max_metadata = agcount;
		}

		for (index = 0; index < agcount; index++) {
			ino = XFS_AGINO_TO_INO(mp, index, agino);
			if (ino > XFS_MAXINUMBER_32) {
				index++;
				break;
			}

			pag = xfs_perag_get(mp, index);
			pag->pagi_inodeok = 1;
			if (index < max_metadata)
				pag->pagf_metadata = 1;
			xfs_perag_put(pag);
		}
	} else {
		for (index = 0; index < agcount; index++) {
			pag = xfs_perag_get(mp, index);
			pag->pagi_inodeok = 1;
			xfs_perag_put(pag);
		}
	}

	if (maxagi)
		*maxagi = index;
	return 0;

out_unwind:
	kmem_free(pag);
	for (; index > first_initialised; index--) {
		pag = radix_tree_delete(&mp->m_perag_tree, index);
		kmem_free(pag);
	}
	return error;
}