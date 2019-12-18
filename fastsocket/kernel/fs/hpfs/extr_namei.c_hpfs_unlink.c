#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct quad_buffer_head {int dummy; } ;
struct inode {int /*<<< orphan*/  i_mode; int /*<<< orphan*/  i_sb; } ;
struct iattr {int ia_valid; int /*<<< orphan*/  ia_size; } ;
struct hpfs_dirent {int /*<<< orphan*/  fnode; scalar_t__ directory; scalar_t__ first; } ;
struct TYPE_3__ {char* name; unsigned int len; } ;
struct dentry {int /*<<< orphan*/  d_lock; int /*<<< orphan*/  d_count; struct inode* d_inode; TYPE_1__ d_name; } ;
typedef  int /*<<< orphan*/  fnode_secno ;
typedef  int /*<<< orphan*/  dnode_secno ;
struct TYPE_4__ {int /*<<< orphan*/  i_parent_mutex; int /*<<< orphan*/  i_mutex; int /*<<< orphan*/  i_dno; } ;

/* Variables and functions */
 int ATTR_CTIME ; 
 int ATTR_SIZE ; 
 int EFSERROR ; 
 int EISDIR ; 
 int ENOENT ; 
 int ENOSPC ; 
 int EPERM ; 
 int /*<<< orphan*/  MAY_WRITE ; 
 int /*<<< orphan*/  S_ISREG (int /*<<< orphan*/ ) ; 
 int atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  d_drop (struct dentry*) ; 
 int /*<<< orphan*/  d_rehash (struct dentry*) ; 
 int /*<<< orphan*/  drop_nlink (struct inode*) ; 
 int /*<<< orphan*/  generic_permission (struct inode*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  get_write_access (struct inode*) ; 
 int /*<<< orphan*/  hpfs_adjust_length (char*,unsigned int*) ; 
 int /*<<< orphan*/  hpfs_brelse4 (struct quad_buffer_head*) ; 
 int /*<<< orphan*/  hpfs_error (int /*<<< orphan*/ ,char*) ; 
 TYPE_2__* hpfs_i (struct inode*) ; 
 int hpfs_remove_dirent (struct inode*,int /*<<< orphan*/ ,struct hpfs_dirent*,struct quad_buffer_head*,int) ; 
 int /*<<< orphan*/  lock_kernel () ; 
 struct hpfs_dirent* map_dirent (struct inode*,int /*<<< orphan*/ ,char*,unsigned int,int /*<<< orphan*/ *,struct quad_buffer_head*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int notify_change (struct dentry*,struct iattr*) ; 
 int /*<<< orphan*/  put_write_access (struct inode*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  unlock_kernel () ; 

__attribute__((used)) static int hpfs_unlink(struct inode *dir, struct dentry *dentry)
{
	const char *name = dentry->d_name.name;
	unsigned len = dentry->d_name.len;
	struct quad_buffer_head qbh;
	struct hpfs_dirent *de;
	struct inode *inode = dentry->d_inode;
	dnode_secno dno;
	fnode_secno fno;
	int r;
	int rep = 0;
	int err;

	lock_kernel();
	hpfs_adjust_length((char *)name, &len);
again:
	mutex_lock(&hpfs_i(inode)->i_parent_mutex);
	mutex_lock(&hpfs_i(dir)->i_mutex);
	err = -ENOENT;
	de = map_dirent(dir, hpfs_i(dir)->i_dno, (char *)name, len, &dno, &qbh);
	if (!de)
		goto out;

	err = -EPERM;
	if (de->first)
		goto out1;

	err = -EISDIR;
	if (de->directory)
		goto out1;

	fno = de->fnode;
	r = hpfs_remove_dirent(dir, dno, de, &qbh, 1);
	switch (r) {
	case 1:
		hpfs_error(dir->i_sb, "there was error when removing dirent");
		err = -EFSERROR;
		break;
	case 2:		/* no space for deleting, try to truncate file */

		err = -ENOSPC;
		if (rep++)
			break;

		mutex_unlock(&hpfs_i(dir)->i_mutex);
		mutex_unlock(&hpfs_i(inode)->i_parent_mutex);
		d_drop(dentry);
		spin_lock(&dentry->d_lock);
		if (atomic_read(&dentry->d_count) > 1 ||
		    generic_permission(inode, MAY_WRITE, NULL) ||
		    !S_ISREG(inode->i_mode) ||
		    get_write_access(inode)) {
			spin_unlock(&dentry->d_lock);
			d_rehash(dentry);
		} else {
			struct iattr newattrs;
			spin_unlock(&dentry->d_lock);
			/*printk("HPFS: truncating file before delete.\n");*/
			newattrs.ia_size = 0;
			newattrs.ia_valid = ATTR_SIZE | ATTR_CTIME;
			err = notify_change(dentry, &newattrs);
			put_write_access(inode);
			if (!err)
				goto again;
		}
		unlock_kernel();
		return -ENOSPC;
	default:
		drop_nlink(inode);
		err = 0;
	}
	goto out;

out1:
	hpfs_brelse4(&qbh);
out:
	mutex_unlock(&hpfs_i(dir)->i_mutex);
	mutex_unlock(&hpfs_i(inode)->i_parent_mutex);
	unlock_kernel();
	return err;
}