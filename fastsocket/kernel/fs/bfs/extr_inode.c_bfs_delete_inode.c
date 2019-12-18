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
struct super_block {char* s_id; } ;
struct inode {unsigned long i_ino; struct super_block* i_sb; int /*<<< orphan*/  i_ctime; int /*<<< orphan*/  i_mtime; int /*<<< orphan*/  i_atime; scalar_t__ i_size; int /*<<< orphan*/  i_data; } ;
struct buffer_head {scalar_t__ b_data; } ;
struct bfs_sb_info {unsigned long si_lasti; scalar_t__ si_lf_eblk; int /*<<< orphan*/  bfs_lock; struct buffer_head* si_sbh; int /*<<< orphan*/  si_imap; int /*<<< orphan*/  si_freei; int /*<<< orphan*/  si_freeb; } ;
struct bfs_inode_info {scalar_t__ i_sblock; scalar_t__ i_eblock; scalar_t__ i_dsk_ino; } ;
struct bfs_inode {int dummy; } ;

/* Variables and functions */
 struct bfs_inode_info* BFS_I (struct inode*) ; 
 unsigned long BFS_INODES_PER_BLOCK ; 
 unsigned long BFS_ROOT_INO ; 
 struct bfs_sb_info* BFS_SB (struct super_block*) ; 
 int /*<<< orphan*/  CURRENT_TIME_SEC ; 
 int /*<<< orphan*/  brelse (struct buffer_head*) ; 
 int /*<<< orphan*/  clear_bit (unsigned long,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clear_inode (struct inode*) ; 
 int /*<<< orphan*/  dprintf (char*,unsigned long) ; 
 int /*<<< orphan*/  dump_imap (char*,struct super_block*) ; 
 int /*<<< orphan*/  mark_buffer_dirty (struct buffer_head*) ; 
 int /*<<< orphan*/  mark_inode_dirty (struct inode*) ; 
 int /*<<< orphan*/  memset (void*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 struct buffer_head* sb_bread (struct super_block*,int) ; 
 int /*<<< orphan*/  truncate_inode_pages (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void bfs_delete_inode(struct inode *inode)
{
	unsigned long ino = inode->i_ino;
	struct bfs_inode *di;
	struct buffer_head *bh;
	int block, off;
	struct super_block *s = inode->i_sb;
	struct bfs_sb_info *info = BFS_SB(s);
	struct bfs_inode_info *bi = BFS_I(inode);

	dprintf("ino=%08lx\n", ino);

	truncate_inode_pages(&inode->i_data, 0);

	if ((ino < BFS_ROOT_INO) || (ino > info->si_lasti)) {
		printf("invalid ino=%08lx\n", ino);
		return;
	}
	
	inode->i_size = 0;
	inode->i_atime = inode->i_mtime = inode->i_ctime = CURRENT_TIME_SEC;
	mutex_lock(&info->bfs_lock);
	mark_inode_dirty(inode);

	block = (ino - BFS_ROOT_INO) / BFS_INODES_PER_BLOCK + 1;
	bh = sb_bread(s, block);
	if (!bh) {
		printf("Unable to read inode %s:%08lx\n",
					inode->i_sb->s_id, ino);
		mutex_unlock(&info->bfs_lock);
		return;
	}
	off = (ino - BFS_ROOT_INO) % BFS_INODES_PER_BLOCK;
	di = (struct bfs_inode *)bh->b_data + off;
	memset((void *)di, 0, sizeof(struct bfs_inode));
	mark_buffer_dirty(bh);
	brelse(bh);

        if (bi->i_dsk_ino) {
		if (bi->i_sblock)
			info->si_freeb += bi->i_eblock + 1 - bi->i_sblock;
		info->si_freei++;
		clear_bit(ino, info->si_imap);
		dump_imap("delete_inode", s);
        }

	/*
	 * If this was the last file, make the previous block
	 * "last block of the last file" even if there is no
	 * real file there, saves us 1 gap.
	 */
	if (info->si_lf_eblk == bi->i_eblock) {
		info->si_lf_eblk = bi->i_sblock - 1;
		mark_buffer_dirty(info->si_sbh);
	}
	mutex_unlock(&info->bfs_lock);
	clear_inode(inode);
}