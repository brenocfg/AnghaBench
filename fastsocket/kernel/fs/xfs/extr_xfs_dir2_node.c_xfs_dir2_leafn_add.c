#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_22__   TYPE_6__ ;
typedef  struct TYPE_21__   TYPE_5__ ;
typedef  struct TYPE_20__   TYPE_4__ ;
typedef  struct TYPE_19__   TYPE_3__ ;
typedef  struct TYPE_18__   TYPE_2__ ;
typedef  struct TYPE_17__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  xfs_trans_t ;
typedef  int /*<<< orphan*/  xfs_mount_t ;
struct TYPE_18__ {int /*<<< orphan*/ * i_mount; } ;
typedef  TYPE_2__ xfs_inode_t ;
struct TYPE_17__ {scalar_t__ stale; scalar_t__ count; } ;
struct TYPE_19__ {TYPE_1__ hdr; TYPE_4__* ents; } ;
typedef  TYPE_3__ xfs_dir2_leaf_t ;
struct TYPE_20__ {void* address; void* hashval; } ;
typedef  TYPE_4__ xfs_dir2_leaf_entry_t ;
struct TYPE_21__ {TYPE_3__* data; } ;
typedef  TYPE_5__ xfs_dabuf_t ;
struct TYPE_22__ {scalar_t__ hashval; int op_flags; int /*<<< orphan*/  index; int /*<<< orphan*/  blkno; int /*<<< orphan*/ * trans; TYPE_2__* dp; } ;
typedef  TYPE_6__ xfs_da_args_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int /*<<< orphan*/  EFSCORRUPTED ; 
 int /*<<< orphan*/  ENOSPC ; 
 int MAX (int,int) ; 
 int MIN (int,int) ; 
 int XFS_DA_OP_JUSTCHECK ; 
 scalar_t__ XFS_DIR2_NULL_DATAPTR ; 
 int XFS_ERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  be16_add_cpu (scalar_t__*,int) ; 
 int be16_to_cpu (scalar_t__) ; 
 scalar_t__ be32_to_cpu (void*) ; 
 void* cpu_to_be32 (scalar_t__) ; 
 int /*<<< orphan*/  memmove (TYPE_4__*,TYPE_4__*,int) ; 
 int /*<<< orphan*/  trace_xfs_dir2_leafn_add (TYPE_6__*,int) ; 
 scalar_t__ xfs_dir2_db_off_to_dataptr (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xfs_dir2_leaf_compact_x1 (TYPE_5__*,int*,int*,int*,int*,int*) ; 
 int /*<<< orphan*/  xfs_dir2_leaf_log_ents (int /*<<< orphan*/ *,TYPE_5__*,int,int) ; 
 int /*<<< orphan*/  xfs_dir2_leaf_log_header (int /*<<< orphan*/ *,TYPE_5__*) ; 
 int /*<<< orphan*/  xfs_dir2_leafn_check (TYPE_2__*,TYPE_5__*) ; 
 int xfs_dir2_max_leaf_ents (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int					/* error */
xfs_dir2_leafn_add(
	xfs_dabuf_t		*bp,		/* leaf buffer */
	xfs_da_args_t		*args,		/* operation arguments */
	int			index)		/* insertion pt for new entry */
{
	int			compact;	/* compacting stale leaves */
	xfs_inode_t		*dp;		/* incore directory inode */
	int			highstale;	/* next stale entry */
	xfs_dir2_leaf_t		*leaf;		/* leaf structure */
	xfs_dir2_leaf_entry_t	*lep;		/* leaf entry */
	int			lfloghigh;	/* high leaf entry logging */
	int			lfloglow;	/* low leaf entry logging */
	int			lowstale;	/* previous stale entry */
	xfs_mount_t		*mp;		/* filesystem mount point */
	xfs_trans_t		*tp;		/* transaction pointer */

	trace_xfs_dir2_leafn_add(args, index);

	dp = args->dp;
	mp = dp->i_mount;
	tp = args->trans;
	leaf = bp->data;

	/*
	 * Quick check just to make sure we are not going to index
	 * into other peoples memory
	 */
	if (index < 0)
		return XFS_ERROR(EFSCORRUPTED);

	/*
	 * If there are already the maximum number of leaf entries in
	 * the block, if there are no stale entries it won't fit.
	 * Caller will do a split.  If there are stale entries we'll do
	 * a compact.
	 */

	if (be16_to_cpu(leaf->hdr.count) == xfs_dir2_max_leaf_ents(mp)) {
		if (!leaf->hdr.stale)
			return XFS_ERROR(ENOSPC);
		compact = be16_to_cpu(leaf->hdr.stale) > 1;
	} else
		compact = 0;
	ASSERT(index == 0 || be32_to_cpu(leaf->ents[index - 1].hashval) <= args->hashval);
	ASSERT(index == be16_to_cpu(leaf->hdr.count) ||
	       be32_to_cpu(leaf->ents[index].hashval) >= args->hashval);

	if (args->op_flags & XFS_DA_OP_JUSTCHECK)
		return 0;

	/*
	 * Compact out all but one stale leaf entry.  Leaves behind
	 * the entry closest to index.
	 */
	if (compact) {
		xfs_dir2_leaf_compact_x1(bp, &index, &lowstale, &highstale,
			&lfloglow, &lfloghigh);
	}
	/*
	 * Set impossible logging indices for this case.
	 */
	else if (leaf->hdr.stale) {
		lfloglow = be16_to_cpu(leaf->hdr.count);
		lfloghigh = -1;
	}
	/*
	 * No stale entries, just insert a space for the new entry.
	 */
	if (!leaf->hdr.stale) {
		lep = &leaf->ents[index];
		if (index < be16_to_cpu(leaf->hdr.count))
			memmove(lep + 1, lep,
				(be16_to_cpu(leaf->hdr.count) - index) * sizeof(*lep));
		lfloglow = index;
		lfloghigh = be16_to_cpu(leaf->hdr.count);
		be16_add_cpu(&leaf->hdr.count, 1);
	}
	/*
	 * There are stale entries.  We'll use one for the new entry.
	 */
	else {
		/*
		 * If we didn't do a compact then we need to figure out
		 * which stale entry will be used.
		 */
		if (compact == 0) {
			/*
			 * Find first stale entry before our insertion point.
			 */
			for (lowstale = index - 1;
			     lowstale >= 0 &&
				be32_to_cpu(leaf->ents[lowstale].address) !=
				XFS_DIR2_NULL_DATAPTR;
			     lowstale--)
				continue;
			/*
			 * Find next stale entry after insertion point.
			 * Stop looking if the answer would be worse than
			 * lowstale already found.
			 */
			for (highstale = index;
			     highstale < be16_to_cpu(leaf->hdr.count) &&
				be32_to_cpu(leaf->ents[highstale].address) !=
				XFS_DIR2_NULL_DATAPTR &&
				(lowstale < 0 ||
				 index - lowstale - 1 >= highstale - index);
			     highstale++)
				continue;
		}
		/*
		 * Using the low stale entry.
		 * Shift entries up toward the stale slot.
		 */
		if (lowstale >= 0 &&
		    (highstale == be16_to_cpu(leaf->hdr.count) ||
		     index - lowstale - 1 < highstale - index)) {
			ASSERT(be32_to_cpu(leaf->ents[lowstale].address) ==
			       XFS_DIR2_NULL_DATAPTR);
			ASSERT(index - lowstale - 1 >= 0);
			if (index - lowstale - 1 > 0)
				memmove(&leaf->ents[lowstale],
					&leaf->ents[lowstale + 1],
					(index - lowstale - 1) * sizeof(*lep));
			lep = &leaf->ents[index - 1];
			lfloglow = MIN(lowstale, lfloglow);
			lfloghigh = MAX(index - 1, lfloghigh);
		}
		/*
		 * Using the high stale entry.
		 * Shift entries down toward the stale slot.
		 */
		else {
			ASSERT(be32_to_cpu(leaf->ents[highstale].address) ==
			       XFS_DIR2_NULL_DATAPTR);
			ASSERT(highstale - index >= 0);
			if (highstale - index > 0)
				memmove(&leaf->ents[index + 1],
					&leaf->ents[index],
					(highstale - index) * sizeof(*lep));
			lep = &leaf->ents[index];
			lfloglow = MIN(index, lfloglow);
			lfloghigh = MAX(highstale, lfloghigh);
		}
		be16_add_cpu(&leaf->hdr.stale, -1);
	}
	/*
	 * Insert the new entry, log everything.
	 */
	lep->hashval = cpu_to_be32(args->hashval);
	lep->address = cpu_to_be32(xfs_dir2_db_off_to_dataptr(mp,
				args->blkno, args->index));
	xfs_dir2_leaf_log_header(tp, bp);
	xfs_dir2_leaf_log_ents(tp, bp, lfloglow, lfloghigh);
	xfs_dir2_leafn_check(dp, bp);
	return 0;
}