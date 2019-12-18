#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct inode {TYPE_1__* i_sb; int /*<<< orphan*/  i_ino; } ;
struct ext4_ext_path {int dummy; } ;
struct buffer_head {scalar_t__ b_blocknr; int /*<<< orphan*/  b_bdev; } ;
typedef  int /*<<< orphan*/  handle_t ;
typedef  scalar_t__ ext4_lblk_t ;
struct TYPE_5__ {scalar_t__ flag; } ;
typedef  TYPE_2__ ext4_io_end_t ;
typedef  scalar_t__ ext4_fsblk_t ;
struct TYPE_6__ {int /*<<< orphan*/  i_aiodio_unwritten; TYPE_2__* cur_aio_dio; } ;
struct TYPE_4__ {int /*<<< orphan*/  s_bdev; } ;

/* Variables and functions */
 scalar_t__ DIO_AIO_UNWRITTEN ; 
 int EXT4_GET_BLOCKS_CREATE ; 
 int EXT4_GET_BLOCKS_DELALLOC_RESERVE ; 
 int EXT4_GET_BLOCKS_DIO_CONVERT_EXT ; 
 int EXT4_GET_BLOCKS_DIO_CREATE_EXT ; 
 int EXT4_GET_BLOCKS_METADATA_NOFAIL ; 
 int EXT4_GET_BLOCKS_UNINIT_EXT ; 
 TYPE_3__* EXT4_I (struct inode*) ; 
 int /*<<< orphan*/  EXT4_STATE_DIO_UNWRITTEN ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int check_eofblocks_fl (int /*<<< orphan*/ *,struct inode*,scalar_t__,struct ext4_ext_path*,unsigned int) ; 
 int ext4_convert_unwritten_extents_dio (int /*<<< orphan*/ *,struct inode*,scalar_t__,unsigned int,struct ext4_ext_path*) ; 
 int /*<<< orphan*/  ext4_da_update_reserve_space (struct inode*,unsigned int,int /*<<< orphan*/ ) ; 
 int ext4_ext_convert_to_initialized (int /*<<< orphan*/ *,struct inode*,struct ext4_ext_path*,scalar_t__,unsigned int,int) ; 
 int /*<<< orphan*/  ext4_ext_drop_refs (struct ext4_ext_path*) ; 
 int /*<<< orphan*/  ext4_ext_show_leaf (struct inode*,struct ext4_ext_path*) ; 
 int /*<<< orphan*/  ext4_set_inode_state (struct inode*,int /*<<< orphan*/ ) ; 
 int ext4_split_unwritten_extents (int /*<<< orphan*/ *,struct inode*,struct ext4_ext_path*,scalar_t__,unsigned int,int) ; 
 int /*<<< orphan*/  ext4_update_inode_fsync_trans (int /*<<< orphan*/ *,struct inode*,int) ; 
 int /*<<< orphan*/  ext_debug (char*,int /*<<< orphan*/ ,unsigned long long,unsigned int,int,unsigned int) ; 
 int /*<<< orphan*/  kfree (struct ext4_ext_path*) ; 
 int /*<<< orphan*/  set_buffer_mapped (struct buffer_head*) ; 
 int /*<<< orphan*/  set_buffer_new (struct buffer_head*) ; 
 int /*<<< orphan*/  set_buffer_unwritten (struct buffer_head*) ; 
 int /*<<< orphan*/  unmap_underlying_metadata_blocks (int /*<<< orphan*/ ,scalar_t__,unsigned int) ; 

