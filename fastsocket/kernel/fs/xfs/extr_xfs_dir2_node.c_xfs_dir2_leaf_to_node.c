#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_37__   TYPE_9__ ;
typedef  struct TYPE_36__   TYPE_7__ ;
typedef  struct TYPE_35__   TYPE_6__ ;
typedef  struct TYPE_34__   TYPE_5__ ;
typedef  struct TYPE_33__   TYPE_4__ ;
typedef  struct TYPE_32__   TYPE_3__ ;
typedef  struct TYPE_31__   TYPE_2__ ;
typedef  struct TYPE_30__   TYPE_1__ ;
typedef  struct TYPE_29__   TYPE_10__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  xfs_trans_t ;
struct TYPE_33__ {int m_dirblksize; } ;
typedef  TYPE_4__ xfs_mount_t ;
struct TYPE_30__ {scalar_t__ di_size; } ;
struct TYPE_34__ {TYPE_1__ i_d; TYPE_4__* i_mount; } ;
typedef  TYPE_5__ xfs_inode_t ;
struct TYPE_35__ {int /*<<< orphan*/  bestcount; } ;
typedef  TYPE_6__ xfs_dir2_leaf_tail_t ;
struct TYPE_31__ {void* magic; } ;
struct TYPE_32__ {int /*<<< orphan*/  nvalid; TYPE_2__ info; void* nused; scalar_t__ firstdb; void* magic; } ;
struct TYPE_36__ {TYPE_3__ hdr; void** bests; } ;
typedef  TYPE_7__ xfs_dir2_leaf_t ;
typedef  TYPE_7__ xfs_dir2_free_t ;
typedef  scalar_t__ xfs_dir2_db_t ;
typedef  int /*<<< orphan*/  xfs_dir2_data_off_t ;
struct TYPE_37__ {TYPE_7__* data; } ;
typedef  TYPE_9__ xfs_dabuf_t ;
struct TYPE_29__ {int /*<<< orphan*/ * trans; TYPE_5__* dp; } ;
typedef  TYPE_10__ xfs_da_args_t ;
typedef  int uint ;
typedef  void* __be16 ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int /*<<< orphan*/  NULLDATAOFF ; 
 int /*<<< orphan*/  XFS_DATA_FORK ; 
 scalar_t__ XFS_DIR2_FREE_FIRSTDB (TYPE_4__*) ; 
 int XFS_DIR2_FREE_MAGIC ; 
 int /*<<< orphan*/  XFS_DIR2_FREE_SPACE ; 
 int /*<<< orphan*/  XFS_DIR2_LEAFN_MAGIC ; 
 int /*<<< orphan*/  be16_to_cpu (void*) ; 
 int be32_to_cpu (int /*<<< orphan*/ ) ; 
 void* cpu_to_be16 (int /*<<< orphan*/ ) ; 
 void* cpu_to_be32 (int) ; 
 int /*<<< orphan*/  trace_xfs_dir2_leaf_to_node (TYPE_10__*) ; 
 int /*<<< orphan*/  xfs_da_buf_done (TYPE_9__*) ; 
 int xfs_da_get_buf (int /*<<< orphan*/ *,TYPE_5__*,int /*<<< orphan*/ ,int,TYPE_9__**,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xfs_dir2_db_to_da (TYPE_4__*,scalar_t__) ; 
 int /*<<< orphan*/  xfs_dir2_free_log_bests (int /*<<< orphan*/ *,TYPE_9__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  xfs_dir2_free_log_header (int /*<<< orphan*/ *,TYPE_9__*) ; 
 int xfs_dir2_grow_inode (TYPE_10__*,int /*<<< orphan*/ ,scalar_t__*) ; 
 void** xfs_dir2_leaf_bests_p (TYPE_6__*) ; 
 int /*<<< orphan*/  xfs_dir2_leaf_log_header (int /*<<< orphan*/ *,TYPE_9__*) ; 
 TYPE_6__* xfs_dir2_leaf_tail_p (TYPE_4__*,TYPE_7__*) ; 
 int /*<<< orphan*/  xfs_dir2_leafn_check (TYPE_5__*,TYPE_9__*) ; 

int						/* error */
xfs_dir2_leaf_to_node(
	xfs_da_args_t		*args,		/* operation arguments */
	xfs_dabuf_t		*lbp)		/* leaf buffer */
{
	xfs_inode_t		*dp;		/* incore directory inode */
	int			error;		/* error return value */
	xfs_dabuf_t		*fbp;		/* freespace buffer */
	xfs_dir2_db_t		fdb;		/* freespace block number */
	xfs_dir2_free_t		*free;		/* freespace structure */
	__be16			*from;		/* pointer to freespace entry */
	int			i;		/* leaf freespace index */
	xfs_dir2_leaf_t		*leaf;		/* leaf structure */
	xfs_dir2_leaf_tail_t	*ltp;		/* leaf tail structure */
	xfs_mount_t		*mp;		/* filesystem mount point */
	int			n;		/* count of live freespc ents */
	xfs_dir2_data_off_t	off;		/* freespace entry value */
	__be16			*to;		/* pointer to freespace entry */
	xfs_trans_t		*tp;		/* transaction pointer */

	trace_xfs_dir2_leaf_to_node(args);

	dp = args->dp;
	mp = dp->i_mount;
	tp = args->trans;
	/*
	 * Add a freespace block to the directory.
	 */
	if ((error = xfs_dir2_grow_inode(args, XFS_DIR2_FREE_SPACE, &fdb))) {
		return error;
	}
	ASSERT(fdb == XFS_DIR2_FREE_FIRSTDB(mp));
	/*
	 * Get the buffer for the new freespace block.
	 */
	if ((error = xfs_da_get_buf(tp, dp, xfs_dir2_db_to_da(mp, fdb), -1, &fbp,
			XFS_DATA_FORK))) {
		return error;
	}
	ASSERT(fbp != NULL);
	free = fbp->data;
	leaf = lbp->data;
	ltp = xfs_dir2_leaf_tail_p(mp, leaf);
	/*
	 * Initialize the freespace block header.
	 */
	free->hdr.magic = cpu_to_be32(XFS_DIR2_FREE_MAGIC);
	free->hdr.firstdb = 0;
	ASSERT(be32_to_cpu(ltp->bestcount) <= (uint)dp->i_d.di_size / mp->m_dirblksize);
	free->hdr.nvalid = ltp->bestcount;
	/*
	 * Copy freespace entries from the leaf block to the new block.
	 * Count active entries.
	 */
	for (i = n = 0, from = xfs_dir2_leaf_bests_p(ltp), to = free->bests;
	     i < be32_to_cpu(ltp->bestcount); i++, from++, to++) {
		if ((off = be16_to_cpu(*from)) != NULLDATAOFF)
			n++;
		*to = cpu_to_be16(off);
	}
	free->hdr.nused = cpu_to_be32(n);
	leaf->hdr.info.magic = cpu_to_be16(XFS_DIR2_LEAFN_MAGIC);
	/*
	 * Log everything.
	 */
	xfs_dir2_leaf_log_header(tp, lbp);
	xfs_dir2_free_log_header(tp, fbp);
	xfs_dir2_free_log_bests(tp, fbp, 0, be32_to_cpu(free->hdr.nvalid) - 1);
	xfs_da_buf_done(fbp);
	xfs_dir2_leafn_check(dp, lbp);
	return 0;
}