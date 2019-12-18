#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct super_block {int dummy; } ;
struct nameidata {int dummy; } ;
struct inode {int i_mode; unsigned long i_ino; TYPE_1__* i_mapping; int /*<<< orphan*/ * i_fop; int /*<<< orphan*/ * i_op; scalar_t__ i_blocks; int /*<<< orphan*/  i_ctime; int /*<<< orphan*/  i_atime; int /*<<< orphan*/  i_mtime; int /*<<< orphan*/  i_gid; int /*<<< orphan*/  i_uid; struct super_block* i_sb; } ;
struct TYPE_5__ {int /*<<< orphan*/  len; int /*<<< orphan*/  name; } ;
struct dentry {TYPE_2__ d_name; } ;
struct bfs_sb_info {unsigned long si_lasti; int /*<<< orphan*/  bfs_lock; int /*<<< orphan*/  si_freei; int /*<<< orphan*/  si_imap; } ;
struct TYPE_6__ {unsigned long i_dsk_ino; scalar_t__ i_eblock; scalar_t__ i_sblock; } ;
struct TYPE_4__ {int /*<<< orphan*/ * a_ops; } ;

/* Variables and functions */
 TYPE_3__* BFS_I (struct inode*) ; 
 struct bfs_sb_info* BFS_SB (struct super_block*) ; 
 int /*<<< orphan*/  CURRENT_TIME_SEC ; 
 int ENOSPC ; 
 int S_ISGID ; 
 int bfs_add_entry (struct inode*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  bfs_aops ; 
 int /*<<< orphan*/  bfs_file_inops ; 
 int /*<<< orphan*/  bfs_file_operations ; 
 int /*<<< orphan*/  current_fsgid () ; 
 int /*<<< orphan*/  current_fsuid () ; 
 int /*<<< orphan*/  d_instantiate (struct dentry*,struct inode*) ; 
 int /*<<< orphan*/  dump_imap (char*,struct super_block*) ; 
 unsigned long find_first_zero_bit (int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  inode_dec_link_count (struct inode*) ; 
 int /*<<< orphan*/  insert_inode_hash (struct inode*) ; 
 int /*<<< orphan*/  iput (struct inode*) ; 
 int /*<<< orphan*/  mark_inode_dirty (struct inode*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct inode* new_inode (struct super_block*) ; 
 int /*<<< orphan*/  set_bit (unsigned long,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int bfs_create(struct inode *dir, struct dentry *dentry, int mode,
						struct nameidata *nd)
{
	int err;
	struct inode *inode;
	struct super_block *s = dir->i_sb;
	struct bfs_sb_info *info = BFS_SB(s);
	unsigned long ino;

	inode = new_inode(s);
	if (!inode)
		return -ENOSPC;
	mutex_lock(&info->bfs_lock);
	ino = find_first_zero_bit(info->si_imap, info->si_lasti);
	if (ino > info->si_lasti) {
		mutex_unlock(&info->bfs_lock);
		iput(inode);
		return -ENOSPC;
	}
	set_bit(ino, info->si_imap);
	info->si_freei--;
	inode->i_uid = current_fsuid();
	inode->i_gid = (dir->i_mode & S_ISGID) ? dir->i_gid : current_fsgid();
	inode->i_mtime = inode->i_atime = inode->i_ctime = CURRENT_TIME_SEC;
	inode->i_blocks = 0;
	inode->i_op = &bfs_file_inops;
	inode->i_fop = &bfs_file_operations;
	inode->i_mapping->a_ops = &bfs_aops;
	inode->i_mode = mode;
	inode->i_ino = ino;
	BFS_I(inode)->i_dsk_ino = ino;
	BFS_I(inode)->i_sblock = 0;
	BFS_I(inode)->i_eblock = 0;
	insert_inode_hash(inode);
        mark_inode_dirty(inode);
	dump_imap("create", s);

	err = bfs_add_entry(dir, dentry->d_name.name, dentry->d_name.len,
							inode->i_ino);
	if (err) {
		inode_dec_link_count(inode);
		mutex_unlock(&info->bfs_lock);
		iput(inode);
		return err;
	}
	mutex_unlock(&info->bfs_lock);
	d_instantiate(dentry, inode);
	return 0;
}