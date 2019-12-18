#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_26__   TYPE_7__ ;
typedef  struct TYPE_25__   TYPE_6__ ;
typedef  struct TYPE_24__   TYPE_5__ ;
typedef  struct TYPE_23__   TYPE_4__ ;
typedef  struct TYPE_22__   TYPE_3__ ;
typedef  struct TYPE_21__   TYPE_2__ ;
typedef  struct TYPE_20__   TYPE_1__ ;

/* Type definitions */
struct TYPE_22__ {TYPE_5__* data; } ;
typedef  TYPE_3__ xfs_dabuf_t ;
struct TYPE_23__ {scalar_t__ blkno; scalar_t__ blkno2; scalar_t__ index; scalar_t__ index2; int /*<<< orphan*/  dp; int /*<<< orphan*/  trans; scalar_t__ valuelen; scalar_t__ rmtblkno; } ;
typedef  TYPE_4__ xfs_da_args_t ;
struct TYPE_20__ {int /*<<< orphan*/  magic; } ;
struct TYPE_21__ {int /*<<< orphan*/  count; TYPE_1__ info; } ;
struct TYPE_24__ {TYPE_6__* entries; TYPE_2__ hdr; } ;
typedef  TYPE_5__ xfs_attr_leafblock_t ;
struct TYPE_25__ {int flags; int namelen; void* valuelen; void* valueblk; int /*<<< orphan*/  hashval; scalar_t__ name; } ;
typedef  TYPE_6__ xfs_attr_leaf_name_remote_t ;
struct TYPE_26__ {int namelen; scalar_t__ nameval; } ;
typedef  TYPE_7__ xfs_attr_leaf_name_local_t ;
typedef  TYPE_6__ xfs_attr_leaf_entry_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int /*<<< orphan*/  XFS_ATTR_FORK ; 
 int XFS_ATTR_INCOMPLETE ; 
 scalar_t__ XFS_ATTR_LEAF_MAGIC ; 
 int XFS_ATTR_LOCAL ; 
 int /*<<< orphan*/  XFS_DA_LOGRANGE (TYPE_5__*,TYPE_6__*,int) ; 
 scalar_t__ be16_to_cpu (int /*<<< orphan*/ ) ; 
 scalar_t__ be32_to_cpu (int /*<<< orphan*/ ) ; 
 void* cpu_to_be32 (scalar_t__) ; 
 scalar_t__ memcmp (char*,char*,int) ; 
 int /*<<< orphan*/  trace_xfs_attr_leaf_flipflags (TYPE_4__*) ; 
 TYPE_7__* xfs_attr_leaf_name_local (TYPE_5__*,size_t) ; 
 TYPE_6__* xfs_attr_leaf_name_remote (TYPE_5__*,size_t) ; 
 int /*<<< orphan*/  xfs_da_buf_done (TYPE_3__*) ; 
 int /*<<< orphan*/  xfs_da_log_buf (int /*<<< orphan*/ ,TYPE_3__*,int /*<<< orphan*/ ) ; 
 int xfs_da_read_buf (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int,TYPE_3__**,int /*<<< orphan*/ ) ; 
 int xfs_trans_roll (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

int
xfs_attr_leaf_flipflags(xfs_da_args_t *args)
{
	xfs_attr_leafblock_t *leaf1, *leaf2;
	xfs_attr_leaf_entry_t *entry1, *entry2;
	xfs_attr_leaf_name_remote_t *name_rmt;
	xfs_dabuf_t *bp1, *bp2;
	int error;
#ifdef DEBUG
	xfs_attr_leaf_name_local_t *name_loc;
	int namelen1, namelen2;
	char *name1, *name2;
#endif /* DEBUG */

	trace_xfs_attr_leaf_flipflags(args);

	/*
	 * Read the block containing the "old" attr
	 */
	error = xfs_da_read_buf(args->trans, args->dp, args->blkno, -1, &bp1,
					     XFS_ATTR_FORK);
	if (error) {
		return(error);
	}
	ASSERT(bp1 != NULL);

	/*
	 * Read the block containing the "new" attr, if it is different
	 */
	if (args->blkno2 != args->blkno) {
		error = xfs_da_read_buf(args->trans, args->dp, args->blkno2,
					-1, &bp2, XFS_ATTR_FORK);
		if (error) {
			return(error);
		}
		ASSERT(bp2 != NULL);
	} else {
		bp2 = bp1;
	}

	leaf1 = bp1->data;
	ASSERT(be16_to_cpu(leaf1->hdr.info.magic) == XFS_ATTR_LEAF_MAGIC);
	ASSERT(args->index < be16_to_cpu(leaf1->hdr.count));
	ASSERT(args->index >= 0);
	entry1 = &leaf1->entries[ args->index ];

	leaf2 = bp2->data;
	ASSERT(be16_to_cpu(leaf2->hdr.info.magic) == XFS_ATTR_LEAF_MAGIC);
	ASSERT(args->index2 < be16_to_cpu(leaf2->hdr.count));
	ASSERT(args->index2 >= 0);
	entry2 = &leaf2->entries[ args->index2 ];

#ifdef DEBUG
	if (entry1->flags & XFS_ATTR_LOCAL) {
		name_loc = xfs_attr_leaf_name_local(leaf1, args->index);
		namelen1 = name_loc->namelen;
		name1 = (char *)name_loc->nameval;
	} else {
		name_rmt = xfs_attr_leaf_name_remote(leaf1, args->index);
		namelen1 = name_rmt->namelen;
		name1 = (char *)name_rmt->name;
	}
	if (entry2->flags & XFS_ATTR_LOCAL) {
		name_loc = xfs_attr_leaf_name_local(leaf2, args->index2);
		namelen2 = name_loc->namelen;
		name2 = (char *)name_loc->nameval;
	} else {
		name_rmt = xfs_attr_leaf_name_remote(leaf2, args->index2);
		namelen2 = name_rmt->namelen;
		name2 = (char *)name_rmt->name;
	}
	ASSERT(be32_to_cpu(entry1->hashval) == be32_to_cpu(entry2->hashval));
	ASSERT(namelen1 == namelen2);
	ASSERT(memcmp(name1, name2, namelen1) == 0);
#endif /* DEBUG */

	ASSERT(entry1->flags & XFS_ATTR_INCOMPLETE);
	ASSERT((entry2->flags & XFS_ATTR_INCOMPLETE) == 0);

	entry1->flags &= ~XFS_ATTR_INCOMPLETE;
	xfs_da_log_buf(args->trans, bp1,
			  XFS_DA_LOGRANGE(leaf1, entry1, sizeof(*entry1)));
	if (args->rmtblkno) {
		ASSERT((entry1->flags & XFS_ATTR_LOCAL) == 0);
		name_rmt = xfs_attr_leaf_name_remote(leaf1, args->index);
		name_rmt->valueblk = cpu_to_be32(args->rmtblkno);
		name_rmt->valuelen = cpu_to_be32(args->valuelen);
		xfs_da_log_buf(args->trans, bp1,
			 XFS_DA_LOGRANGE(leaf1, name_rmt, sizeof(*name_rmt)));
	}

	entry2->flags |= XFS_ATTR_INCOMPLETE;
	xfs_da_log_buf(args->trans, bp2,
			  XFS_DA_LOGRANGE(leaf2, entry2, sizeof(*entry2)));
	if ((entry2->flags & XFS_ATTR_LOCAL) == 0) {
		name_rmt = xfs_attr_leaf_name_remote(leaf2, args->index2);
		name_rmt->valueblk = 0;
		name_rmt->valuelen = 0;
		xfs_da_log_buf(args->trans, bp2,
			 XFS_DA_LOGRANGE(leaf2, name_rmt, sizeof(*name_rmt)));
	}
	xfs_da_buf_done(bp1);
	if (bp1 != bp2)
		xfs_da_buf_done(bp2);

	/*
	 * Commit the flag value change and start the next trans in series.
	 */
	error = xfs_trans_roll(&args->trans, args->dp);

	return(error);
}