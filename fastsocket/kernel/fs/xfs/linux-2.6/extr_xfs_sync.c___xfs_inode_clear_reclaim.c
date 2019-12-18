#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  pag_agno; int /*<<< orphan*/  pag_ici_reclaimable; } ;
typedef  TYPE_1__ xfs_perag_t ;
struct TYPE_8__ {TYPE_3__* i_mount; int /*<<< orphan*/  i_ino; } ;
typedef  TYPE_2__ xfs_inode_t ;
struct TYPE_9__ {int /*<<< orphan*/  m_perag_lock; int /*<<< orphan*/  m_perag_tree; } ;

/* Variables and functions */
 int /*<<< orphan*/  XFS_ICI_RECLAIM_TAG ; 
 int /*<<< orphan*/  XFS_INO_TO_AGNO (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _RET_IP_ ; 
 int /*<<< orphan*/  radix_tree_tag_clear (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  trace_xfs_perag_clear_reclaim (TYPE_3__*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

void
__xfs_inode_clear_reclaim(
	xfs_perag_t	*pag,
	xfs_inode_t	*ip)
{
	pag->pag_ici_reclaimable--;
	if (!pag->pag_ici_reclaimable) {
		/* clear the reclaim tag from the perag radix tree */
		spin_lock(&ip->i_mount->m_perag_lock);
		radix_tree_tag_clear(&ip->i_mount->m_perag_tree,
				XFS_INO_TO_AGNO(ip->i_mount, ip->i_ino),
				XFS_ICI_RECLAIM_TAG);
		spin_unlock(&ip->i_mount->m_perag_lock);
		trace_xfs_perag_clear_reclaim(ip->i_mount, pag->pag_agno,
							-1, _RET_IP_);
	}
}