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
struct vfsmount {int dummy; } ;
struct inode {TYPE_1__* i_sb; } ;
struct hppfs_private {int /*<<< orphan*/  proc_file; } ;
struct file {struct hppfs_private* private_data; int /*<<< orphan*/  f_mode; struct cred* f_cred; } ;
struct dentry {int dummy; } ;
struct cred {int dummy; } ;
struct TYPE_4__ {struct dentry* proc_dentry; } ;
struct TYPE_3__ {struct vfsmount* s_fs_info; } ;

/* Variables and functions */
 int ENOMEM ; 
 TYPE_2__* HPPFS_I (struct inode*) ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dentry_open (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct cred const*) ; 
 int /*<<< orphan*/  dget (struct dentry*) ; 
 int /*<<< orphan*/  file_mode (int /*<<< orphan*/ ) ; 
 struct hppfs_private* hppfs_data () ; 
 int /*<<< orphan*/  kfree (struct hppfs_private*) ; 
 int /*<<< orphan*/  mntget (struct vfsmount*) ; 

__attribute__((used)) static int hppfs_dir_open(struct inode *inode, struct file *file)
{
	const struct cred *cred = file->f_cred;
	struct hppfs_private *data;
	struct vfsmount *proc_mnt;
	struct dentry *proc_dentry;
	int err;

	err = -ENOMEM;
	data = hppfs_data();
	if (data == NULL)
		goto out;

	proc_dentry = HPPFS_I(inode)->proc_dentry;
	proc_mnt = inode->i_sb->s_fs_info;
	data->proc_file = dentry_open(dget(proc_dentry), mntget(proc_mnt),
				      file_mode(file->f_mode), cred);
	err = PTR_ERR(data->proc_file);
	if (IS_ERR(data->proc_file))
		goto out_free;

	file->private_data = data;
	return 0;

 out_free:
	kfree(data);
 out:
	return err;
}