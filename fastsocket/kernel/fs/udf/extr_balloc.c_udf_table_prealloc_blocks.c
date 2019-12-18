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
typedef  int uint32_t ;
typedef  size_t uint16_t ;
struct unallocSpaceEntry {int dummy; } ;
struct udf_sb_info {int /*<<< orphan*/  s_alloc_mutex; TYPE_1__* s_partmaps; } ;
struct udf_inode_info {scalar_t__ i_alloc_type; int /*<<< orphan*/  i_location; } ;
struct super_block {int s_blocksize_bits; } ;
struct short_ad {int dummy; } ;
struct long_ad {int dummy; } ;
struct kernel_lb_addr {int logicalBlockNum; } ;
struct inode {int dummy; } ;
struct extent_position {int offset; int /*<<< orphan*/ * bh; int /*<<< orphan*/  block; } ;
typedef  int int8_t ;
struct TYPE_2__ {int s_partition_len; } ;

/* Variables and functions */
 scalar_t__ ICBTAG_FLAG_AD_LONG ; 
 scalar_t__ ICBTAG_FLAG_AD_SHORT ; 
 struct udf_inode_info* UDF_I (struct inode*) ; 
 struct udf_sb_info* UDF_SB (struct super_block*) ; 
 int /*<<< orphan*/  brelse (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  udf_add_free_space (struct super_block*,size_t,int) ; 
 int /*<<< orphan*/  udf_debug (char*,int,int,int) ; 
 int /*<<< orphan*/  udf_delete_aext (struct inode*,struct extent_position,struct kernel_lb_addr,int) ; 
 int udf_next_aext (struct inode*,struct extent_position*,struct kernel_lb_addr*,int*,int) ; 
 int /*<<< orphan*/  udf_write_aext (struct inode*,struct extent_position*,struct kernel_lb_addr*,int,int) ; 
 scalar_t__ vfs_dq_prealloc_block (struct inode*,int) ; 

__attribute__((used)) static int udf_table_prealloc_blocks(struct super_block *sb,
				     struct inode *inode,
				     struct inode *table, uint16_t partition,
				     uint32_t first_block, uint32_t block_count)
{
	struct udf_sb_info *sbi = UDF_SB(sb);
	int alloc_count = 0;
	uint32_t elen, adsize;
	struct kernel_lb_addr eloc;
	struct extent_position epos;
	int8_t etype = -1;
	struct udf_inode_info *iinfo;

	if (first_block >= sbi->s_partmaps[partition].s_partition_len)
		return 0;

	iinfo = UDF_I(table);
	if (iinfo->i_alloc_type == ICBTAG_FLAG_AD_SHORT)
		adsize = sizeof(struct short_ad);
	else if (iinfo->i_alloc_type == ICBTAG_FLAG_AD_LONG)
		adsize = sizeof(struct long_ad);
	else
		return 0;

	mutex_lock(&sbi->s_alloc_mutex);
	epos.offset = sizeof(struct unallocSpaceEntry);
	epos.block = iinfo->i_location;
	epos.bh = NULL;
	eloc.logicalBlockNum = 0xFFFFFFFF;

	while (first_block != eloc.logicalBlockNum &&
	       (etype = udf_next_aext(table, &epos, &eloc, &elen, 1)) != -1) {
		udf_debug("eloc=%d, elen=%d, first_block=%d\n",
			  eloc.logicalBlockNum, elen, first_block);
		; /* empty loop body */
	}

	if (first_block == eloc.logicalBlockNum) {
		epos.offset -= adsize;

		alloc_count = (elen >> sb->s_blocksize_bits);
		if (inode && vfs_dq_prealloc_block(inode,
			alloc_count > block_count ? block_count : alloc_count))
			alloc_count = 0;
		else if (alloc_count > block_count) {
			alloc_count = block_count;
			eloc.logicalBlockNum += alloc_count;
			elen -= (alloc_count << sb->s_blocksize_bits);
			udf_write_aext(table, &epos, &eloc,
					(etype << 30) | elen, 1);
		} else
			udf_delete_aext(table, epos, eloc,
					(etype << 30) | elen);
	} else {
		alloc_count = 0;
	}

	brelse(epos.bh);

	if (alloc_count)
		udf_add_free_space(sb, partition, -alloc_count);
	mutex_unlock(&sbi->s_alloc_mutex);
	return alloc_count;
}