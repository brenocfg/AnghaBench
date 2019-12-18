#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct super_block {int dummy; } ;
struct inode {struct super_block* i_sb; } ;
struct ext4_extent {int /*<<< orphan*/  ee_block; } ;
struct ext4_ext_path {int p_depth; TYPE_1__* p_hdr; struct buffer_head* p_bh; void* p_block; scalar_t__ p_idx; struct ext4_extent* p_ext; } ;
struct buffer_head {int dummy; } ;
typedef  struct ext4_ext_path handle_t ;
typedef  int ext4_lblk_t ;
struct TYPE_7__ {scalar_t__ eh_entries; int /*<<< orphan*/  eh_max; scalar_t__ eh_depth; } ;

/* Variables and functions */
 int EAGAIN ; 
 int EIO ; 
 int ENOMEM ; 
 int /*<<< orphan*/  EXT4_ERROR_INODE (struct inode*,char*,int) ; 
 int EXT4_EXT_MARK_UNINIT1 ; 
 int EXT4_EXT_MARK_UNINIT2 ; 
 int EXT4_GET_BLOCKS_DIO ; 
 int EXT4_GET_BLOCKS_METADATA_NOFAIL ; 
 int /*<<< orphan*/  EXT_FIRST_INDEX (TYPE_1__*) ; 
 scalar_t__ EXT_LAST_INDEX (TYPE_1__*) ; 
 int EXT_MAX_BLOCKS ; 
 int /*<<< orphan*/  GFP_NOFS ; 
 scalar_t__ IS_ERR (struct ext4_ext_path*) ; 
 int PTR_ERR (struct ext4_ext_path*) ; 
 scalar_t__ WARN_ON (int) ; 
 int /*<<< orphan*/  brelse (struct buffer_head*) ; 
 int /*<<< orphan*/  cpu_to_le16 (int /*<<< orphan*/ ) ; 
 scalar_t__ ext4_ext_check (struct inode*,TYPE_1__*,int) ; 
 scalar_t__ ext4_ext_check_block (struct inode*,TYPE_1__*,int,struct buffer_head*) ; 
 int ext4_ext_dirty (struct ext4_ext_path*,struct inode*,struct ext4_ext_path*) ; 
 int /*<<< orphan*/  ext4_ext_drop_refs (struct ext4_ext_path*) ; 
 struct ext4_ext_path* ext4_ext_find_extent (struct inode*,int,int /*<<< orphan*/ *) ; 
 int ext4_ext_get_access (struct ext4_ext_path*,struct inode*,struct ext4_ext_path*) ; 
 int ext4_ext_get_actual_len (struct ext4_extent*) ; 
 int /*<<< orphan*/  ext4_ext_invalidate_cache (struct inode*) ; 
 scalar_t__ ext4_ext_is_uninitialized (struct ext4_extent*) ; 
 scalar_t__ ext4_ext_more_to_rm (struct ext4_ext_path*) ; 
 int ext4_ext_rm_idx (struct ext4_ext_path*,struct inode*,struct ext4_ext_path*) ; 
 int ext4_ext_rm_leaf (struct ext4_ext_path*,struct inode*,struct ext4_ext_path*,int,int) ; 
 int /*<<< orphan*/  ext4_ext_space_root (struct inode*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ext4_idx_pblock (scalar_t__) ; 
 struct ext4_ext_path* ext4_journal_start (struct inode*,int) ; 
 int /*<<< orphan*/  ext4_journal_stop (struct ext4_ext_path*) ; 
 int ext4_split_extent_at (struct ext4_ext_path*,struct inode*,struct ext4_ext_path*,int,int,int) ; 
 TYPE_1__* ext_block_hdr (struct buffer_head*) ; 
 int /*<<< orphan*/  ext_debug (char*,...) ; 
 int ext_depth (struct inode*) ; 
 TYPE_1__* ext_inode_hdr (struct inode*) ; 
 int /*<<< orphan*/  kfree (struct ext4_ext_path*) ; 
 struct ext4_ext_path* kzalloc (int,int /*<<< orphan*/ ) ; 
 void* le16_to_cpu (scalar_t__) ; 
 int le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct ext4_ext_path*,int /*<<< orphan*/ ,int) ; 
 struct buffer_head* sb_bread (struct super_block*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ext4_ext_remove_space(struct inode *inode, ext4_lblk_t start,
				ext4_lblk_t end)
{
	struct super_block *sb = inode->i_sb;
	int depth = ext_depth(inode);
	struct ext4_ext_path *path = NULL;
	handle_t *handle;
	int i = 0, err = 0;

	ext_debug("truncate since %u to %u\n", start, end);

	/* probably first extent we're gonna free will be last in block */
	handle = ext4_journal_start(inode, depth + 1);
	if (IS_ERR(handle))
		return PTR_ERR(handle);

again:
	ext4_ext_invalidate_cache(inode);

	/*
	 * Check if we are removing extents inside the extent tree. If that
	 * is the case, we are going to punch a hole inside the extent tree
	 * so we have to check whether we need to split the extent covering
	 * the last block to remove so we can easily remove the part of it
	 * in ext4_ext_rm_leaf().
	 */
	if (end < EXT_MAX_BLOCKS - 1) {
		struct ext4_extent *ex;
		ext4_lblk_t ee_block;

		/* find extent for this block */
		path = ext4_ext_find_extent(inode, end, NULL);
		if (IS_ERR(path)) {
			ext4_journal_stop(handle);
			return PTR_ERR(path);
		}
		depth = ext_depth(inode);
		/* Leaf not may not exist only if inode has no blocks at all */
		ex = path[depth].p_ext;
		if (!ex) {
			if (depth) {
				EXT4_ERROR_INODE(inode,
						 "path[%d].p_hdr == NULL",
						 depth);
				err = -EIO;
			}
			goto out;
		}

		ee_block = le32_to_cpu(ex->ee_block);

		/*
		 * See if the last block is inside the extent, if so split
		 * the extent at 'end' block so we can easily remove the
		 * tail of the first part of the split extent in
		 * ext4_ext_rm_leaf().
		 */
		if (end >= ee_block &&
		    end < ee_block + ext4_ext_get_actual_len(ex) - 1) {
			int split_flag = 0;

			if (ext4_ext_is_uninitialized(ex))
				split_flag = EXT4_EXT_MARK_UNINIT1 |
					     EXT4_EXT_MARK_UNINIT2;

			/*
			 * Split the extent in two so that 'end' is the last
			 * block in the first new extent. Also we should not
			 * fail removing space due to ENOSPC so try to use
			 * reserved block if that happens.
			 */
			err = ext4_split_extent_at(handle, inode, path,
					end + 1, split_flag,
					EXT4_GET_BLOCKS_DIO |
					EXT4_GET_BLOCKS_METADATA_NOFAIL);

			if (err < 0)
				goto out;
		}
	}
	/*
	 * We start scanning from right side, freeing all the blocks
	 * after i_size and walking into the tree depth-wise.
	 */
	depth = ext_depth(inode);
	if (path) {
		int k = i = depth;
		while (--k > 0)
			path[k].p_block =
				le16_to_cpu(path[k].p_hdr->eh_entries)+1;
	} else {
		path = kzalloc(sizeof(struct ext4_ext_path) * (depth + 1),
			       GFP_NOFS);
		if (path == NULL) {
			ext4_journal_stop(handle);
			return -ENOMEM;
		}
		path[0].p_depth = depth;
		path[0].p_hdr = ext_inode_hdr(inode);
		i = 0;

		if (ext4_ext_check(inode, path[0].p_hdr, depth)) {
			err = -EIO;
			goto out;
		}
	}
	err = 0;

	while (i >= 0 && err == 0) {
		if (i == depth) {
			/* this is leaf block */
			err = ext4_ext_rm_leaf(handle, inode, path,
					start, end);
			/* root level has p_bh == NULL, brelse() eats this */
			brelse(path[i].p_bh);
			path[i].p_bh = NULL;
			i--;
			continue;
		}

		/* this is index block */
		if (!path[i].p_hdr) {
			ext_debug("initialize header\n");
			path[i].p_hdr = ext_block_hdr(path[i].p_bh);
		}

		if (!path[i].p_idx) {
			/* this level hasn't been touched yet */
			path[i].p_idx = EXT_LAST_INDEX(path[i].p_hdr);
			path[i].p_block = le16_to_cpu(path[i].p_hdr->eh_entries)+1;
			ext_debug("init index ptr: hdr 0x%p, num %d\n",
				  path[i].p_hdr,
				  le16_to_cpu(path[i].p_hdr->eh_entries));
		} else {
			/* we were already here, see at next index */
			path[i].p_idx--;
		}

		ext_debug("level %d - index, first 0x%p, cur 0x%p\n",
				i, EXT_FIRST_INDEX(path[i].p_hdr),
				path[i].p_idx);
		if (ext4_ext_more_to_rm(path + i)) {
			struct buffer_head *bh;
			/* go to the next level */
			ext_debug("move to level %d (block %llu)\n",
				  i + 1, ext4_idx_pblock(path[i].p_idx));
			memset(path + i + 1, 0, sizeof(*path));
			bh = sb_bread(sb, ext4_idx_pblock(path[i].p_idx));
			if (!bh) {
				/* should we reset i_size? */
				err = -EIO;
				break;
			}
			if (WARN_ON(i + 1 > depth)) {
				err = -EIO;
				break;
			}
			if (ext4_ext_check_block(inode, ext_block_hdr(bh),
							depth - i - 1, bh)) {
				err = -EIO;
				break;
			}
			path[i + 1].p_bh = bh;

			/* save actual number of indexes since this
			 * number is changed at the next iteration */
			path[i].p_block = le16_to_cpu(path[i].p_hdr->eh_entries);
			i++;
		} else {
			/* we finished processing this index, go up */
			if (path[i].p_hdr->eh_entries == 0 && i > 0) {
				/* index is empty, remove it;
				 * handle must be already prepared by the
				 * truncatei_leaf() */
				err = ext4_ext_rm_idx(handle, inode, path + i);
			}
			/* root level has p_bh == NULL, brelse() eats this */
			brelse(path[i].p_bh);
			path[i].p_bh = NULL;
			i--;
			ext_debug("return to level %d\n", i);
		}
	}

	/* TODO: flexible tree reduction should be here */
	if (path->p_hdr->eh_entries == 0) {
		/*
		 * truncate to zero freed all the tree,
		 * so we need to correct eh_depth
		 */
		err = ext4_ext_get_access(handle, inode, path);
		if (err == 0) {
			ext_inode_hdr(inode)->eh_depth = 0;
			ext_inode_hdr(inode)->eh_max =
				cpu_to_le16(ext4_ext_space_root(inode, 0));
			err = ext4_ext_dirty(handle, inode, path);
		}
	}
out:
	ext4_ext_drop_refs(path);
	kfree(path);
	if (err == -EAGAIN) {
		path = NULL;
		goto again;
	}
	ext4_journal_stop(handle);

	return err;
}