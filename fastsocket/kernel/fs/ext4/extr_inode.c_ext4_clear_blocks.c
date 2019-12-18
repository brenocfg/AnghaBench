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
typedef  scalar_t__ u32 ;
struct inode {int /*<<< orphan*/  i_sb; int /*<<< orphan*/  i_mode; } ;
struct buffer_head {int dummy; } ;
typedef  int /*<<< orphan*/  handle_t ;
typedef  int /*<<< orphan*/  ext4_fsblk_t ;
typedef  scalar_t__ __le32 ;

/* Variables and functions */
 int /*<<< orphan*/  BUFFER_TRACE (struct buffer_head*,char*) ; 
 int EXT4_FREE_BLOCKS_METADATA ; 
 scalar_t__ S_ISDIR (int /*<<< orphan*/ ) ; 
 scalar_t__ S_ISLNK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  blocks_for_truncate (struct inode*) ; 
 int /*<<< orphan*/  ext4_forget (int /*<<< orphan*/ *,int,struct inode*,struct buffer_head*,scalar_t__) ; 
 int /*<<< orphan*/  ext4_free_blocks (int /*<<< orphan*/ *,struct inode*,int /*<<< orphan*/ ,unsigned long,int) ; 
 int /*<<< orphan*/  ext4_handle_dirty_metadata (int /*<<< orphan*/ *,struct inode*,struct buffer_head*) ; 
 int /*<<< orphan*/  ext4_journal_get_write_access (int /*<<< orphan*/ *,struct buffer_head*) ; 
 int /*<<< orphan*/  ext4_mark_inode_dirty (int /*<<< orphan*/ *,struct inode*) ; 
 int /*<<< orphan*/  ext4_truncate_restart_trans (int /*<<< orphan*/ *,struct inode*,int /*<<< orphan*/ ) ; 
 scalar_t__ le32_to_cpu (scalar_t__) ; 
 struct buffer_head* sb_find_get_block (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ try_to_extend_transaction (int /*<<< orphan*/ *,struct inode*) ; 

__attribute__((used)) static void ext4_clear_blocks(handle_t *handle, struct inode *inode,
			      struct buffer_head *bh,
			      ext4_fsblk_t block_to_free,
			      unsigned long count, __le32 *first,
			      __le32 *last)
{
	__le32 *p;
	int is_metadata = 0;
	int flags = 0;

	if (S_ISDIR(inode->i_mode) || S_ISLNK(inode->i_mode)) {
		flags |= EXT4_FREE_BLOCKS_METADATA;
		is_metadata = 1;
	}


	if (try_to_extend_transaction(handle, inode)) {
		if (bh) {
			BUFFER_TRACE(bh, "call ext4_handle_dirty_metadata");
			ext4_handle_dirty_metadata(handle, inode, bh);
		}
		ext4_mark_inode_dirty(handle, inode);
		ext4_truncate_restart_trans(handle, inode,
					    blocks_for_truncate(inode));
		if (bh) {
			BUFFER_TRACE(bh, "retaking write access");
			ext4_journal_get_write_access(handle, bh);
		}
	}

	/*
	 * Any buffers which are on the journal will be in memory. We
	 * find them on the hash table so jbd2_journal_revoke() will
	 * run jbd2_journal_forget() on them.  We've already detached
	 * each block from the file, so bforget() in
	 * jbd2_journal_forget() should be safe.
	 *
	 * AKPM: turn on bforget in jbd2_journal_forget()!!!
	 */
	for (p = first; p < last; p++) {
		u32 nr = le32_to_cpu(*p);
		if (nr) {
			struct buffer_head *tbh;

			*p = 0;
			tbh = sb_find_get_block(inode->i_sb, nr);
			ext4_forget(handle, is_metadata, inode, tbh, nr);
		}
	}

	ext4_free_blocks(handle, inode, block_to_free, count, flags);
}