#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_50__   TYPE_9__ ;
typedef  struct TYPE_49__   TYPE_7__ ;
typedef  struct TYPE_48__   TYPE_6__ ;
typedef  struct TYPE_47__   TYPE_5__ ;
typedef  struct TYPE_46__   TYPE_4__ ;
typedef  struct TYPE_45__   TYPE_3__ ;
typedef  struct TYPE_44__   TYPE_2__ ;
typedef  struct TYPE_43__   TYPE_1__ ;
typedef  struct TYPE_42__   TYPE_11__ ;
typedef  struct TYPE_41__   TYPE_10__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  xfs_trans_t ;
struct TYPE_45__ {scalar_t__ m_dirblksize; size_t m_dirdatablk; } ;
typedef  TYPE_3__ xfs_mount_t ;
struct TYPE_46__ {TYPE_3__* i_mount; } ;
typedef  TYPE_4__ xfs_inode_t ;
struct TYPE_47__ {int /*<<< orphan*/  bestcount; } ;
typedef  TYPE_5__ xfs_dir2_leaf_tail_t ;
struct TYPE_44__ {TYPE_1__* bestfree; int /*<<< orphan*/  stale; } ;
struct TYPE_48__ {TYPE_2__ hdr; TYPE_7__* ents; } ;
typedef  TYPE_6__ xfs_dir2_leaf_t ;
struct TYPE_49__ {int /*<<< orphan*/  address; } ;
typedef  TYPE_7__ xfs_dir2_leaf_entry_t ;
typedef  size_t xfs_dir2_db_t ;
typedef  TYPE_6__ xfs_dir2_data_t ;
typedef  scalar_t__ xfs_dir2_data_off_t ;
struct TYPE_50__ {int /*<<< orphan*/  namelen; } ;
typedef  TYPE_9__ xfs_dir2_data_entry_t ;
typedef  int /*<<< orphan*/  xfs_dir2_data_aoff_t ;
struct TYPE_41__ {TYPE_6__* data; } ;
typedef  TYPE_10__ xfs_dabuf_t ;
struct TYPE_42__ {scalar_t__ total; int /*<<< orphan*/ * trans; TYPE_4__* dp; } ;
typedef  TYPE_11__ xfs_da_args_t ;
typedef  scalar_t__ uint ;
typedef  int /*<<< orphan*/  __be16 ;
struct TYPE_43__ {int /*<<< orphan*/  length; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int ENOSPC ; 
 scalar_t__ NULLDATAOFF ; 
 int /*<<< orphan*/  XFS_DIR2_NULL_DATAPTR ; 
 int /*<<< orphan*/  be16_add_cpu (int /*<<< orphan*/ *,int) ; 
 scalar_t__ be16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  be32_add_cpu (int /*<<< orphan*/ *,size_t) ; 
 int be32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_to_be16 (scalar_t__) ; 
 int /*<<< orphan*/  cpu_to_be32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memmove (int /*<<< orphan*/ *,int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  trace_xfs_dir2_leaf_removename (TYPE_11__*) ; 
 int /*<<< orphan*/  xfs_da_buf_done (TYPE_10__*) ; 
 int /*<<< orphan*/  xfs_dir2_data_check (TYPE_4__*,TYPE_10__*) ; 
 int /*<<< orphan*/  xfs_dir2_data_entsize (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xfs_dir2_data_freescan (TYPE_3__*,TYPE_6__*,int*) ; 
 int /*<<< orphan*/  xfs_dir2_data_log_header (int /*<<< orphan*/ *,TYPE_10__*) ; 
 int /*<<< orphan*/  xfs_dir2_data_make_free (int /*<<< orphan*/ *,TYPE_10__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int*) ; 
 size_t xfs_dir2_dataptr_to_db (TYPE_3__*,int) ; 
 int xfs_dir2_dataptr_to_off (TYPE_3__*,int) ; 
 int /*<<< orphan*/ * xfs_dir2_leaf_bests_p (TYPE_5__*) ; 
 int /*<<< orphan*/  xfs_dir2_leaf_check (TYPE_4__*,TYPE_10__*) ; 
 int /*<<< orphan*/  xfs_dir2_leaf_log_bests (int /*<<< orphan*/ *,TYPE_10__*,size_t,int) ; 
 int /*<<< orphan*/  xfs_dir2_leaf_log_ents (int /*<<< orphan*/ *,TYPE_10__*,int,int) ; 
 int /*<<< orphan*/  xfs_dir2_leaf_log_header (int /*<<< orphan*/ *,TYPE_10__*) ; 
 int /*<<< orphan*/  xfs_dir2_leaf_log_tail (int /*<<< orphan*/ *,TYPE_10__*) ; 
 int xfs_dir2_leaf_lookup_int (TYPE_11__*,TYPE_10__**,int*,TYPE_10__**) ; 
 TYPE_5__* xfs_dir2_leaf_tail_p (TYPE_3__*,TYPE_6__*) ; 
 int xfs_dir2_leaf_to_block (TYPE_11__*,TYPE_10__*,TYPE_10__*) ; 
 int xfs_dir2_shrink_inode (TYPE_11__*,size_t,TYPE_10__*) ; 

int						/* error */
xfs_dir2_leaf_removename(
	xfs_da_args_t		*args)		/* operation arguments */
{
	__be16			*bestsp;	/* leaf block best freespace */
	xfs_dir2_data_t		*data;		/* data block structure */
	xfs_dir2_db_t		db;		/* data block number */
	xfs_dabuf_t		*dbp;		/* data block buffer */
	xfs_dir2_data_entry_t	*dep;		/* data entry structure */
	xfs_inode_t		*dp;		/* incore directory inode */
	int			error;		/* error return code */
	xfs_dir2_db_t		i;		/* temporary data block # */
	int			index;		/* index into leaf entries */
	xfs_dabuf_t		*lbp;		/* leaf buffer */
	xfs_dir2_leaf_t		*leaf;		/* leaf structure */
	xfs_dir2_leaf_entry_t	*lep;		/* leaf entry */
	xfs_dir2_leaf_tail_t	*ltp;		/* leaf tail structure */
	xfs_mount_t		*mp;		/* filesystem mount point */
	int			needlog;	/* need to log data header */
	int			needscan;	/* need to rescan data frees */
	xfs_dir2_data_off_t	oldbest;	/* old value of best free */
	xfs_trans_t		*tp;		/* transaction pointer */

	trace_xfs_dir2_leaf_removename(args);

	/*
	 * Lookup the leaf entry, get the leaf and data blocks read in.
	 */
	if ((error = xfs_dir2_leaf_lookup_int(args, &lbp, &index, &dbp))) {
		return error;
	}
	dp = args->dp;
	tp = args->trans;
	mp = dp->i_mount;
	leaf = lbp->data;
	data = dbp->data;
	xfs_dir2_data_check(dp, dbp);
	/*
	 * Point to the leaf entry, use that to point to the data entry.
	 */
	lep = &leaf->ents[index];
	db = xfs_dir2_dataptr_to_db(mp, be32_to_cpu(lep->address));
	dep = (xfs_dir2_data_entry_t *)
	      ((char *)data + xfs_dir2_dataptr_to_off(mp, be32_to_cpu(lep->address)));
	needscan = needlog = 0;
	oldbest = be16_to_cpu(data->hdr.bestfree[0].length);
	ltp = xfs_dir2_leaf_tail_p(mp, leaf);
	bestsp = xfs_dir2_leaf_bests_p(ltp);
	ASSERT(be16_to_cpu(bestsp[db]) == oldbest);
	/*
	 * Mark the former data entry unused.
	 */
	xfs_dir2_data_make_free(tp, dbp,
		(xfs_dir2_data_aoff_t)((char *)dep - (char *)data),
		xfs_dir2_data_entsize(dep->namelen), &needlog, &needscan);
	/*
	 * We just mark the leaf entry stale by putting a null in it.
	 */
	be16_add_cpu(&leaf->hdr.stale, 1);
	xfs_dir2_leaf_log_header(tp, lbp);
	lep->address = cpu_to_be32(XFS_DIR2_NULL_DATAPTR);
	xfs_dir2_leaf_log_ents(tp, lbp, index, index);
	/*
	 * Scan the freespace in the data block again if necessary,
	 * log the data block header if necessary.
	 */
	if (needscan)
		xfs_dir2_data_freescan(mp, data, &needlog);
	if (needlog)
		xfs_dir2_data_log_header(tp, dbp);
	/*
	 * If the longest freespace in the data block has changed,
	 * put the new value in the bests table and log that.
	 */
	if (be16_to_cpu(data->hdr.bestfree[0].length) != oldbest) {
		bestsp[db] = data->hdr.bestfree[0].length;
		xfs_dir2_leaf_log_bests(tp, lbp, db, db);
	}
	xfs_dir2_data_check(dp, dbp);
	/*
	 * If the data block is now empty then get rid of the data block.
	 */
	if (be16_to_cpu(data->hdr.bestfree[0].length) ==
	    mp->m_dirblksize - (uint)sizeof(data->hdr)) {
		ASSERT(db != mp->m_dirdatablk);
		if ((error = xfs_dir2_shrink_inode(args, db, dbp))) {
			/*
			 * Nope, can't get rid of it because it caused
			 * allocation of a bmap btree block to do so.
			 * Just go on, returning success, leaving the
			 * empty block in place.
			 */
			if (error == ENOSPC && args->total == 0) {
				xfs_da_buf_done(dbp);
				error = 0;
			}
			xfs_dir2_leaf_check(dp, lbp);
			xfs_da_buf_done(lbp);
			return error;
		}
		dbp = NULL;
		/*
		 * If this is the last data block then compact the
		 * bests table by getting rid of entries.
		 */
		if (db == be32_to_cpu(ltp->bestcount) - 1) {
			/*
			 * Look for the last active entry (i).
			 */
			for (i = db - 1; i > 0; i--) {
				if (be16_to_cpu(bestsp[i]) != NULLDATAOFF)
					break;
			}
			/*
			 * Copy the table down so inactive entries at the
			 * end are removed.
			 */
			memmove(&bestsp[db - i], bestsp,
				(be32_to_cpu(ltp->bestcount) - (db - i)) * sizeof(*bestsp));
			be32_add_cpu(&ltp->bestcount, -(db - i));
			xfs_dir2_leaf_log_tail(tp, lbp);
			xfs_dir2_leaf_log_bests(tp, lbp, 0, be32_to_cpu(ltp->bestcount) - 1);
		} else
			bestsp[db] = cpu_to_be16(NULLDATAOFF);
	}
	/*
	 * If the data block was not the first one, drop it.
	 */
	else if (db != mp->m_dirdatablk && dbp != NULL) {
		xfs_da_buf_done(dbp);
		dbp = NULL;
	}
	xfs_dir2_leaf_check(dp, lbp);
	/*
	 * See if we can convert to block form.
	 */
	return xfs_dir2_leaf_to_block(args, lbp, dbp);
}