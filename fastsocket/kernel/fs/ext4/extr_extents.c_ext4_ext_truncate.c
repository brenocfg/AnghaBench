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
struct super_block {int s_blocksize; } ;
struct inode {int i_size; int /*<<< orphan*/  i_ctime; int /*<<< orphan*/  i_mtime; scalar_t__ i_nlink; struct super_block* i_sb; struct address_space* i_mapping; } ;
struct address_space {int dummy; } ;
typedef  int /*<<< orphan*/  handle_t ;
typedef  int ext4_lblk_t ;
struct TYPE_2__ {int i_disksize; int /*<<< orphan*/  i_data_sem; } ;

/* Variables and functions */
 int EXT4_BLOCK_SIZE_BITS (struct super_block*) ; 
 TYPE_1__* EXT4_I (struct inode*) ; 
 scalar_t__ EXT_MAX_BLOCKS ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ *) ; 
 scalar_t__ IS_SYNC (struct inode*) ; 
 int /*<<< orphan*/  down_write (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ext4_block_truncate_page (int /*<<< orphan*/ *,struct address_space*,int) ; 
 int /*<<< orphan*/  ext4_current_time (struct inode*) ; 
 int /*<<< orphan*/  ext4_discard_preallocations (struct inode*) ; 
 int /*<<< orphan*/  ext4_ext_invalidate_cache (struct inode*) ; 
 int ext4_ext_remove_space (struct inode*,int,scalar_t__) ; 
 int /*<<< orphan*/  ext4_handle_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * ext4_journal_start (struct inode*,int) ; 
 int /*<<< orphan*/  ext4_journal_stop (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ext4_mark_inode_dirty (int /*<<< orphan*/ *,struct inode*) ; 
 scalar_t__ ext4_orphan_add (int /*<<< orphan*/ *,struct inode*) ; 
 int /*<<< orphan*/  ext4_orphan_del (int /*<<< orphan*/ *,struct inode*) ; 
 int ext4_writepage_trans_blocks (struct inode*) ; 
 int /*<<< orphan*/  flush_aio_dio_completed_IO (struct inode*) ; 
 int /*<<< orphan*/  up_write (int /*<<< orphan*/ *) ; 

void ext4_ext_truncate(struct inode *inode)
{
	struct address_space *mapping = inode->i_mapping;
	struct super_block *sb = inode->i_sb;
	ext4_lblk_t last_block;
	handle_t *handle;
	int err = 0;

	/*
	 * finish any pending end_io work so we won't run the risk of
	 * converting any truncated blocks to initialized later
	 */
	flush_aio_dio_completed_IO(inode);

	/*
	 * probably first extent we're gonna free will be last in block
	 */
	err = ext4_writepage_trans_blocks(inode);
	handle = ext4_journal_start(inode, err);
	if (IS_ERR(handle))
		return;

	if (inode->i_size & (sb->s_blocksize - 1))
		ext4_block_truncate_page(handle, mapping, inode->i_size);

	if (ext4_orphan_add(handle, inode))
		goto out_stop;

	down_write(&EXT4_I(inode)->i_data_sem);
	ext4_ext_invalidate_cache(inode);

	ext4_discard_preallocations(inode);

	/*
	 * TODO: optimization is possible here.
	 * Probably we need not scan at all,
	 * because page truncation is enough.
	 */

	/* we have to know where to truncate from in crash case */
	EXT4_I(inode)->i_disksize = inode->i_size;
	ext4_mark_inode_dirty(handle, inode);

	last_block = (inode->i_size + sb->s_blocksize - 1)
			>> EXT4_BLOCK_SIZE_BITS(sb);
	err = ext4_ext_remove_space(inode, last_block, EXT_MAX_BLOCKS - 1);

	/* In a multi-transaction truncate, we only make the final
	 * transaction synchronous.
	 */
	if (IS_SYNC(inode))
		ext4_handle_sync(handle);

out_stop:
	up_write(&EXT4_I(inode)->i_data_sem);
	/*
	 * If this was a simple ftruncate() and the file will remain alive,
	 * then we need to clear up the orphan record which we created above.
	 * However, if this was a real unlink then we were called by
	 * ext4_delete_inode(), and we allow that function to clean up the
	 * orphan info for us.
	 */
	if (inode->i_nlink)
		ext4_orphan_del(handle, inode);

	inode->i_mtime = inode->i_ctime = ext4_current_time(inode);
	ext4_mark_inode_dirty(handle, inode);
	ext4_journal_stop(handle);
}