#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_8__ ;
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct super_block {int dummy; } ;
struct TYPE_12__ {int tv_sec; scalar_t__ tv_nsec; } ;
struct TYPE_11__ {int tv_sec; scalar_t__ tv_nsec; } ;
struct TYPE_10__ {int tv_sec; scalar_t__ tv_nsec; } ;
struct inode {int i_state; int i_mode; int i_uid; int i_gid; int i_nlink; TYPE_4__ i_ctime; TYPE_3__ i_mtime; TYPE_2__ i_atime; int /*<<< orphan*/  i_blocks; int /*<<< orphan*/  i_size; TYPE_1__* i_mapping; int /*<<< orphan*/ * i_fop; int /*<<< orphan*/ * i_op; TYPE_5__* i_sb; } ;
struct buffer_head {scalar_t__ b_data; } ;
struct bfs_inode {int /*<<< orphan*/  i_ctime; int /*<<< orphan*/  i_mtime; int /*<<< orphan*/  i_atime; int /*<<< orphan*/  i_nlink; int /*<<< orphan*/  i_gid; int /*<<< orphan*/  i_uid; int /*<<< orphan*/  i_ino; int /*<<< orphan*/  i_eblock; int /*<<< orphan*/  i_sblock; int /*<<< orphan*/  i_vtype; int /*<<< orphan*/  i_mode; } ;
struct TYPE_15__ {int i_sblock; int i_eblock; int /*<<< orphan*/  i_dsk_ino; } ;
struct TYPE_14__ {unsigned long si_lasti; } ;
struct TYPE_13__ {char* s_id; } ;
struct TYPE_9__ {int /*<<< orphan*/ * a_ops; } ;

/* Variables and functions */
 int /*<<< orphan*/  BFS_FILEBLOCKS (struct bfs_inode*) ; 
 int /*<<< orphan*/  BFS_FILESIZE (struct bfs_inode*) ; 
 TYPE_8__* BFS_I (struct inode*) ; 
 unsigned long BFS_INODES_PER_BLOCK ; 
 unsigned long BFS_ROOT_INO ; 
 TYPE_6__* BFS_SB (TYPE_5__*) ; 
 int BFS_VDIR ; 
 int BFS_VREG ; 
 int /*<<< orphan*/  EIO ; 
 int /*<<< orphan*/  ENOMEM ; 
 struct inode* ERR_PTR (int /*<<< orphan*/ ) ; 
 scalar_t__ IS_ERR (struct inode*) ; 
 int I_NEW ; 
 int S_IFDIR ; 
 int S_IFREG ; 
 int /*<<< orphan*/  bfs_aops ; 
 int /*<<< orphan*/  bfs_dir_inops ; 
 int /*<<< orphan*/  bfs_dir_operations ; 
 int /*<<< orphan*/  bfs_file_inops ; 
 int /*<<< orphan*/  bfs_file_operations ; 
 int /*<<< orphan*/  brelse (struct buffer_head*) ; 
 int /*<<< orphan*/  iget_failed (struct inode*) ; 
 struct inode* iget_locked (struct super_block*,unsigned long) ; 
 int /*<<< orphan*/  le16_to_cpu (int /*<<< orphan*/ ) ; 
 int le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,char*,unsigned long) ; 
 struct buffer_head* sb_bread (TYPE_5__*,int) ; 
 int /*<<< orphan*/  unlock_new_inode (struct inode*) ; 

struct inode *bfs_iget(struct super_block *sb, unsigned long ino)
{
	struct bfs_inode *di;
	struct inode *inode;
	struct buffer_head *bh;
	int block, off;

	inode = iget_locked(sb, ino);
	if (IS_ERR(inode))
		return ERR_PTR(-ENOMEM);
	if (!(inode->i_state & I_NEW))
		return inode;

	if ((ino < BFS_ROOT_INO) || (ino > BFS_SB(inode->i_sb)->si_lasti)) {
		printf("Bad inode number %s:%08lx\n", inode->i_sb->s_id, ino);
		goto error;
	}

	block = (ino - BFS_ROOT_INO) / BFS_INODES_PER_BLOCK + 1;
	bh = sb_bread(inode->i_sb, block);
	if (!bh) {
		printf("Unable to read inode %s:%08lx\n", inode->i_sb->s_id,
									ino);
		goto error;
	}

	off = (ino - BFS_ROOT_INO) % BFS_INODES_PER_BLOCK;
	di = (struct bfs_inode *)bh->b_data + off;

	inode->i_mode = 0x0000FFFF & le32_to_cpu(di->i_mode);
	if (le32_to_cpu(di->i_vtype) == BFS_VDIR) {
		inode->i_mode |= S_IFDIR;
		inode->i_op = &bfs_dir_inops;
		inode->i_fop = &bfs_dir_operations;
	} else if (le32_to_cpu(di->i_vtype) == BFS_VREG) {
		inode->i_mode |= S_IFREG;
		inode->i_op = &bfs_file_inops;
		inode->i_fop = &bfs_file_operations;
		inode->i_mapping->a_ops = &bfs_aops;
	}

	BFS_I(inode)->i_sblock =  le32_to_cpu(di->i_sblock);
	BFS_I(inode)->i_eblock =  le32_to_cpu(di->i_eblock);
	BFS_I(inode)->i_dsk_ino = le16_to_cpu(di->i_ino);
	inode->i_uid =  le32_to_cpu(di->i_uid);
	inode->i_gid =  le32_to_cpu(di->i_gid);
	inode->i_nlink =  le32_to_cpu(di->i_nlink);
	inode->i_size = BFS_FILESIZE(di);
	inode->i_blocks = BFS_FILEBLOCKS(di);
	inode->i_atime.tv_sec =  le32_to_cpu(di->i_atime);
	inode->i_mtime.tv_sec =  le32_to_cpu(di->i_mtime);
	inode->i_ctime.tv_sec =  le32_to_cpu(di->i_ctime);
	inode->i_atime.tv_nsec = 0;
	inode->i_mtime.tv_nsec = 0;
	inode->i_ctime.tv_nsec = 0;

	brelse(bh);
	unlock_new_inode(inode);
	return inode;

error:
	iget_failed(inode);
	return ERR_PTR(-EIO);
}