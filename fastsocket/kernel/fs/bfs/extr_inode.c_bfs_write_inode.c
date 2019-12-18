#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_6__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  unsigned int u16 ;
struct writeback_control {scalar_t__ sync_mode; } ;
struct TYPE_9__ {unsigned long tv_sec; } ;
struct TYPE_8__ {unsigned long tv_sec; } ;
struct TYPE_7__ {unsigned long tv_sec; } ;
struct inode {unsigned long i_mode; unsigned long i_uid; unsigned long i_gid; unsigned long i_nlink; unsigned long i_size; TYPE_3__ i_ctime; TYPE_2__ i_mtime; TYPE_1__ i_atime; TYPE_4__* i_sb; int /*<<< orphan*/  i_ino; } ;
struct buffer_head {scalar_t__ b_data; } ;
struct bfs_sb_info {unsigned int si_lasti; int /*<<< orphan*/  bfs_lock; } ;
struct bfs_inode {void* i_eoffset; void* i_eblock; void* i_sblock; void* i_ctime; void* i_mtime; void* i_atime; void* i_nlink; void* i_gid; void* i_uid; void* i_mode; int /*<<< orphan*/  i_ino; void* i_vtype; } ;
struct TYPE_11__ {unsigned long i_sblock; unsigned long i_eblock; } ;
struct TYPE_10__ {char* s_id; } ;

/* Variables and functions */
 unsigned long BFS_BSIZE ; 
 TYPE_6__* BFS_I (struct inode*) ; 
 unsigned int BFS_INODES_PER_BLOCK ; 
 unsigned int BFS_ROOT_INO ; 
 struct bfs_sb_info* BFS_SB (TYPE_4__*) ; 
 unsigned long BFS_VDIR ; 
 unsigned long BFS_VREG ; 
 int EIO ; 
 scalar_t__ WB_SYNC_ALL ; 
 int /*<<< orphan*/  brelse (struct buffer_head*) ; 
 scalar_t__ buffer_req (struct buffer_head*) ; 
 int /*<<< orphan*/  buffer_uptodate (struct buffer_head*) ; 
 int /*<<< orphan*/  cpu_to_le16 (unsigned int) ; 
 void* cpu_to_le32 (unsigned long) ; 
 int /*<<< orphan*/  dprintf (char*,unsigned int) ; 
 int /*<<< orphan*/  mark_buffer_dirty (struct buffer_head*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  printf (char*,char*,unsigned int) ; 
 struct buffer_head* sb_bread (TYPE_4__*,int) ; 
 int /*<<< orphan*/  sync_dirty_buffer (struct buffer_head*) ; 

__attribute__((used)) static int bfs_write_inode(struct inode *inode, struct writeback_control *wbc)
{
	struct bfs_sb_info *info = BFS_SB(inode->i_sb);
	unsigned int ino = (u16)inode->i_ino;
        unsigned long i_sblock;
	struct bfs_inode *di;
	struct buffer_head *bh;
	int block, off;
	int err = 0;

        dprintf("ino=%08x\n", ino);

	if ((ino < BFS_ROOT_INO) || (ino > BFS_SB(inode->i_sb)->si_lasti)) {
		printf("Bad inode number %s:%08x\n", inode->i_sb->s_id, ino);
		return -EIO;
	}

	mutex_lock(&info->bfs_lock);
	block = (ino - BFS_ROOT_INO) / BFS_INODES_PER_BLOCK + 1;
	bh = sb_bread(inode->i_sb, block);
	if (!bh) {
		printf("Unable to read inode %s:%08x\n",
				inode->i_sb->s_id, ino);
		mutex_unlock(&info->bfs_lock);
		return -EIO;
	}

	off = (ino - BFS_ROOT_INO) % BFS_INODES_PER_BLOCK;
	di = (struct bfs_inode *)bh->b_data + off;

	if (ino == BFS_ROOT_INO)
		di->i_vtype = cpu_to_le32(BFS_VDIR);
	else
		di->i_vtype = cpu_to_le32(BFS_VREG);

	di->i_ino = cpu_to_le16(ino);
	di->i_mode = cpu_to_le32(inode->i_mode);
	di->i_uid = cpu_to_le32(inode->i_uid);
	di->i_gid = cpu_to_le32(inode->i_gid);
	di->i_nlink = cpu_to_le32(inode->i_nlink);
	di->i_atime = cpu_to_le32(inode->i_atime.tv_sec);
	di->i_mtime = cpu_to_le32(inode->i_mtime.tv_sec);
	di->i_ctime = cpu_to_le32(inode->i_ctime.tv_sec);
        i_sblock = BFS_I(inode)->i_sblock;
	di->i_sblock = cpu_to_le32(i_sblock);
	di->i_eblock = cpu_to_le32(BFS_I(inode)->i_eblock);
	di->i_eoffset = cpu_to_le32(i_sblock * BFS_BSIZE + inode->i_size - 1);

	mark_buffer_dirty(bh);
	if (wbc->sync_mode == WB_SYNC_ALL) {
		sync_dirty_buffer(bh);
		if (buffer_req(bh) && !buffer_uptodate(bh))
			err = -EIO;
	}
	brelse(bh);
	mutex_unlock(&info->bfs_lock);
	return err;
}