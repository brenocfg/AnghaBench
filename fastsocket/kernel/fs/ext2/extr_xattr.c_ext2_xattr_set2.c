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
struct super_block {int dummy; } ;
struct mb_cache_entry {int dummy; } ;
struct inode {int /*<<< orphan*/  i_ctime; struct super_block* i_sb; } ;
struct ext2_xattr_header {scalar_t__ h_refcount; } ;
struct buffer_head {int b_blocknr; int /*<<< orphan*/  b_bdev; int /*<<< orphan*/  b_size; int /*<<< orphan*/  b_data; } ;
typedef  int /*<<< orphan*/  ext2_fsblk_t ;
struct TYPE_2__ {int i_file_acl; int /*<<< orphan*/  i_block_group; } ;

/* Variables and functions */
 int /*<<< orphan*/  CURRENT_TIME_SEC ; 
 int EDQUOT ; 
 int EIO ; 
 int ENOSPC ; 
 TYPE_1__* EXT2_I (struct inode*) ; 
 struct ext2_xattr_header* HDR (struct buffer_head*) ; 
 scalar_t__ IS_SYNC (struct inode*) ; 
 int /*<<< orphan*/  bforget (struct buffer_head*) ; 
 int /*<<< orphan*/  brelse (struct buffer_head*) ; 
 scalar_t__ buffer_req (struct buffer_head*) ; 
 int /*<<< orphan*/  buffer_uptodate (struct buffer_head*) ; 
 scalar_t__ cpu_to_le32 (int) ; 
 int /*<<< orphan*/  ea_bdebug (struct buffer_head*,char*,...) ; 
 int /*<<< orphan*/  ea_idebug (struct inode*,char*,int) ; 
 int /*<<< orphan*/  ext2_free_blocks (struct inode*,int,int) ; 
 int /*<<< orphan*/  ext2_group_first_block_no (struct super_block*,int /*<<< orphan*/ ) ; 
 int ext2_new_block (struct inode*,int /*<<< orphan*/ ,int*) ; 
 int ext2_sync_inode (struct inode*) ; 
 int /*<<< orphan*/  ext2_xattr_cache ; 
 struct buffer_head* ext2_xattr_cache_find (struct inode*,struct ext2_xattr_header*) ; 
 int /*<<< orphan*/  ext2_xattr_cache_insert (struct buffer_head*) ; 
 int /*<<< orphan*/  ext2_xattr_update_super_block (struct super_block*) ; 
 int /*<<< orphan*/  get_bh (struct buffer_head*) ; 
 int /*<<< orphan*/  le32_add_cpu (scalar_t__*,int) ; 
 int /*<<< orphan*/  le32_to_cpu (scalar_t__) ; 
 int /*<<< orphan*/  lock_buffer (struct buffer_head*) ; 
 int /*<<< orphan*/  mark_buffer_dirty (struct buffer_head*) ; 
 int /*<<< orphan*/  mark_inode_dirty (struct inode*) ; 
 int /*<<< orphan*/  mb_cache_entry_free (struct mb_cache_entry*) ; 
 struct mb_cache_entry* mb_cache_entry_get (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mb_cache_entry_release (struct mb_cache_entry*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,struct ext2_xattr_header*,int /*<<< orphan*/ ) ; 
 struct buffer_head* sb_getblk (struct super_block*,int) ; 
 int /*<<< orphan*/  set_buffer_uptodate (struct buffer_head*) ; 
 int /*<<< orphan*/  sync_dirty_buffer (struct buffer_head*) ; 
 int /*<<< orphan*/  unlock_buffer (struct buffer_head*) ; 
 scalar_t__ vfs_dq_alloc_block (struct inode*,int) ; 
 int /*<<< orphan*/  vfs_dq_free_block (struct inode*,int) ; 

__attribute__((used)) static int
ext2_xattr_set2(struct inode *inode, struct buffer_head *old_bh,
		struct ext2_xattr_header *header)
{
	struct super_block *sb = inode->i_sb;
	struct buffer_head *new_bh = NULL;
	int error;

	if (header) {
		new_bh = ext2_xattr_cache_find(inode, header);
		if (new_bh) {
			/* We found an identical block in the cache. */
			if (new_bh == old_bh) {
				ea_bdebug(new_bh, "keeping this block");
			} else {
				/* The old block is released after updating
				   the inode.  */
				ea_bdebug(new_bh, "reusing block");

				error = -EDQUOT;
				if (vfs_dq_alloc_block(inode, 1)) {
					unlock_buffer(new_bh);
					goto cleanup;
				}
				le32_add_cpu(&HDR(new_bh)->h_refcount, 1);
				ea_bdebug(new_bh, "refcount now=%d",
					le32_to_cpu(HDR(new_bh)->h_refcount));
			}
			unlock_buffer(new_bh);
		} else if (old_bh && header == HDR(old_bh)) {
			/* Keep this block. No need to lock the block as we
			   don't need to change the reference count. */
			new_bh = old_bh;
			get_bh(new_bh);
			ext2_xattr_cache_insert(new_bh);
		} else {
			/* We need to allocate a new block */
			ext2_fsblk_t goal = ext2_group_first_block_no(sb,
						EXT2_I(inode)->i_block_group);
			int block = ext2_new_block(inode, goal, &error);
			if (error)
				goto cleanup;
			ea_idebug(inode, "creating block %d", block);

			new_bh = sb_getblk(sb, block);
			if (!new_bh) {
				ext2_free_blocks(inode, block, 1);
				error = -EIO;
				goto cleanup;
			}
			lock_buffer(new_bh);
			memcpy(new_bh->b_data, header, new_bh->b_size);
			set_buffer_uptodate(new_bh);
			unlock_buffer(new_bh);
			ext2_xattr_cache_insert(new_bh);
			
			ext2_xattr_update_super_block(sb);
		}
		mark_buffer_dirty(new_bh);
		if (IS_SYNC(inode)) {
			sync_dirty_buffer(new_bh);
			error = -EIO;
			if (buffer_req(new_bh) && !buffer_uptodate(new_bh))
				goto cleanup;
		}
	}

	/* Update the inode. */
	EXT2_I(inode)->i_file_acl = new_bh ? new_bh->b_blocknr : 0;
	inode->i_ctime = CURRENT_TIME_SEC;
	if (IS_SYNC(inode)) {
		error = ext2_sync_inode (inode);
		/* In case sync failed due to ENOSPC the inode was actually
		 * written (only some dirty data were not) so we just proceed
		 * as if nothing happened and cleanup the unused block */
		if (error && error != -ENOSPC) {
			if (new_bh && new_bh != old_bh)
				vfs_dq_free_block(inode, 1);
			goto cleanup;
		}
	} else
		mark_inode_dirty(inode);

	error = 0;
	if (old_bh && old_bh != new_bh) {
		struct mb_cache_entry *ce;

		/*
		 * If there was an old block and we are no longer using it,
		 * release the old block.
		 */
		ce = mb_cache_entry_get(ext2_xattr_cache, old_bh->b_bdev,
					old_bh->b_blocknr);
		lock_buffer(old_bh);
		if (HDR(old_bh)->h_refcount == cpu_to_le32(1)) {
			/* Free the old block. */
			if (ce)
				mb_cache_entry_free(ce);
			ea_bdebug(old_bh, "freeing");
			ext2_free_blocks(inode, old_bh->b_blocknr, 1);
			/* We let our caller release old_bh, so we
			 * need to duplicate the buffer before. */
			get_bh(old_bh);
			bforget(old_bh);
		} else {
			/* Decrement the refcount only. */
			le32_add_cpu(&HDR(old_bh)->h_refcount, -1);
			if (ce)
				mb_cache_entry_release(ce);
			vfs_dq_free_block(inode, 1);
			mark_buffer_dirty(old_bh);
			ea_bdebug(old_bh, "refcount now=%d",
				le32_to_cpu(HDR(old_bh)->h_refcount));
		}
		unlock_buffer(old_bh);
	}

cleanup:
	brelse(new_bh);

	return error;
}