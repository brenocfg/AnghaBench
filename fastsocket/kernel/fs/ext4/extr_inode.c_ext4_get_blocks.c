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
struct inode {int /*<<< orphan*/  i_ino; } ;
struct buffer_head {int /*<<< orphan*/  b_blocknr; } ;
typedef  scalar_t__ sector_t ;
typedef  int /*<<< orphan*/  handle_t ;
struct TYPE_2__ {int i_delalloc_reserved_flag; int /*<<< orphan*/  i_data_sem; } ;

/* Variables and functions */
 int EXT4_GET_BLOCKS_CREATE ; 
 int EXT4_GET_BLOCKS_DELALLOC_RESERVE ; 
 TYPE_1__* EXT4_I (struct inode*) ; 
 int /*<<< orphan*/  EXT4_INODE_EXTENTS ; 
 int /*<<< orphan*/  EXT4_STATE_EXT_MIGRATE ; 
 scalar_t__ buffer_mapped (struct buffer_head*) ; 
 scalar_t__ buffer_new (struct buffer_head*) ; 
 int check_block_validity (struct inode*,char*,scalar_t__,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  clear_buffer_mapped (struct buffer_head*) ; 
 int /*<<< orphan*/  clear_buffer_unwritten (struct buffer_head*) ; 
 int /*<<< orphan*/  down_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  down_write (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ext4_clear_inode_state (struct inode*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ext4_da_update_reserve_space (struct inode*,int,int) ; 
 int ext4_ext_get_blocks (int /*<<< orphan*/ *,struct inode*,scalar_t__,unsigned int,struct buffer_head*,int) ; 
 int ext4_ind_get_blocks (int /*<<< orphan*/ *,struct inode*,scalar_t__,unsigned int,struct buffer_head*,int) ; 
 scalar_t__ ext4_test_inode_flag (struct inode*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ext_debug (char*,int /*<<< orphan*/ ,int,unsigned int,unsigned long) ; 
 int /*<<< orphan*/  up_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  up_write (int /*<<< orphan*/ *) ; 

int ext4_get_blocks(handle_t *handle, struct inode *inode, sector_t block,
		    unsigned int max_blocks, struct buffer_head *bh,
		    int flags)
{
	int retval;

	clear_buffer_mapped(bh);
	clear_buffer_unwritten(bh);

	ext_debug("ext4_get_blocks(): inode %lu, flag %d, max_blocks %u,"
		  "logical block %lu\n", inode->i_ino, flags, max_blocks,
		  (unsigned long)block);
	/*
	 * Try to see if we can get the block without requesting a new
	 * file system block.
	 */
	down_read((&EXT4_I(inode)->i_data_sem));
	if (ext4_test_inode_flag(inode, EXT4_INODE_EXTENTS)) {
		retval =  ext4_ext_get_blocks(handle, inode, block, max_blocks,
				bh, 0);
	} else {
		retval = ext4_ind_get_blocks(handle, inode, block, max_blocks,
					     bh, 0);
	}
	up_read((&EXT4_I(inode)->i_data_sem));

	if (retval > 0 && buffer_mapped(bh)) {
		int ret = check_block_validity(inode, "file system corruption",
					       block, bh->b_blocknr, retval);
		if (ret != 0)
			return ret;
	}

	/* If it is only a block(s) look up */
	if ((flags & EXT4_GET_BLOCKS_CREATE) == 0)
		return retval;

	/*
	 * Returns if the blocks have already allocated
	 *
	 * Note that if blocks have been preallocated
	 * ext4_ext_get_block() returns th create = 0
	 * with buffer head unmapped.
	 */
	if (retval > 0 && buffer_mapped(bh))
		return retval;

	/*
	 * When we call get_blocks without the create flag, the
	 * BH_Unwritten flag could have gotten set if the blocks
	 * requested were part of a uninitialized extent.  We need to
	 * clear this flag now that we are committed to convert all or
	 * part of the uninitialized extent to be an initialized
	 * extent.  This is because we need to avoid the combination
	 * of BH_Unwritten and BH_Mapped flags being simultaneously
	 * set on the buffer_head.
	 */
	clear_buffer_unwritten(bh);

	/*
	 * New blocks allocate and/or writing to uninitialized extent
	 * will possibly result in updating i_data, so we take
	 * the write lock of i_data_sem, and call get_blocks()
	 * with create == 1 flag.
	 */
	down_write((&EXT4_I(inode)->i_data_sem));

	/*
	 * if the caller is from delayed allocation writeout path
	 * we have already reserved fs blocks for allocation
	 * let the underlying get_block() function know to
	 * avoid double accounting
	 */
	if (flags & EXT4_GET_BLOCKS_DELALLOC_RESERVE)
		EXT4_I(inode)->i_delalloc_reserved_flag = 1;
	/*
	 * We need to check for EXT4 here because migrate
	 * could have changed the inode type in between
	 */
	if (ext4_test_inode_flag(inode, EXT4_INODE_EXTENTS)) {
		retval =  ext4_ext_get_blocks(handle, inode, block, max_blocks,
					      bh, flags);
	} else {
		retval = ext4_ind_get_blocks(handle, inode, block,
					     max_blocks, bh, flags);

		if (retval > 0 && buffer_new(bh)) {
			/*
			 * We allocated new blocks which will result in
			 * i_data's format changing.  Force the migrate
			 * to fail by clearing migrate flags
			 */
			ext4_clear_inode_state(inode, EXT4_STATE_EXT_MIGRATE);
		}

		/*
		 * Update reserved blocks/metadata blocks after successful
		 * block allocation which had been deferred till now. We don't
		 * support fallocate for non extent files. So we can update
		 * reserve space here.
		 */
		if ((retval > 0) &&
			(flags & EXT4_GET_BLOCKS_DELALLOC_RESERVE))
			ext4_da_update_reserve_space(inode, retval, 1);
	}
	if (flags & EXT4_GET_BLOCKS_DELALLOC_RESERVE)
		EXT4_I(inode)->i_delalloc_reserved_flag = 0;

	up_write((&EXT4_I(inode)->i_data_sem));
	if (retval > 0 && buffer_mapped(bh)) {
		int ret = check_block_validity(inode, "file system "
					       "corruption after allocation",
					       block, bh->b_blocknr, retval);
		if (ret != 0)
			return ret;
	}
	return retval;
}