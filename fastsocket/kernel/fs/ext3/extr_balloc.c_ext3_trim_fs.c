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
typedef  int uint64_t ;
struct super_block {int s_blocksize_bits; int s_blocksize; } ;
struct fstrim_range {int start; int len; int minlen; } ;
struct ext3_super_block {int /*<<< orphan*/  s_blocks_count; int /*<<< orphan*/  s_first_data_block; } ;
struct ext3_group_desc {int /*<<< orphan*/  bg_free_blocks_count; } ;
typedef  int ext3_grpblk_t ;
typedef  int ext3_fsblk_t ;
struct TYPE_2__ {struct ext3_super_block* s_es; } ;

/* Variables and functions */
 int EINVAL ; 
 int EXT3_BLOCKS_PER_GROUP (struct super_block*) ; 
 TYPE_1__* EXT3_SB (struct super_block*) ; 
 struct ext3_group_desc* ext3_get_group_desc (struct super_block*,unsigned long,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ext3_get_group_no_and_offset (struct super_block*,int,unsigned long*,int*) ; 
 int ext3_trim_all_free (struct super_block*,unsigned long,int,int,int) ; 
 int le16_to_cpu (int /*<<< orphan*/ ) ; 
 int le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  smp_rmb () ; 
 scalar_t__ unlikely (int) ; 

int ext3_trim_fs(struct super_block *sb, struct fstrim_range *range)
{
	ext3_grpblk_t last_block, first_block;
	unsigned long group, first_group, last_group;
	struct ext3_group_desc *gdp;
	struct ext3_super_block *es = EXT3_SB(sb)->s_es;
	uint64_t start, minlen, end, trimmed = 0;
	ext3_fsblk_t first_data_blk =
			le32_to_cpu(EXT3_SB(sb)->s_es->s_first_data_block);
	ext3_fsblk_t max_blks = le32_to_cpu(es->s_blocks_count);
	int ret = 0;

	start = range->start >> sb->s_blocksize_bits;
	end = start + (range->len >> sb->s_blocksize_bits) - 1;
	minlen = range->minlen >> sb->s_blocksize_bits;

	if (unlikely(minlen > EXT3_BLOCKS_PER_GROUP(sb)) ||
	    unlikely(start >= max_blks))
		return -EINVAL;
	if (unlikely(end >= max_blks))
		end = max_blks - 1;
	if (end <= first_data_blk)
		return 0;
	if (start < first_data_blk)
		start = first_data_blk;

	smp_rmb();

	/* Determine first and last group to examine based on start and len */
	ext3_get_group_no_and_offset(sb, (ext3_fsblk_t) start,
				     &first_group, &first_block);
	ext3_get_group_no_and_offset(sb, (ext3_fsblk_t) end,
				     &last_group, &last_block);

	/* The last block to discard in the group */
	end = EXT3_BLOCKS_PER_GROUP(sb);

	for (group = first_group; group <= last_group; group++) {
		gdp = ext3_get_group_desc(sb, group, NULL);
		if (!gdp)
			break;

		if (le16_to_cpu(gdp->bg_free_blocks_count) < minlen)
			continue;

		/*
		 * For all the groups except the last one, last block will
		 * always be EXT3_BLOCKS_PER_GROUP(sb), so we only need to
		 * change it for the last group, note that last_block is
		 * already computed earlier by ext3_get_group_no_and_offset()
		 */
		if (group == last_group)
			end = last_block;

		ret = ext3_trim_all_free(sb, group, first_block,
					 end, minlen);
		if (ret < 0)
			break;
		trimmed += ret;

		/*
		 * For every group except the first one, we are sure
		 * that the first block to discard will be block #0.
		 */
		first_block = 0;
	}

	if (ret > 0)
		ret = 0;
	range->len = trimmed * sb->s_blocksize;

	return ret;
}