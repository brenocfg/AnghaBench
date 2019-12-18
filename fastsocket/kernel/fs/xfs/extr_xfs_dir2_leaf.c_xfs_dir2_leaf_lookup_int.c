#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_34__   TYPE_9__ ;
typedef  struct TYPE_33__   TYPE_8__ ;
typedef  struct TYPE_32__   TYPE_7__ ;
typedef  struct TYPE_31__   TYPE_6__ ;
typedef  struct TYPE_30__   TYPE_5__ ;
typedef  struct TYPE_29__   TYPE_4__ ;
typedef  struct TYPE_28__   TYPE_3__ ;
typedef  struct TYPE_27__   TYPE_2__ ;
typedef  struct TYPE_26__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  xfs_trans_t ;
struct TYPE_28__ {TYPE_2__* m_dirnameops; int /*<<< orphan*/  m_dirleafblk; } ;
typedef  TYPE_3__ xfs_mount_t ;
struct TYPE_29__ {TYPE_3__* i_mount; } ;
typedef  TYPE_4__ xfs_inode_t ;
struct TYPE_26__ {int /*<<< orphan*/  count; } ;
struct TYPE_30__ {TYPE_1__ hdr; TYPE_6__* ents; } ;
typedef  TYPE_5__ xfs_dir2_leaf_t ;
struct TYPE_31__ {int /*<<< orphan*/  address; int /*<<< orphan*/  hashval; } ;
typedef  TYPE_6__ xfs_dir2_leaf_entry_t ;
typedef  int xfs_dir2_db_t ;
struct TYPE_32__ {int /*<<< orphan*/  namelen; int /*<<< orphan*/  name; } ;
typedef  TYPE_7__ xfs_dir2_data_entry_t ;
struct TYPE_33__ {TYPE_5__* data; } ;
typedef  TYPE_8__ xfs_dabuf_t ;
struct TYPE_34__ {scalar_t__ hashval; int cmpresult; int op_flags; int /*<<< orphan*/ * trans; TYPE_4__* dp; } ;
typedef  TYPE_9__ xfs_da_args_t ;
typedef  enum xfs_dacmp { ____Placeholder_xfs_dacmp } xfs_dacmp ;
struct TYPE_27__ {int (* compname ) (TYPE_9__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int /*<<< orphan*/  ENOENT ; 
 scalar_t__ XFS_CMP_CASE ; 
 int XFS_CMP_DIFFERENT ; 
 int XFS_CMP_EXACT ; 
 int /*<<< orphan*/  XFS_DATA_FORK ; 
 int XFS_DA_OP_OKNOENT ; 
 scalar_t__ XFS_DIR2_NULL_DATAPTR ; 
 int XFS_ERROR (int /*<<< orphan*/ ) ; 
 int be16_to_cpu (int /*<<< orphan*/ ) ; 
 scalar_t__ be32_to_cpu (int /*<<< orphan*/ ) ; 
 int stub1 (TYPE_9__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xfs_da_brelse (int /*<<< orphan*/ *,TYPE_8__*) ; 
 int xfs_da_read_buf (int /*<<< orphan*/ *,TYPE_4__*,int /*<<< orphan*/ ,int,TYPE_8__**,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xfs_dir2_data_check (TYPE_4__*,TYPE_8__*) ; 
 int xfs_dir2_dataptr_to_db (TYPE_3__*,scalar_t__) ; 
 int xfs_dir2_dataptr_to_off (TYPE_3__*,scalar_t__) ; 
 int /*<<< orphan*/  xfs_dir2_db_to_da (TYPE_3__*,int) ; 
 int /*<<< orphan*/  xfs_dir2_leaf_check (TYPE_4__*,TYPE_8__*) ; 
 int xfs_dir2_leaf_search_hash (TYPE_9__*,TYPE_8__*) ; 

__attribute__((used)) static int					/* error */
xfs_dir2_leaf_lookup_int(
	xfs_da_args_t		*args,		/* operation arguments */
	xfs_dabuf_t		**lbpp,		/* out: leaf buffer */
	int			*indexp,	/* out: index in leaf block */
	xfs_dabuf_t		**dbpp)		/* out: data buffer */
{
	xfs_dir2_db_t		curdb = -1;	/* current data block number */
	xfs_dabuf_t		*dbp = NULL;	/* data buffer */
	xfs_dir2_data_entry_t	*dep;		/* data entry */
	xfs_inode_t		*dp;		/* incore directory inode */
	int			error;		/* error return code */
	int			index;		/* index in leaf block */
	xfs_dabuf_t		*lbp;		/* leaf buffer */
	xfs_dir2_leaf_entry_t	*lep;		/* leaf entry */
	xfs_dir2_leaf_t		*leaf;		/* leaf structure */
	xfs_mount_t		*mp;		/* filesystem mount point */
	xfs_dir2_db_t		newdb;		/* new data block number */
	xfs_trans_t		*tp;		/* transaction pointer */
	xfs_dir2_db_t		cidb = -1;	/* case match data block no. */
	enum xfs_dacmp		cmp;		/* name compare result */

	dp = args->dp;
	tp = args->trans;
	mp = dp->i_mount;
	/*
	 * Read the leaf block into the buffer.
	 */
	error = xfs_da_read_buf(tp, dp, mp->m_dirleafblk, -1, &lbp,
							XFS_DATA_FORK);
	if (error)
		return error;
	*lbpp = lbp;
	leaf = lbp->data;
	xfs_dir2_leaf_check(dp, lbp);
	/*
	 * Look for the first leaf entry with our hash value.
	 */
	index = xfs_dir2_leaf_search_hash(args, lbp);
	/*
	 * Loop over all the entries with the right hash value
	 * looking to match the name.
	 */
	for (lep = &leaf->ents[index]; index < be16_to_cpu(leaf->hdr.count) &&
				be32_to_cpu(lep->hashval) == args->hashval;
				lep++, index++) {
		/*
		 * Skip over stale leaf entries.
		 */
		if (be32_to_cpu(lep->address) == XFS_DIR2_NULL_DATAPTR)
			continue;
		/*
		 * Get the new data block number.
		 */
		newdb = xfs_dir2_dataptr_to_db(mp, be32_to_cpu(lep->address));
		/*
		 * If it's not the same as the old data block number,
		 * need to pitch the old one and read the new one.
		 */
		if (newdb != curdb) {
			if (dbp)
				xfs_da_brelse(tp, dbp);
			error = xfs_da_read_buf(tp, dp,
						xfs_dir2_db_to_da(mp, newdb),
						-1, &dbp, XFS_DATA_FORK);
			if (error) {
				xfs_da_brelse(tp, lbp);
				return error;
			}
			xfs_dir2_data_check(dp, dbp);
			curdb = newdb;
		}
		/*
		 * Point to the data entry.
		 */
		dep = (xfs_dir2_data_entry_t *)((char *)dbp->data +
			xfs_dir2_dataptr_to_off(mp, be32_to_cpu(lep->address)));
		/*
		 * Compare name and if it's an exact match, return the index
		 * and buffer. If it's the first case-insensitive match, store
		 * the index and buffer and continue looking for an exact match.
		 */
		cmp = mp->m_dirnameops->compname(args, dep->name, dep->namelen);
		if (cmp != XFS_CMP_DIFFERENT && cmp != args->cmpresult) {
			args->cmpresult = cmp;
			*indexp = index;
			/* case exact match: return the current buffer. */
			if (cmp == XFS_CMP_EXACT) {
				*dbpp = dbp;
				return 0;
			}
			cidb = curdb;
		}
	}
	ASSERT(args->op_flags & XFS_DA_OP_OKNOENT);
	/*
	 * Here, we can only be doing a lookup (not a rename or remove).
	 * If a case-insensitive match was found earlier, re-read the
	 * appropriate data block if required and return it.
	 */
	if (args->cmpresult == XFS_CMP_CASE) {
		ASSERT(cidb != -1);
		if (cidb != curdb) {
			xfs_da_brelse(tp, dbp);
			error = xfs_da_read_buf(tp, dp,
						xfs_dir2_db_to_da(mp, cidb),
						-1, &dbp, XFS_DATA_FORK);
			if (error) {
				xfs_da_brelse(tp, lbp);
				return error;
			}
		}
		*dbpp = dbp;
		return 0;
	}
	/*
	 * No match found, return ENOENT.
	 */
	ASSERT(cidb == -1);
	if (dbp)
		xfs_da_brelse(tp, dbp);
	xfs_da_brelse(tp, lbp);
	return XFS_ERROR(ENOENT);
}