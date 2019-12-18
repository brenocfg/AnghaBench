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
struct super_block {int dummy; } ;
struct inode {int i_nlink; unsigned long i_ino; int /*<<< orphan*/  i_mode; int /*<<< orphan*/  i_count; struct super_block* i_sb; } ;
struct ext3_super_block {int /*<<< orphan*/  s_inodes_count; } ;
struct ext3_sb_info {int /*<<< orphan*/  s_dirs_counter; int /*<<< orphan*/  s_freeinodes_counter; struct ext3_super_block* s_es; } ;
struct ext3_group_desc {int /*<<< orphan*/  bg_used_dirs_count; int /*<<< orphan*/  bg_free_inodes_count; } ;
struct buffer_head {int /*<<< orphan*/  b_data; } ;
typedef  int /*<<< orphan*/  handle_t ;

/* Variables and functions */
 int /*<<< orphan*/  BUFFER_TRACE (struct buffer_head*,char*) ; 
 unsigned long EXT3_FIRST_INO (struct super_block*) ; 
 unsigned long EXT3_INODES_PER_GROUP (struct super_block*) ; 
 struct ext3_sb_info* EXT3_SB (struct super_block*) ; 
 int S_ISDIR (int /*<<< orphan*/ ) ; 
 int atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  brelse (struct buffer_head*) ; 
 int /*<<< orphan*/  clear_inode (struct inode*) ; 
 int /*<<< orphan*/  ext3_clear_bit_atomic (int /*<<< orphan*/ ,unsigned long,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ext3_debug (char*,unsigned long) ; 
 int /*<<< orphan*/  ext3_error (struct super_block*,char*,char*,unsigned long) ; 
 struct ext3_group_desc* ext3_get_group_desc (struct super_block*,unsigned long,struct buffer_head**) ; 
 int ext3_journal_dirty_metadata (int /*<<< orphan*/ *,struct buffer_head*) ; 
 int ext3_journal_get_write_access (int /*<<< orphan*/ *,struct buffer_head*) ; 
 int /*<<< orphan*/  ext3_std_error (struct super_block*,int) ; 
 int /*<<< orphan*/  ext3_xattr_delete_inode (int /*<<< orphan*/ *,struct inode*) ; 
 int /*<<< orphan*/  le16_add_cpu (int /*<<< orphan*/ *,int) ; 
 unsigned long le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  percpu_counter_dec (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  percpu_counter_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  printk (char*,...) ; 
 struct buffer_head* read_inode_bitmap (struct super_block*,unsigned long) ; 
 int /*<<< orphan*/  sb_bgl_lock (struct ext3_sb_info*,unsigned long) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trace_ext3_free_inode (struct inode*) ; 
 int /*<<< orphan*/  vfs_dq_drop (struct inode*) ; 
 int /*<<< orphan*/  vfs_dq_free_inode (struct inode*) ; 
 int /*<<< orphan*/  vfs_dq_init (struct inode*) ; 

void ext3_free_inode (handle_t *handle, struct inode * inode)
{
	struct super_block * sb = inode->i_sb;
	int is_directory;
	unsigned long ino;
	struct buffer_head *bitmap_bh = NULL;
	struct buffer_head *bh2;
	unsigned long block_group;
	unsigned long bit;
	struct ext3_group_desc * gdp;
	struct ext3_super_block * es;
	struct ext3_sb_info *sbi;
	int fatal = 0, err;

	if (atomic_read(&inode->i_count) > 1) {
		printk ("ext3_free_inode: inode has count=%d\n",
					atomic_read(&inode->i_count));
		return;
	}
	if (inode->i_nlink) {
		printk ("ext3_free_inode: inode has nlink=%d\n",
			inode->i_nlink);
		return;
	}
	if (!sb) {
		printk("ext3_free_inode: inode on nonexistent device\n");
		return;
	}
	sbi = EXT3_SB(sb);

	ino = inode->i_ino;
	ext3_debug ("freeing inode %lu\n", ino);
	trace_ext3_free_inode(inode);

	/*
	 * Note: we must free any quota before locking the superblock,
	 * as writing the quota to disk may need the lock as well.
	 */
	vfs_dq_init(inode);
	ext3_xattr_delete_inode(handle, inode);
	vfs_dq_free_inode(inode);
	vfs_dq_drop(inode);

	is_directory = S_ISDIR(inode->i_mode);

	/* Do this BEFORE marking the inode not in use or returning an error */
	clear_inode (inode);

	es = EXT3_SB(sb)->s_es;
	if (ino < EXT3_FIRST_INO(sb) || ino > le32_to_cpu(es->s_inodes_count)) {
		ext3_error (sb, "ext3_free_inode",
			    "reserved or nonexistent inode %lu", ino);
		goto error_return;
	}
	block_group = (ino - 1) / EXT3_INODES_PER_GROUP(sb);
	bit = (ino - 1) % EXT3_INODES_PER_GROUP(sb);
	bitmap_bh = read_inode_bitmap(sb, block_group);
	if (!bitmap_bh)
		goto error_return;

	BUFFER_TRACE(bitmap_bh, "get_write_access");
	fatal = ext3_journal_get_write_access(handle, bitmap_bh);
	if (fatal)
		goto error_return;

	/* Ok, now we can actually update the inode bitmaps.. */
	if (!ext3_clear_bit_atomic(sb_bgl_lock(sbi, block_group),
					bit, bitmap_bh->b_data))
		ext3_error (sb, "ext3_free_inode",
			      "bit already cleared for inode %lu", ino);
	else {
		gdp = ext3_get_group_desc (sb, block_group, &bh2);

		BUFFER_TRACE(bh2, "get_write_access");
		fatal = ext3_journal_get_write_access(handle, bh2);
		if (fatal) goto error_return;

		if (gdp) {
			spin_lock(sb_bgl_lock(sbi, block_group));
			le16_add_cpu(&gdp->bg_free_inodes_count, 1);
			if (is_directory)
				le16_add_cpu(&gdp->bg_used_dirs_count, -1);
			spin_unlock(sb_bgl_lock(sbi, block_group));
			percpu_counter_inc(&sbi->s_freeinodes_counter);
			if (is_directory)
				percpu_counter_dec(&sbi->s_dirs_counter);

		}
		BUFFER_TRACE(bh2, "call ext3_journal_dirty_metadata");
		err = ext3_journal_dirty_metadata(handle, bh2);
		if (!fatal) fatal = err;
	}
	BUFFER_TRACE(bitmap_bh, "call ext3_journal_dirty_metadata");
	err = ext3_journal_dirty_metadata(handle, bitmap_bh);
	if (!fatal)
		fatal = err;

error_return:
	brelse(bitmap_bh);
	ext3_std_error(sb, fatal);
}