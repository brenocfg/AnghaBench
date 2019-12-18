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
struct inode {int i_size; TYPE_1__* i_sb; int /*<<< orphan*/  i_ino; } ;
struct ext4_extent_header {int dummy; } ;
struct ext4_extent {void* ee_len; void* ee_block; } ;
struct ext4_ext_path {struct ext4_extent* p_ext; struct ext4_extent_header* p_hdr; } ;
typedef  int /*<<< orphan*/  handle_t ;
typedef  unsigned int ext4_lblk_t ;
typedef  scalar_t__ ext4_fsblk_t ;
struct TYPE_2__ {int s_blocksize; int s_blocksize_bits; } ;

/* Variables and functions */
 int ENOSPC ; 
 int EXT4_EXT_ZERO_LEN ; 
 struct ext4_extent* EXT_FIRST_EXTENT (struct ext4_extent_header*) ; 
 scalar_t__ IS_ERR (struct ext4_ext_path*) ; 
 int PTR_ERR (struct ext4_ext_path*) ; 
 void* cpu_to_le16 (unsigned int) ; 
 void* cpu_to_le32 (unsigned int) ; 
 int ext4_ext_correct_indexes (int /*<<< orphan*/ *,struct inode*,struct ext4_ext_path*) ; 
 int ext4_ext_dirty (int /*<<< orphan*/ *,struct inode*,struct ext4_ext_path*) ; 
 int /*<<< orphan*/  ext4_ext_drop_refs (struct ext4_ext_path*) ; 
 struct ext4_ext_path* ext4_ext_find_extent (struct inode*,unsigned int,struct ext4_ext_path*) ; 
 int ext4_ext_get_access (int /*<<< orphan*/ *,struct inode*,struct ext4_ext_path*) ; 
 unsigned int ext4_ext_get_actual_len (struct ext4_extent*) ; 
 int ext4_ext_insert_extent (int /*<<< orphan*/ *,struct inode*,struct ext4_ext_path*,struct ext4_extent*,int) ; 
 int /*<<< orphan*/  ext4_ext_mark_uninitialized (struct ext4_extent*) ; 
 scalar_t__ ext4_ext_pblock (struct ext4_extent*) ; 
 int /*<<< orphan*/  ext4_ext_show_leaf (struct inode*,struct ext4_ext_path*) ; 
 int /*<<< orphan*/  ext4_ext_store_pblock (struct ext4_extent*,scalar_t__) ; 
 int ext4_ext_try_to_merge (struct inode*,struct ext4_ext_path*,struct ext4_extent*) ; 
 int ext4_ext_zeroout (struct inode*,struct ext4_extent*) ; 
 int /*<<< orphan*/  ext_debug (char*,int /*<<< orphan*/ ,unsigned long long,unsigned int) ; 
 unsigned int ext_depth (struct inode*) ; 
 int le16_to_cpu (void*) ; 
 unsigned int le32_to_cpu (void*) ; 

