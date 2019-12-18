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
struct quad_buffer_head {int dummy; } ;
struct inode {int /*<<< orphan*/  i_sb; int /*<<< orphan*/  i_ino; int /*<<< orphan*/  i_mode; } ;
struct hpfs_dirent {int hidden; int /*<<< orphan*/ * name; } ;
struct fnode {int len; int /*<<< orphan*/ * name; int /*<<< orphan*/  up; } ;
struct TYPE_4__ {int len; scalar_t__ name; } ;
struct dentry {struct inode* d_inode; TYPE_1__ d_name; } ;
struct buffer_head {int dummy; } ;
typedef  int /*<<< orphan*/  dnode_secno ;
struct TYPE_6__ {int /*<<< orphan*/  i_parent_mutex; int /*<<< orphan*/  i_mutex; int /*<<< orphan*/  i_conv; int /*<<< orphan*/  i_parent_dir; int /*<<< orphan*/  i_dno; } ;
struct TYPE_5__ {int /*<<< orphan*/  sb_conv; } ;

/* Variables and functions */
 int EFSERROR ; 
 int EINVAL ; 
 int ENOENT ; 
 int ENOSPC ; 
 scalar_t__ S_ISDIR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  brelse (struct buffer_head*) ; 
 int /*<<< orphan*/  clear_nlink (struct inode*) ; 
 int /*<<< orphan*/  copy_de (struct hpfs_dirent*,struct hpfs_dirent*) ; 
 int /*<<< orphan*/  drop_nlink (struct inode*) ; 
 int hpfs_add_dirent (struct inode*,char*,int,struct hpfs_dirent*,int) ; 
 int /*<<< orphan*/  hpfs_adjust_length (char*,int*) ; 
 int /*<<< orphan*/  hpfs_brelse4 (struct quad_buffer_head*) ; 
 int hpfs_chk_name (char*,int*) ; 
 int /*<<< orphan*/  hpfs_decide_conv (struct inode*,char*,int) ; 
 int /*<<< orphan*/  hpfs_error (int /*<<< orphan*/ ,char*) ; 
 TYPE_3__* hpfs_i (struct inode*) ; 
 int /*<<< orphan*/  hpfs_lock_creation (int /*<<< orphan*/ ) ; 
 struct fnode* hpfs_map_fnode (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct buffer_head**) ; 
 int /*<<< orphan*/  hpfs_mark_4buffers_dirty (struct quad_buffer_head*) ; 
 int hpfs_remove_dirent (struct inode*,int /*<<< orphan*/ ,struct hpfs_dirent*,struct quad_buffer_head*,int) ; 
 TYPE_2__* hpfs_sb (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hpfs_unlock_creation (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  inc_nlink (struct inode*) ; 
 int /*<<< orphan*/  lock_kernel () ; 
 struct hpfs_dirent* map_dirent (struct inode*,int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ *,struct quad_buffer_head*) ; 
 int /*<<< orphan*/  mark_buffer_dirty (struct buffer_head*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  unlock_kernel () ; 

__attribute__((used)) static int hpfs_rename(struct inode *old_dir, struct dentry *old_dentry,
		struct inode *new_dir, struct dentry *new_dentry)
{
	char *old_name = (char *)old_dentry->d_name.name;
	int old_len = old_dentry->d_name.len;
	char *new_name = (char *)new_dentry->d_name.name;
	int new_len = new_dentry->d_name.len;
	struct inode *i = old_dentry->d_inode;
	struct inode *new_inode = new_dentry->d_inode;
	struct quad_buffer_head qbh, qbh1;
	struct hpfs_dirent *dep, *nde;
	struct hpfs_dirent de;
	dnode_secno dno;
	int r;
	struct buffer_head *bh;
	struct fnode *fnode;
	int err;
	if ((err = hpfs_chk_name((char *)new_name, &new_len))) return err;
	err = 0;
	hpfs_adjust_length((char *)old_name, &old_len);

	lock_kernel();
	/* order doesn't matter, due to VFS exclusion */
	mutex_lock(&hpfs_i(i)->i_parent_mutex);
	if (new_inode)
		mutex_lock(&hpfs_i(new_inode)->i_parent_mutex);
	mutex_lock(&hpfs_i(old_dir)->i_mutex);
	if (new_dir != old_dir)
		mutex_lock(&hpfs_i(new_dir)->i_mutex);
	
	/* Erm? Moving over the empty non-busy directory is perfectly legal */
	if (new_inode && S_ISDIR(new_inode->i_mode)) {
		err = -EINVAL;
		goto end1;
	}

	if (!(dep = map_dirent(old_dir, hpfs_i(old_dir)->i_dno, (char *)old_name, old_len, &dno, &qbh))) {
		hpfs_error(i->i_sb, "lookup succeeded but map dirent failed");
		err = -ENOENT;
		goto end1;
	}
	copy_de(&de, dep);
	de.hidden = new_name[0] == '.';

	if (new_inode) {
		int r;
		if ((r = hpfs_remove_dirent(old_dir, dno, dep, &qbh, 1)) != 2) {
			if ((nde = map_dirent(new_dir, hpfs_i(new_dir)->i_dno, (char *)new_name, new_len, NULL, &qbh1))) {
				clear_nlink(new_inode);
				copy_de(nde, &de);
				memcpy(nde->name, new_name, new_len);
				hpfs_mark_4buffers_dirty(&qbh1);
				hpfs_brelse4(&qbh1);
				goto end;
			}
			hpfs_error(new_dir->i_sb, "hpfs_rename: could not find dirent");
			err = -EFSERROR;
			goto end1;
		}
		err = r == 2 ? -ENOSPC : r == 1 ? -EFSERROR : 0;
		goto end1;
	}

	if (new_dir == old_dir) hpfs_brelse4(&qbh);

	hpfs_lock_creation(i->i_sb);
	if ((r = hpfs_add_dirent(new_dir, new_name, new_len, &de, 1))) {
		hpfs_unlock_creation(i->i_sb);
		if (r == -1) hpfs_error(new_dir->i_sb, "hpfs_rename: dirent already exists!");
		err = r == 1 ? -ENOSPC : -EFSERROR;
		if (new_dir != old_dir) hpfs_brelse4(&qbh);
		goto end1;
	}
	
	if (new_dir == old_dir)
		if (!(dep = map_dirent(old_dir, hpfs_i(old_dir)->i_dno, (char *)old_name, old_len, &dno, &qbh))) {
			hpfs_unlock_creation(i->i_sb);
			hpfs_error(i->i_sb, "lookup succeeded but map dirent failed at #2");
			err = -ENOENT;
			goto end1;
		}

	if ((r = hpfs_remove_dirent(old_dir, dno, dep, &qbh, 0))) {
		hpfs_unlock_creation(i->i_sb);
		hpfs_error(i->i_sb, "hpfs_rename: could not remove dirent");
		err = r == 2 ? -ENOSPC : -EFSERROR;
		goto end1;
	}
	hpfs_unlock_creation(i->i_sb);
	
	end:
	hpfs_i(i)->i_parent_dir = new_dir->i_ino;
	if (S_ISDIR(i->i_mode)) {
		inc_nlink(new_dir);
		drop_nlink(old_dir);
	}
	if ((fnode = hpfs_map_fnode(i->i_sb, i->i_ino, &bh))) {
		fnode->up = new_dir->i_ino;
		fnode->len = new_len;
		memcpy(fnode->name, new_name, new_len>15?15:new_len);
		if (new_len < 15) memset(&fnode->name[new_len], 0, 15 - new_len);
		mark_buffer_dirty(bh);
		brelse(bh);
	}
	hpfs_i(i)->i_conv = hpfs_sb(i->i_sb)->sb_conv;
	hpfs_decide_conv(i, (char *)new_name, new_len);
end1:
	if (old_dir != new_dir)
		mutex_unlock(&hpfs_i(new_dir)->i_mutex);
	mutex_unlock(&hpfs_i(old_dir)->i_mutex);
	mutex_unlock(&hpfs_i(i)->i_parent_mutex);
	if (new_inode)
		mutex_unlock(&hpfs_i(new_inode)->i_parent_mutex);
	unlock_kernel();
	return err;
}