__attribute__((used)) static int
ext4_ext_handle_uninitialized_extents(handle_t *handle, struct inode *inode,
			ext4_lblk_t iblock, unsigned int max_blocks,
			struct ext4_ext_path *path, int flags,
			unsigned int allocated, struct buffer_head *bh_result,
			ext4_fsblk_t newblock)
{
	int ret = 0;
	int err = 0;
	ext4_io_end_t *io = EXT4_I(inode)->cur_aio_dio;

	ext_debug("ext4_ext_handle_uninitialized_extents: inode %lu, logical"
		  "block %llu, max_blocks %u, flags %d, allocated %u",
		  inode->i_ino, (unsigned long long)iblock, max_blocks,
		  flags, allocated);
	ext4_ext_show_leaf(inode, path);

	/*
	 * When writing into uninitialized space, we should not fail to
	 * allocate metadata blocks for the new extent block if needed.
	 */
	flags |= EXT4_GET_BLOCKS_METADATA_NOFAIL;

	/* DIO get_block() before submit the IO, split the extent */
	if ((flags & ~EXT4_GET_BLOCKS_METADATA_NOFAIL) ==
	    EXT4_GET_BLOCKS_DIO_CREATE_EXT) {
		ret = ext4_split_unwritten_extents(handle,
						inode, path, iblock,
						max_blocks, flags);
		/*
		 * Flag the inode(non aio case) or end_io struct (aio case)
		 * that this IO needs to convertion to written when IO is
		 * completed
		 */
		if (io && (io->flag != DIO_AIO_UNWRITTEN)) {
			io->flag = DIO_AIO_UNWRITTEN;
			atomic_inc(&EXT4_I(inode)->i_aiodio_unwritten);
		} else
			ext4_set_inode_state(inode, EXT4_STATE_DIO_UNWRITTEN);
		goto out;
	}
	/* async DIO end_io complete, convert the filled extent to written */
	if ((flags & ~EXT4_GET_BLOCKS_METADATA_NOFAIL) ==
	    EXT4_GET_BLOCKS_DIO_CONVERT_EXT) {
		ret = ext4_convert_unwritten_extents_dio(handle, inode,
							 iblock, max_blocks,
							 path);
		if (ret >= 0) {
			ext4_update_inode_fsync_trans(handle, inode, 1);
			err = check_eofblocks_fl(handle, inode, iblock, path,
						 max_blocks);
		} else
			err = ret;
		goto out2;
	}
	/* buffered IO case */
	/*
	 * repeat fallocate creation request
	 * we already have an unwritten extent
	 */
	if (flags & EXT4_GET_BLOCKS_UNINIT_EXT)
		goto map_out;

	/* buffered READ or buffered write_begin() lookup */
	if ((flags & EXT4_GET_BLOCKS_CREATE) == 0) {
		/*
		 * We have blocks reserved already.  We
		 * return allocated blocks so that delalloc
		 * won't do block reservation for us.  But
		 * the buffer head will be unmapped so that
		 * a read from the block returns 0s.
		 */
		set_buffer_unwritten(bh_result);
		goto out1;
	}

	/* buffered write, writepage time, convert*/
	ret = ext4_ext_convert_to_initialized(handle, inode,
						path, iblock,
						max_blocks,
						flags);
	if (ret >= 0) {
		ext4_update_inode_fsync_trans(handle, inode, 1);
		err = check_eofblocks_fl(handle, inode, iblock, path, max_blocks);
		if (err < 0)
			goto out2;
	}
out:
	if (ret <= 0) {
		err = ret;
		goto out2;
	} else
		allocated = ret;
	set_buffer_new(bh_result);
	/*
	 * if we allocated more blocks than requested
	 * we need to make sure we unmap the extra block
	 * allocated. The actual needed block will get
	 * unmapped later when we find the buffer_head marked
	 * new.
	 */
	if (allocated > max_blocks) {
		unmap_underlying_metadata_blocks(inode->i_sb->s_bdev,
					newblock + max_blocks,
					allocated - max_blocks);
		allocated = max_blocks;
	}

	/*
	 * If we have done fallocate with the offset that is already
	 * delayed allocated, we would have block reservation
	 * and quota reservation done in the delayed write path.
	 * But fallocate would have already updated quota and block
	 * count for this offset. So cancel these reservation
	 */
	if (flags & EXT4_GET_BLOCKS_DELALLOC_RESERVE)
		ext4_da_update_reserve_space(inode, allocated, 0);

map_out:
	set_buffer_mapped(bh_result);
out1:
	if (allocated > max_blocks)
		allocated = max_blocks;
	ext4_ext_show_leaf(inode, path);
	bh_result->b_bdev = inode->i_sb->s_bdev;
	bh_result->b_blocknr = newblock;
out2:
	if (path) {
		ext4_ext_drop_refs(path);
		kfree(path);
	}
	return err ? err : allocated;
}