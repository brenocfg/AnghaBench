#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u64 ;
struct ocfs2_super {unsigned long long max_slots; TYPE_1__* sb; } ;
struct ocfs2_slot_info {unsigned long long si_blocks; int si_slots_per_block; struct buffer_head** si_bh; TYPE_2__* si_inode; scalar_t__ si_extended; } ;
struct ocfs2_extended_slot {int dummy; } ;
struct buffer_head {int dummy; } ;
typedef  int /*<<< orphan*/  __le16 ;
struct TYPE_6__ {int /*<<< orphan*/  i_sb; } ;
struct TYPE_5__ {int s_blocksize; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INODE_CACHE (TYPE_2__*) ; 
 int /*<<< orphan*/  OCFS2_BH_IGNORE_CACHE ; 
 unsigned long long UINT_MAX ; 
 struct buffer_head** kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlog (int /*<<< orphan*/ ,char*,unsigned int,unsigned long long) ; 
 int /*<<< orphan*/  mlog_errno (int) ; 
 unsigned long long ocfs2_blocks_for_bytes (int /*<<< orphan*/ ,unsigned long long) ; 
 int ocfs2_extent_map_get_blocks (TYPE_2__*,unsigned int,scalar_t__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int ocfs2_read_blocks (int /*<<< orphan*/ ,scalar_t__,int,struct buffer_head**,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int ocfs2_slot_map_physical_size (struct ocfs2_super*,TYPE_2__*,unsigned long long*) ; 

__attribute__((used)) static int ocfs2_map_slot_buffers(struct ocfs2_super *osb,
				  struct ocfs2_slot_info *si)
{
	int status = 0;
	u64 blkno;
	unsigned long long blocks, bytes;
	unsigned int i;
	struct buffer_head *bh;

	status = ocfs2_slot_map_physical_size(osb, si->si_inode, &bytes);
	if (status)
		goto bail;

	blocks = ocfs2_blocks_for_bytes(si->si_inode->i_sb, bytes);
	BUG_ON(blocks > UINT_MAX);
	si->si_blocks = blocks;
	if (!si->si_blocks)
		goto bail;

	if (si->si_extended)
		si->si_slots_per_block =
			(osb->sb->s_blocksize /
			 sizeof(struct ocfs2_extended_slot));
	else
		si->si_slots_per_block = osb->sb->s_blocksize / sizeof(__le16);

	/* The size checks above should ensure this */
	BUG_ON((osb->max_slots / si->si_slots_per_block) > blocks);

	mlog(0, "Slot map needs %u buffers for %llu bytes\n",
	     si->si_blocks, bytes);

	si->si_bh = kzalloc(sizeof(struct buffer_head *) * si->si_blocks,
			    GFP_KERNEL);
	if (!si->si_bh) {
		status = -ENOMEM;
		mlog_errno(status);
		goto bail;
	}

	for (i = 0; i < si->si_blocks; i++) {
		status = ocfs2_extent_map_get_blocks(si->si_inode, i,
						     &blkno, NULL, NULL);
		if (status < 0) {
			mlog_errno(status);
			goto bail;
		}

		mlog(0, "Reading slot map block %u at %llu\n", i,
		     (unsigned long long)blkno);

		bh = NULL;  /* Acquire a fresh bh */
		status = ocfs2_read_blocks(INODE_CACHE(si->si_inode), blkno,
					   1, &bh, OCFS2_BH_IGNORE_CACHE, NULL);
		if (status < 0) {
			mlog_errno(status);
			goto bail;
		}

		si->si_bh[i] = bh;
	}

bail:
	return status;
}