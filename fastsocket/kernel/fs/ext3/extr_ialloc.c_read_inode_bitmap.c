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
struct ext3_group_desc {int /*<<< orphan*/  bg_inode_bitmap; } ;
struct buffer_head {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ext3_error (struct super_block*,char*,char*,unsigned long,int /*<<< orphan*/ ) ; 
 struct ext3_group_desc* ext3_get_group_desc (struct super_block*,unsigned long,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  le32_to_cpu (int /*<<< orphan*/ ) ; 
 struct buffer_head* sb_bread (struct super_block*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct buffer_head *
read_inode_bitmap(struct super_block * sb, unsigned long block_group)
{
	struct ext3_group_desc *desc;
	struct buffer_head *bh = NULL;

	desc = ext3_get_group_desc(sb, block_group, NULL);
	if (!desc)
		goto error_out;

	bh = sb_bread(sb, le32_to_cpu(desc->bg_inode_bitmap));
	if (!bh)
		ext3_error(sb, "read_inode_bitmap",
			    "Cannot read inode bitmap - "
			    "block_group = %lu, inode_bitmap = %u",
			    block_group, le32_to_cpu(desc->bg_inode_bitmap));
error_out:
	return bh;
}