#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_20__   TYPE_5__ ;
typedef  struct TYPE_19__   TYPE_4__ ;
typedef  struct TYPE_18__   TYPE_3__ ;
typedef  struct TYPE_17__   TYPE_2__ ;
typedef  struct TYPE_16__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  xfs_mount_t ;
struct TYPE_16__ {int /*<<< orphan*/ * i_mount; } ;
typedef  TYPE_1__ xfs_inode_t ;
struct TYPE_17__ {int /*<<< orphan*/  address; } ;
typedef  TYPE_2__ xfs_dir2_leaf_entry_t ;
struct TYPE_18__ {int /*<<< orphan*/  inumber; } ;
typedef  TYPE_3__ xfs_dir2_data_entry_t ;
typedef  int /*<<< orphan*/  xfs_dir2_block_tail_t ;
typedef  int /*<<< orphan*/  xfs_dir2_block_t ;
struct TYPE_19__ {int /*<<< orphan*/ * data; } ;
typedef  TYPE_4__ xfs_dabuf_t ;
struct TYPE_20__ {scalar_t__ inumber; int /*<<< orphan*/  trans; TYPE_1__* dp; } ;
typedef  TYPE_5__ xfs_da_args_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int /*<<< orphan*/  be32_to_cpu (int /*<<< orphan*/ ) ; 
 scalar_t__ be64_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_to_be64 (scalar_t__) ; 
 int /*<<< orphan*/  trace_xfs_dir2_block_replace (TYPE_5__*) ; 
 int /*<<< orphan*/  xfs_da_buf_done (TYPE_4__*) ; 
 TYPE_2__* xfs_dir2_block_leaf_p (int /*<<< orphan*/ *) ; 
 int xfs_dir2_block_lookup_int (TYPE_5__*,TYPE_4__**,int*) ; 
 int /*<<< orphan*/ * xfs_dir2_block_tail_p (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xfs_dir2_data_check (TYPE_1__*,TYPE_4__*) ; 
 int /*<<< orphan*/  xfs_dir2_data_log_entry (int /*<<< orphan*/ ,TYPE_4__*,TYPE_3__*) ; 
 int xfs_dir2_dataptr_to_off (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

int						/* error */
xfs_dir2_block_replace(
	xfs_da_args_t		*args)		/* directory operation args */
{
	xfs_dir2_block_t	*block;		/* block structure */
	xfs_dir2_leaf_entry_t	*blp;		/* block leaf entries */
	xfs_dabuf_t		*bp;		/* block buffer */
	xfs_dir2_block_tail_t	*btp;		/* block tail */
	xfs_dir2_data_entry_t	*dep;		/* block data entry */
	xfs_inode_t		*dp;		/* incore inode */
	int			ent;		/* leaf entry index */
	int			error;		/* error return value */
	xfs_mount_t		*mp;		/* filesystem mount point */

	trace_xfs_dir2_block_replace(args);

	/*
	 * Lookup the entry in the directory.  Get buffer and entry index.
	 * This will always succeed since the caller has already done a lookup.
	 */
	if ((error = xfs_dir2_block_lookup_int(args, &bp, &ent))) {
		return error;
	}
	dp = args->dp;
	mp = dp->i_mount;
	block = bp->data;
	btp = xfs_dir2_block_tail_p(mp, block);
	blp = xfs_dir2_block_leaf_p(btp);
	/*
	 * Point to the data entry we need to change.
	 */
	dep = (xfs_dir2_data_entry_t *)
	      ((char *)block + xfs_dir2_dataptr_to_off(mp, be32_to_cpu(blp[ent].address)));
	ASSERT(be64_to_cpu(dep->inumber) != args->inumber);
	/*
	 * Change the inode number to the new value.
	 */
	dep->inumber = cpu_to_be64(args->inumber);
	xfs_dir2_data_log_entry(args->trans, bp, dep);
	xfs_dir2_data_check(dp, bp);
	xfs_da_buf_done(bp);
	return 0;
}