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
struct inode {unsigned int i_blkbits; int /*<<< orphan*/  i_ino; } ;
struct buffer_head {unsigned int b_size; } ;
typedef  int /*<<< orphan*/  sector_t ;
typedef  int /*<<< orphan*/  handle_t ;

/* Variables and functions */
 unsigned int DIO_MAX_BLOCKS ; 
 int EXT4_GET_BLOCKS_DIO_CREATE_EXT ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ *) ; 
 int PTR_ERR (int /*<<< orphan*/ *) ; 
 int ext4_chunk_trans_blocks (struct inode*,unsigned int) ; 
 int /*<<< orphan*/  ext4_debug (char*,int /*<<< orphan*/ ,int) ; 
 int ext4_get_blocks (int /*<<< orphan*/ *,struct inode*,int /*<<< orphan*/ ,unsigned int,struct buffer_head*,int) ; 
 int /*<<< orphan*/ * ext4_journal_start (struct inode*,int) ; 
 int /*<<< orphan*/  ext4_journal_stop (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ext4_get_block_dio_write(struct inode *inode, sector_t iblock,
		   struct buffer_head *bh_result, int create)
{
	handle_t *handle = NULL;
	int ret = 0;
	unsigned max_blocks = bh_result->b_size >> inode->i_blkbits;
	int dio_credits;

	ext4_debug("ext4_get_block_dio_write: inode %lu, create flag %d\n",
		   inode->i_ino, create);
	/*
	 * DIO VFS code passes create = 0 flag for write to
	 * the middle of file. It does this to avoid block
	 * allocation for holes, to prevent expose stale data
	 * out when there is parallel buffered read (which does
	 * not hold the i_mutex lock) while direct IO write has
	 * not completed. DIO request on holes finally falls back
	 * to buffered IO for this reason.
	 *
	 * For ext4 extent based file, since we support fallocate,
	 * new allocated extent as uninitialized, for holes, we
	 * could fallocate blocks for holes, thus parallel
	 * buffered IO read will zero out the page when read on
	 * a hole while parallel DIO write to the hole has not completed.
	 *
	 * when we come here, we know it's a direct IO write to
	 * to the middle of file (<i_size)
	 * so it's safe to override the create flag from VFS.
	 */
	create = EXT4_GET_BLOCKS_DIO_CREATE_EXT;

	if (max_blocks > DIO_MAX_BLOCKS)
		max_blocks = DIO_MAX_BLOCKS;
	dio_credits = ext4_chunk_trans_blocks(inode, max_blocks);
	handle = ext4_journal_start(inode, dio_credits);
	if (IS_ERR(handle)) {
		ret = PTR_ERR(handle);
		goto out;
	}
	ret = ext4_get_blocks(handle, inode, iblock, max_blocks, bh_result,
			      create);
	if (ret > 0) {
		bh_result->b_size = (ret << inode->i_blkbits);
		ret = 0;
	}
	ext4_journal_stop(handle);
out:
	return ret;
}