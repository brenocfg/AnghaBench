#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct vfsmount {int dummy; } ;
struct inode {int /*<<< orphan*/  i_ino; int /*<<< orphan*/  i_fop; int /*<<< orphan*/  i_mode; } ;
struct getdents_callback {char* name; int sequence; scalar_t__ found; int /*<<< orphan*/  ino; } ;
struct file {TYPE_1__* f_op; } ;
struct dentry {struct inode* d_inode; } ;
struct cred {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  readdir; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOENT ; 
 int ENOTDIR ; 
 scalar_t__ IS_ERR (struct file*) ; 
 int /*<<< orphan*/  O_RDONLY ; 
 int PTR_ERR (struct file*) ; 
 int /*<<< orphan*/  S_ISDIR (int /*<<< orphan*/ ) ; 
 struct cred* current_cred () ; 
 struct file* dentry_open (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct cred const*) ; 
 int /*<<< orphan*/  dget (struct dentry*) ; 
 int /*<<< orphan*/  filldir_one ; 
 int /*<<< orphan*/  fput (struct file*) ; 
 int /*<<< orphan*/  mntget (struct vfsmount*) ; 
 int vfs_readdir (struct file*,int /*<<< orphan*/ ,struct getdents_callback*) ; 

__attribute__((used)) static int get_name(struct vfsmount *mnt, struct dentry *dentry,
		char *name, struct dentry *child)
{
	const struct cred *cred = current_cred();
	struct inode *dir = dentry->d_inode;
	int error;
	struct file *file;
	struct getdents_callback buffer;

	error = -ENOTDIR;
	if (!dir || !S_ISDIR(dir->i_mode))
		goto out;
	error = -EINVAL;
	if (!dir->i_fop)
		goto out;
	/*
	 * Open the directory ...
	 */
	file = dentry_open(dget(dentry), mntget(mnt), O_RDONLY, cred);
	error = PTR_ERR(file);
	if (IS_ERR(file))
		goto out;

	error = -EINVAL;
	if (!file->f_op->readdir)
		goto out_close;

	buffer.name = name;
	buffer.ino = child->d_inode->i_ino;
	buffer.found = 0;
	buffer.sequence = 0;
	while (1) {
		int old_seq = buffer.sequence;

		error = vfs_readdir(file, filldir_one, &buffer);
		if (buffer.found) {
			error = 0;
			break;
		}

		if (error < 0)
			break;

		error = -ENOENT;
		if (old_seq == buffer.sequence)
			break;
	}

out_close:
	fput(file);
out:
	return error;
}