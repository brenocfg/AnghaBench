#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_23__   TYPE_6__ ;
typedef  struct TYPE_22__   TYPE_5__ ;
typedef  struct TYPE_21__   TYPE_4__ ;
typedef  struct TYPE_20__   TYPE_3__ ;
typedef  struct TYPE_19__   TYPE_2__ ;
typedef  struct TYPE_18__   TYPE_1__ ;

/* Type definitions */
typedef  int xfs_off_t ;
struct TYPE_18__ {scalar_t__ m_dirdatablk; } ;
typedef  TYPE_1__ xfs_mount_t ;
struct TYPE_19__ {TYPE_1__* i_mount; } ;
typedef  TYPE_2__ xfs_inode_t ;
struct TYPE_20__ {int /*<<< orphan*/  length; int /*<<< orphan*/  freetag; } ;
typedef  TYPE_3__ xfs_dir2_data_unused_t ;
struct TYPE_21__ {int /*<<< orphan*/  inumber; int /*<<< orphan*/  namelen; scalar_t__ name; } ;
typedef  TYPE_4__ xfs_dir2_data_entry_t ;
typedef  int /*<<< orphan*/  xfs_dir2_block_tail_t ;
struct TYPE_22__ {scalar_t__ u; } ;
typedef  TYPE_5__ xfs_dir2_block_t ;
struct TYPE_23__ {TYPE_5__* data; } ;
typedef  TYPE_6__ xfs_dabuf_t ;
typedef  scalar_t__ (* filldir_t ) (void*,char*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DT_UNKNOWN ; 
 int /*<<< orphan*/  XFS_DATA_FORK ; 
 scalar_t__ XFS_DIR2_DATA_FREE_TAG ; 
 scalar_t__ be16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  be64_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xfs_da_brelse (int /*<<< orphan*/ *,TYPE_6__*) ; 
 int xfs_da_read_buf (int /*<<< orphan*/ *,TYPE_2__*,scalar_t__,int,TYPE_6__**,int /*<<< orphan*/ ) ; 
 scalar_t__ xfs_dir2_block_leaf_p (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * xfs_dir2_block_tail_p (TYPE_1__*,TYPE_5__*) ; 
 int /*<<< orphan*/  xfs_dir2_data_check (TYPE_2__*,TYPE_6__*) ; 
 int /*<<< orphan*/  xfs_dir2_data_entsize (int /*<<< orphan*/ ) ; 
 scalar_t__ xfs_dir2_dataptr_to_db (TYPE_1__*,int) ; 
 int xfs_dir2_dataptr_to_off (TYPE_1__*,int) ; 
 int xfs_dir2_db_off_to_dataptr (TYPE_1__*,scalar_t__,int) ; 

int						/* error */
xfs_dir2_block_getdents(
	xfs_inode_t		*dp,		/* incore inode */
	void			*dirent,
	xfs_off_t		*offset,
	filldir_t		filldir)
{
	xfs_dir2_block_t	*block;		/* directory block structure */
	xfs_dabuf_t		*bp;		/* buffer for block */
	xfs_dir2_block_tail_t	*btp;		/* block tail */
	xfs_dir2_data_entry_t	*dep;		/* block data entry */
	xfs_dir2_data_unused_t	*dup;		/* block unused entry */
	char			*endptr;	/* end of the data entries */
	int			error;		/* error return value */
	xfs_mount_t		*mp;		/* filesystem mount point */
	char			*ptr;		/* current data entry */
	int			wantoff;	/* starting block offset */
	xfs_off_t		cook;

	mp = dp->i_mount;
	/*
	 * If the block number in the offset is out of range, we're done.
	 */
	if (xfs_dir2_dataptr_to_db(mp, *offset) > mp->m_dirdatablk) {
		return 0;
	}
	/*
	 * Can't read the block, give up, else get dabuf in bp.
	 */
	error = xfs_da_read_buf(NULL, dp, mp->m_dirdatablk, -1,
				&bp, XFS_DATA_FORK);
	if (error)
		return error;

	ASSERT(bp != NULL);
	/*
	 * Extract the byte offset we start at from the seek pointer.
	 * We'll skip entries before this.
	 */
	wantoff = xfs_dir2_dataptr_to_off(mp, *offset);
	block = bp->data;
	xfs_dir2_data_check(dp, bp);
	/*
	 * Set up values for the loop.
	 */
	btp = xfs_dir2_block_tail_p(mp, block);
	ptr = (char *)block->u;
	endptr = (char *)xfs_dir2_block_leaf_p(btp);

	/*
	 * Loop over the data portion of the block.
	 * Each object is a real entry (dep) or an unused one (dup).
	 */
	while (ptr < endptr) {
		dup = (xfs_dir2_data_unused_t *)ptr;
		/*
		 * Unused, skip it.
		 */
		if (be16_to_cpu(dup->freetag) == XFS_DIR2_DATA_FREE_TAG) {
			ptr += be16_to_cpu(dup->length);
			continue;
		}

		dep = (xfs_dir2_data_entry_t *)ptr;

		/*
		 * Bump pointer for the next iteration.
		 */
		ptr += xfs_dir2_data_entsize(dep->namelen);
		/*
		 * The entry is before the desired starting point, skip it.
		 */
		if ((char *)dep - (char *)block < wantoff)
			continue;

		cook = xfs_dir2_db_off_to_dataptr(mp, mp->m_dirdatablk,
					    (char *)dep - (char *)block);

		/*
		 * If it didn't fit, set the final offset to here & return.
		 */
		if (filldir(dirent, (char *)dep->name, dep->namelen,
			    cook & 0x7fffffff, be64_to_cpu(dep->inumber),
			    DT_UNKNOWN)) {
			*offset = cook & 0x7fffffff;
			xfs_da_brelse(NULL, bp);
			return 0;
		}
	}

	/*
	 * Reached the end of the block.
	 * Set the offset to a non-existent block 1 and return.
	 */
	*offset = xfs_dir2_db_off_to_dataptr(mp, mp->m_dirdatablk + 1, 0) &
			0x7fffffff;
	xfs_da_brelse(NULL, bp);
	return 0;
}