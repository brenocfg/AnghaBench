#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  scalar_t__ xfs_agnumber_t ;
struct xfs_perag {scalar_t__ pag_agno; } ;
struct xfs_mount {int dummy; } ;

/* Variables and functions */
 int EFSCORRUPTED ; 
 int XFS_ERROR (int) ; 
 int xfs_inode_ag_walk (struct xfs_mount*,struct xfs_perag*,int (*) (struct xfs_inode*,struct xfs_perag*,int,void*),int,void*,int) ; 
 struct xfs_perag* xfs_perag_get_tag (struct xfs_mount*,scalar_t__,int) ; 
 int /*<<< orphan*/  xfs_perag_put (struct xfs_perag*) ; 

int
xfs_inode_ag_iterator_tag(
	struct xfs_mount	*mp,
	int			(*execute)(struct xfs_inode *ip,
					   struct xfs_perag *pag, int flags,
					   void *args),
	int			flags,
	void			*args,
	int			tag)
{
	struct xfs_perag	*pag;
	int			error = 0;
	int			last_error = 0;
	xfs_agnumber_t		ag;

	ag = 0;
	while ((pag = xfs_perag_get_tag(mp, ag, tag))) {
		ag = pag->pag_agno + 1;
		error = xfs_inode_ag_walk(mp, pag, execute, flags, args, tag);
		xfs_perag_put(pag);
		if (error) {
			last_error = error;
			if (error == EFSCORRUPTED)
				break;
		}
	}
	return XFS_ERROR(last_error);
}