__attribute__((used)) static int ext4_ext_convert_to_initialized(handle_t *handle,
						struct inode *inode,
						struct ext4_ext_path *path,
						ext4_lblk_t iblock,
						unsigned int max_blocks,
						int flags)
{
	struct ext4_extent *ex, newex, orig_ex;
	struct ext4_extent *ex1 = NULL;
	struct ext4_extent *ex2 = NULL;
	struct ext4_extent *ex3 = NULL;
	struct ext4_extent_header *eh;
	ext4_lblk_t ee_block, eof_block;
	unsigned int allocated, ee_len, depth;
	ext4_fsblk_t newblock;
	int err = 0;
	int ret = 0;
	int may_zeroout;

	ext_debug("ext4_ext_convert_to_initialized: inode %lu, logical"
		"block %llu, max_blocks %u\n", inode->i_ino,
		(unsigned long long)iblock, max_blocks);

	eof_block = (inode->i_size + inode->i_sb->s_blocksize - 1) >>
		inode->i_sb->s_blocksize_bits;
	if (eof_block < iblock + max_blocks)
		eof_block = iblock + max_blocks;

	depth = ext_depth(inode);
	eh = path[depth].p_hdr;
	ex = path[depth].p_ext;
	ee_block = le32_to_cpu(ex->ee_block);
	ee_len = ext4_ext_get_actual_len(ex);
	allocated = ee_len - (iblock - ee_block);
	newblock = iblock - ee_block + ext4_ext_pblock(ex);

	ex2 = ex;
	orig_ex.ee_block = ex->ee_block;
	orig_ex.ee_len   = cpu_to_le16(ee_len);
	ext4_ext_store_pblock(&orig_ex, ext4_ext_pblock(ex));

	/*
	 * It is safe to convert extent to initialized via explicit
	 * zeroout only if extent is fully insde i_size or new_size.
	 */
	may_zeroout = ee_block + ee_len <= eof_block;

	err = ext4_ext_get_access(handle, inode, path + depth);
	if (err)
		goto out;
	/* If extent has less than 2*EXT4_EXT_ZERO_LEN zerout directly */
	if (ee_len <= 2*EXT4_EXT_ZERO_LEN && may_zeroout) {
		err =  ext4_ext_zeroout(inode, &orig_ex);
		if (err)
			goto fix_extent_len;
		/* update the extent length and mark as initialized */
		ex->ee_block = orig_ex.ee_block;
		ex->ee_len   = orig_ex.ee_len;
		ext4_ext_store_pblock(ex, ext4_ext_pblock(&orig_ex));
		ext4_ext_dirty(handle, inode, path + depth);
		/* zeroed the full extent */
		return allocated;
	}

	/* ex1: ee_block to iblock - 1 : uninitialized */
	if (iblock > ee_block) {
		ex1 = ex;
		ex1->ee_len = cpu_to_le16(iblock - ee_block);
		ext4_ext_mark_uninitialized(ex1);
		ext4_ext_dirty(handle, inode, path + depth);
		ex2 = &newex;
	}
	/*
	 * for sanity, update the length of the ex2 extent before
	 * we insert ex3, if ex1 is NULL. This is to avoid temporary
	 * overlap of blocks.
	 */
	if (!ex1 && allocated > max_blocks)
		ex2->ee_len = cpu_to_le16(max_blocks);
	/* ex3: to ee_block + ee_len : uninitialised */
	if (allocated > max_blocks) {
		unsigned int newdepth;
		/* If extent has less than EXT4_EXT_ZERO_LEN zerout directly */
		if (allocated <= EXT4_EXT_ZERO_LEN && may_zeroout) {
			/*
			 * iblock == ee_block is handled by the zerouout
			 * at the beginning.
			 * Mark first half uninitialized.
			 * Mark second half initialized and zero out the
			 * initialized extent
			 */
			ex->ee_block = orig_ex.ee_block;
			ex->ee_len   = cpu_to_le16(ee_len - allocated);
			ext4_ext_mark_uninitialized(ex);
			ext4_ext_store_pblock(ex, ext4_ext_pblock(&orig_ex));
			ext4_ext_dirty(handle, inode, path + depth);

			ex3 = &newex;
			ex3->ee_block = cpu_to_le32(iblock);
			ext4_ext_store_pblock(ex3, newblock);
			ex3->ee_len = cpu_to_le16(allocated);
			err = ext4_ext_insert_extent(handle, inode, path,
							ex3, 0);
			if (err == -ENOSPC) {
				err =  ext4_ext_zeroout(inode, &orig_ex);
				if (err)
					goto fix_extent_len;
				ex->ee_block = orig_ex.ee_block;
				ex->ee_len   = orig_ex.ee_len;
				ext4_ext_store_pblock(ex,
					ext4_ext_pblock(&orig_ex));
				ext4_ext_dirty(handle, inode, path + depth);
				/* blocks available from iblock */
				return allocated;

			} else if (err)
				goto fix_extent_len;

			/*
			 * We need to zero out the second half because
			 * an fallocate request can update file size and
			 * converting the second half to initialized extent
			 * implies that we can leak some junk data to user
			 * space.
			 */
			err =  ext4_ext_zeroout(inode, ex3);
			if (err) {
				/*
				 * We should actually mark the
				 * second half as uninit and return error
				 * Insert would have changed the extent
				 */
				depth = ext_depth(inode);
				ext4_ext_drop_refs(path);
				path = ext4_ext_find_extent(inode,
								iblock, path);
				if (IS_ERR(path)) {
					err = PTR_ERR(path);
					return err;
				}
				/* get the second half extent details */
				ex = path[depth].p_ext;
				err = ext4_ext_get_access(handle, inode,
								path + depth);
				if (err)
					return err;
				ext4_ext_mark_uninitialized(ex);
				ext4_ext_dirty(handle, inode, path + depth);
				return err;
			}

			/* zeroed the second half */
			return allocated;
		}
		ex3 = &newex;
		ex3->ee_block = cpu_to_le32(iblock + max_blocks);
		ext4_ext_store_pblock(ex3, newblock + max_blocks);
		ex3->ee_len = cpu_to_le16(allocated - max_blocks);
		ext4_ext_mark_uninitialized(ex3);
		err = ext4_ext_insert_extent(handle, inode, path, ex3, flags);
		if (err == -ENOSPC && may_zeroout) {
			err =  ext4_ext_zeroout(inode, &orig_ex);
			if (err)
				goto fix_extent_len;
			/* update the extent length and mark as initialized */
			ex->ee_block = orig_ex.ee_block;
			ex->ee_len   = orig_ex.ee_len;
			ext4_ext_store_pblock(ex, ext4_ext_pblock(&orig_ex));
			ext4_ext_dirty(handle, inode, path + depth);
			/* zeroed the full extent */
			/* blocks available from iblock */
			return allocated;

		} else if (err)
			goto fix_extent_len;
		/*
		 * The depth, and hence eh & ex might change
		 * as part of the insert above.
		 */
		newdepth = ext_depth(inode);
		/*
		 * update the extent length after successful insert of the
		 * split extent
		 */
		ee_len -= ext4_ext_get_actual_len(ex3);
		orig_ex.ee_len = cpu_to_le16(ee_len);
		may_zeroout = ee_block + ee_len <= eof_block;

		depth = newdepth;
		ext4_ext_drop_refs(path);
		path = ext4_ext_find_extent(inode, iblock, path);
		if (IS_ERR(path)) {
			err = PTR_ERR(path);
			goto out;
		}
		eh = path[depth].p_hdr;
		ex = path[depth].p_ext;
		if (ex2 != &newex)
			ex2 = ex;

		err = ext4_ext_get_access(handle, inode, path + depth);
		if (err)
			goto out;

		allocated = max_blocks;

		/* If extent has less than EXT4_EXT_ZERO_LEN and we are trying
		 * to insert a extent in the middle zerout directly
		 * otherwise give the extent a chance to merge to left
		 */
		if (le16_to_cpu(orig_ex.ee_len) <= EXT4_EXT_ZERO_LEN &&
			iblock != ee_block && may_zeroout) {
			err =  ext4_ext_zeroout(inode, &orig_ex);
			if (err)
				goto fix_extent_len;
			/* update the extent length and mark as initialized */
			ex->ee_block = orig_ex.ee_block;
			ex->ee_len   = orig_ex.ee_len;
			ext4_ext_store_pblock(ex, ext4_ext_pblock(&orig_ex));
			ext4_ext_dirty(handle, inode, path + depth);
			/* zero out the first half */
			/* blocks available from iblock */
			return allocated;
		}
	}
	/*
	 * If there was a change of depth as part of the
	 * insertion of ex3 above, we need to update the length
	 * of the ex1 extent again here
	 */
	if (ex1 && ex1 != ex) {
		ex1 = ex;
		ex1->ee_len = cpu_to_le16(iblock - ee_block);
		ext4_ext_mark_uninitialized(ex1);
		ext4_ext_dirty(handle, inode, path + depth);
		ex2 = &newex;
	}
	/* ex2: iblock to iblock + maxblocks-1 : initialised */
	ex2->ee_block = cpu_to_le32(iblock);
	ext4_ext_store_pblock(ex2, newblock);
	ex2->ee_len = cpu_to_le16(allocated);
	if (ex2 != ex)
		goto insert;
	/*
	 * New (initialized) extent starts from the first block
	 * in the current extent. i.e., ex2 == ex
	 * We have to see if it can be merged with the extent
	 * on the left.
	 */
	if (ex2 > EXT_FIRST_EXTENT(eh)) {
		/*
		 * To merge left, pass "ex2 - 1" to try_to_merge(),
		 * since it merges towards right _only_.
		 */
		ret = ext4_ext_try_to_merge(inode, path, ex2 - 1);
		if (ret) {
			err = ext4_ext_correct_indexes(handle, inode, path);
			if (err)
				goto out;
			depth = ext_depth(inode);
			ex2--;
		}
	}
	/*
	 * Try to Merge towards right. This might be required
	 * only when the whole extent is being written to.
	 * i.e. ex2 == ex and ex3 == NULL.
	 */
	if (!ex3) {
		ret = ext4_ext_try_to_merge(inode, path, ex2);
		if (ret) {
			err = ext4_ext_correct_indexes(handle, inode, path);
			if (err)
				goto out;
		}
	}
	/* Mark modified extent as dirty */
	err = ext4_ext_dirty(handle, inode, path + depth);
	goto out;
insert:
	err = ext4_ext_insert_extent(handle, inode, path, &newex, flags);
	if (err == -ENOSPC && may_zeroout) {
		err =  ext4_ext_zeroout(inode, &orig_ex);
		if (err)
			goto fix_extent_len;
		/* update the extent length and mark as initialized */
		ex->ee_block = orig_ex.ee_block;
		ex->ee_len   = orig_ex.ee_len;
		ext4_ext_store_pblock(ex, ext4_ext_pblock(&orig_ex));
		ext4_ext_dirty(handle, inode, path + depth);
		/* zero out the first half */
		return allocated;
	} else if (err)
		goto fix_extent_len;
out:
	ext4_ext_show_leaf(inode, path);
	return err ? err : allocated;

fix_extent_len:
	ex->ee_block = orig_ex.ee_block;
	ex->ee_len   = orig_ex.ee_len;
	ext4_ext_store_pblock(ex, ext4_ext_pblock(&orig_ex));
	ext4_ext_mark_uninitialized(ex);
	ext4_ext_dirty(handle, inode, path + depth);
	return err;
}