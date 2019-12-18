#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct super_block {int dummy; } ;
struct ext3_iloc {unsigned long block_group; unsigned long offset; } ;
struct ext3_group_desc {int /*<<< orphan*/  bg_inode_table; } ;
typedef  scalar_t__ ext3_fsblk_t ;

/* Variables and functions */
 int EXT3_BLOCK_SIZE (struct super_block*) ; 
 unsigned long EXT3_BLOCK_SIZE_BITS (struct super_block*) ; 
 unsigned long EXT3_INODES_PER_GROUP (struct super_block*) ; 
 unsigned long EXT3_INODE_SIZE (struct super_block*) ; 
 struct ext3_group_desc* ext3_get_group_desc (struct super_block*,unsigned long,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ext3_valid_inum (struct super_block*,unsigned long) ; 
 scalar_t__ le32_to_cpu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static ext3_fsblk_t ext3_get_inode_block(struct super_block *sb,
		unsigned long ino, struct ext3_iloc *iloc)
{
	unsigned long block_group;
	unsigned long offset;
	ext3_fsblk_t block;
	struct ext3_group_desc *gdp;

	if (!ext3_valid_inum(sb, ino)) {
		/*
		 * This error is already checked for in namei.c unless we are
		 * looking at an NFS filehandle, in which case no error
		 * report is needed
		 */
		return 0;
	}

	block_group = (ino - 1) / EXT3_INODES_PER_GROUP(sb);
	gdp = ext3_get_group_desc(sb, block_group, NULL);
	if (!gdp)
		return 0;
	/*
	 * Figure out the offset within the block group inode table
	 */
	offset = ((ino - 1) % EXT3_INODES_PER_GROUP(sb)) *
		EXT3_INODE_SIZE(sb);
	block = le32_to_cpu(gdp->bg_inode_table) +
		(offset >> EXT3_BLOCK_SIZE_BITS(sb));

	iloc->block_group = block_group;
	iloc->offset = offset & (EXT3_BLOCK_SIZE(sb) - 1);
	return block;
}