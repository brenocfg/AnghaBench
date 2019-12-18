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
struct TYPE_19__ {TYPE_5__* data; } ;
typedef  TYPE_3__ xfs_dabuf_t ;
struct TYPE_20__ {scalar_t__ index; int /*<<< orphan*/  dp; int /*<<< orphan*/  trans; int /*<<< orphan*/  blkno; } ;
typedef  TYPE_4__ xfs_da_args_t ;
struct TYPE_17__ {int /*<<< orphan*/  magic; } ;
struct TYPE_18__ {int /*<<< orphan*/  count; TYPE_1__ info; } ;
struct TYPE_21__ {TYPE_6__* entries; TYPE_2__ hdr; } ;
typedef  TYPE_5__ xfs_attr_leafblock_t ;
struct TYPE_22__ {int flags; scalar_t__ valuelen; scalar_t__ valueblk; } ;
typedef  TYPE_6__ xfs_attr_leaf_name_remote_t ;
typedef  TYPE_6__ xfs_attr_leaf_entry_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int /*<<< orphan*/  XFS_ATTR_FORK ; 
 int XFS_ATTR_INCOMPLETE ; 
 scalar_t__ XFS_ATTR_LEAF_MAGIC ; 
 int XFS_ATTR_LOCAL ; 
 int /*<<< orphan*/  XFS_DA_LOGRANGE (TYPE_5__*,TYPE_6__*,int) ; 
 scalar_t__ be16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trace_xfs_attr_leaf_setflag (TYPE_4__*) ; 
 TYPE_6__* xfs_attr_leaf_name_remote (TYPE_5__*,size_t) ; 
 int /*<<< orphan*/  xfs_da_buf_done (TYPE_3__*) ; 
 int /*<<< orphan*/  xfs_da_log_buf (int /*<<< orphan*/ ,TYPE_3__*,int /*<<< orphan*/ ) ; 
 int xfs_da_read_buf (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,TYPE_3__**,int /*<<< orphan*/ ) ; 
 int xfs_trans_roll (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

int
xfs_attr_leaf_setflag(xfs_da_args_t *args)
{
	xfs_attr_leafblock_t *leaf;
	xfs_attr_leaf_entry_t *entry;
	xfs_attr_leaf_name_remote_t *name_rmt;
	xfs_dabuf_t *bp;
	int error;

	trace_xfs_attr_leaf_setflag(args);

	/*
	 * Set up the operation.
	 */
	error = xfs_da_read_buf(args->trans, args->dp, args->blkno, -1, &bp,
					     XFS_ATTR_FORK);
	if (error) {
		return(error);
	}
	ASSERT(bp != NULL);

	leaf = bp->data;
	ASSERT(be16_to_cpu(leaf->hdr.info.magic) == XFS_ATTR_LEAF_MAGIC);
	ASSERT(args->index < be16_to_cpu(leaf->hdr.count));
	ASSERT(args->index >= 0);
	entry = &leaf->entries[ args->index ];

	ASSERT((entry->flags & XFS_ATTR_INCOMPLETE) == 0);
	entry->flags |= XFS_ATTR_INCOMPLETE;
	xfs_da_log_buf(args->trans, bp,
			XFS_DA_LOGRANGE(leaf, entry, sizeof(*entry)));
	if ((entry->flags & XFS_ATTR_LOCAL) == 0) {
		name_rmt = xfs_attr_leaf_name_remote(leaf, args->index);
		name_rmt->valueblk = 0;
		name_rmt->valuelen = 0;
		xfs_da_log_buf(args->trans, bp,
			 XFS_DA_LOGRANGE(leaf, name_rmt, sizeof(*name_rmt)));
	}
	xfs_da_buf_done(bp);

	/*
	 * Commit the flag value change and start the next trans in series.
	 */
	return xfs_trans_roll(&args->trans, args->dp);
}