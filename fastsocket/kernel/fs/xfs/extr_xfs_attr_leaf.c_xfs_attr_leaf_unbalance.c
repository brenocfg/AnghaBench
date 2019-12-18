#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_23__   TYPE_7__ ;
typedef  struct TYPE_22__   TYPE_6__ ;
typedef  struct TYPE_21__   TYPE_5__ ;
typedef  struct TYPE_20__   TYPE_4__ ;
typedef  struct TYPE_19__   TYPE_3__ ;
typedef  struct TYPE_18__   TYPE_2__ ;
typedef  struct TYPE_17__   TYPE_1__ ;
typedef  struct TYPE_16__   TYPE_15__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  xfs_mount_t ;
struct TYPE_19__ {scalar_t__ blocksize; TYPE_15__* args; int /*<<< orphan*/ * mp; } ;
typedef  TYPE_3__ xfs_da_state_t ;
struct TYPE_20__ {scalar_t__ magic; void* hashval; TYPE_7__* bp; } ;
typedef  TYPE_4__ xfs_da_state_blk_t ;
struct TYPE_17__ {scalar_t__ magic; } ;
struct TYPE_22__ {scalar_t__ holes; scalar_t__ count; scalar_t__ usedbytes; void* firstused; TYPE_1__ info; } ;
struct TYPE_21__ {TYPE_6__ hdr; TYPE_2__* entries; } ;
typedef  TYPE_5__ xfs_attr_leafblock_t ;
typedef  TYPE_6__ xfs_attr_leaf_hdr_t ;
struct TYPE_23__ {TYPE_5__* data; } ;
struct TYPE_18__ {int /*<<< orphan*/  hashval; } ;
struct TYPE_16__ {int /*<<< orphan*/  trans; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int /*<<< orphan*/  KM_SLEEP ; 
 scalar_t__ XFS_ATTR_LEAF_MAGIC ; 
 scalar_t__ XFS_ATTR_LEAF_NAME_ALIGN ; 
 int be16_to_cpu (scalar_t__) ; 
 void* be32_to_cpu (int /*<<< orphan*/ ) ; 
 void* cpu_to_be16 (scalar_t__) ; 
 char* kmem_alloc (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kmem_free (char*) ; 
 int /*<<< orphan*/  memcpy (char*,char*,scalar_t__) ; 
 int /*<<< orphan*/  memset (char*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  trace_xfs_attr_leaf_unbalance (TYPE_15__*) ; 
 int /*<<< orphan*/  xfs_attr_leaf_moveents (TYPE_5__*,int /*<<< orphan*/ ,TYPE_5__*,int,int,int /*<<< orphan*/ *) ; 
 scalar_t__ xfs_attr_leaf_order (TYPE_7__*,TYPE_7__*) ; 
 int /*<<< orphan*/  xfs_da_log_buf (int /*<<< orphan*/ ,TYPE_7__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
xfs_attr_leaf_unbalance(xfs_da_state_t *state, xfs_da_state_blk_t *drop_blk,
				       xfs_da_state_blk_t *save_blk)
{
	xfs_attr_leafblock_t *drop_leaf, *save_leaf, *tmp_leaf;
	xfs_attr_leaf_hdr_t *drop_hdr, *save_hdr, *tmp_hdr;
	xfs_mount_t *mp;
	char *tmpbuffer;

	trace_xfs_attr_leaf_unbalance(state->args);

	/*
	 * Set up environment.
	 */
	mp = state->mp;
	ASSERT(drop_blk->magic == XFS_ATTR_LEAF_MAGIC);
	ASSERT(save_blk->magic == XFS_ATTR_LEAF_MAGIC);
	drop_leaf = drop_blk->bp->data;
	save_leaf = save_blk->bp->data;
	ASSERT(be16_to_cpu(drop_leaf->hdr.info.magic) == XFS_ATTR_LEAF_MAGIC);
	ASSERT(be16_to_cpu(save_leaf->hdr.info.magic) == XFS_ATTR_LEAF_MAGIC);
	drop_hdr = &drop_leaf->hdr;
	save_hdr = &save_leaf->hdr;

	/*
	 * Save last hashval from dying block for later Btree fixup.
	 */
	drop_blk->hashval = be32_to_cpu(
		drop_leaf->entries[be16_to_cpu(drop_leaf->hdr.count)-1].hashval);

	/*
	 * Check if we need a temp buffer, or can we do it in place.
	 * Note that we don't check "leaf" for holes because we will
	 * always be dropping it, toosmall() decided that for us already.
	 */
	if (save_hdr->holes == 0) {
		/*
		 * dest leaf has no holes, so we add there.  May need
		 * to make some room in the entry array.
		 */
		if (xfs_attr_leaf_order(save_blk->bp, drop_blk->bp)) {
			xfs_attr_leaf_moveents(drop_leaf, 0, save_leaf, 0,
			     be16_to_cpu(drop_hdr->count), mp);
		} else {
			xfs_attr_leaf_moveents(drop_leaf, 0, save_leaf,
				  be16_to_cpu(save_hdr->count),
				  be16_to_cpu(drop_hdr->count), mp);
		}
	} else {
		/*
		 * Destination has holes, so we make a temporary copy
		 * of the leaf and add them both to that.
		 */
		tmpbuffer = kmem_alloc(state->blocksize, KM_SLEEP);
		ASSERT(tmpbuffer != NULL);
		memset(tmpbuffer, 0, state->blocksize);
		tmp_leaf = (xfs_attr_leafblock_t *)tmpbuffer;
		tmp_hdr = &tmp_leaf->hdr;
		tmp_hdr->info = save_hdr->info;	/* struct copy */
		tmp_hdr->count = 0;
		tmp_hdr->firstused = cpu_to_be16(state->blocksize);
		if (!tmp_hdr->firstused) {
			tmp_hdr->firstused = cpu_to_be16(
				state->blocksize - XFS_ATTR_LEAF_NAME_ALIGN);
		}
		tmp_hdr->usedbytes = 0;
		if (xfs_attr_leaf_order(save_blk->bp, drop_blk->bp)) {
			xfs_attr_leaf_moveents(drop_leaf, 0, tmp_leaf, 0,
				be16_to_cpu(drop_hdr->count), mp);
			xfs_attr_leaf_moveents(save_leaf, 0, tmp_leaf,
				  be16_to_cpu(tmp_leaf->hdr.count),
				  be16_to_cpu(save_hdr->count), mp);
		} else {
			xfs_attr_leaf_moveents(save_leaf, 0, tmp_leaf, 0,
				be16_to_cpu(save_hdr->count), mp);
			xfs_attr_leaf_moveents(drop_leaf, 0, tmp_leaf,
				be16_to_cpu(tmp_leaf->hdr.count),
				be16_to_cpu(drop_hdr->count), mp);
		}
		memcpy((char *)save_leaf, (char *)tmp_leaf, state->blocksize);
		kmem_free(tmpbuffer);
	}

	xfs_da_log_buf(state->args->trans, save_blk->bp, 0,
					   state->blocksize - 1);

	/*
	 * Copy out last hashval in each block for B-tree code.
	 */
	save_blk->hashval = be32_to_cpu(
		save_leaf->entries[be16_to_cpu(save_leaf->hdr.count)-1].hashval);
}