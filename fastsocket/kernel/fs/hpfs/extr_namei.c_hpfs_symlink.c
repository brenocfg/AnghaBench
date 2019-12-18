#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_7__ ;
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {int /*<<< orphan*/ * a_ops; } ;
struct TYPE_11__ {scalar_t__ tv_nsec; int /*<<< orphan*/  tv_sec; } ;
struct TYPE_10__ {scalar_t__ tv_nsec; int /*<<< orphan*/  tv_sec; } ;
struct TYPE_9__ {scalar_t__ tv_nsec; int /*<<< orphan*/  tv_sec; } ;
struct inode {int i_mode; int i_blocks; int i_nlink; int /*<<< orphan*/  i_sb; void* i_ino; TYPE_5__ i_data; int /*<<< orphan*/ * i_op; int /*<<< orphan*/  i_size; int /*<<< orphan*/  i_gid; int /*<<< orphan*/  i_uid; TYPE_4__ i_atime; TYPE_3__ i_mtime; TYPE_2__ i_ctime; } ;
struct hpfs_dirent {int archive; int hidden; int /*<<< orphan*/  creation_date; int /*<<< orphan*/  read_date; int /*<<< orphan*/  write_date; void* fnode; } ;
struct fnode {unsigned int len; void* up; int /*<<< orphan*/  name; } ;
struct TYPE_8__ {char* name; unsigned int len; } ;
struct dentry {TYPE_1__ d_name; } ;
struct buffer_head {int dummy; } ;
typedef  void* fnode_secno ;
struct TYPE_14__ {int /*<<< orphan*/  i_mutex; scalar_t__ i_ea_size; void* i_parent_dir; int /*<<< orphan*/  i_dno; } ;
struct TYPE_13__ {int sb_eas; } ;

/* Variables and functions */
 int EEXIST ; 
 int EINVAL ; 
 int ENOENT ; 
 int ENOSPC ; 
 int EPERM ; 
 int S_IFLNK ; 
 int /*<<< orphan*/  brelse (struct buffer_head*) ; 
 int /*<<< orphan*/  current_fsgid () ; 
 int /*<<< orphan*/  current_fsuid () ; 
 int /*<<< orphan*/  d_instantiate (struct dentry*,struct inode*) ; 
 int /*<<< orphan*/  get_seconds () ; 
 int /*<<< orphan*/  gmt_to_local (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int hpfs_add_dirent (struct inode*,char*,unsigned int,struct hpfs_dirent*,int /*<<< orphan*/ ) ; 
 struct fnode* hpfs_alloc_fnode (int /*<<< orphan*/ ,int /*<<< orphan*/ ,void**,struct buffer_head**) ; 
 int hpfs_chk_name (char*,unsigned int*) ; 
 int /*<<< orphan*/  hpfs_free_sectors (int /*<<< orphan*/ ,void*,int) ; 
 TYPE_7__* hpfs_i (struct inode*) ; 
 int /*<<< orphan*/  hpfs_init_inode (struct inode*) ; 
 TYPE_6__* hpfs_sb (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hpfs_set_ea (struct inode*,struct fnode*,char*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hpfs_symlink_aops ; 
 int /*<<< orphan*/  hpfs_write_inode_nolock (struct inode*) ; 
 int /*<<< orphan*/  insert_inode_hash (struct inode*) ; 
 int /*<<< orphan*/  iput (struct inode*) ; 
 int /*<<< orphan*/  local_to_gmt (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lock_kernel () ; 
 int /*<<< orphan*/  mark_buffer_dirty (struct buffer_head*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,char const*,int) ; 
 int /*<<< orphan*/  memset (struct hpfs_dirent*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct inode* new_inode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  page_symlink_inode_operations ; 
 int /*<<< orphan*/  strlen (char const*) ; 
 int /*<<< orphan*/  unlock_kernel () ; 

__attribute__((used)) static int hpfs_symlink(struct inode *dir, struct dentry *dentry, const char *symlink)
{
	const char *name = dentry->d_name.name;
	unsigned len = dentry->d_name.len;
	struct buffer_head *bh;
	struct fnode *fnode;
	fnode_secno fno;
	int r;
	struct hpfs_dirent dee;
	struct inode *result;
	int err;
	if ((err = hpfs_chk_name((char *)name, &len))) return err==-ENOENT ? -EINVAL : err;
	lock_kernel();
	if (hpfs_sb(dir->i_sb)->sb_eas < 2) {
		unlock_kernel();
		return -EPERM;
	}
	err = -ENOSPC;
	fnode = hpfs_alloc_fnode(dir->i_sb, hpfs_i(dir)->i_dno, &fno, &bh);
	if (!fnode)
		goto bail;
	memset(&dee, 0, sizeof dee);
	dee.archive = 1;
	dee.hidden = name[0] == '.';
	dee.fnode = fno;
	dee.creation_date = dee.write_date = dee.read_date = gmt_to_local(dir->i_sb, get_seconds());

	result = new_inode(dir->i_sb);
	if (!result)
		goto bail1;
	result->i_ino = fno;
	hpfs_init_inode(result);
	hpfs_i(result)->i_parent_dir = dir->i_ino;
	result->i_ctime.tv_sec = result->i_mtime.tv_sec = result->i_atime.tv_sec = local_to_gmt(dir->i_sb, dee.creation_date);
	result->i_ctime.tv_nsec = 0;
	result->i_mtime.tv_nsec = 0;
	result->i_atime.tv_nsec = 0;
	hpfs_i(result)->i_ea_size = 0;
	result->i_mode = S_IFLNK | 0777;
	result->i_uid = current_fsuid();
	result->i_gid = current_fsgid();
	result->i_blocks = 1;
	result->i_nlink = 1;
	result->i_size = strlen(symlink);
	result->i_op = &page_symlink_inode_operations;
	result->i_data.a_ops = &hpfs_symlink_aops;

	mutex_lock(&hpfs_i(dir)->i_mutex);
	r = hpfs_add_dirent(dir, (char *)name, len, &dee, 0);
	if (r == 1)
		goto bail2;
	if (r == -1) {
		err = -EEXIST;
		goto bail2;
	}
	fnode->len = len;
	memcpy(fnode->name, name, len > 15 ? 15 : len);
	fnode->up = dir->i_ino;
	hpfs_set_ea(result, fnode, "SYMLINK", (char *)symlink, strlen(symlink));
	mark_buffer_dirty(bh);
	brelse(bh);

	insert_inode_hash(result);

	hpfs_write_inode_nolock(result);
	d_instantiate(dentry, result);
	mutex_unlock(&hpfs_i(dir)->i_mutex);
	unlock_kernel();
	return 0;
bail2:
	mutex_unlock(&hpfs_i(dir)->i_mutex);
	iput(result);
bail1:
	brelse(bh);
	hpfs_free_sectors(dir->i_sb, fno, 1);
bail:
	unlock_kernel();
	return err;
}