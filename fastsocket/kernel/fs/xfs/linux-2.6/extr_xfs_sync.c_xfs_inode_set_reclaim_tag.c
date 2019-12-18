#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  i_flags_lock; int /*<<< orphan*/  i_ino; struct xfs_mount* i_mount; } ;
typedef  TYPE_1__ xfs_inode_t ;
struct xfs_perag {int /*<<< orphan*/  pag_ici_lock; } ;
struct xfs_mount {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  XFS_INO_TO_AGNO (struct xfs_mount*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XFS_IRECLAIMABLE ; 
 int /*<<< orphan*/  __xfs_iflags_set (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __xfs_inode_set_reclaim_tag (struct xfs_perag*,TYPE_1__*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 struct xfs_perag* xfs_perag_get (struct xfs_mount*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xfs_perag_put (struct xfs_perag*) ; 

void
xfs_inode_set_reclaim_tag(
	xfs_inode_t	*ip)
{
	struct xfs_mount *mp = ip->i_mount;
	struct xfs_perag *pag;

	pag = xfs_perag_get(mp, XFS_INO_TO_AGNO(mp, ip->i_ino));

	spin_lock(&pag->pag_ici_lock);
	spin_lock(&ip->i_flags_lock);
	__xfs_inode_set_reclaim_tag(pag, ip);
	__xfs_iflags_set(ip, XFS_IRECLAIMABLE);
	spin_unlock(&ip->i_flags_lock);
	spin_unlock(&pag->pag_ici_lock);
	xfs_perag_put(pag);
}