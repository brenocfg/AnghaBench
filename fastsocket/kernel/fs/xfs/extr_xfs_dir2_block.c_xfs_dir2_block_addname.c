#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_53__   TYPE_9__ ;
typedef  struct TYPE_52__   TYPE_8__ ;
typedef  struct TYPE_51__   TYPE_7__ ;
typedef  struct TYPE_50__   TYPE_6__ ;
typedef  struct TYPE_49__   TYPE_5__ ;
typedef  struct TYPE_48__   TYPE_4__ ;
typedef  struct TYPE_47__   TYPE_3__ ;
typedef  struct TYPE_46__   TYPE_2__ ;
typedef  struct TYPE_45__   TYPE_1__ ;
typedef  struct TYPE_44__   TYPE_11__ ;
typedef  struct TYPE_43__   TYPE_10__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  xfs_trans_t ;
struct TYPE_46__ {int /*<<< orphan*/  m_dirdatablk; } ;
typedef  TYPE_2__ xfs_mount_t ;
struct TYPE_47__ {TYPE_2__* i_mount; } ;
typedef  TYPE_3__ xfs_inode_t ;
struct TYPE_48__ {void* address; void* hashval; } ;
typedef  TYPE_4__ xfs_dir2_leaf_entry_t ;
struct TYPE_49__ {int /*<<< orphan*/  length; int /*<<< orphan*/  freetag; } ;
typedef  TYPE_5__ xfs_dir2_data_unused_t ;
typedef  int /*<<< orphan*/  xfs_dir2_data_t ;
struct TYPE_50__ {int /*<<< orphan*/  offset; int /*<<< orphan*/  length; } ;
typedef  TYPE_6__ xfs_dir2_data_free_t ;
struct TYPE_51__ {int /*<<< orphan*/  name; int /*<<< orphan*/  namelen; int /*<<< orphan*/  inumber; } ;
typedef  TYPE_7__ xfs_dir2_data_entry_t ;
typedef  int /*<<< orphan*/  xfs_dir2_data_aoff_t ;
struct TYPE_52__ {void* stale; void* count; } ;
typedef  TYPE_8__ xfs_dir2_block_tail_t ;
struct TYPE_45__ {TYPE_6__* bestfree; void* magic; } ;
struct TYPE_53__ {TYPE_1__ hdr; } ;
typedef  TYPE_9__ xfs_dir2_block_t ;
typedef  int xfs_dahash_t ;
struct TYPE_43__ {TYPE_9__* data; } ;
typedef  TYPE_10__ xfs_dabuf_t ;
struct TYPE_44__ {int op_flags; scalar_t__ total; int hashval; int /*<<< orphan*/  namelen; int /*<<< orphan*/  name; int /*<<< orphan*/  inumber; int /*<<< orphan*/ * trans; TYPE_3__* dp; } ;
typedef  TYPE_11__ xfs_da_args_t ;
typedef  int uint ;
typedef  int /*<<< orphan*/  __be16 ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int /*<<< orphan*/  EFSCORRUPTED ; 
 int /*<<< orphan*/  ENOSPC ; 
 int MAX (int,int) ; 
 int MIN (int,int) ; 
 int /*<<< orphan*/  XFS_CORRUPTION_ERROR (char*,int /*<<< orphan*/ ,TYPE_2__*,TYPE_9__*) ; 
 int /*<<< orphan*/  XFS_DATA_FORK ; 
 int XFS_DA_OP_JUSTCHECK ; 
 int XFS_DIR2_BLOCK_MAGIC ; 
 int XFS_DIR2_DATA_FREE_TAG ; 
 int XFS_DIR2_NULL_DATAPTR ; 
 int /*<<< orphan*/  XFS_ERRLEVEL_LOW ; 
 int XFS_ERROR (int /*<<< orphan*/ ) ; 
 int be16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  be32_add_cpu (void**,int) ; 
 int be32_to_cpu (void*) ; 
 int /*<<< orphan*/  cpu_to_be16 (int) ; 
 void* cpu_to_be32 (int) ; 
 int /*<<< orphan*/  cpu_to_be64 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memmove (TYPE_4__*,TYPE_4__*,int) ; 
 int /*<<< orphan*/  trace_xfs_dir2_block_addname (TYPE_11__*) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  xfs_da_brelse (int /*<<< orphan*/ *,TYPE_10__*) ; 
 int /*<<< orphan*/  xfs_da_buf_done (TYPE_10__*) ; 
 int xfs_da_read_buf (int /*<<< orphan*/ *,TYPE_3__*,int /*<<< orphan*/ ,int,TYPE_10__**,int /*<<< orphan*/ ) ; 
 TYPE_4__* xfs_dir2_block_leaf_p (TYPE_8__*) ; 
 int /*<<< orphan*/  xfs_dir2_block_log_leaf (int /*<<< orphan*/ *,TYPE_10__*,int,int) ; 
 int /*<<< orphan*/  xfs_dir2_block_log_tail (int /*<<< orphan*/ *,TYPE_10__*) ; 
 TYPE_8__* xfs_dir2_block_tail_p (TYPE_2__*,TYPE_9__*) ; 
 int xfs_dir2_block_to_leaf (TYPE_11__*,TYPE_10__*) ; 
 int xfs_dir2_byte_to_dataptr (TYPE_2__*,int) ; 
 int /*<<< orphan*/  xfs_dir2_data_check (TYPE_3__*,TYPE_10__*) ; 
 int /*<<< orphan*/ * xfs_dir2_data_entry_tag_p (TYPE_7__*) ; 
 int xfs_dir2_data_entsize (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xfs_dir2_data_freescan (TYPE_2__*,int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  xfs_dir2_data_log_entry (int /*<<< orphan*/ *,TYPE_10__*,TYPE_7__*) ; 
 int /*<<< orphan*/  xfs_dir2_data_log_header (int /*<<< orphan*/ *,TYPE_10__*) ; 
 int /*<<< orphan*/  xfs_dir2_data_make_free (int /*<<< orphan*/ *,TYPE_10__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int*) ; 
 int /*<<< orphan*/  xfs_dir2_data_use_free (int /*<<< orphan*/ *,TYPE_10__*,TYPE_5__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int*) ; 
 int xfs_dir2_leaf_addname (TYPE_11__*) ; 

int						/* error */
xfs_dir2_block_addname(
	xfs_da_args_t		*args)		/* directory op arguments */
{
	xfs_dir2_data_free_t	*bf;		/* bestfree table in block */
	xfs_dir2_block_t	*block;		/* directory block structure */
	xfs_dir2_leaf_entry_t	*blp;		/* block leaf entries */
	xfs_dabuf_t		*bp;		/* buffer for block */
	xfs_dir2_block_tail_t	*btp;		/* block tail */
	int			compact;	/* need to compact leaf ents */
	xfs_dir2_data_entry_t	*dep;		/* block data entry */
	xfs_inode_t		*dp;		/* directory inode */
	xfs_dir2_data_unused_t	*dup;		/* block unused entry */
	int			error;		/* error return value */
	xfs_dir2_data_unused_t	*enddup=NULL;	/* unused at end of data */
	xfs_dahash_t		hash;		/* hash value of found entry */
	int			high;		/* high index for binary srch */
	int			highstale;	/* high stale index */
	int			lfloghigh=0;	/* last final leaf to log */
	int			lfloglow=0;	/* first final leaf to log */
	int			len;		/* length of the new entry */
	int			low;		/* low index for binary srch */
	int			lowstale;	/* low stale index */
	int			mid=0;		/* midpoint for binary srch */
	xfs_mount_t		*mp;		/* filesystem mount point */
	int			needlog;	/* need to log header */
	int			needscan;	/* need to rescan freespace */
	__be16			*tagp;		/* pointer to tag value */
	xfs_trans_t		*tp;		/* transaction structure */

	trace_xfs_dir2_block_addname(args);

	dp = args->dp;
	tp = args->trans;
	mp = dp->i_mount;
	/*
	 * Read the (one and only) directory block into dabuf bp.
	 */
	if ((error =
	    xfs_da_read_buf(tp, dp, mp->m_dirdatablk, -1, &bp, XFS_DATA_FORK))) {
		return error;
	}
	ASSERT(bp != NULL);
	block = bp->data;
	/*
	 * Check the magic number, corrupted if wrong.
	 */
	if (unlikely(be32_to_cpu(block->hdr.magic) != XFS_DIR2_BLOCK_MAGIC)) {
		XFS_CORRUPTION_ERROR("xfs_dir2_block_addname",
				     XFS_ERRLEVEL_LOW, mp, block);
		xfs_da_brelse(tp, bp);
		return XFS_ERROR(EFSCORRUPTED);
	}
	len = xfs_dir2_data_entsize(args->namelen);
	/*
	 * Set up pointers to parts of the block.
	 */
	bf = block->hdr.bestfree;
	btp = xfs_dir2_block_tail_p(mp, block);
	blp = xfs_dir2_block_leaf_p(btp);
	/*
	 * No stale entries?  Need space for entry and new leaf.
	 */
	if (!btp->stale) {
		/*
		 * Tag just before the first leaf entry.
		 */
		tagp = (__be16 *)blp - 1;
		/*
		 * Data object just before the first leaf entry.
		 */
		enddup = (xfs_dir2_data_unused_t *)((char *)block + be16_to_cpu(*tagp));
		/*
		 * If it's not free then can't do this add without cleaning up:
		 * the space before the first leaf entry needs to be free so it
		 * can be expanded to hold the pointer to the new entry.
		 */
		if (be16_to_cpu(enddup->freetag) != XFS_DIR2_DATA_FREE_TAG)
			dup = enddup = NULL;
		/*
		 * Check out the biggest freespace and see if it's the same one.
		 */
		else {
			dup = (xfs_dir2_data_unused_t *)
			      ((char *)block + be16_to_cpu(bf[0].offset));
			if (dup == enddup) {
				/*
				 * It is the biggest freespace, is it too small
				 * to hold the new leaf too?
				 */
				if (be16_to_cpu(dup->length) < len + (uint)sizeof(*blp)) {
					/*
					 * Yes, we use the second-largest
					 * entry instead if it works.
					 */
					if (be16_to_cpu(bf[1].length) >= len)
						dup = (xfs_dir2_data_unused_t *)
						      ((char *)block +
						       be16_to_cpu(bf[1].offset));
					else
						dup = NULL;
				}
			} else {
				/*
				 * Not the same free entry,
				 * just check its length.
				 */
				if (be16_to_cpu(dup->length) < len) {
					dup = NULL;
				}
			}
		}
		compact = 0;
	}
	/*
	 * If there are stale entries we'll use one for the leaf.
	 * Is the biggest entry enough to avoid compaction?
	 */
	else if (be16_to_cpu(bf[0].length) >= len) {
		dup = (xfs_dir2_data_unused_t *)
		      ((char *)block + be16_to_cpu(bf[0].offset));
		compact = 0;
	}
	/*
	 * Will need to compact to make this work.
	 */
	else {
		/*
		 * Tag just before the first leaf entry.
		 */
		tagp = (__be16 *)blp - 1;
		/*
		 * Data object just before the first leaf entry.
		 */
		dup = (xfs_dir2_data_unused_t *)((char *)block + be16_to_cpu(*tagp));
		/*
		 * If it's not free then the data will go where the
		 * leaf data starts now, if it works at all.
		 */
		if (be16_to_cpu(dup->freetag) == XFS_DIR2_DATA_FREE_TAG) {
			if (be16_to_cpu(dup->length) + (be32_to_cpu(btp->stale) - 1) *
			    (uint)sizeof(*blp) < len)
				dup = NULL;
		} else if ((be32_to_cpu(btp->stale) - 1) * (uint)sizeof(*blp) < len)
			dup = NULL;
		else
			dup = (xfs_dir2_data_unused_t *)blp;
		compact = 1;
	}
	/*
	 * If this isn't a real add, we're done with the buffer.
	 */
	if (args->op_flags & XFS_DA_OP_JUSTCHECK)
		xfs_da_brelse(tp, bp);
	/*
	 * If we don't have space for the new entry & leaf ...
	 */
	if (!dup) {
		/*
		 * Not trying to actually do anything, or don't have
		 * a space reservation: return no-space.
		 */
		if ((args->op_flags & XFS_DA_OP_JUSTCHECK) || args->total == 0)
			return XFS_ERROR(ENOSPC);
		/*
		 * Convert to the next larger format.
		 * Then add the new entry in that format.
		 */
		error = xfs_dir2_block_to_leaf(args, bp);
		xfs_da_buf_done(bp);
		if (error)
			return error;
		return xfs_dir2_leaf_addname(args);
	}
	/*
	 * Just checking, and it would work, so say so.
	 */
	if (args->op_flags & XFS_DA_OP_JUSTCHECK)
		return 0;
	needlog = needscan = 0;
	/*
	 * If need to compact the leaf entries, do it now.
	 * Leave the highest-numbered stale entry stale.
	 * XXX should be the one closest to mid but mid is not yet computed.
	 */
	if (compact) {
		int	fromidx;		/* source leaf index */
		int	toidx;			/* target leaf index */

		for (fromidx = toidx = be32_to_cpu(btp->count) - 1,
			highstale = lfloghigh = -1;
		     fromidx >= 0;
		     fromidx--) {
			if (be32_to_cpu(blp[fromidx].address) == XFS_DIR2_NULL_DATAPTR) {
				if (highstale == -1)
					highstale = toidx;
				else {
					if (lfloghigh == -1)
						lfloghigh = toidx;
					continue;
				}
			}
			if (fromidx < toidx)
				blp[toidx] = blp[fromidx];
			toidx--;
		}
		lfloglow = toidx + 1 - (be32_to_cpu(btp->stale) - 1);
		lfloghigh -= be32_to_cpu(btp->stale) - 1;
		be32_add_cpu(&btp->count, -(be32_to_cpu(btp->stale) - 1));
		xfs_dir2_data_make_free(tp, bp,
			(xfs_dir2_data_aoff_t)((char *)blp - (char *)block),
			(xfs_dir2_data_aoff_t)((be32_to_cpu(btp->stale) - 1) * sizeof(*blp)),
			&needlog, &needscan);
		blp += be32_to_cpu(btp->stale) - 1;
		btp->stale = cpu_to_be32(1);
		/*
		 * If we now need to rebuild the bestfree map, do so.
		 * This needs to happen before the next call to use_free.
		 */
		if (needscan) {
			xfs_dir2_data_freescan(mp, (xfs_dir2_data_t *)block, &needlog);
			needscan = 0;
		}
	}
	/*
	 * Set leaf logging boundaries to impossible state.
	 * For the no-stale case they're set explicitly.
	 */
	else if (btp->stale) {
		lfloglow = be32_to_cpu(btp->count);
		lfloghigh = -1;
	}
	/*
	 * Find the slot that's first lower than our hash value, -1 if none.
	 */
	for (low = 0, high = be32_to_cpu(btp->count) - 1; low <= high; ) {
		mid = (low + high) >> 1;
		if ((hash = be32_to_cpu(blp[mid].hashval)) == args->hashval)
			break;
		if (hash < args->hashval)
			low = mid + 1;
		else
			high = mid - 1;
	}
	while (mid >= 0 && be32_to_cpu(blp[mid].hashval) >= args->hashval) {
		mid--;
	}
	/*
	 * No stale entries, will use enddup space to hold new leaf.
	 */
	if (!btp->stale) {
		/*
		 * Mark the space needed for the new leaf entry, now in use.
		 */
		xfs_dir2_data_use_free(tp, bp, enddup,
			(xfs_dir2_data_aoff_t)
			((char *)enddup - (char *)block + be16_to_cpu(enddup->length) -
			 sizeof(*blp)),
			(xfs_dir2_data_aoff_t)sizeof(*blp),
			&needlog, &needscan);
		/*
		 * Update the tail (entry count).
		 */
		be32_add_cpu(&btp->count, 1);
		/*
		 * If we now need to rebuild the bestfree map, do so.
		 * This needs to happen before the next call to use_free.
		 */
		if (needscan) {
			xfs_dir2_data_freescan(mp, (xfs_dir2_data_t *)block,
				&needlog);
			needscan = 0;
		}
		/*
		 * Adjust pointer to the first leaf entry, we're about to move
		 * the table up one to open up space for the new leaf entry.
		 * Then adjust our index to match.
		 */
		blp--;
		mid++;
		if (mid)
			memmove(blp, &blp[1], mid * sizeof(*blp));
		lfloglow = 0;
		lfloghigh = mid;
	}
	/*
	 * Use a stale leaf for our new entry.
	 */
	else {
		for (lowstale = mid;
		     lowstale >= 0 &&
			be32_to_cpu(blp[lowstale].address) != XFS_DIR2_NULL_DATAPTR;
		     lowstale--)
			continue;
		for (highstale = mid + 1;
		     highstale < be32_to_cpu(btp->count) &&
			be32_to_cpu(blp[highstale].address) != XFS_DIR2_NULL_DATAPTR &&
			(lowstale < 0 || mid - lowstale > highstale - mid);
		     highstale++)
			continue;
		/*
		 * Move entries toward the low-numbered stale entry.
		 */
		if (lowstale >= 0 &&
		    (highstale == be32_to_cpu(btp->count) ||
		     mid - lowstale <= highstale - mid)) {
			if (mid - lowstale)
				memmove(&blp[lowstale], &blp[lowstale + 1],
					(mid - lowstale) * sizeof(*blp));
			lfloglow = MIN(lowstale, lfloglow);
			lfloghigh = MAX(mid, lfloghigh);
		}
		/*
		 * Move entries toward the high-numbered stale entry.
		 */
		else {
			ASSERT(highstale < be32_to_cpu(btp->count));
			mid++;
			if (highstale - mid)
				memmove(&blp[mid + 1], &blp[mid],
					(highstale - mid) * sizeof(*blp));
			lfloglow = MIN(mid, lfloglow);
			lfloghigh = MAX(highstale, lfloghigh);
		}
		be32_add_cpu(&btp->stale, -1);
	}
	/*
	 * Point to the new data entry.
	 */
	dep = (xfs_dir2_data_entry_t *)dup;
	/*
	 * Fill in the leaf entry.
	 */
	blp[mid].hashval = cpu_to_be32(args->hashval);
	blp[mid].address = cpu_to_be32(xfs_dir2_byte_to_dataptr(mp,
				(char *)dep - (char *)block));
	xfs_dir2_block_log_leaf(tp, bp, lfloglow, lfloghigh);
	/*
	 * Mark space for the data entry used.
	 */
	xfs_dir2_data_use_free(tp, bp, dup,
		(xfs_dir2_data_aoff_t)((char *)dup - (char *)block),
		(xfs_dir2_data_aoff_t)len, &needlog, &needscan);
	/*
	 * Create the new data entry.
	 */
	dep->inumber = cpu_to_be64(args->inumber);
	dep->namelen = args->namelen;
	memcpy(dep->name, args->name, args->namelen);
	tagp = xfs_dir2_data_entry_tag_p(dep);
	*tagp = cpu_to_be16((char *)dep - (char *)block);
	/*
	 * Clean up the bestfree array and log the header, tail, and entry.
	 */
	if (needscan)
		xfs_dir2_data_freescan(mp, (xfs_dir2_data_t *)block, &needlog);
	if (needlog)
		xfs_dir2_data_log_header(tp, bp);
	xfs_dir2_block_log_tail(tp, bp);
	xfs_dir2_data_log_entry(tp, bp, dep);
	xfs_dir2_data_check(dp, bp);
	xfs_da_buf_done(bp);
	return 0;
}