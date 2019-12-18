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
typedef  scalar_t__ uint32_t ;
typedef  size_t uint16_t ;
struct udf_sb_info {int /*<<< orphan*/  s_alloc_mutex; TYPE_1__* s_partmaps; } ;
struct udf_bitmap {struct buffer_head** s_block_bitmap; } ;
struct super_block {int s_blocksize_bits; int s_blocksize; } ;
struct spaceBitmapDesc {int dummy; } ;
struct inode {int dummy; } ;
struct buffer_head {int /*<<< orphan*/  b_data; } ;
typedef  scalar_t__ __u32 ;
struct TYPE_2__ {scalar_t__ s_partition_len; } ;

/* Variables and functions */
 struct udf_sb_info* UDF_SB (struct super_block*) ; 
 int load_block_bitmap (struct super_block*,struct udf_bitmap*,int) ; 
 int /*<<< orphan*/  mark_buffer_dirty (struct buffer_head*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  udf_add_free_space (struct super_block*,size_t,int) ; 
 int /*<<< orphan*/  udf_clear_bit (int,int /*<<< orphan*/ ) ; 
 int udf_compute_nr_groups (struct super_block*,size_t) ; 
 int /*<<< orphan*/  udf_debug (char*,int) ; 
 int /*<<< orphan*/  udf_test_bit (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vfs_dq_free_block (struct inode*,int) ; 
 scalar_t__ vfs_dq_prealloc_block (struct inode*,int) ; 

__attribute__((used)) static int udf_bitmap_prealloc_blocks(struct super_block *sb,
				      struct inode *inode,
				      struct udf_bitmap *bitmap,
				      uint16_t partition, uint32_t first_block,
				      uint32_t block_count)
{
	struct udf_sb_info *sbi = UDF_SB(sb);
	int alloc_count = 0;
	int bit, block, block_group, group_start;
	int nr_groups, bitmap_nr;
	struct buffer_head *bh;
	__u32 part_len;

	mutex_lock(&sbi->s_alloc_mutex);
	part_len = sbi->s_partmaps[partition].s_partition_len;
	if (first_block >= part_len)
		goto out;

	if (first_block + block_count > part_len)
		block_count = part_len - first_block;

	do {
		nr_groups = udf_compute_nr_groups(sb, partition);
		block = first_block + (sizeof(struct spaceBitmapDesc) << 3);
		block_group = block >> (sb->s_blocksize_bits + 3);
		group_start = block_group ? 0 : sizeof(struct spaceBitmapDesc);

		bitmap_nr = load_block_bitmap(sb, bitmap, block_group);
		if (bitmap_nr < 0)
			goto out;
		bh = bitmap->s_block_bitmap[bitmap_nr];

		bit = block % (sb->s_blocksize << 3);

		while (bit < (sb->s_blocksize << 3) && block_count > 0) {
			if (!udf_test_bit(bit, bh->b_data))
				goto out;
			else if (vfs_dq_prealloc_block(inode, 1))
				goto out;
			else if (!udf_clear_bit(bit, bh->b_data)) {
				udf_debug("bit already cleared for block %d\n", bit);
				vfs_dq_free_block(inode, 1);
				goto out;
			}
			block_count--;
			alloc_count++;
			bit++;
			block++;
		}
		mark_buffer_dirty(bh);
	} while (block_count > 0);

out:
	udf_add_free_space(sb, partition, -alloc_count);
	mutex_unlock(&sbi->s_alloc_mutex);
	return alloc_count;
}