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
struct inode {int /*<<< orphan*/  i_sb; } ;
struct buffer_head {int dummy; } ;
typedef  int /*<<< orphan*/  handle_t ;
typedef  int /*<<< orphan*/  ext3_fsblk_t ;
typedef  scalar_t__ __le32 ;

/* Variables and functions */
 int /*<<< orphan*/  BUFFER_TRACE (struct buffer_head*,char*) ; 
 int /*<<< orphan*/  ext3_forget (int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct inode*,struct buffer_head*,scalar_t__) ; 
 int /*<<< orphan*/  ext3_free_blocks (int /*<<< orphan*/ *,struct inode*,int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  ext3_journal_dirty_metadata (int /*<<< orphan*/ *,struct buffer_head*) ; 
 int /*<<< orphan*/  ext3_journal_get_write_access (int /*<<< orphan*/ *,struct buffer_head*) ; 
 int /*<<< orphan*/  ext3_mark_inode_dirty (int /*<<< orphan*/ *,struct inode*) ; 
 scalar_t__ le32_to_cpu (scalar_t__) ; 
 struct buffer_head* sb_find_get_block (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  truncate_restart_transaction (int /*<<< orphan*/ *,struct inode*) ; 
 scalar_t__ try_to_extend_transaction (int /*<<< orphan*/ *,struct inode*) ; 

__attribute__((used)) static void ext3_clear_blocks(handle_t *handle, struct inode *inode,
		struct buffer_head *bh, ext3_fsblk_t block_to_free,
		unsigned long count, __le32 *first, __le32 *last)
{
	__le32 *p;
	if (try_to_extend_transaction(handle, inode)) {
		if (bh) {
			BUFFER_TRACE(bh, "call ext3_journal_dirty_metadata");
			ext3_journal_dirty_metadata(handle, bh);
		}
		ext3_mark_inode_dirty(handle, inode);
		truncate_restart_transaction(handle, inode);
		if (bh) {
			BUFFER_TRACE(bh, "retaking write access");
			ext3_journal_get_write_access(handle, bh);
		}
	}

	/*
	 * Any buffers which are on the journal will be in memory. We find
	 * them on the hash table so journal_revoke() will run journal_forget()
	 * on them.  We've already detached each block from the file, so
	 * bforget() in journal_forget() should be safe.
	 *
	 * AKPM: turn on bforget in journal_forget()!!!
	 */
	for (p = first; p < last; p++) {
		u32 nr = le32_to_cpu(*p);
		if (nr) {
			struct buffer_head *bh;

			*p = 0;
			bh = sb_find_get_block(inode->i_sb, nr);
			ext3_forget(handle, 0, inode, bh, nr);
		}
	}

	ext3_free_blocks(handle, inode, block_to_free, count);
}