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
typedef  int /*<<< orphan*/  xfs_inode_t ;
struct TYPE_4__ {int if_flags; int if_bytes; } ;
typedef  TYPE_1__ xfs_ifork_t ;
typedef  scalar_t__ xfs_fsblock_t ;
typedef  scalar_t__ xfs_fileoff_t ;
typedef  int xfs_extnum_t ;
typedef  int /*<<< orphan*/  xfs_bmbt_rec_t ;
typedef  int /*<<< orphan*/  xfs_bmbt_rec_host_t ;
typedef  int uint ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int XFS_DATA_FORK ; 
 int XFS_IFEXTENTS ; 
 TYPE_1__* XFS_IFORK_PTR (int /*<<< orphan*/ *,int) ; 
 scalar_t__ xfs_bmbt_get_blockcount (int /*<<< orphan*/ *) ; 
 scalar_t__ xfs_bmbt_get_startoff (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * xfs_iext_get_ext (TYPE_1__*,int) ; 
 int xfs_iread_extents (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 

int					/* error */
xfs_bmap_eof(
	xfs_inode_t	*ip,		/* incore inode pointer */
	xfs_fileoff_t	endoff,		/* file offset in fsblocks */
	int		whichfork,	/* data or attribute fork */
	int		*eof)		/* result value */
{
	xfs_fsblock_t	blockcount;	/* extent block count */
	int		error;		/* error return value */
	xfs_ifork_t	*ifp;		/* inode fork pointer */
	xfs_bmbt_rec_host_t *lastrec;	/* extent record pointer */
	xfs_extnum_t	nextents;	/* number of file extents */
	xfs_fileoff_t	startoff;	/* extent starting file offset */

	ASSERT(whichfork == XFS_DATA_FORK);
	ifp = XFS_IFORK_PTR(ip, whichfork);
	if (!(ifp->if_flags & XFS_IFEXTENTS) &&
	    (error = xfs_iread_extents(NULL, ip, whichfork)))
		return error;
	nextents = ifp->if_bytes / (uint)sizeof(xfs_bmbt_rec_t);
	if (nextents == 0) {
		*eof = 1;
		return 0;
	}
	/*
	 * Go to the last extent
	 */
	lastrec = xfs_iext_get_ext(ifp, nextents - 1);
	startoff = xfs_bmbt_get_startoff(lastrec);
	blockcount = xfs_bmbt_get_blockcount(lastrec);
	*eof = endoff >= startoff + blockcount;
	return 0;
}