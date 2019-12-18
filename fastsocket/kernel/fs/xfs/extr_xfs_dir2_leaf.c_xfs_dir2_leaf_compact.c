#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {scalar_t__ stale; scalar_t__ count; } ;
struct TYPE_12__ {TYPE_2__ hdr; TYPE_1__* ents; } ;
typedef  TYPE_3__ xfs_dir2_leaf_t ;
struct TYPE_13__ {TYPE_3__* data; } ;
typedef  TYPE_4__ xfs_dabuf_t ;
struct TYPE_14__ {int /*<<< orphan*/  trans; } ;
typedef  TYPE_5__ xfs_da_args_t ;
struct TYPE_10__ {int /*<<< orphan*/  address; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 scalar_t__ XFS_DIR2_NULL_DATAPTR ; 
 int /*<<< orphan*/  be16_add_cpu (scalar_t__*,int) ; 
 int be16_to_cpu (scalar_t__) ; 
 scalar_t__ be32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xfs_dir2_leaf_log_ents (int /*<<< orphan*/ ,TYPE_4__*,int,int) ; 
 int /*<<< orphan*/  xfs_dir2_leaf_log_header (int /*<<< orphan*/ ,TYPE_4__*) ; 

void
xfs_dir2_leaf_compact(
	xfs_da_args_t	*args,		/* operation arguments */
	xfs_dabuf_t	*bp)		/* leaf buffer */
{
	int		from;		/* source leaf index */
	xfs_dir2_leaf_t	*leaf;		/* leaf structure */
	int		loglow;		/* first leaf entry to log */
	int		to;		/* target leaf index */

	leaf = bp->data;
	if (!leaf->hdr.stale) {
		return;
	}
	/*
	 * Compress out the stale entries in place.
	 */
	for (from = to = 0, loglow = -1; from < be16_to_cpu(leaf->hdr.count); from++) {
		if (be32_to_cpu(leaf->ents[from].address) == XFS_DIR2_NULL_DATAPTR)
			continue;
		/*
		 * Only actually copy the entries that are different.
		 */
		if (from > to) {
			if (loglow == -1)
				loglow = to;
			leaf->ents[to] = leaf->ents[from];
		}
		to++;
	}
	/*
	 * Update and log the header, log the leaf entries.
	 */
	ASSERT(be16_to_cpu(leaf->hdr.stale) == from - to);
	be16_add_cpu(&leaf->hdr.count, -(be16_to_cpu(leaf->hdr.stale)));
	leaf->hdr.stale = 0;
	xfs_dir2_leaf_log_header(args->trans, bp);
	if (loglow != -1)
		xfs_dir2_leaf_log_ents(args->trans, bp, loglow, to - 1);
}