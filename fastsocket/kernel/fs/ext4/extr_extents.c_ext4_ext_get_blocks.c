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
struct inode {unsigned int i_ino; TYPE_1__* i_sb; int /*<<< orphan*/  i_mode; } ;
struct ext4_extent_header {int dummy; } ;
struct ext4_extent {void* ee_len; int /*<<< orphan*/  ee_block; int /*<<< orphan*/  ee_start_hi; int /*<<< orphan*/  ee_start_lo; } ;
struct ext4_ext_path {struct ext4_extent* p_ext; struct ext4_extent_header* p_hdr; int /*<<< orphan*/  p_block; } ;
struct ext4_allocation_request {unsigned short lleft; unsigned short lright; unsigned short goal; unsigned short logical; unsigned int len; scalar_t__ flags; struct inode* inode; int /*<<< orphan*/  pright; int /*<<< orphan*/  pleft; } ;
struct buffer_head {unsigned int b_blocknr; int /*<<< orphan*/  b_bdev; int /*<<< orphan*/  b_state; } ;
typedef  int /*<<< orphan*/  handle_t ;
typedef  unsigned short ext4_lblk_t ;
struct TYPE_5__ {scalar_t__ flag; } ;
typedef  TYPE_2__ ext4_io_end_t ;
typedef  unsigned int ext4_fsblk_t ;
struct TYPE_6__ {int /*<<< orphan*/  i_aiodio_unwritten; TYPE_2__* cur_aio_dio; } ;
struct TYPE_4__ {int /*<<< orphan*/  s_bdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  BH_New ; 
 scalar_t__ DIO_AIO_UNWRITTEN ; 
 int EIO ; 
 int /*<<< orphan*/  EXT4_ERROR_INODE (struct inode*,char*,unsigned short,int,int /*<<< orphan*/ ) ; 
 int EXT4_FREE_BLOCKS_NO_QUOT_UPDATE ; 
 int EXT4_GET_BLOCKS_CREATE ; 
 int EXT4_GET_BLOCKS_DELALLOC_RESERVE ; 
 int EXT4_GET_BLOCKS_DIO_CREATE_EXT ; 
 int EXT4_GET_BLOCKS_METADATA_NOFAIL ; 
 int EXT4_GET_BLOCKS_UNINIT_EXT ; 
 TYPE_3__* EXT4_I (struct inode*) ; 
 scalar_t__ EXT4_MB_HINT_DATA ; 
 int /*<<< orphan*/  EXT4_STATE_DIO_UNWRITTEN ; 
 unsigned int EXT_INIT_MAX_LEN ; 
 unsigned int EXT_UNINIT_MAX_LEN ; 
 scalar_t__ IS_ERR (struct ext4_ext_path*) ; 
 int PTR_ERR (struct ext4_ext_path*) ; 
 scalar_t__ S_ISREG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int check_eofblocks_fl (int /*<<< orphan*/ *,struct inode*,unsigned short,struct ext4_ext_path*,unsigned int) ; 
 void* cpu_to_le16 (unsigned int) ; 
 int /*<<< orphan*/  cpu_to_le32 (unsigned short) ; 
 int /*<<< orphan*/  ext4_da_update_reserve_space (struct inode*,unsigned int,int) ; 
 int /*<<< orphan*/  ext4_discard_preallocations (struct inode*) ; 
 int ext4_ext_check_overlap (struct inode*,struct ext4_extent*,struct ext4_ext_path*) ; 
 int /*<<< orphan*/  ext4_ext_drop_refs (struct ext4_ext_path*) ; 
 struct ext4_ext_path* ext4_ext_find_extent (struct inode*,unsigned short,int /*<<< orphan*/ *) ; 
 unsigned short ext4_ext_find_goal (struct inode*,struct ext4_ext_path*,unsigned short) ; 
 void* ext4_ext_get_actual_len (struct ext4_extent*) ; 
 int ext4_ext_handle_uninitialized_extents (int /*<<< orphan*/ *,struct inode*,unsigned short,unsigned int,struct ext4_ext_path*,int,unsigned int,struct buffer_head*,unsigned int) ; 
 scalar_t__ ext4_ext_in_cache (struct inode*,unsigned short,struct ext4_extent*) ; 
 int ext4_ext_insert_extent (int /*<<< orphan*/ *,struct inode*,struct ext4_ext_path*,struct ext4_extent*,int) ; 
 int /*<<< orphan*/  ext4_ext_is_uninitialized (struct ext4_extent*) ; 
 int /*<<< orphan*/  ext4_ext_mark_uninitialized (struct ext4_extent*) ; 
 unsigned int ext4_ext_pblock (struct ext4_extent*) ; 
 int /*<<< orphan*/  ext4_ext_put_gap_in_cache (struct inode*,struct ext4_ext_path*,unsigned short) ; 
 int /*<<< orphan*/  ext4_ext_put_in_cache (struct inode*,unsigned short,unsigned int,unsigned int) ; 
 int ext4_ext_search_left (struct inode*,struct ext4_ext_path*,unsigned short*,int /*<<< orphan*/ *) ; 
 int ext4_ext_search_right (struct inode*,struct ext4_ext_path*,unsigned short*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ext4_ext_show_leaf (struct inode*,struct ext4_ext_path*) ; 
 int /*<<< orphan*/  ext4_ext_store_pblock (struct ext4_extent*,unsigned int) ; 
 int /*<<< orphan*/  ext4_free_blocks (int /*<<< orphan*/ *,struct inode*,unsigned int,void*,int) ; 
 unsigned int ext4_mb_new_blocks (int /*<<< orphan*/ *,struct ext4_allocation_request*,int*) ; 
 int /*<<< orphan*/  ext4_set_inode_state (struct inode*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ext4_update_inode_fsync_trans (int /*<<< orphan*/ *,struct inode*,int) ; 
 int /*<<< orphan*/  ext_debug (char*,unsigned short,unsigned int,unsigned int,...) ; 
 int ext_depth (struct inode*) ; 
 scalar_t__ in_range (unsigned short,unsigned short,unsigned short) ; 
 int /*<<< orphan*/  kfree (struct ext4_ext_path*) ; 
 unsigned short le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_buffer_mapped (struct buffer_head*) ; 
 int /*<<< orphan*/  set_buffer_new (struct buffer_head*) ; 
 scalar_t__ unlikely (int) ; 

int ext4_ext_get_blocks(handle_t *handle, struct inode *inode,
			ext4_lblk_t iblock,
			unsigned int max_blocks, struct buffer_head *bh_result,
			int flags)
{
	struct ext4_ext_path *path = NULL;
	struct ext4_extent_header *eh;
	struct ext4_extent newex, *ex;
	ext4_fsblk_t newblock;
	int err = 0, depth, ret;
	unsigned int allocated = 0;
	struct ext4_allocation_request ar;
	ext4_io_end_t *io = EXT4_I(inode)->cur_aio_dio;

	__clear_bit(BH_New, &bh_result->b_state);
	ext_debug("blocks %u/%u requested for inode %lu\n",
			iblock, max_blocks, inode->i_ino);

	/* check in cache */
	if (ext4_ext_in_cache(inode, iblock, &newex)) {
		if (!newex.ee_start_lo && !newex.ee_start_hi) {
			if ((flags & EXT4_GET_BLOCKS_CREATE) == 0) {
				/*
				 * block isn't allocated yet and
				 * user doesn't want to allocate it
				 */
				goto out2;
			}
			/* we should allocate requested block */
		} else {
			/* block is already allocated */
			newblock = iblock
				   - le32_to_cpu(newex.ee_block)
				   + ext4_ext_pblock(&newex);
			/* number of remaining blocks in the extent */
			allocated = ext4_ext_get_actual_len(&newex) -
					(iblock - le32_to_cpu(newex.ee_block));
			goto out;
		}
	}

	/* find extent for this block */
	path = ext4_ext_find_extent(inode, iblock, NULL);
	if (IS_ERR(path)) {
		err = PTR_ERR(path);
		path = NULL;
		goto out2;
	}

	depth = ext_depth(inode);

	/*
	 * consistent leaf must not be empty;
	 * this situation is possible, though, _during_ tree modification;
	 * this is why assert can't be put in ext4_ext_find_extent()
	 */
	if (unlikely(path[depth].p_ext == NULL && depth != 0)) {
		EXT4_ERROR_INODE(inode, "bad extent address "
				 "iblock: %d, depth: %d pblock %lld",
				 iblock, depth, path[depth].p_block);
		err = -EIO;
		goto out2;
	}
	eh = path[depth].p_hdr;

	ex = path[depth].p_ext;
	if (ex) {
		ext4_lblk_t ee_block = le32_to_cpu(ex->ee_block);
		ext4_fsblk_t ee_start = ext4_ext_pblock(ex);
		unsigned short ee_len;

		/*
		 * Uninitialized extents are treated as holes, except that
		 * we split out initialized portions during a write.
		 */
		ee_len = ext4_ext_get_actual_len(ex);
		/* if found extent covers block, simply return it */
		if (in_range(iblock, ee_block, ee_len)) {
			newblock = iblock - ee_block + ee_start;
			/* number of remaining blocks in the extent */
			allocated = ee_len - (iblock - ee_block);
			ext_debug("%u fit into %u:%d -> %llu\n", iblock,
					ee_block, ee_len, newblock);

			/*
			 * Do not put uninitialized extent
			 * in the cache
			 */
			if (!ext4_ext_is_uninitialized(ex)) {
				ext4_ext_put_in_cache(inode, ee_block,
					ee_len, ee_start);
				goto out;
			}
			ret = ext4_ext_handle_uninitialized_extents(
				handle, inode, iblock, max_blocks, path,
				flags, allocated, bh_result, newblock);
			return ret;
		}
	}

	/*
	 * requested block isn't allocated yet;
	 * we couldn't try to create block if create flag is zero
	 */
	if ((flags & EXT4_GET_BLOCKS_CREATE) == 0) {
		/*
		 * put just found gap into cache to speed up
		 * subsequent requests
		 */
		ext4_ext_put_gap_in_cache(inode, path, iblock);
		goto out2;
	}
	/*
	 * Okay, we need to do block allocation.
	 */

	/* find neighbour allocated blocks */
	ar.lleft = iblock;
	err = ext4_ext_search_left(inode, path, &ar.lleft, &ar.pleft);
	if (err)
		goto out2;
	ar.lright = iblock;
	err = ext4_ext_search_right(inode, path, &ar.lright, &ar.pright);
	if (err)
		goto out2;

	/*
	 * See if request is beyond maximum number of blocks we can have in
	 * a single extent. For an initialized extent this limit is
	 * EXT_INIT_MAX_LEN and for an uninitialized extent this limit is
	 * EXT_UNINIT_MAX_LEN.
	 */
	if (max_blocks > EXT_INIT_MAX_LEN &&
	    !(flags & EXT4_GET_BLOCKS_UNINIT_EXT))
		max_blocks = EXT_INIT_MAX_LEN;
	else if (max_blocks > EXT_UNINIT_MAX_LEN &&
		 (flags & EXT4_GET_BLOCKS_UNINIT_EXT))
		max_blocks = EXT_UNINIT_MAX_LEN;

	/* Check if we can really insert (iblock)::(iblock+max_blocks) extent */
	newex.ee_block = cpu_to_le32(iblock);
	newex.ee_len = cpu_to_le16(max_blocks);
	err = ext4_ext_check_overlap(inode, &newex, path);
	if (err)
		allocated = ext4_ext_get_actual_len(&newex);
	else
		allocated = max_blocks;

	/* allocate new block */
	ar.inode = inode;
	ar.goal = ext4_ext_find_goal(inode, path, iblock);
	ar.logical = iblock;
	ar.len = allocated;
	if (S_ISREG(inode->i_mode))
		ar.flags = EXT4_MB_HINT_DATA;
	else
		/* disable in-core preallocation for non-regular files */
		ar.flags = 0;
	newblock = ext4_mb_new_blocks(handle, &ar, &err);
	if (!newblock)
		goto out2;
	ext_debug("allocate new block: goal %llu, found %llu/%u\n",
		  ar.goal, newblock, allocated);

	/* try to insert new extent into found leaf and return */
	ext4_ext_store_pblock(&newex, newblock);
	newex.ee_len = cpu_to_le16(ar.len);
	/* Mark uninitialized */
	if (flags & EXT4_GET_BLOCKS_UNINIT_EXT){
		ext4_ext_mark_uninitialized(&newex);
		/*
		 * io_end structure was created for every async
		 * direct IO write to the middle of the file.
		 * To avoid unecessary convertion for every aio dio rewrite
		 * to the mid of file, here we flag the IO that is really
		 * need the convertion.
		 * For non asycn direct IO case, flag the inode state
		 * that we need to perform convertion when IO is done.
		 */
		if ((flags & ~EXT4_GET_BLOCKS_METADATA_NOFAIL) ==
		    EXT4_GET_BLOCKS_DIO_CREATE_EXT) {
			if (io && (io->flag != DIO_AIO_UNWRITTEN)) {
				io->flag = DIO_AIO_UNWRITTEN;
				atomic_inc(&EXT4_I(inode)->i_aiodio_unwritten);
			} else
				ext4_set_inode_state(inode,
						     EXT4_STATE_DIO_UNWRITTEN);
		}
	}

	err = check_eofblocks_fl(handle, inode, iblock, path, ar.len);
	if (err)
		goto out2;

	err = ext4_ext_insert_extent(handle, inode, path, &newex, flags);
	if (err) {
		int fb_flags = flags & EXT4_GET_BLOCKS_DELALLOC_RESERVE ?
			EXT4_FREE_BLOCKS_NO_QUOT_UPDATE : 0;
		/* free data blocks we just allocated */
		/* not a good idea to call discard here directly,
		 * but otherwise we'd need to call it every free() */
		ext4_discard_preallocations(inode);
		ext4_free_blocks(handle, inode, ext4_ext_pblock(&newex),
				 ext4_ext_get_actual_len(&newex), fb_flags);
		goto out2;
	}

	/* previous routine could use block we allocated */
	newblock = ext4_ext_pblock(&newex);
	allocated = ext4_ext_get_actual_len(&newex);
	if (allocated > max_blocks)
		allocated = max_blocks;
	set_buffer_new(bh_result);

	/*
	 * Update reserved blocks/metadata blocks after successful
	 * block allocation which had been deferred till now.
	 */
	if (flags & EXT4_GET_BLOCKS_DELALLOC_RESERVE)
		ext4_da_update_reserve_space(inode, allocated, 1);

	/*
	 * Cache the extent and update transaction to commit on fdatasync only
	 * when it is _not_ an uninitialized extent.
	 */
	if ((flags & EXT4_GET_BLOCKS_UNINIT_EXT) == 0) {
		ext4_ext_put_in_cache(inode, iblock, allocated, newblock);
		ext4_update_inode_fsync_trans(handle, inode, 1);
	} else
		ext4_update_inode_fsync_trans(handle, inode, 0);
out:
	if (allocated > max_blocks)
		allocated = max_blocks;
	ext4_ext_show_leaf(inode, path);
	set_buffer_mapped(bh_result);
	bh_result->b_bdev = inode->i_sb->s_bdev;
	bh_result->b_blocknr = newblock;
out2:
	if (path) {
		ext4_ext_drop_refs(path);
		kfree(path);
	}

	return err ? err : allocated;
}