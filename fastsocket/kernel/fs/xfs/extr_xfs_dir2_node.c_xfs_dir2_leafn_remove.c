#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_52__   TYPE_7__ ;
typedef  struct TYPE_51__   TYPE_6__ ;
typedef  struct TYPE_50__   TYPE_5__ ;
typedef  struct TYPE_49__   TYPE_4__ ;
typedef  struct TYPE_48__   TYPE_3__ ;
typedef  struct TYPE_47__   TYPE_2__ ;
typedef  struct TYPE_46__   TYPE_1__ ;
typedef  struct TYPE_45__   TYPE_13__ ;
typedef  struct TYPE_44__   TYPE_12__ ;
typedef  struct TYPE_43__   TYPE_11__ ;
typedef  struct TYPE_42__   TYPE_10__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  xfs_trans_t ;
struct TYPE_49__ {int m_dirblksize; int m_dir_magicpct; } ;
typedef  TYPE_4__ xfs_mount_t ;
struct TYPE_50__ {TYPE_4__* i_mount; } ;
typedef  TYPE_5__ xfs_inode_t ;
struct TYPE_46__ {void* magic; } ;
struct TYPE_48__ {void* stale; void* count; int /*<<< orphan*/  nused; void* nvalid; TYPE_2__* bestfree; void* firstdb; void* magic; TYPE_1__ info; } ;
struct TYPE_51__ {TYPE_3__ hdr; void** bests; TYPE_7__* ents; } ;
typedef  TYPE_6__ xfs_dir2_leaf_t ;
struct TYPE_52__ {void* address; } ;
typedef  TYPE_7__ xfs_dir2_leaf_entry_t ;
typedef  TYPE_6__ xfs_dir2_free_t ;
typedef  scalar_t__ xfs_dir2_db_t ;
typedef  TYPE_6__ xfs_dir2_data_t ;
struct TYPE_42__ {int /*<<< orphan*/  namelen; } ;
typedef  TYPE_10__ xfs_dir2_data_entry_t ;
struct TYPE_43__ {TYPE_6__* data; } ;
typedef  TYPE_11__ xfs_dabuf_t ;
struct TYPE_44__ {scalar_t__ blkno; int index; TYPE_11__* bp; } ;
typedef  TYPE_12__ xfs_da_state_blk_t ;
struct TYPE_45__ {scalar_t__ total; int /*<<< orphan*/ * trans; TYPE_5__* dp; } ;
typedef  TYPE_13__ xfs_da_args_t ;
typedef  int uint ;
struct TYPE_47__ {void* length; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int ENOSPC ; 
 scalar_t__ NULLDATAOFF ; 
 int /*<<< orphan*/  XFS_DATA_FORK ; 
 scalar_t__ XFS_DIR2_FREE_FIRSTDB (TYPE_4__*) ; 
 int XFS_DIR2_FREE_MAGIC ; 
 int XFS_DIR2_LEAFN_MAGIC ; 
 scalar_t__ XFS_DIR2_MAX_FREE_BESTS (TYPE_4__*) ; 
 int XFS_DIR2_NULL_DATAPTR ; 
 int /*<<< orphan*/  be16_add_cpu (void**,int) ; 
 int be16_to_cpu (void*) ; 
 int /*<<< orphan*/  be32_add_cpu (int /*<<< orphan*/ *,int) ; 
 int be32_to_cpu (void*) ; 
 void* cpu_to_be16 (int) ; 
 void* cpu_to_be32 (int) ; 
 int /*<<< orphan*/  trace_xfs_dir2_leafn_remove (TYPE_13__*,int) ; 
 int /*<<< orphan*/  xfs_da_buf_done (TYPE_11__*) ; 
 int xfs_da_read_buf (int /*<<< orphan*/ *,TYPE_5__*,int /*<<< orphan*/ ,int,TYPE_11__**,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xfs_dir2_data_check (TYPE_5__*,TYPE_11__*) ; 
 int /*<<< orphan*/  xfs_dir2_data_entsize (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xfs_dir2_data_freescan (TYPE_4__*,TYPE_6__*,int*) ; 
 int /*<<< orphan*/  xfs_dir2_data_log_header (int /*<<< orphan*/ *,TYPE_11__*) ; 
 int /*<<< orphan*/  xfs_dir2_data_make_free (int /*<<< orphan*/ *,TYPE_11__*,int,int /*<<< orphan*/ ,int*,int*) ; 
 scalar_t__ xfs_dir2_dataptr_to_db (TYPE_4__*,int) ; 
 int xfs_dir2_dataptr_to_off (TYPE_4__*,int) ; 
 int /*<<< orphan*/  xfs_dir2_db_to_da (TYPE_4__*,scalar_t__) ; 
 scalar_t__ xfs_dir2_db_to_fdb (TYPE_4__*,scalar_t__) ; 
 int xfs_dir2_db_to_fdindex (TYPE_4__*,scalar_t__) ; 
 int /*<<< orphan*/  xfs_dir2_free_log_bests (int /*<<< orphan*/ *,TYPE_11__*,int,int) ; 
 int /*<<< orphan*/  xfs_dir2_free_log_header (int /*<<< orphan*/ *,TYPE_11__*) ; 
 int /*<<< orphan*/  xfs_dir2_leaf_log_ents (int /*<<< orphan*/ *,TYPE_11__*,int,int) ; 
 int /*<<< orphan*/  xfs_dir2_leaf_log_header (int /*<<< orphan*/ *,TYPE_11__*) ; 
 int /*<<< orphan*/  xfs_dir2_leafn_check (TYPE_5__*,TYPE_11__*) ; 
 int xfs_dir2_shrink_inode (TYPE_13__*,scalar_t__,TYPE_11__*) ; 

__attribute__((used)) static int					/* error */
xfs_dir2_leafn_remove(
	xfs_da_args_t		*args,		/* operation arguments */
	xfs_dabuf_t		*bp,		/* leaf buffer */
	int			index,		/* leaf entry index */
	xfs_da_state_blk_t	*dblk,		/* data block */
	int			*rval)		/* resulting block needs join */
{
	xfs_dir2_data_t		*data;		/* data block structure */
	xfs_dir2_db_t		db;		/* data block number */
	xfs_dabuf_t		*dbp;		/* data block buffer */
	xfs_dir2_data_entry_t	*dep;		/* data block entry */
	xfs_inode_t		*dp;		/* incore directory inode */
	xfs_dir2_leaf_t		*leaf;		/* leaf structure */
	xfs_dir2_leaf_entry_t	*lep;		/* leaf entry */
	int			longest;	/* longest data free entry */
	int			off;		/* data block entry offset */
	xfs_mount_t		*mp;		/* filesystem mount point */
	int			needlog;	/* need to log data header */
	int			needscan;	/* need to rescan data frees */
	xfs_trans_t		*tp;		/* transaction pointer */

	trace_xfs_dir2_leafn_remove(args, index);

	dp = args->dp;
	tp = args->trans;
	mp = dp->i_mount;
	leaf = bp->data;
	ASSERT(be16_to_cpu(leaf->hdr.info.magic) == XFS_DIR2_LEAFN_MAGIC);
	/*
	 * Point to the entry we're removing.
	 */
	lep = &leaf->ents[index];
	/*
	 * Extract the data block and offset from the entry.
	 */
	db = xfs_dir2_dataptr_to_db(mp, be32_to_cpu(lep->address));
	ASSERT(dblk->blkno == db);
	off = xfs_dir2_dataptr_to_off(mp, be32_to_cpu(lep->address));
	ASSERT(dblk->index == off);
	/*
	 * Kill the leaf entry by marking it stale.
	 * Log the leaf block changes.
	 */
	be16_add_cpu(&leaf->hdr.stale, 1);
	xfs_dir2_leaf_log_header(tp, bp);
	lep->address = cpu_to_be32(XFS_DIR2_NULL_DATAPTR);
	xfs_dir2_leaf_log_ents(tp, bp, index, index);
	/*
	 * Make the data entry free.  Keep track of the longest freespace
	 * in the data block in case it changes.
	 */
	dbp = dblk->bp;
	data = dbp->data;
	dep = (xfs_dir2_data_entry_t *)((char *)data + off);
	longest = be16_to_cpu(data->hdr.bestfree[0].length);
	needlog = needscan = 0;
	xfs_dir2_data_make_free(tp, dbp, off,
		xfs_dir2_data_entsize(dep->namelen), &needlog, &needscan);
	/*
	 * Rescan the data block freespaces for bestfree.
	 * Log the data block header if needed.
	 */
	if (needscan)
		xfs_dir2_data_freescan(mp, data, &needlog);
	if (needlog)
		xfs_dir2_data_log_header(tp, dbp);
	xfs_dir2_data_check(dp, dbp);
	/*
	 * If the longest data block freespace changes, need to update
	 * the corresponding freeblock entry.
	 */
	if (longest < be16_to_cpu(data->hdr.bestfree[0].length)) {
		int		error;		/* error return value */
		xfs_dabuf_t	*fbp;		/* freeblock buffer */
		xfs_dir2_db_t	fdb;		/* freeblock block number */
		int		findex;		/* index in freeblock entries */
		xfs_dir2_free_t	*free;		/* freeblock structure */
		int		logfree;	/* need to log free entry */

		/*
		 * Convert the data block number to a free block,
		 * read in the free block.
		 */
		fdb = xfs_dir2_db_to_fdb(mp, db);
		if ((error = xfs_da_read_buf(tp, dp, xfs_dir2_db_to_da(mp, fdb),
				-1, &fbp, XFS_DATA_FORK))) {
			return error;
		}
		free = fbp->data;
		ASSERT(be32_to_cpu(free->hdr.magic) == XFS_DIR2_FREE_MAGIC);
		ASSERT(be32_to_cpu(free->hdr.firstdb) ==
		       XFS_DIR2_MAX_FREE_BESTS(mp) *
		       (fdb - XFS_DIR2_FREE_FIRSTDB(mp)));
		/*
		 * Calculate which entry we need to fix.
		 */
		findex = xfs_dir2_db_to_fdindex(mp, db);
		longest = be16_to_cpu(data->hdr.bestfree[0].length);
		/*
		 * If the data block is now empty we can get rid of it
		 * (usually).
		 */
		if (longest == mp->m_dirblksize - (uint)sizeof(data->hdr)) {
			/*
			 * Try to punch out the data block.
			 */
			error = xfs_dir2_shrink_inode(args, db, dbp);
			if (error == 0) {
				dblk->bp = NULL;
				data = NULL;
			}
			/*
			 * We can get ENOSPC if there's no space reservation.
			 * In this case just drop the buffer and some one else
			 * will eventually get rid of the empty block.
			 */
			else if (error == ENOSPC && args->total == 0)
				xfs_da_buf_done(dbp);
			else
				return error;
		}
		/*
		 * If we got rid of the data block, we can eliminate that entry
		 * in the free block.
		 */
		if (data == NULL) {
			/*
			 * One less used entry in the free table.
			 */
			be32_add_cpu(&free->hdr.nused, -1);
			xfs_dir2_free_log_header(tp, fbp);
			/*
			 * If this was the last entry in the table, we can
			 * trim the table size back.  There might be other
			 * entries at the end referring to non-existent
			 * data blocks, get those too.
			 */
			if (findex == be32_to_cpu(free->hdr.nvalid) - 1) {
				int	i;		/* free entry index */

				for (i = findex - 1;
				     i >= 0 && be16_to_cpu(free->bests[i]) == NULLDATAOFF;
				     i--)
					continue;
				free->hdr.nvalid = cpu_to_be32(i + 1);
				logfree = 0;
			}
			/*
			 * Not the last entry, just punch it out.
			 */
			else {
				free->bests[findex] = cpu_to_be16(NULLDATAOFF);
				logfree = 1;
			}
			/*
			 * If there are no useful entries left in the block,
			 * get rid of the block if we can.
			 */
			if (!free->hdr.nused) {
				error = xfs_dir2_shrink_inode(args, fdb, fbp);
				if (error == 0) {
					fbp = NULL;
					logfree = 0;
				} else if (error != ENOSPC || args->total != 0)
					return error;
				/*
				 * It's possible to get ENOSPC if there is no
				 * space reservation.  In this case some one
				 * else will eventually get rid of this block.
				 */
			}
		}
		/*
		 * Data block is not empty, just set the free entry to
		 * the new value.
		 */
		else {
			free->bests[findex] = cpu_to_be16(longest);
			logfree = 1;
		}
		/*
		 * Log the free entry that changed, unless we got rid of it.
		 */
		if (logfree)
			xfs_dir2_free_log_bests(tp, fbp, findex, findex);
		/*
		 * Drop the buffer if we still have it.
		 */
		if (fbp)
			xfs_da_buf_done(fbp);
	}
	xfs_dir2_leafn_check(dp, bp);
	/*
	 * Return indication of whether this leaf block is empty enough
	 * to justify trying to join it with a neighbor.
	 */
	*rval =
		((uint)sizeof(leaf->hdr) +
		 (uint)sizeof(leaf->ents[0]) *
		 (be16_to_cpu(leaf->hdr.count) - be16_to_cpu(leaf->hdr.stale))) <
		mp->m_dir_magicpct;
	return 0;
}