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
struct xfs_mount {int dummy; } ;
struct xfs_eofblocks {int eof_flags; } ;

/* Variables and functions */
 int SYNC_TRYLOCK ; 
 int SYNC_WAIT ; 
 int XFS_EOF_FLAGS_SYNC ; 
 int /*<<< orphan*/  XFS_ICI_EOFBLOCKS_TAG ; 
 int xfs_inode_ag_iterator_tag (struct xfs_mount*,int /*<<< orphan*/ ,int,struct xfs_eofblocks*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xfs_inode_free_eofblocks ; 

int
xfs_icache_free_eofblocks(
	struct xfs_mount	*mp,
	struct xfs_eofblocks	*eofb)
{
	int flags = SYNC_TRYLOCK;

	if (eofb && (eofb->eof_flags & XFS_EOF_FLAGS_SYNC))
		flags = SYNC_WAIT;

	return xfs_inode_ag_iterator_tag(mp, xfs_inode_free_eofblocks, flags,
					 eofb, XFS_ICI_EOFBLOCKS_TAG);
}