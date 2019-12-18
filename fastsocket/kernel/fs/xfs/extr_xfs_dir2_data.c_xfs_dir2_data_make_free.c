#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_29__   TYPE_7__ ;
typedef  struct TYPE_28__   TYPE_6__ ;
typedef  struct TYPE_27__   TYPE_5__ ;
typedef  struct TYPE_26__   TYPE_4__ ;
typedef  struct TYPE_25__   TYPE_3__ ;
typedef  struct TYPE_24__   TYPE_2__ ;
typedef  struct TYPE_23__   TYPE_1__ ;

/* Type definitions */
struct TYPE_24__ {TYPE_3__* t_mountp; } ;
typedef  TYPE_2__ xfs_trans_t ;
struct TYPE_25__ {int m_dirblksize; } ;
typedef  TYPE_3__ xfs_mount_t ;
struct TYPE_26__ {scalar_t__ freetag; scalar_t__ length; } ;
typedef  TYPE_4__ xfs_dir2_data_unused_t ;
struct TYPE_23__ {TYPE_6__* bestfree; int /*<<< orphan*/  magic; } ;
struct TYPE_27__ {TYPE_1__ hdr; } ;
typedef  TYPE_5__ xfs_dir2_data_t ;
struct TYPE_28__ {scalar_t__ length; } ;
typedef  TYPE_6__ xfs_dir2_data_free_t ;
typedef  int xfs_dir2_data_aoff_t ;
typedef  int /*<<< orphan*/  xfs_dir2_block_tail_t ;
typedef  int /*<<< orphan*/  xfs_dir2_block_t ;
struct TYPE_29__ {TYPE_5__* data; } ;
typedef  TYPE_7__ xfs_dabuf_t ;
typedef  scalar_t__ __be16 ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 scalar_t__ XFS_DIR2_BLOCK_MAGIC ; 
 int XFS_DIR2_DATA_FREE_TAG ; 
 scalar_t__ XFS_DIR2_DATA_MAGIC ; 
 int /*<<< orphan*/  be16_add_cpu (scalar_t__*,int) ; 
 int be16_to_cpu (scalar_t__) ; 
 scalar_t__ be32_to_cpu (int /*<<< orphan*/ ) ; 
 void* cpu_to_be16 (int) ; 
 scalar_t__ xfs_dir2_block_leaf_p (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * xfs_dir2_block_tail_p (TYPE_3__*,int /*<<< orphan*/ *) ; 
 TYPE_6__* xfs_dir2_data_freefind (TYPE_5__*,TYPE_4__*) ; 
 TYPE_6__* xfs_dir2_data_freeinsert (TYPE_5__*,TYPE_4__*,int*) ; 
 int /*<<< orphan*/  xfs_dir2_data_freeremove (TYPE_5__*,TYPE_6__*,int*) ; 
 int /*<<< orphan*/  xfs_dir2_data_log_unused (TYPE_2__*,TYPE_7__*,TYPE_4__*) ; 
 void** xfs_dir2_data_unused_tag_p (TYPE_4__*) ; 

void
xfs_dir2_data_make_free(
	xfs_trans_t		*tp,		/* transaction pointer */
	xfs_dabuf_t		*bp,		/* block buffer */
	xfs_dir2_data_aoff_t	offset,		/* starting byte offset */
	xfs_dir2_data_aoff_t	len,		/* length in bytes */
	int			*needlogp,	/* out: log header */
	int			*needscanp)	/* out: regen bestfree */
{
	xfs_dir2_data_t		*d;		/* data block pointer */
	xfs_dir2_data_free_t	*dfp;		/* bestfree pointer */
	char			*endptr;	/* end of data area */
	xfs_mount_t		*mp;		/* filesystem mount point */
	int			needscan;	/* need to regen bestfree */
	xfs_dir2_data_unused_t	*newdup;	/* new unused entry */
	xfs_dir2_data_unused_t	*postdup;	/* unused entry after us */
	xfs_dir2_data_unused_t	*prevdup;	/* unused entry before us */

	mp = tp->t_mountp;
	d = bp->data;
	/*
	 * Figure out where the end of the data area is.
	 */
	if (be32_to_cpu(d->hdr.magic) == XFS_DIR2_DATA_MAGIC)
		endptr = (char *)d + mp->m_dirblksize;
	else {
		xfs_dir2_block_tail_t	*btp;	/* block tail */

		ASSERT(be32_to_cpu(d->hdr.magic) == XFS_DIR2_BLOCK_MAGIC);
		btp = xfs_dir2_block_tail_p(mp, (xfs_dir2_block_t *)d);
		endptr = (char *)xfs_dir2_block_leaf_p(btp);
	}
	/*
	 * If this isn't the start of the block, then back up to
	 * the previous entry and see if it's free.
	 */
	if (offset > sizeof(d->hdr)) {
		__be16			*tagp;	/* tag just before us */

		tagp = (__be16 *)((char *)d + offset) - 1;
		prevdup = (xfs_dir2_data_unused_t *)((char *)d + be16_to_cpu(*tagp));
		if (be16_to_cpu(prevdup->freetag) != XFS_DIR2_DATA_FREE_TAG)
			prevdup = NULL;
	} else
		prevdup = NULL;
	/*
	 * If this isn't the end of the block, see if the entry after
	 * us is free.
	 */
	if ((char *)d + offset + len < endptr) {
		postdup =
			(xfs_dir2_data_unused_t *)((char *)d + offset + len);
		if (be16_to_cpu(postdup->freetag) != XFS_DIR2_DATA_FREE_TAG)
			postdup = NULL;
	} else
		postdup = NULL;
	ASSERT(*needscanp == 0);
	needscan = 0;
	/*
	 * Previous and following entries are both free,
	 * merge everything into a single free entry.
	 */
	if (prevdup && postdup) {
		xfs_dir2_data_free_t	*dfp2;	/* another bestfree pointer */

		/*
		 * See if prevdup and/or postdup are in bestfree table.
		 */
		dfp = xfs_dir2_data_freefind(d, prevdup);
		dfp2 = xfs_dir2_data_freefind(d, postdup);
		/*
		 * We need a rescan unless there are exactly 2 free entries
		 * namely our two.  Then we know what's happening, otherwise
		 * since the third bestfree is there, there might be more
		 * entries.
		 */
		needscan = (d->hdr.bestfree[2].length != 0);
		/*
		 * Fix up the new big freespace.
		 */
		be16_add_cpu(&prevdup->length, len + be16_to_cpu(postdup->length));
		*xfs_dir2_data_unused_tag_p(prevdup) =
			cpu_to_be16((char *)prevdup - (char *)d);
		xfs_dir2_data_log_unused(tp, bp, prevdup);
		if (!needscan) {
			/*
			 * Has to be the case that entries 0 and 1 are
			 * dfp and dfp2 (don't know which is which), and
			 * entry 2 is empty.
			 * Remove entry 1 first then entry 0.
			 */
			ASSERT(dfp && dfp2);
			if (dfp == &d->hdr.bestfree[1]) {
				dfp = &d->hdr.bestfree[0];
				ASSERT(dfp2 == dfp);
				dfp2 = &d->hdr.bestfree[1];
			}
			xfs_dir2_data_freeremove(d, dfp2, needlogp);
			xfs_dir2_data_freeremove(d, dfp, needlogp);
			/*
			 * Now insert the new entry.
			 */
			dfp = xfs_dir2_data_freeinsert(d, prevdup, needlogp);
			ASSERT(dfp == &d->hdr.bestfree[0]);
			ASSERT(dfp->length == prevdup->length);
			ASSERT(!dfp[1].length);
			ASSERT(!dfp[2].length);
		}
	}
	/*
	 * The entry before us is free, merge with it.
	 */
	else if (prevdup) {
		dfp = xfs_dir2_data_freefind(d, prevdup);
		be16_add_cpu(&prevdup->length, len);
		*xfs_dir2_data_unused_tag_p(prevdup) =
			cpu_to_be16((char *)prevdup - (char *)d);
		xfs_dir2_data_log_unused(tp, bp, prevdup);
		/*
		 * If the previous entry was in the table, the new entry
		 * is longer, so it will be in the table too.  Remove
		 * the old one and add the new one.
		 */
		if (dfp) {
			xfs_dir2_data_freeremove(d, dfp, needlogp);
			(void)xfs_dir2_data_freeinsert(d, prevdup, needlogp);
		}
		/*
		 * Otherwise we need a scan if the new entry is big enough.
		 */
		else {
			needscan = be16_to_cpu(prevdup->length) >
				   be16_to_cpu(d->hdr.bestfree[2].length);
		}
	}
	/*
	 * The following entry is free, merge with it.
	 */
	else if (postdup) {
		dfp = xfs_dir2_data_freefind(d, postdup);
		newdup = (xfs_dir2_data_unused_t *)((char *)d + offset);
		newdup->freetag = cpu_to_be16(XFS_DIR2_DATA_FREE_TAG);
		newdup->length = cpu_to_be16(len + be16_to_cpu(postdup->length));
		*xfs_dir2_data_unused_tag_p(newdup) =
			cpu_to_be16((char *)newdup - (char *)d);
		xfs_dir2_data_log_unused(tp, bp, newdup);
		/*
		 * If the following entry was in the table, the new entry
		 * is longer, so it will be in the table too.  Remove
		 * the old one and add the new one.
		 */
		if (dfp) {
			xfs_dir2_data_freeremove(d, dfp, needlogp);
			(void)xfs_dir2_data_freeinsert(d, newdup, needlogp);
		}
		/*
		 * Otherwise we need a scan if the new entry is big enough.
		 */
		else {
			needscan = be16_to_cpu(newdup->length) >
				   be16_to_cpu(d->hdr.bestfree[2].length);
		}
	}
	/*
	 * Neither neighbor is free.  Make a new entry.
	 */
	else {
		newdup = (xfs_dir2_data_unused_t *)((char *)d + offset);
		newdup->freetag = cpu_to_be16(XFS_DIR2_DATA_FREE_TAG);
		newdup->length = cpu_to_be16(len);
		*xfs_dir2_data_unused_tag_p(newdup) =
			cpu_to_be16((char *)newdup - (char *)d);
		xfs_dir2_data_log_unused(tp, bp, newdup);
		(void)xfs_dir2_data_freeinsert(d, newdup, needlogp);
	}
	*needscanp = needscan;
}