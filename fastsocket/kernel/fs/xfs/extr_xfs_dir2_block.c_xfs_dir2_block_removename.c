#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_30__   TYPE_6__ ;
typedef  struct TYPE_29__   TYPE_5__ ;
typedef  struct TYPE_28__   TYPE_4__ ;
typedef  struct TYPE_27__   TYPE_3__ ;
typedef  struct TYPE_26__   TYPE_2__ ;
typedef  struct TYPE_25__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  xfs_trans_t ;
typedef  int /*<<< orphan*/  xfs_mount_t ;
struct TYPE_25__ {int /*<<< orphan*/ * i_mount; } ;
typedef  TYPE_1__ xfs_inode_t ;
typedef  int /*<<< orphan*/  xfs_dir2_sf_hdr_t ;
struct TYPE_26__ {int /*<<< orphan*/  address; } ;
typedef  TYPE_2__ xfs_dir2_leaf_entry_t ;
typedef  int /*<<< orphan*/  xfs_dir2_data_t ;
struct TYPE_27__ {int /*<<< orphan*/  namelen; } ;
typedef  TYPE_3__ xfs_dir2_data_entry_t ;
typedef  int /*<<< orphan*/  xfs_dir2_data_aoff_t ;
struct TYPE_28__ {int /*<<< orphan*/  stale; } ;
typedef  TYPE_4__ xfs_dir2_block_tail_t ;
typedef  int /*<<< orphan*/  xfs_dir2_block_t ;
struct TYPE_29__ {int /*<<< orphan*/ * data; } ;
typedef  TYPE_5__ xfs_dabuf_t ;
struct TYPE_30__ {int /*<<< orphan*/ * trans; TYPE_1__* dp; } ;
typedef  TYPE_6__ xfs_da_args_t ;

/* Variables and functions */
 int /*<<< orphan*/  XFS_DIR2_NULL_DATAPTR ; 
 int XFS_IFORK_DSIZE (TYPE_1__*) ; 
 int /*<<< orphan*/  be32_add_cpu (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  be32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_to_be32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trace_xfs_dir2_block_removename (TYPE_6__*) ; 
 int /*<<< orphan*/  xfs_da_buf_done (TYPE_5__*) ; 
 TYPE_2__* xfs_dir2_block_leaf_p (TYPE_4__*) ; 
 int /*<<< orphan*/  xfs_dir2_block_log_leaf (int /*<<< orphan*/ *,TYPE_5__*,int,int) ; 
 int /*<<< orphan*/  xfs_dir2_block_log_tail (int /*<<< orphan*/ *,TYPE_5__*) ; 
 int xfs_dir2_block_lookup_int (TYPE_6__*,TYPE_5__**,int*) ; 
 int xfs_dir2_block_sfsize (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 TYPE_4__* xfs_dir2_block_tail_p (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int xfs_dir2_block_to_sf (TYPE_6__*,TYPE_5__*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xfs_dir2_data_check (TYPE_1__*,TYPE_5__*) ; 
 int /*<<< orphan*/  xfs_dir2_data_entsize (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xfs_dir2_data_freescan (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  xfs_dir2_data_log_header (int /*<<< orphan*/ *,TYPE_5__*) ; 
 int /*<<< orphan*/  xfs_dir2_data_make_free (int /*<<< orphan*/ *,TYPE_5__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int*) ; 
 int xfs_dir2_dataptr_to_off (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

int						/* error */
xfs_dir2_block_removename(
	xfs_da_args_t		*args)		/* directory operation args */
{
	xfs_dir2_block_t	*block;		/* block structure */
	xfs_dir2_leaf_entry_t	*blp;		/* block leaf pointer */
	xfs_dabuf_t		*bp;		/* block buffer */
	xfs_dir2_block_tail_t	*btp;		/* block tail */
	xfs_dir2_data_entry_t	*dep;		/* block data entry */
	xfs_inode_t		*dp;		/* incore inode */
	int			ent;		/* block leaf entry index */
	int			error;		/* error return value */
	xfs_mount_t		*mp;		/* filesystem mount point */
	int			needlog;	/* need to log block header */
	int			needscan;	/* need to fixup bestfree */
	xfs_dir2_sf_hdr_t	sfh;		/* shortform header */
	int			size;		/* shortform size */
	xfs_trans_t		*tp;		/* transaction pointer */

	trace_xfs_dir2_block_removename(args);

	/*
	 * Look up the entry in the block.  Gets the buffer and entry index.
	 * It will always be there, the vnodeops level does a lookup first.
	 */
	if ((error = xfs_dir2_block_lookup_int(args, &bp, &ent))) {
		return error;
	}
	dp = args->dp;
	tp = args->trans;
	mp = dp->i_mount;
	block = bp->data;
	btp = xfs_dir2_block_tail_p(mp, block);
	blp = xfs_dir2_block_leaf_p(btp);
	/*
	 * Point to the data entry using the leaf entry.
	 */
	dep = (xfs_dir2_data_entry_t *)
	      ((char *)block + xfs_dir2_dataptr_to_off(mp, be32_to_cpu(blp[ent].address)));
	/*
	 * Mark the data entry's space free.
	 */
	needlog = needscan = 0;
	xfs_dir2_data_make_free(tp, bp,
		(xfs_dir2_data_aoff_t)((char *)dep - (char *)block),
		xfs_dir2_data_entsize(dep->namelen), &needlog, &needscan);
	/*
	 * Fix up the block tail.
	 */
	be32_add_cpu(&btp->stale, 1);
	xfs_dir2_block_log_tail(tp, bp);
	/*
	 * Remove the leaf entry by marking it stale.
	 */
	blp[ent].address = cpu_to_be32(XFS_DIR2_NULL_DATAPTR);
	xfs_dir2_block_log_leaf(tp, bp, ent, ent);
	/*
	 * Fix up bestfree, log the header if necessary.
	 */
	if (needscan)
		xfs_dir2_data_freescan(mp, (xfs_dir2_data_t *)block, &needlog);
	if (needlog)
		xfs_dir2_data_log_header(tp, bp);
	xfs_dir2_data_check(dp, bp);
	/*
	 * See if the size as a shortform is good enough.
	 */
	if ((size = xfs_dir2_block_sfsize(dp, block, &sfh)) >
	    XFS_IFORK_DSIZE(dp)) {
		xfs_da_buf_done(bp);
		return 0;
	}
	/*
	 * If it works, do the conversion.
	 */
	return xfs_dir2_block_to_sf(args, bp, size, &sfh);
}