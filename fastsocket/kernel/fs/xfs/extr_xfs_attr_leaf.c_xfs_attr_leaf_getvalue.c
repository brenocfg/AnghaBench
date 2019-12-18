#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_24__   TYPE_9__ ;
typedef  struct TYPE_23__   TYPE_8__ ;
typedef  struct TYPE_22__   TYPE_7__ ;
typedef  struct TYPE_21__   TYPE_6__ ;
typedef  struct TYPE_20__   TYPE_5__ ;
typedef  struct TYPE_19__   TYPE_4__ ;
typedef  struct TYPE_18__   TYPE_3__ ;
typedef  struct TYPE_17__   TYPE_2__ ;
typedef  struct TYPE_16__   TYPE_1__ ;

/* Type definitions */
struct TYPE_19__ {TYPE_6__* data; } ;
typedef  TYPE_4__ xfs_dabuf_t ;
struct TYPE_20__ {int index; size_t namelen; int flags; int valuelen; TYPE_3__* dp; int /*<<< orphan*/  rmtblkcnt; void* rmtblkno; int /*<<< orphan*/  name; int /*<<< orphan*/  value; } ;
typedef  TYPE_5__ xfs_da_args_t ;
struct TYPE_16__ {int /*<<< orphan*/  magic; } ;
struct TYPE_17__ {int /*<<< orphan*/  count; TYPE_1__ info; } ;
struct TYPE_21__ {TYPE_9__* entries; TYPE_2__ hdr; } ;
typedef  TYPE_6__ xfs_attr_leafblock_t ;
struct TYPE_22__ {size_t namelen; int /*<<< orphan*/  valueblk; int /*<<< orphan*/  valuelen; int /*<<< orphan*/ * name; } ;
typedef  TYPE_7__ xfs_attr_leaf_name_remote_t ;
struct TYPE_23__ {size_t namelen; int /*<<< orphan*/ * nameval; int /*<<< orphan*/  valuelen; } ;
typedef  TYPE_8__ xfs_attr_leaf_name_local_t ;
struct TYPE_24__ {int flags; } ;
typedef  TYPE_9__ xfs_attr_leaf_entry_t ;
struct TYPE_18__ {int /*<<< orphan*/  i_mount; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int ATTR_KERNOVAL ; 
 int /*<<< orphan*/  ERANGE ; 
 int XFS_ATTR_LEAF_MAGIC ; 
 int XFS_ATTR_LOCAL ; 
 int /*<<< orphan*/  XFS_B_TO_FSB (int /*<<< orphan*/ ,int) ; 
 int XFS_ERROR (int /*<<< orphan*/ ) ; 
 int XFS_LBSIZE (int /*<<< orphan*/ ) ; 
 int be16_to_cpu (int /*<<< orphan*/ ) ; 
 void* be32_to_cpu (int /*<<< orphan*/ ) ; 
 scalar_t__ memcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 TYPE_8__* xfs_attr_leaf_name_local (TYPE_6__*,size_t) ; 
 TYPE_7__* xfs_attr_leaf_name_remote (TYPE_6__*,size_t) ; 

int
xfs_attr_leaf_getvalue(xfs_dabuf_t *bp, xfs_da_args_t *args)
{
	int valuelen;
	xfs_attr_leafblock_t *leaf;
	xfs_attr_leaf_entry_t *entry;
	xfs_attr_leaf_name_local_t *name_loc;
	xfs_attr_leaf_name_remote_t *name_rmt;

	leaf = bp->data;
	ASSERT(be16_to_cpu(leaf->hdr.info.magic) == XFS_ATTR_LEAF_MAGIC);
	ASSERT(be16_to_cpu(leaf->hdr.count)
					< (XFS_LBSIZE(args->dp->i_mount)/8));
	ASSERT(args->index < be16_to_cpu(leaf->hdr.count));

	entry = &leaf->entries[args->index];
	if (entry->flags & XFS_ATTR_LOCAL) {
		name_loc = xfs_attr_leaf_name_local(leaf, args->index);
		ASSERT(name_loc->namelen == args->namelen);
		ASSERT(memcmp(args->name, name_loc->nameval, args->namelen) == 0);
		valuelen = be16_to_cpu(name_loc->valuelen);
		if (args->flags & ATTR_KERNOVAL) {
			args->valuelen = valuelen;
			return(0);
		}
		if (args->valuelen < valuelen) {
			args->valuelen = valuelen;
			return(XFS_ERROR(ERANGE));
		}
		args->valuelen = valuelen;
		memcpy(args->value, &name_loc->nameval[args->namelen], valuelen);
	} else {
		name_rmt = xfs_attr_leaf_name_remote(leaf, args->index);
		ASSERT(name_rmt->namelen == args->namelen);
		ASSERT(memcmp(args->name, name_rmt->name, args->namelen) == 0);
		valuelen = be32_to_cpu(name_rmt->valuelen);
		args->rmtblkno = be32_to_cpu(name_rmt->valueblk);
		args->rmtblkcnt = XFS_B_TO_FSB(args->dp->i_mount, valuelen);
		if (args->flags & ATTR_KERNOVAL) {
			args->valuelen = valuelen;
			return(0);
		}
		if (args->valuelen < valuelen) {
			args->valuelen = valuelen;
			return(XFS_ERROR(ERANGE));
		}
		args->valuelen = valuelen;
	}
	return(0);
}