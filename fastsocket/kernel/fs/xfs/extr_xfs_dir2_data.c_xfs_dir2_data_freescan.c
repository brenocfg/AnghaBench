#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_5__ ;
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
struct TYPE_14__ {int m_dirblksize; } ;
typedef  TYPE_2__ xfs_mount_t ;
struct TYPE_15__ {int /*<<< orphan*/  length; int /*<<< orphan*/  freetag; } ;
typedef  TYPE_3__ xfs_dir2_data_unused_t ;
struct TYPE_13__ {int /*<<< orphan*/  magic; int /*<<< orphan*/  bestfree; } ;
struct TYPE_16__ {TYPE_1__ hdr; scalar_t__ u; } ;
typedef  TYPE_4__ xfs_dir2_data_t ;
struct TYPE_17__ {int /*<<< orphan*/  namelen; } ;
typedef  TYPE_5__ xfs_dir2_data_entry_t ;
typedef  int /*<<< orphan*/  xfs_dir2_block_tail_t ;
typedef  int /*<<< orphan*/  xfs_dir2_block_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 scalar_t__ XFS_DIR2_BLOCK_MAGIC ; 
 int XFS_DIR2_DATA_FREE_TAG ; 
 scalar_t__ XFS_DIR2_DATA_MAGIC ; 
 int be16_to_cpu (int /*<<< orphan*/ ) ; 
 scalar_t__ be32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 scalar_t__ xfs_dir2_block_leaf_p (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * xfs_dir2_block_tail_p (TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * xfs_dir2_data_entry_tag_p (TYPE_5__*) ; 
 int /*<<< orphan*/  xfs_dir2_data_entsize (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xfs_dir2_data_freeinsert (TYPE_4__*,TYPE_3__*,int*) ; 
 int /*<<< orphan*/ * xfs_dir2_data_unused_tag_p (TYPE_3__*) ; 

void
xfs_dir2_data_freescan(
	xfs_mount_t		*mp,		/* filesystem mount point */
	xfs_dir2_data_t		*d,		/* data block pointer */
	int			*loghead)	/* out: log data header */
{
	xfs_dir2_block_tail_t	*btp;		/* block tail */
	xfs_dir2_data_entry_t	*dep;		/* active data entry */
	xfs_dir2_data_unused_t	*dup;		/* unused data entry */
	char			*endp;		/* end of block's data */
	char			*p;		/* current entry pointer */

#ifdef __KERNEL__
	ASSERT(be32_to_cpu(d->hdr.magic) == XFS_DIR2_DATA_MAGIC ||
	       be32_to_cpu(d->hdr.magic) == XFS_DIR2_BLOCK_MAGIC);
#endif
	/*
	 * Start by clearing the table.
	 */
	memset(d->hdr.bestfree, 0, sizeof(d->hdr.bestfree));
	*loghead = 1;
	/*
	 * Set up pointers.
	 */
	p = (char *)d->u;
	if (be32_to_cpu(d->hdr.magic) == XFS_DIR2_BLOCK_MAGIC) {
		btp = xfs_dir2_block_tail_p(mp, (xfs_dir2_block_t *)d);
		endp = (char *)xfs_dir2_block_leaf_p(btp);
	} else
		endp = (char *)d + mp->m_dirblksize;
	/*
	 * Loop over the block's entries.
	 */
	while (p < endp) {
		dup = (xfs_dir2_data_unused_t *)p;
		/*
		 * If it's a free entry, insert it.
		 */
		if (be16_to_cpu(dup->freetag) == XFS_DIR2_DATA_FREE_TAG) {
			ASSERT((char *)dup - (char *)d ==
			       be16_to_cpu(*xfs_dir2_data_unused_tag_p(dup)));
			xfs_dir2_data_freeinsert(d, dup, loghead);
			p += be16_to_cpu(dup->length);
		}
		/*
		 * For active entries, check their tags and skip them.
		 */
		else {
			dep = (xfs_dir2_data_entry_t *)p;
			ASSERT((char *)dep - (char *)d ==
			       be16_to_cpu(*xfs_dir2_data_entry_tag_p(dep)));
			p += xfs_dir2_data_entsize(dep->namelen);
		}
	}
}