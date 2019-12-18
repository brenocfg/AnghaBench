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
struct inode {unsigned int i_blkbits; } ;
struct buffer_head {unsigned int b_size; } ;
typedef  int /*<<< orphan*/  sector_t ;
typedef  int /*<<< orphan*/  handle_t ;

/* Variables and functions */
 unsigned int DIO_MAX_BLOCKS ; 
 int /*<<< orphan*/  EXT4_GET_BLOCKS_CREATE ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ *) ; 
 int PTR_ERR (int /*<<< orphan*/ *) ; 
 int ext4_chunk_trans_blocks (struct inode*,unsigned int) ; 
 int ext4_get_blocks (int /*<<< orphan*/ *,struct inode*,int /*<<< orphan*/ ,unsigned int,struct buffer_head*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * ext4_journal_current_handle () ; 
 int /*<<< orphan*/ * ext4_journal_start (struct inode*,int) ; 
 int /*<<< orphan*/  ext4_journal_stop (int /*<<< orphan*/ *) ; 

int ext4_get_block(struct inode *inode, sector_t iblock,
		   struct buffer_head *bh_result, int create)
{
	handle_t *handle = ext4_journal_current_handle();
	int ret = 0, started = 0;
	unsigned max_blocks = bh_result->b_size >> inode->i_blkbits;
	int dio_credits;

	if (create && !handle) {
		/* Direct IO write... */
		if (max_blocks > DIO_MAX_BLOCKS)
			max_blocks = DIO_MAX_BLOCKS;
		dio_credits = ext4_chunk_trans_blocks(inode, max_blocks);
		handle = ext4_journal_start(inode, dio_credits);
		if (IS_ERR(handle)) {
			ret = PTR_ERR(handle);
			goto out;
		}
		started = 1;
	}

	ret = ext4_get_blocks(handle, inode, iblock, max_blocks, bh_result,
			      create ? EXT4_GET_BLOCKS_CREATE : 0);
	if (ret > 0) {
		bh_result->b_size = (ret << inode->i_blkbits);
		ret = 0;
	}
	if (started)
		ext4_journal_stop(handle);
out:
	return ret;
}