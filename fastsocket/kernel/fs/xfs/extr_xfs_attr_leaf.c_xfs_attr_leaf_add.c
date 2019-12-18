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
struct TYPE_20__ {scalar_t__ index; TYPE_9__* trans; int /*<<< orphan*/  valuelen; int /*<<< orphan*/  namelen; } ;
typedef  TYPE_5__ xfs_da_args_t ;
struct TYPE_16__ {int /*<<< orphan*/  magic; } ;
struct TYPE_23__ {TYPE_7__* freemap; int /*<<< orphan*/  holes; int /*<<< orphan*/  firstused; int /*<<< orphan*/  count; TYPE_1__ info; } ;
struct TYPE_21__ {TYPE_8__ hdr; } ;
typedef  TYPE_6__ xfs_attr_leafblock_t ;
struct TYPE_22__ {int /*<<< orphan*/  size; int /*<<< orphan*/  base; } ;
typedef  TYPE_7__ xfs_attr_leaf_map_t ;
typedef  TYPE_8__ xfs_attr_leaf_hdr_t ;
typedef  int /*<<< orphan*/  xfs_attr_leaf_entry_t ;
struct TYPE_24__ {TYPE_3__* t_mountp; } ;
struct TYPE_17__ {int /*<<< orphan*/  sb_blocksize; } ;
struct TYPE_18__ {TYPE_2__ m_sb; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int /*<<< orphan*/  ENOSPC ; 
 int XFS_ATTR_LEAF_MAGIC ; 
 int XFS_ATTR_LEAF_MAPSIZE ; 
 int XFS_ERROR (int /*<<< orphan*/ ) ; 
 int be16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trace_xfs_attr_leaf_add (TYPE_5__*) ; 
 int xfs_attr_leaf_add_work (TYPE_4__*,TYPE_5__*,int) ; 
 int /*<<< orphan*/  xfs_attr_leaf_compact (TYPE_9__*,TYPE_4__*) ; 
 int xfs_attr_leaf_newentsize (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

int
xfs_attr_leaf_add(xfs_dabuf_t *bp, xfs_da_args_t *args)
{
	xfs_attr_leafblock_t *leaf;
	xfs_attr_leaf_hdr_t *hdr;
	xfs_attr_leaf_map_t *map;
	int tablesize, entsize, sum, tmp, i;

	trace_xfs_attr_leaf_add(args);

	leaf = bp->data;
	ASSERT(be16_to_cpu(leaf->hdr.info.magic) == XFS_ATTR_LEAF_MAGIC);
	ASSERT((args->index >= 0)
		&& (args->index <= be16_to_cpu(leaf->hdr.count)));
	hdr = &leaf->hdr;
	entsize = xfs_attr_leaf_newentsize(args->namelen, args->valuelen,
			   args->trans->t_mountp->m_sb.sb_blocksize, NULL);

	/*
	 * Search through freemap for first-fit on new name length.
	 * (may need to figure in size of entry struct too)
	 */
	tablesize = (be16_to_cpu(hdr->count) + 1)
					* sizeof(xfs_attr_leaf_entry_t)
					+ sizeof(xfs_attr_leaf_hdr_t);
	map = &hdr->freemap[XFS_ATTR_LEAF_MAPSIZE-1];
	for (sum = 0, i = XFS_ATTR_LEAF_MAPSIZE-1; i >= 0; map--, i--) {
		if (tablesize > be16_to_cpu(hdr->firstused)) {
			sum += be16_to_cpu(map->size);
			continue;
		}
		if (!map->size)
			continue;	/* no space in this map */
		tmp = entsize;
		if (be16_to_cpu(map->base) < be16_to_cpu(hdr->firstused))
			tmp += sizeof(xfs_attr_leaf_entry_t);
		if (be16_to_cpu(map->size) >= tmp) {
			tmp = xfs_attr_leaf_add_work(bp, args, i);
			return(tmp);
		}
		sum += be16_to_cpu(map->size);
	}

	/*
	 * If there are no holes in the address space of the block,
	 * and we don't have enough freespace, then compaction will do us
	 * no good and we should just give up.
	 */
	if (!hdr->holes && (sum < entsize))
		return(XFS_ERROR(ENOSPC));

	/*
	 * Compact the entries to coalesce free space.
	 * This may change the hdr->count via dropping INCOMPLETE entries.
	 */
	xfs_attr_leaf_compact(args->trans, bp);

	/*
	 * After compaction, the block is guaranteed to have only one
	 * free region, in freemap[0].  If it is not big enough, give up.
	 */
	if (be16_to_cpu(hdr->freemap[0].size)
				< (entsize + sizeof(xfs_attr_leaf_entry_t)))
		return(XFS_ERROR(ENOSPC));

	return(xfs_attr_leaf_add_work(bp, args, 0));
}