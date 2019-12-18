#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_45__   TYPE_9__ ;
typedef  struct TYPE_44__   TYPE_7__ ;
typedef  struct TYPE_43__   TYPE_6__ ;
typedef  struct TYPE_42__   TYPE_5__ ;
typedef  struct TYPE_41__   TYPE_4__ ;
typedef  struct TYPE_40__   TYPE_3__ ;
typedef  struct TYPE_39__   TYPE_2__ ;
typedef  struct TYPE_38__   TYPE_1__ ;
typedef  struct TYPE_37__   TYPE_10__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  xfs_trans_t ;
struct TYPE_40__ {int m_dirblksize; } ;
typedef  TYPE_3__ xfs_mount_t ;
struct TYPE_41__ {TYPE_3__* i_mount; } ;
typedef  TYPE_4__ xfs_inode_t ;
struct TYPE_42__ {void* bestcount; } ;
typedef  TYPE_5__ xfs_dir2_leaf_tail_t ;
struct TYPE_39__ {TYPE_1__* bestfree; void* magic; void* count; void* stale; } ;
struct TYPE_43__ {TYPE_2__ hdr; int /*<<< orphan*/  ents; } ;
typedef  TYPE_6__ xfs_dir2_leaf_t ;
typedef  int /*<<< orphan*/  xfs_dir2_leaf_entry_t ;
typedef  scalar_t__ xfs_dir2_db_t ;
typedef  int /*<<< orphan*/  xfs_dir2_data_t ;
typedef  int /*<<< orphan*/  xfs_dir2_data_aoff_t ;
struct TYPE_44__ {int /*<<< orphan*/  count; int /*<<< orphan*/  stale; } ;
typedef  TYPE_7__ xfs_dir2_block_tail_t ;
typedef  TYPE_6__ xfs_dir2_block_t ;
struct TYPE_45__ {TYPE_6__* data; } ;
typedef  TYPE_9__ xfs_dabuf_t ;
typedef  int /*<<< orphan*/  xfs_dablk_t ;
struct TYPE_37__ {int /*<<< orphan*/ * trans; TYPE_4__* dp; } ;
typedef  TYPE_10__ xfs_da_args_t ;
typedef  int /*<<< orphan*/  __be16 ;
struct TYPE_38__ {int /*<<< orphan*/  length; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int XFS_DIR2_DATA_MAGIC ; 
 int /*<<< orphan*/  XFS_DIR2_LEAF1_MAGIC ; 
 scalar_t__ XFS_DIR2_LEAF_FIRSTDB (TYPE_3__*) ; 
 scalar_t__ be16_to_cpu (void*) ; 
 int be32_to_cpu (int /*<<< orphan*/ ) ; 
 void* cpu_to_be16 (int) ; 
 void* cpu_to_be32 (int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  trace_xfs_dir2_block_to_leaf (TYPE_10__*) ; 
 int /*<<< orphan*/  xfs_da_buf_done (TYPE_9__*) ; 
 int xfs_da_grow_inode (TYPE_10__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * xfs_dir2_block_leaf_p (TYPE_7__*) ; 
 TYPE_7__* xfs_dir2_block_tail_p (TYPE_3__*,TYPE_6__*) ; 
 scalar_t__ xfs_dir2_da_to_db (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xfs_dir2_data_check (TYPE_4__*,TYPE_9__*) ; 
 int /*<<< orphan*/  xfs_dir2_data_freescan (TYPE_3__*,int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  xfs_dir2_data_log_header (int /*<<< orphan*/ *,TYPE_9__*) ; 
 int /*<<< orphan*/  xfs_dir2_data_make_free (int /*<<< orphan*/ *,TYPE_9__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int*) ; 
 int /*<<< orphan*/ * xfs_dir2_leaf_bests_p (TYPE_5__*) ; 
 int /*<<< orphan*/  xfs_dir2_leaf_check (TYPE_4__*,TYPE_9__*) ; 
 int xfs_dir2_leaf_init (TYPE_10__*,scalar_t__,TYPE_9__**,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xfs_dir2_leaf_log_bests (int /*<<< orphan*/ *,TYPE_9__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xfs_dir2_leaf_log_ents (int /*<<< orphan*/ *,TYPE_9__*,int /*<<< orphan*/ ,scalar_t__) ; 
 TYPE_5__* xfs_dir2_leaf_tail_p (TYPE_3__*,TYPE_6__*) ; 

int						/* error */
xfs_dir2_block_to_leaf(
	xfs_da_args_t		*args,		/* operation arguments */
	xfs_dabuf_t		*dbp)		/* input block's buffer */
{
	__be16			*bestsp;	/* leaf's bestsp entries */
	xfs_dablk_t		blkno;		/* leaf block's bno */
	xfs_dir2_block_t	*block;		/* block structure */
	xfs_dir2_leaf_entry_t	*blp;		/* block's leaf entries */
	xfs_dir2_block_tail_t	*btp;		/* block's tail */
	xfs_inode_t		*dp;		/* incore directory inode */
	int			error;		/* error return code */
	xfs_dabuf_t		*lbp;		/* leaf block's buffer */
	xfs_dir2_db_t		ldb;		/* leaf block's bno */
	xfs_dir2_leaf_t		*leaf;		/* leaf structure */
	xfs_dir2_leaf_tail_t	*ltp;		/* leaf's tail */
	xfs_mount_t		*mp;		/* filesystem mount point */
	int			needlog;	/* need to log block header */
	int			needscan;	/* need to rescan bestfree */
	xfs_trans_t		*tp;		/* transaction pointer */

	trace_xfs_dir2_block_to_leaf(args);

	dp = args->dp;
	mp = dp->i_mount;
	tp = args->trans;
	/*
	 * Add the leaf block to the inode.
	 * This interface will only put blocks in the leaf/node range.
	 * Since that's empty now, we'll get the root (block 0 in range).
	 */
	if ((error = xfs_da_grow_inode(args, &blkno))) {
		return error;
	}
	ldb = xfs_dir2_da_to_db(mp, blkno);
	ASSERT(ldb == XFS_DIR2_LEAF_FIRSTDB(mp));
	/*
	 * Initialize the leaf block, get a buffer for it.
	 */
	if ((error = xfs_dir2_leaf_init(args, ldb, &lbp, XFS_DIR2_LEAF1_MAGIC))) {
		return error;
	}
	ASSERT(lbp != NULL);
	leaf = lbp->data;
	block = dbp->data;
	xfs_dir2_data_check(dp, dbp);
	btp = xfs_dir2_block_tail_p(mp, block);
	blp = xfs_dir2_block_leaf_p(btp);
	/*
	 * Set the counts in the leaf header.
	 */
	leaf->hdr.count = cpu_to_be16(be32_to_cpu(btp->count));
	leaf->hdr.stale = cpu_to_be16(be32_to_cpu(btp->stale));
	/*
	 * Could compact these but I think we always do the conversion
	 * after squeezing out stale entries.
	 */
	memcpy(leaf->ents, blp, be32_to_cpu(btp->count) * sizeof(xfs_dir2_leaf_entry_t));
	xfs_dir2_leaf_log_ents(tp, lbp, 0, be16_to_cpu(leaf->hdr.count) - 1);
	needscan = 0;
	needlog = 1;
	/*
	 * Make the space formerly occupied by the leaf entries and block
	 * tail be free.
	 */
	xfs_dir2_data_make_free(tp, dbp,
		(xfs_dir2_data_aoff_t)((char *)blp - (char *)block),
		(xfs_dir2_data_aoff_t)((char *)block + mp->m_dirblksize -
				       (char *)blp),
		&needlog, &needscan);
	/*
	 * Fix up the block header, make it a data block.
	 */
	block->hdr.magic = cpu_to_be32(XFS_DIR2_DATA_MAGIC);
	if (needscan)
		xfs_dir2_data_freescan(mp, (xfs_dir2_data_t *)block, &needlog);
	/*
	 * Set up leaf tail and bests table.
	 */
	ltp = xfs_dir2_leaf_tail_p(mp, leaf);
	ltp->bestcount = cpu_to_be32(1);
	bestsp = xfs_dir2_leaf_bests_p(ltp);
	bestsp[0] =  block->hdr.bestfree[0].length;
	/*
	 * Log the data header and leaf bests table.
	 */
	if (needlog)
		xfs_dir2_data_log_header(tp, dbp);
	xfs_dir2_leaf_check(dp, lbp);
	xfs_dir2_data_check(dp, dbp);
	xfs_dir2_leaf_log_bests(tp, lbp, 0, 0);
	xfs_da_buf_done(lbp);
	return 0;
}