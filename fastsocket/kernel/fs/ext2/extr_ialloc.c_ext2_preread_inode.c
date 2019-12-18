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
struct inode {int i_ino; int /*<<< orphan*/  i_sb; TYPE_1__* i_mapping; } ;
struct ext2_group_desc {int /*<<< orphan*/  bg_inode_table; } ;
struct backing_dev_info {int dummy; } ;
struct TYPE_2__ {struct backing_dev_info* backing_dev_info; } ;

/* Variables and functions */
 unsigned long EXT2_BLOCK_SIZE_BITS (int /*<<< orphan*/ ) ; 
 int EXT2_INODES_PER_GROUP (int /*<<< orphan*/ ) ; 
 int EXT2_INODE_SIZE (int /*<<< orphan*/ ) ; 
 scalar_t__ bdi_read_congested (struct backing_dev_info*) ; 
 scalar_t__ bdi_write_congested (struct backing_dev_info*) ; 
 struct ext2_group_desc* ext2_get_group_desc (int /*<<< orphan*/ ,unsigned long,int /*<<< orphan*/ *) ; 
 unsigned long le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sb_breadahead (int /*<<< orphan*/ ,unsigned long) ; 

__attribute__((used)) static void ext2_preread_inode(struct inode *inode)
{
	unsigned long block_group;
	unsigned long offset;
	unsigned long block;
	struct ext2_group_desc * gdp;
	struct backing_dev_info *bdi;

	bdi = inode->i_mapping->backing_dev_info;
	if (bdi_read_congested(bdi))
		return;
	if (bdi_write_congested(bdi))
		return;

	block_group = (inode->i_ino - 1) / EXT2_INODES_PER_GROUP(inode->i_sb);
	gdp = ext2_get_group_desc(inode->i_sb, block_group, NULL);
	if (gdp == NULL)
		return;

	/*
	 * Figure out the offset within the block group inode table
	 */
	offset = ((inode->i_ino - 1) % EXT2_INODES_PER_GROUP(inode->i_sb)) *
				EXT2_INODE_SIZE(inode->i_sb);
	block = le32_to_cpu(gdp->bg_inode_table) +
				(offset >> EXT2_BLOCK_SIZE_BITS(inode->i_sb));
	sb_breadahead(inode->i_sb, block);
}