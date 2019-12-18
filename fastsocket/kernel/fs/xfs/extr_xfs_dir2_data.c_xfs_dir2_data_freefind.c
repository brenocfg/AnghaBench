#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {scalar_t__ length; } ;
typedef  TYPE_2__ xfs_dir2_data_unused_t ;
struct TYPE_8__ {TYPE_4__* bestfree; int /*<<< orphan*/  magic; } ;
struct TYPE_10__ {TYPE_1__ hdr; } ;
typedef  TYPE_3__ xfs_dir2_data_t ;
struct TYPE_11__ {scalar_t__ offset; scalar_t__ length; } ;
typedef  TYPE_4__ xfs_dir2_data_free_t ;
typedef  scalar_t__ xfs_dir2_data_aoff_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 scalar_t__ XFS_DIR2_BLOCK_MAGIC ; 
 size_t XFS_DIR2_DATA_FD_COUNT ; 
 scalar_t__ XFS_DIR2_DATA_MAGIC ; 
 scalar_t__ be16_to_cpu (scalar_t__) ; 
 scalar_t__ be32_to_cpu (int /*<<< orphan*/ ) ; 

xfs_dir2_data_free_t *
xfs_dir2_data_freefind(
	xfs_dir2_data_t		*d,		/* data block */
	xfs_dir2_data_unused_t	*dup)		/* data unused entry */
{
	xfs_dir2_data_free_t	*dfp;		/* bestfree entry */
	xfs_dir2_data_aoff_t	off;		/* offset value needed */
#if defined(DEBUG) && defined(__KERNEL__)
	int			matched;	/* matched the value */
	int			seenzero;	/* saw a 0 bestfree entry */
#endif

	off = (xfs_dir2_data_aoff_t)((char *)dup - (char *)d);
#if defined(DEBUG) && defined(__KERNEL__)
	/*
	 * Validate some consistency in the bestfree table.
	 * Check order, non-overlapping entries, and if we find the
	 * one we're looking for it has to be exact.
	 */
	ASSERT(be32_to_cpu(d->hdr.magic) == XFS_DIR2_DATA_MAGIC ||
	       be32_to_cpu(d->hdr.magic) == XFS_DIR2_BLOCK_MAGIC);
	for (dfp = &d->hdr.bestfree[0], seenzero = matched = 0;
	     dfp < &d->hdr.bestfree[XFS_DIR2_DATA_FD_COUNT];
	     dfp++) {
		if (!dfp->offset) {
			ASSERT(!dfp->length);
			seenzero = 1;
			continue;
		}
		ASSERT(seenzero == 0);
		if (be16_to_cpu(dfp->offset) == off) {
			matched = 1;
			ASSERT(dfp->length == dup->length);
		} else if (off < be16_to_cpu(dfp->offset))
			ASSERT(off + be16_to_cpu(dup->length) <= be16_to_cpu(dfp->offset));
		else
			ASSERT(be16_to_cpu(dfp->offset) + be16_to_cpu(dfp->length) <= off);
		ASSERT(matched || be16_to_cpu(dfp->length) >= be16_to_cpu(dup->length));
		if (dfp > &d->hdr.bestfree[0])
			ASSERT(be16_to_cpu(dfp[-1].length) >= be16_to_cpu(dfp[0].length));
	}
#endif
	/*
	 * If this is smaller than the smallest bestfree entry,
	 * it can't be there since they're sorted.
	 */
	if (be16_to_cpu(dup->length) <
	    be16_to_cpu(d->hdr.bestfree[XFS_DIR2_DATA_FD_COUNT - 1].length))
		return NULL;
	/*
	 * Look at the three bestfree entries for our guy.
	 */
	for (dfp = &d->hdr.bestfree[0];
	     dfp < &d->hdr.bestfree[XFS_DIR2_DATA_FD_COUNT];
	     dfp++) {
		if (!dfp->offset)
			return NULL;
		if (be16_to_cpu(dfp->offset) == off)
			return dfp;
	}
	/*
	 * Didn't find it.  This only happens if there are duplicate lengths.
	 */
	return NULL;
}