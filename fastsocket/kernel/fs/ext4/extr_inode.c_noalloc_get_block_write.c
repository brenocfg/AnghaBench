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
struct inode {unsigned int i_blkbits; TYPE_1__* i_sb; } ;
struct buffer_head {unsigned int b_size; } ;
typedef  int /*<<< orphan*/  sector_t ;
struct TYPE_2__ {unsigned int s_blocksize; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int ext4_get_blocks (int /*<<< orphan*/ *,struct inode*,int /*<<< orphan*/ ,unsigned int,struct buffer_head*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int noalloc_get_block_write(struct inode *inode, sector_t iblock,
				   struct buffer_head *bh_result, int create)
{
	int ret = 0;
	unsigned max_blocks = bh_result->b_size >> inode->i_blkbits;

	BUG_ON(bh_result->b_size != inode->i_sb->s_blocksize);

	/*
	 * we don't want to do block allocation in writepage
	 * so call get_block_wrap with create = 0
	 */
	ret = ext4_get_blocks(NULL, inode, iblock, max_blocks, bh_result, 0);
	if (ret > 0) {
		bh_result->b_size = (ret << inode->i_blkbits);
		ret = 0;
	}
	return ret;
}