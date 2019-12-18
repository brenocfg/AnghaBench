#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct super_block {int s_flags; } ;
struct inode {unsigned long i_ino; int /*<<< orphan*/  i_mode; struct super_block* i_sb; } ;
struct ext2_super_block {int /*<<< orphan*/  s_inodes_count; } ;
struct buffer_head {scalar_t__ b_data; } ;
struct TYPE_3__ {struct ext2_super_block* s_es; } ;

/* Variables and functions */
 unsigned long EXT2_FIRST_INO (struct super_block*) ; 
 unsigned long EXT2_INODES_PER_GROUP (struct super_block*) ; 
 TYPE_1__* EXT2_SB (struct super_block*) ; 
 int MS_SYNCHRONOUS ; 
 int S_ISDIR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  brelse (struct buffer_head*) ; 
 int /*<<< orphan*/  clear_inode (struct inode*) ; 
 int /*<<< orphan*/  ext2_clear_bit_atomic (int /*<<< orphan*/ ,unsigned long,void*) ; 
 int /*<<< orphan*/  ext2_debug (char*,unsigned long) ; 
 int /*<<< orphan*/  ext2_error (struct super_block*,char*,char*,unsigned long) ; 
 int /*<<< orphan*/  ext2_release_inode (struct super_block*,unsigned long,int) ; 
 int /*<<< orphan*/  ext2_xattr_delete_inode (struct inode*) ; 
 int /*<<< orphan*/  is_bad_inode (struct inode*) ; 
 unsigned long le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mark_buffer_dirty (struct buffer_head*) ; 
 struct buffer_head* read_inode_bitmap (struct super_block*,unsigned long) ; 
 int /*<<< orphan*/  sb_bgl_lock (TYPE_1__*,unsigned long) ; 
 int /*<<< orphan*/  sync_dirty_buffer (struct buffer_head*) ; 
 int /*<<< orphan*/  vfs_dq_drop (struct inode*) ; 
 int /*<<< orphan*/  vfs_dq_free_inode (struct inode*) ; 

void ext2_free_inode (struct inode * inode)
{
	struct super_block * sb = inode->i_sb;
	int is_directory;
	unsigned long ino;
	struct buffer_head *bitmap_bh = NULL;
	unsigned long block_group;
	unsigned long bit;
	struct ext2_super_block * es;

	ino = inode->i_ino;
	ext2_debug ("freeing inode %lu\n", ino);

	/*
	 * Note: we must free any quota before locking the superblock,
	 * as writing the quota to disk may need the lock as well.
	 */
	if (!is_bad_inode(inode)) {
		/* Quota is already initialized in iput() */
		ext2_xattr_delete_inode(inode);
		vfs_dq_free_inode(inode);
		vfs_dq_drop(inode);
	}

	es = EXT2_SB(sb)->s_es;
	is_directory = S_ISDIR(inode->i_mode);

	/* Do this BEFORE marking the inode not in use or returning an error */
	clear_inode (inode);

	if (ino < EXT2_FIRST_INO(sb) ||
	    ino > le32_to_cpu(es->s_inodes_count)) {
		ext2_error (sb, "ext2_free_inode",
			    "reserved or nonexistent inode %lu", ino);
		goto error_return;
	}
	block_group = (ino - 1) / EXT2_INODES_PER_GROUP(sb);
	bit = (ino - 1) % EXT2_INODES_PER_GROUP(sb);
	brelse(bitmap_bh);
	bitmap_bh = read_inode_bitmap(sb, block_group);
	if (!bitmap_bh)
		goto error_return;

	/* Ok, now we can actually update the inode bitmaps.. */
	if (!ext2_clear_bit_atomic(sb_bgl_lock(EXT2_SB(sb), block_group),
				bit, (void *) bitmap_bh->b_data))
		ext2_error (sb, "ext2_free_inode",
			      "bit already cleared for inode %lu", ino);
	else
		ext2_release_inode(sb, block_group, is_directory);
	mark_buffer_dirty(bitmap_bh);
	if (sb->s_flags & MS_SYNCHRONOUS)
		sync_dirty_buffer(bitmap_bh);
error_return:
	brelse(bitmap_bh);
}