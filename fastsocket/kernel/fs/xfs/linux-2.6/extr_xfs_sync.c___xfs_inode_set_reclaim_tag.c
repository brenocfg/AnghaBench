#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct xfs_perag {int /*<<< orphan*/  pag_ici_reclaimable; int /*<<< orphan*/  pag_agno; int /*<<< orphan*/  pag_ici_root; } ;
struct xfs_inode {TYPE_1__* i_mount; int /*<<< orphan*/  i_ino; } ;
struct TYPE_4__ {int /*<<< orphan*/  m_perag_lock; int /*<<< orphan*/  m_perag_tree; } ;

/* Variables and functions */
 int /*<<< orphan*/  XFS_ICI_RECLAIM_TAG ; 
 int /*<<< orphan*/  XFS_INO_TO_AGINO (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XFS_INO_TO_AGNO (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _RET_IP_ ; 
 int /*<<< orphan*/  radix_tree_tag_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  trace_xfs_perag_set_reclaim (TYPE_1__*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

void
__xfs_inode_set_reclaim_tag(
	struct xfs_perag	*pag,
	struct xfs_inode	*ip)
{
	radix_tree_tag_set(&pag->pag_ici_root,
			   XFS_INO_TO_AGINO(ip->i_mount, ip->i_ino),
			   XFS_ICI_RECLAIM_TAG);

	if (!pag->pag_ici_reclaimable) {
		/* propagate the reclaim tag up into the perag radix tree */
		spin_lock(&ip->i_mount->m_perag_lock);
		radix_tree_tag_set(&ip->i_mount->m_perag_tree,
				XFS_INO_TO_AGNO(ip->i_mount, ip->i_ino),
				XFS_ICI_RECLAIM_TAG);
		spin_unlock(&ip->i_mount->m_perag_lock);
		trace_xfs_perag_set_reclaim(ip->i_mount, pag->pag_agno,
							-1, _RET_IP_);
	}
	pag->pag_ici_reclaimable++;
}