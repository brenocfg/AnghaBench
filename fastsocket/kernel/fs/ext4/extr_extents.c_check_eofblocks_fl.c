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
struct inode {int dummy; } ;
struct ext4_extent_header {int /*<<< orphan*/  eh_entries; } ;
struct ext4_extent {int /*<<< orphan*/  ee_block; } ;
struct ext4_ext_path {scalar_t__ p_idx; struct ext4_extent_header* p_hdr; struct ext4_extent* p_ext; } ;
typedef  int /*<<< orphan*/  handle_t ;
typedef  scalar_t__ ext4_lblk_t ;

/* Variables and functions */
 int /*<<< orphan*/  EXT4_INODE_EOFBLOCKS ; 
 struct ext4_extent* EXT_LAST_EXTENT (struct ext4_extent_header*) ; 
 scalar_t__ EXT_LAST_INDEX (struct ext4_extent_header*) ; 
 int /*<<< orphan*/  ext4_clear_inode_flag (struct inode*,int /*<<< orphan*/ ) ; 
 scalar_t__ ext4_ext_get_actual_len (struct ext4_extent*) ; 
 int ext4_mark_inode_dirty (int /*<<< orphan*/ *,struct inode*) ; 
 int /*<<< orphan*/  ext4_test_inode_flag (struct inode*,int /*<<< orphan*/ ) ; 
 int ext_depth (struct inode*) ; 
 scalar_t__ le32_to_cpu (int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int check_eofblocks_fl(handle_t *handle, struct inode *inode,
			      ext4_lblk_t iblock,
			      struct ext4_ext_path *path,
			      unsigned int len)
{
	int i, depth;
	struct ext4_extent_header *eh;
	struct ext4_extent *ex, *last_ex;

	if (!ext4_test_inode_flag(inode, EXT4_INODE_EOFBLOCKS))
		return 0;

	depth = ext_depth(inode);
	eh = path[depth].p_hdr;
	ex = path[depth].p_ext;

	/*
	 * We're going to remove EOFBLOCKS_FL entirely in future so we
	 * do not care for this case anymore. Simply remove the flag
	 * if there are no extents.
	 */
	if (unlikely(!eh->eh_entries))
		goto out;
	last_ex = EXT_LAST_EXTENT(eh);
	/*
	 * We should clear the EOFBLOCKS_FL flag if we are writing the
	 * last block in the last extent in the file.  We test this by
	 * first checking to see if the caller to
	 * ext4_ext_get_blocks() was interested in the last block (or
	 * a block beyond the last block) in the current extent.  If
	 * this turns out to be false, we can bail out from this
	 * function immediately.
	 */
	if (iblock + len < le32_to_cpu(last_ex->ee_block) +
	    ext4_ext_get_actual_len(last_ex))
		return 0;
	/*
	 * If the caller does appear to be planning to write at or
	 * beyond the end of the current extent, we then test to see
	 * if the current extent is the last extent in the file, by
	 * checking to make sure it was reached via the rightmost node
	 * at each level of the tree.
	 */
	for (i = depth-1; i >= 0; i--)
		if (path[i].p_idx != EXT_LAST_INDEX(path[i].p_hdr))
			return 0;
out:
	ext4_clear_inode_flag(inode, EXT4_INODE_EOFBLOCKS);
	return ext4_mark_inode_dirty(handle, inode);
}