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
struct inode {unsigned int i_blkbits; int /*<<< orphan*/  i_sb; } ;
struct buffer_head {unsigned int b_size; } ;
typedef  int /*<<< orphan*/  sector_t ;
typedef  int /*<<< orphan*/  handle_t ;

/* Variables and functions */
 scalar_t__ DIO_CREDITS ; 
 unsigned int DIO_MAX_BLOCKS ; 
 int EXT3_QUOTA_TRANS_BLOCKS (int /*<<< orphan*/ ) ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ *) ; 
 int PTR_ERR (int /*<<< orphan*/ *) ; 
 int ext3_get_blocks_handle (int /*<<< orphan*/ *,struct inode*,int /*<<< orphan*/ ,unsigned int,struct buffer_head*,int) ; 
 int /*<<< orphan*/ * ext3_journal_current_handle () ; 
 int /*<<< orphan*/ * ext3_journal_start (struct inode*,scalar_t__) ; 
 int /*<<< orphan*/  ext3_journal_stop (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ext3_get_block(struct inode *inode, sector_t iblock,
			struct buffer_head *bh_result, int create)
{
	handle_t *handle = ext3_journal_current_handle();
	int ret = 0, started = 0;
	unsigned max_blocks = bh_result->b_size >> inode->i_blkbits;

	if (create && !handle) {	/* Direct IO write... */
		if (max_blocks > DIO_MAX_BLOCKS)
			max_blocks = DIO_MAX_BLOCKS;
		handle = ext3_journal_start(inode, DIO_CREDITS +
				2 * EXT3_QUOTA_TRANS_BLOCKS(inode->i_sb));
		if (IS_ERR(handle)) {
			ret = PTR_ERR(handle);
			goto out;
		}
		started = 1;
	}

	ret = ext3_get_blocks_handle(handle, inode, iblock,
					max_blocks, bh_result, create);
	if (ret > 0) {
		bh_result->b_size = (ret << inode->i_blkbits);
		ret = 0;
	}
	if (started)
		ext3_journal_stop(handle);
out:
	return ret;
}