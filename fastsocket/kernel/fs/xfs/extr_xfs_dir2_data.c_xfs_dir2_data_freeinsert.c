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
struct TYPE_9__ {int /*<<< orphan*/  length; } ;
typedef  TYPE_2__ xfs_dir2_data_unused_t ;
struct TYPE_8__ {TYPE_4__* bestfree; int /*<<< orphan*/  magic; } ;
struct TYPE_10__ {TYPE_1__ hdr; } ;
typedef  TYPE_3__ xfs_dir2_data_t ;
struct TYPE_11__ {int /*<<< orphan*/  length; int /*<<< orphan*/  offset; } ;
typedef  TYPE_4__ xfs_dir2_data_free_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 scalar_t__ XFS_DIR2_BLOCK_MAGIC ; 
 scalar_t__ XFS_DIR2_DATA_MAGIC ; 
 scalar_t__ be16_to_cpu (int /*<<< orphan*/ ) ; 
 scalar_t__ be32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_to_be16 (int) ; 

xfs_dir2_data_free_t *				/* entry inserted */
xfs_dir2_data_freeinsert(
	xfs_dir2_data_t		*d,		/* data block pointer */
	xfs_dir2_data_unused_t	*dup,		/* unused space */
	int			*loghead)	/* log the data header (out) */
{
	xfs_dir2_data_free_t	*dfp;		/* bestfree table pointer */
	xfs_dir2_data_free_t	new;		/* new bestfree entry */

#ifdef __KERNEL__
	ASSERT(be32_to_cpu(d->hdr.magic) == XFS_DIR2_DATA_MAGIC ||
	       be32_to_cpu(d->hdr.magic) == XFS_DIR2_BLOCK_MAGIC);
#endif
	dfp = d->hdr.bestfree;
	new.length = dup->length;
	new.offset = cpu_to_be16((char *)dup - (char *)d);
	/*
	 * Insert at position 0, 1, or 2; or not at all.
	 */
	if (be16_to_cpu(new.length) > be16_to_cpu(dfp[0].length)) {
		dfp[2] = dfp[1];
		dfp[1] = dfp[0];
		dfp[0] = new;
		*loghead = 1;
		return &dfp[0];
	}
	if (be16_to_cpu(new.length) > be16_to_cpu(dfp[1].length)) {
		dfp[2] = dfp[1];
		dfp[1] = new;
		*loghead = 1;
		return &dfp[1];
	}
	if (be16_to_cpu(new.length) > be16_to_cpu(dfp[2].length)) {
		dfp[2] = new;
		*loghead = 1;
		return &dfp[2];
	}
	return NULL;
}