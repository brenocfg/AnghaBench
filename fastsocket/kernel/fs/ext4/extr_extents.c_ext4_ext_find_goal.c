#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct inode {int /*<<< orphan*/  i_sb; int /*<<< orphan*/  i_mode; } ;
struct ext4_inode_info {int i_block_group; } ;
struct ext4_extent {int /*<<< orphan*/  ee_block; } ;
struct ext4_ext_path {int p_depth; TYPE_1__* p_bh; struct ext4_extent* p_ext; } ;
typedef  scalar_t__ ext4_lblk_t ;
typedef  int ext4_grpblk_t ;
typedef  int ext4_group_t ;
typedef  scalar_t__ ext4_fsblk_t ;
struct TYPE_9__ {int pid; } ;
struct TYPE_8__ {int /*<<< orphan*/  s_first_data_block; } ;
struct TYPE_7__ {TYPE_3__* s_es; } ;
struct TYPE_6__ {scalar_t__ b_blocknr; } ;

/* Variables and functions */
 int /*<<< orphan*/  DELALLOC ; 
 int EXT4_BLOCKS_PER_GROUP (int /*<<< orphan*/ ) ; 
 int EXT4_FLEX_SIZE_DIR_ALLOC_SCHEME ; 
 struct ext4_inode_info* EXT4_I (struct inode*) ; 
 TYPE_2__* EXT4_SB (int /*<<< orphan*/ ) ; 
 scalar_t__ S_ISREG (int /*<<< orphan*/ ) ; 
 TYPE_4__* current ; 
 scalar_t__ ext4_blocks_count (TYPE_3__*) ; 
 scalar_t__ ext4_ext_pblock (struct ext4_extent*) ; 
 int ext4_flex_bg_size (TYPE_2__*) ; 
 scalar_t__ le32_to_cpu (int /*<<< orphan*/ ) ; 
 scalar_t__ test_opt (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static ext4_fsblk_t ext4_ext_find_goal(struct inode *inode,
			      struct ext4_ext_path *path,
			      ext4_lblk_t block)
{
	struct ext4_inode_info *ei = EXT4_I(inode);
	ext4_fsblk_t bg_start;
	ext4_fsblk_t last_block;
	ext4_grpblk_t colour;
	ext4_group_t block_group;
	int flex_size = ext4_flex_bg_size(EXT4_SB(inode->i_sb));
	int depth;

	if (path) {
		struct ext4_extent *ex;
		depth = path->p_depth;

		/* try to predict block placement */
		ex = path[depth].p_ext;
		if (ex)
			return (ext4_ext_pblock(ex) +
				(block - le32_to_cpu(ex->ee_block)));

		/* it looks like index is empty;
		 * try to find starting block from index itself */
		if (path[depth].p_bh)
			return path[depth].p_bh->b_blocknr;
	}

	/* OK. use inode's group */
	block_group = ei->i_block_group;
	if (flex_size >= EXT4_FLEX_SIZE_DIR_ALLOC_SCHEME) {
		/*
		 * If there are at least EXT4_FLEX_SIZE_DIR_ALLOC_SCHEME
		 * block groups per flexgroup, reserve the first block 
		 * group for directories and special files.  Regular 
		 * files will start at the second block group.  This
		 * tends to speed up directory access and improves 
		 * fsck times.
		 */
		block_group &= ~(flex_size-1);
		if (S_ISREG(inode->i_mode))
			block_group++;
	}
	bg_start = (block_group * EXT4_BLOCKS_PER_GROUP(inode->i_sb)) +
		le32_to_cpu(EXT4_SB(inode->i_sb)->s_es->s_first_data_block);
	last_block = ext4_blocks_count(EXT4_SB(inode->i_sb)->s_es) - 1;

	/*
	 * If we are doing delayed allocation, we don't need take
	 * colour into account.
	 */
	if (test_opt(inode->i_sb, DELALLOC))
		return bg_start;

	if (bg_start + EXT4_BLOCKS_PER_GROUP(inode->i_sb) <= last_block)
		colour = (current->pid % 16) *
			(EXT4_BLOCKS_PER_GROUP(inode->i_sb) / 16);
	else
		colour = (current->pid % 16) * ((last_block - bg_start) / 16);
	return bg_start + colour + block;
}