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
struct inode {int /*<<< orphan*/  i_sb; } ;
struct ext4_extent_idx {int dummy; } ;
struct ext4_ext_path {scalar_t__ p_idx; TYPE_1__* p_hdr; } ;
struct buffer_head {int dummy; } ;
typedef  int /*<<< orphan*/  handle_t ;
typedef  int /*<<< orphan*/  ext4_fsblk_t ;
struct TYPE_2__ {scalar_t__ eh_entries; } ;

/* Variables and functions */
 int EIO ; 
 int /*<<< orphan*/  EXT4_ERROR_INODE (struct inode*,char*) ; 
 int /*<<< orphan*/  EXT4_FREE_BLOCKS_METADATA ; 
 scalar_t__ EXT_LAST_INDEX (TYPE_1__*) ; 
 int ext4_ext_dirty (int /*<<< orphan*/ *,struct inode*,struct ext4_ext_path*) ; 
 int ext4_ext_get_access (int /*<<< orphan*/ *,struct inode*,struct ext4_ext_path*) ; 
 int /*<<< orphan*/  ext4_forget (int /*<<< orphan*/ *,int,struct inode*,struct buffer_head*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ext4_free_blocks (int /*<<< orphan*/ *,struct inode*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ext4_idx_pblock (scalar_t__) ; 
 int /*<<< orphan*/  ext_debug (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  le16_add_cpu (scalar_t__*,int) ; 
 int /*<<< orphan*/  memmove (scalar_t__,scalar_t__,int) ; 
 struct buffer_head* sb_find_get_block (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int ext4_ext_rm_idx(handle_t *handle, struct inode *inode,
			struct ext4_ext_path *path)
{
	struct buffer_head *bh;
	int err;
	ext4_fsblk_t leaf;

	/* free index block */
	path--;
	leaf = ext4_idx_pblock(path->p_idx);
	if (unlikely(path->p_hdr->eh_entries == 0)) {
		EXT4_ERROR_INODE(inode, "path->p_hdr->eh_entries == 0");
		return -EIO;
	}
	err = ext4_ext_get_access(handle, inode, path);
	if (err)
		return err;

	if (path->p_idx != EXT_LAST_INDEX(path->p_hdr)) {
		int len = EXT_LAST_INDEX(path->p_hdr) - path->p_idx;
		len *= sizeof(struct ext4_extent_idx);
		memmove(path->p_idx, path->p_idx + 1, len);
	}

	le16_add_cpu(&path->p_hdr->eh_entries, -1);
	err = ext4_ext_dirty(handle, inode, path);
	if (err)
		return err;
	ext_debug("index is empty, remove it, free block %llu\n", leaf);
	bh = sb_find_get_block(inode->i_sb, leaf);
	ext4_forget(handle, 1, inode, bh, leaf);
	ext4_free_blocks(handle, inode, leaf, 1, EXT4_FREE_BLOCKS_METADATA);
	return err;
}