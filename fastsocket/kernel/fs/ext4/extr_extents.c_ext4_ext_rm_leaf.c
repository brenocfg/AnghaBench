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
struct inode {int /*<<< orphan*/  i_sb; } ;
struct ext4_extent_header {scalar_t__ eh_entries; } ;
struct ext4_extent {int /*<<< orphan*/  ee_block; int /*<<< orphan*/  ee_len; } ;
struct ext4_ext_path {int /*<<< orphan*/ * p_bh; struct ext4_extent* p_ext; struct ext4_extent_header* p_hdr; } ;
typedef  int /*<<< orphan*/  handle_t ;
typedef  unsigned short ext4_lblk_t ;

/* Variables and functions */
 int EIO ; 
 unsigned short EXT4_BLOCKS_PER_GROUP (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EXT4_ERROR_INODE (struct inode*,char*,unsigned short,...) ; 
 scalar_t__ EXT4_MAXQUOTAS_TRANS_BLOCKS (int /*<<< orphan*/ ) ; 
 struct ext4_extent* EXT_FIRST_EXTENT (struct ext4_extent_header*) ; 
 struct ext4_extent* EXT_LAST_EXTENT (struct ext4_extent_header*) ; 
 int EXT_MAX_BLOCKS ; 
 unsigned short block ; 
 int /*<<< orphan*/  cpu_to_le16 (unsigned int) ; 
 int ext4_ext_correct_indexes (int /*<<< orphan*/ *,struct inode*,struct ext4_ext_path*) ; 
 int ext4_ext_dirty (int /*<<< orphan*/ *,struct inode*,struct ext4_ext_path*) ; 
 int ext4_ext_get_access (int /*<<< orphan*/ *,struct inode*,struct ext4_ext_path*) ; 
 unsigned short ext4_ext_get_actual_len (struct ext4_extent*) ; 
 scalar_t__ ext4_ext_is_uninitialized (struct ext4_extent*) ; 
 int /*<<< orphan*/  ext4_ext_mark_uninitialized (struct ext4_extent*) ; 
 unsigned short ext4_ext_pblock (struct ext4_extent*) ; 
 int ext4_ext_rm_idx (int /*<<< orphan*/ *,struct inode*,struct ext4_ext_path*) ; 
 int /*<<< orphan*/  ext4_ext_store_pblock (struct ext4_extent*,int /*<<< orphan*/ ) ; 
 int ext4_ext_truncate_extend_restart (int /*<<< orphan*/ *,struct inode*,int) ; 
 int ext4_remove_blocks (int /*<<< orphan*/ *,struct inode*,struct ext4_extent*,unsigned short,unsigned short) ; 
 struct ext4_extent_header* ext_block_hdr (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ext_debug (char*,unsigned short,unsigned int,...) ; 
 int ext_depth (struct inode*) ; 
 int /*<<< orphan*/  le16_add_cpu (scalar_t__*,int) ; 
 unsigned short le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memmove (struct ext4_extent*,struct ext4_extent*,int) ; 
 int /*<<< orphan*/  memset (struct ext4_extent*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
ext4_ext_rm_leaf(handle_t *handle, struct inode *inode,
		struct ext4_ext_path *path, ext4_lblk_t start,
		ext4_lblk_t end)
{
	int err = 0, correct_index = 0;
	int depth = ext_depth(inode), credits;
	struct ext4_extent_header *eh;
	ext4_lblk_t a, b;
	unsigned num;
	ext4_lblk_t ex_ee_block;
	unsigned short ex_ee_len;
	unsigned uninitialized = 0;
	struct ext4_extent *ex;

	/* the header must be checked already in ext4_ext_remove_space() */
	ext_debug("truncate since %u in leaf to %u\n", start, end);
	if (!path[depth].p_hdr)
		path[depth].p_hdr = ext_block_hdr(path[depth].p_bh);
	eh = path[depth].p_hdr;
	if (unlikely(path[depth].p_hdr == NULL)) {
		EXT4_ERROR_INODE(inode, "path[%d].p_hdr == NULL", depth);
		return -EIO;
	}
	/* find where to start removing */
	ex = EXT_LAST_EXTENT(eh);

	ex_ee_block = le32_to_cpu(ex->ee_block);
	ex_ee_len = ext4_ext_get_actual_len(ex);

	while (ex >= EXT_FIRST_EXTENT(eh) &&
			ex_ee_block + ex_ee_len > start) {

		if (ext4_ext_is_uninitialized(ex))
			uninitialized = 1;
		else
			uninitialized = 0;

		ext_debug("remove ext %u:[%d]%d\n", ex_ee_block,
			 uninitialized, ex_ee_len);
		path[depth].p_ext = ex;

		a = ex_ee_block > start ? ex_ee_block : start;
		b = ex_ee_block+ex_ee_len - 1 < end ?
			ex_ee_block+ex_ee_len - 1 : end;

		ext_debug("  border %u:%u\n", a, b);

		/* If this extent is beyond the end of the hole, skip it */
		if (end < ex_ee_block) {
			ex--;
			ex_ee_block = le32_to_cpu(ex->ee_block);
			ex_ee_len = ext4_ext_get_actual_len(ex);
			continue;
		} else if (b != ex_ee_block + ex_ee_len - 1) {
			EXT4_ERROR_INODE(inode,
					 "can not handle truncate %u:%u "
					 "on extent %u:%u",
					 start, end, ex_ee_block,
					 ex_ee_block + ex_ee_len - 1);
			err = -EIO;
			goto out;
		} else if (a != ex_ee_block) {
			/* remove tail of the extent */
			num = a - ex_ee_block;
		} else {
			/* remove whole extent: excellent! */
			num = 0;
		}
		/*
		 * 3 for leaf, sb, and inode plus 2 (bmap and group
		 * descriptor) for each block group; assume two block
		 * groups plus ex_ee_len/blocks_per_block_group for
		 * the worst case
		 */
		credits = 7 + 2*(ex_ee_len/EXT4_BLOCKS_PER_GROUP(inode->i_sb));
		if (ex == EXT_FIRST_EXTENT(eh)) {
			correct_index = 1;
			credits += (ext_depth(inode)) + 1;
		}
		credits += EXT4_MAXQUOTAS_TRANS_BLOCKS(inode->i_sb);

		err = ext4_ext_truncate_extend_restart(handle, inode, credits);
		if (err)
			goto out;

		err = ext4_ext_get_access(handle, inode, path + depth);
		if (err)
			goto out;

		err = ext4_remove_blocks(handle, inode, ex, a, b);
		if (err)
			goto out;

		if (num == 0)
			/* this extent is removed; mark slot entirely unused */
			ext4_ext_store_pblock(ex, 0);

		ex->ee_len = cpu_to_le16(num);
		/*
		 * Do not mark uninitialized if all the blocks in the
		 * extent have been removed.
		 */
		if (uninitialized && num)
			ext4_ext_mark_uninitialized(ex);
		/*
		 * If the extent was completely released,
		 * we need to remove it from the leaf
		 */
		if (num == 0) {
			if (end != EXT_MAX_BLOCKS - 1) {
				/*
				 * For hole punching, we need to scoot all the
				 * extents up when an extent is removed so that
				 * we dont have blank extents in the middle
				 */
				memmove(ex, ex+1, (EXT_LAST_EXTENT(eh) - ex) *
					sizeof(struct ext4_extent));

				/* Now get rid of the one at the end */
				memset(EXT_LAST_EXTENT(eh), 0,
					sizeof(struct ext4_extent));
			}
			le16_add_cpu(&eh->eh_entries, -1);
		}

		err = ext4_ext_dirty(handle, inode, path + depth);
		if (err)
			goto out;

		ext_debug("new extent: %u:%u:%llu\n", block, num,
				ext4_ext_pblock(ex));
		ex--;
		ex_ee_block = le32_to_cpu(ex->ee_block);
		ex_ee_len = ext4_ext_get_actual_len(ex);
	}

	if (correct_index && eh->eh_entries)
		err = ext4_ext_correct_indexes(handle, inode, path);

	/* if this leaf is free, then we should
	 * remove it from index block above */
	if (err == 0 && eh->eh_entries == 0 && path[depth].p_bh != NULL)
		err = ext4_ext_rm_idx(handle, inode, path + depth);

out:
	return err;
}