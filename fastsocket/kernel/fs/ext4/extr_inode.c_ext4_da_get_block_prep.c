#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct inode {int i_blkbits; TYPE_1__* i_sb; } ;
struct buffer_head {int b_size; } ;
typedef  int /*<<< orphan*/  sector_t ;
struct TYPE_5__ {int /*<<< orphan*/  s_es; } ;
struct TYPE_4__ {int s_blocksize; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 TYPE_2__* EXT4_SB (TYPE_1__*) ; 
 int /*<<< orphan*/  buffer_delay (struct buffer_head*) ; 
 scalar_t__ buffer_unwritten (struct buffer_head*) ; 
 int /*<<< orphan*/  ext4_blocks_count (int /*<<< orphan*/ ) ; 
 int ext4_da_reserve_space (struct inode*,int /*<<< orphan*/ ) ; 
 int ext4_get_blocks (int /*<<< orphan*/ *,struct inode*,int /*<<< orphan*/ ,int,struct buffer_head*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  map_bh (struct buffer_head*,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_buffer_delay (struct buffer_head*) ; 
 int /*<<< orphan*/  set_buffer_mapped (struct buffer_head*) ; 
 int /*<<< orphan*/  set_buffer_new (struct buffer_head*) ; 

__attribute__((used)) static int ext4_da_get_block_prep(struct inode *inode, sector_t iblock,
				  struct buffer_head *bh_result, int create)
{
	int ret = 0;
	sector_t invalid_block = ~((sector_t) 0xffff);

	if (invalid_block < ext4_blocks_count(EXT4_SB(inode->i_sb)->s_es))
		invalid_block = ~0;

	BUG_ON(create == 0);
	BUG_ON(bh_result->b_size != inode->i_sb->s_blocksize);

	/*
	 * first, we need to know whether the block is allocated already
	 * preallocated blocks are unmapped but should treated
	 * the same as allocated blocks.
	 */
	ret = ext4_get_blocks(NULL, inode, iblock, 1,  bh_result, 0);
	if ((ret == 0) && !buffer_delay(bh_result)) {
		/* the block isn't (pre)allocated yet, let's reserve space */
		/*
		 * XXX: __block_prepare_write() unmaps passed block,
		 * is it OK?
		 */
		ret = ext4_da_reserve_space(inode, iblock);
		if (ret)
			/* not enough space to reserve */
			return ret;

		map_bh(bh_result, inode->i_sb, invalid_block);
		set_buffer_new(bh_result);
		set_buffer_delay(bh_result);
	} else if (ret > 0) {
		bh_result->b_size = (ret << inode->i_blkbits);
		if (buffer_unwritten(bh_result)) {
			/* A delayed write to unwritten bh should
			 * be marked new and mapped.  Mapped ensures
			 * that we don't do get_block multiple times
			 * when we write to the same offset and new
			 * ensures that we do proper zero out for
			 * partial write.
			 */
			set_buffer_new(bh_result);
			set_buffer_mapped(bh_result);
		}
		ret = 0;
	}

	return ret;
}