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
struct TYPE_4__ {struct xfs_mount* i_mount; int /*<<< orphan*/  i_ino; } ;
typedef  TYPE_1__ xfs_inode_t ;
struct xfs_perag {int /*<<< orphan*/  pag_ici_lock; int /*<<< orphan*/  pag_agno; int /*<<< orphan*/  pag_ici_root; } ;
struct xfs_mount {int /*<<< orphan*/  m_perag_lock; int /*<<< orphan*/  m_perag_tree; } ;

/* Variables and functions */
 int /*<<< orphan*/  XFS_ICI_EOFBLOCKS_TAG ; 
 int /*<<< orphan*/  XFS_INO_TO_AGINO (struct xfs_mount*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XFS_INO_TO_AGNO (struct xfs_mount*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _RET_IP_ ; 
 int /*<<< orphan*/  radix_tree_tag_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int radix_tree_tagged (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  trace_xfs_inode_set_eofblocks_tag (TYPE_1__*) ; 
 int /*<<< orphan*/  trace_xfs_perag_set_eofblocks (struct xfs_mount*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 struct xfs_perag* xfs_perag_get (struct xfs_mount*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xfs_perag_put (struct xfs_perag*) ; 
 int /*<<< orphan*/  xfs_queue_eofblocks (struct xfs_mount*) ; 

void
xfs_inode_set_eofblocks_tag(
	xfs_inode_t	*ip)
{
	struct xfs_mount *mp = ip->i_mount;
	struct xfs_perag *pag;
	int tagged;

	pag = xfs_perag_get(mp, XFS_INO_TO_AGNO(mp, ip->i_ino));
	spin_lock(&pag->pag_ici_lock);
	trace_xfs_inode_set_eofblocks_tag(ip);

	tagged = radix_tree_tagged(&pag->pag_ici_root,
				   XFS_ICI_EOFBLOCKS_TAG);
	radix_tree_tag_set(&pag->pag_ici_root,
			   XFS_INO_TO_AGINO(ip->i_mount, ip->i_ino),
			   XFS_ICI_EOFBLOCKS_TAG);
	if (!tagged) {
		/* propagate the eofblocks tag up into the perag radix tree */
		spin_lock(&ip->i_mount->m_perag_lock);
		radix_tree_tag_set(&ip->i_mount->m_perag_tree,
				   XFS_INO_TO_AGNO(ip->i_mount, ip->i_ino),
				   XFS_ICI_EOFBLOCKS_TAG);
		spin_unlock(&ip->i_mount->m_perag_lock);

		/* kick off background trimming */
		xfs_queue_eofblocks(ip->i_mount);

		trace_xfs_perag_set_eofblocks(ip->i_mount, pag->pag_agno,
					      -1, _RET_IP_);
	}

	spin_unlock(&pag->pag_ici_lock);
	xfs_perag_put(pag);
}