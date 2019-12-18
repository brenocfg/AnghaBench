#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_19__   TYPE_5__ ;
typedef  struct TYPE_18__   TYPE_4__ ;
typedef  struct TYPE_17__   TYPE_3__ ;
typedef  struct TYPE_16__   TYPE_2__ ;
typedef  struct TYPE_15__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  xfs_mount_t ;
struct TYPE_15__ {int /*<<< orphan*/ * i_mount; } ;
typedef  TYPE_1__ xfs_inode_t ;
struct TYPE_16__ {int /*<<< orphan*/  address; } ;
typedef  TYPE_2__ xfs_dir2_leaf_entry_t ;
struct TYPE_17__ {int /*<<< orphan*/  namelen; int /*<<< orphan*/  name; int /*<<< orphan*/  inumber; } ;
typedef  TYPE_3__ xfs_dir2_data_entry_t ;
typedef  int /*<<< orphan*/  xfs_dir2_block_tail_t ;
typedef  int /*<<< orphan*/  xfs_dir2_block_t ;
struct TYPE_18__ {int /*<<< orphan*/ * data; } ;
typedef  TYPE_4__ xfs_dabuf_t ;
struct TYPE_19__ {int /*<<< orphan*/  trans; int /*<<< orphan*/  inumber; TYPE_1__* dp; } ;
typedef  TYPE_5__ xfs_da_args_t ;

/* Variables and functions */
 int XFS_ERROR (int) ; 
 int /*<<< orphan*/  be32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  be64_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trace_xfs_dir2_block_lookup (TYPE_5__*) ; 
 int /*<<< orphan*/  xfs_da_brelse (int /*<<< orphan*/ ,TYPE_4__*) ; 
 TYPE_2__* xfs_dir2_block_leaf_p (int /*<<< orphan*/ *) ; 
 int xfs_dir2_block_lookup_int (TYPE_5__*,TYPE_4__**,int*) ; 
 int /*<<< orphan*/ * xfs_dir2_block_tail_p (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xfs_dir2_data_check (TYPE_1__*,TYPE_4__*) ; 
 int xfs_dir2_dataptr_to_off (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int xfs_dir_cilookup_result (TYPE_5__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int						/* error */
xfs_dir2_block_lookup(
	xfs_da_args_t		*args)		/* dir lookup arguments */
{
	xfs_dir2_block_t	*block;		/* block structure */
	xfs_dir2_leaf_entry_t	*blp;		/* block leaf entries */
	xfs_dabuf_t		*bp;		/* block buffer */
	xfs_dir2_block_tail_t	*btp;		/* block tail */
	xfs_dir2_data_entry_t	*dep;		/* block data entry */
	xfs_inode_t		*dp;		/* incore inode */
	int			ent;		/* entry index */
	int			error;		/* error return value */
	xfs_mount_t		*mp;		/* filesystem mount point */

	trace_xfs_dir2_block_lookup(args);

	/*
	 * Get the buffer, look up the entry.
	 * If not found (ENOENT) then return, have no buffer.
	 */
	if ((error = xfs_dir2_block_lookup_int(args, &bp, &ent)))
		return error;
	dp = args->dp;
	mp = dp->i_mount;
	block = bp->data;
	xfs_dir2_data_check(dp, bp);
	btp = xfs_dir2_block_tail_p(mp, block);
	blp = xfs_dir2_block_leaf_p(btp);
	/*
	 * Get the offset from the leaf entry, to point to the data.
	 */
	dep = (xfs_dir2_data_entry_t *)((char *)block +
		xfs_dir2_dataptr_to_off(mp, be32_to_cpu(blp[ent].address)));
	/*
	 * Fill in inode number, CI name if appropriate, release the block.
	 */
	args->inumber = be64_to_cpu(dep->inumber);
	error = xfs_dir_cilookup_result(args, dep->name, dep->namelen);
	xfs_da_brelse(args->trans, bp);
	return XFS_ERROR(error);
}