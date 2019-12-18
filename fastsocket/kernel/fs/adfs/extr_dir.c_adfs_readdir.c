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
struct object_info {char* name; int name_len; int /*<<< orphan*/  file_id; } ;
struct inode {int /*<<< orphan*/  i_ino; int /*<<< orphan*/  i_size; struct super_block* i_sb; } ;
struct TYPE_5__ {TYPE_1__* dentry; } ;
struct file {int f_pos; TYPE_2__ f_path; } ;
struct adfs_dir_ops {int (* read ) (struct super_block*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct adfs_dir*) ;int (* setpos ) (struct adfs_dir*,int) ;scalar_t__ (* getnext ) (struct adfs_dir*,struct object_info*) ;int /*<<< orphan*/  (* free ) (struct adfs_dir*) ;} ;
struct adfs_dir {int /*<<< orphan*/  parent_id; } ;
typedef  scalar_t__ (* filldir_t ) (void*,char*,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;
struct TYPE_6__ {struct adfs_dir_ops* s_dir; } ;
struct TYPE_4__ {struct inode* d_inode; } ;

/* Variables and functions */
 TYPE_3__* ADFS_SB (struct super_block*) ; 
 int /*<<< orphan*/  DT_DIR ; 
 int /*<<< orphan*/  DT_UNKNOWN ; 
 int /*<<< orphan*/  adfs_dir_lock ; 
 int /*<<< orphan*/  lock_kernel () ; 
 int /*<<< orphan*/  read_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  read_unlock (int /*<<< orphan*/ *) ; 
 int stub1 (struct super_block*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct adfs_dir*) ; 
 int stub2 (struct adfs_dir*,int) ; 
 scalar_t__ stub3 (struct adfs_dir*,struct object_info*) ; 
 int /*<<< orphan*/  stub4 (struct adfs_dir*) ; 
 int /*<<< orphan*/  unlock_kernel () ; 

__attribute__((used)) static int
adfs_readdir(struct file *filp, void *dirent, filldir_t filldir)
{
	struct inode *inode = filp->f_path.dentry->d_inode;
	struct super_block *sb = inode->i_sb;
	struct adfs_dir_ops *ops = ADFS_SB(sb)->s_dir;
	struct object_info obj;
	struct adfs_dir dir;
	int ret = 0;

	lock_kernel();	

	if (filp->f_pos >> 32)
		goto out;

	ret = ops->read(sb, inode->i_ino, inode->i_size, &dir);
	if (ret)
		goto out;

	switch ((unsigned long)filp->f_pos) {
	case 0:
		if (filldir(dirent, ".", 1, 0, inode->i_ino, DT_DIR) < 0)
			goto free_out;
		filp->f_pos += 1;

	case 1:
		if (filldir(dirent, "..", 2, 1, dir.parent_id, DT_DIR) < 0)
			goto free_out;
		filp->f_pos += 1;

	default:
		break;
	}

	read_lock(&adfs_dir_lock);

	ret = ops->setpos(&dir, filp->f_pos - 2);
	if (ret)
		goto unlock_out;
	while (ops->getnext(&dir, &obj) == 0) {
		if (filldir(dirent, obj.name, obj.name_len,
			    filp->f_pos, obj.file_id, DT_UNKNOWN) < 0)
			goto unlock_out;
		filp->f_pos += 1;
	}

unlock_out:
	read_unlock(&adfs_dir_lock);

free_out:
	ops->free(&dir);

out:
	unlock_kernel();
	return ret;
}