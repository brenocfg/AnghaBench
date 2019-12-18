#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u64 ;
typedef  scalar_t__ u32 ;
struct ocfs2_super {TYPE_1__* local_alloc_bh; } ;
struct ocfs2_local_alloc {int /*<<< orphan*/  la_bm_off; } ;
struct ocfs2_dinode {int dummy; } ;
struct ocfs2_alloc_context {scalar_t__ ac_max_block; } ;
struct inode {int /*<<< orphan*/  i_sb; } ;
struct TYPE_2__ {scalar_t__ b_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENOSPC ; 
 struct ocfs2_local_alloc* OCFS2_LOCAL_ALLOC (struct ocfs2_dinode*) ; 
 struct ocfs2_super* OCFS2_SB (int /*<<< orphan*/ ) ; 
 scalar_t__ le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlog (int /*<<< orphan*/ ,char*,unsigned long long,unsigned long long) ; 
 int /*<<< orphan*/  mlog_errno (int /*<<< orphan*/ ) ; 
 scalar_t__ ocfs2_clusters_to_blocks (int /*<<< orphan*/ ,scalar_t__) ; 
 int ocfs2_local_alloc_find_clear_bits (struct ocfs2_super*,struct ocfs2_dinode*,scalar_t__) ; 

__attribute__((used)) static int ocfs2_local_alloc_in_range(struct inode *inode,
				      struct ocfs2_alloc_context *ac,
				      u32 bits_wanted)
{
	struct ocfs2_super *osb = OCFS2_SB(inode->i_sb);
	struct ocfs2_dinode *alloc;
	struct ocfs2_local_alloc *la;
	int start;
	u64 block_off;

	if (!ac->ac_max_block)
		return 1;

	alloc = (struct ocfs2_dinode *) osb->local_alloc_bh->b_data;
	la = OCFS2_LOCAL_ALLOC(alloc);

	start = ocfs2_local_alloc_find_clear_bits(osb, alloc, bits_wanted);
	if (start == -1) {
		mlog_errno(-ENOSPC);
		return 0;
	}

	/*
	 * Converting (bm_off + start + bits_wanted) to blocks gives us
	 * the blkno just past our actual allocation.  This is perfect
	 * to compare with ac_max_block.
	 */
	block_off = ocfs2_clusters_to_blocks(inode->i_sb,
					     le32_to_cpu(la->la_bm_off) +
					     start + bits_wanted);
	mlog(0, "Checking %llu against %llu\n",
	     (unsigned long long)block_off,
	     (unsigned long long)ac->ac_max_block);
	if (block_off > ac->ac_max_block)
		return 0;

	return 1;
}