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
struct inode {int dummy; } ;
struct TYPE_4__ {TYPE_1__* dentry; } ;
struct file {TYPE_2__ f_path; int /*<<< orphan*/  f_pos; } ;
struct ecryptfs_getdents_callback {scalar_t__ entries_written; scalar_t__ filldir_called; int /*<<< orphan*/  filldir; TYPE_1__* dentry; void* dirent; } ;
typedef  int /*<<< orphan*/  filldir_t ;
typedef  int /*<<< orphan*/  buf ;
struct TYPE_3__ {struct inode* d_inode; } ;

/* Variables and functions */
 struct file* ecryptfs_file_to_lower (struct file*) ; 
 int /*<<< orphan*/  ecryptfs_filldir ; 
 int /*<<< orphan*/  fsstack_copy_attr_atime (struct inode*,struct inode*) ; 
 int /*<<< orphan*/  memset (struct ecryptfs_getdents_callback*,int /*<<< orphan*/ ,int) ; 
 int vfs_readdir (struct file*,int /*<<< orphan*/ ,void*) ; 

__attribute__((used)) static int ecryptfs_readdir(struct file *file, void *dirent, filldir_t filldir)
{
	int rc;
	struct file *lower_file;
	struct inode *inode;
	struct ecryptfs_getdents_callback buf;

	lower_file = ecryptfs_file_to_lower(file);
	lower_file->f_pos = file->f_pos;
	inode = file->f_path.dentry->d_inode;
	memset(&buf, 0, sizeof(buf));
	buf.dirent = dirent;
	buf.dentry = file->f_path.dentry;
	buf.filldir = filldir;
	buf.filldir_called = 0;
	buf.entries_written = 0;
	rc = vfs_readdir(lower_file, ecryptfs_filldir, (void *)&buf);
	file->f_pos = lower_file->f_pos;
	if (rc < 0)
		goto out;
	if (buf.filldir_called && !buf.entries_written)
		goto out;
	if (rc >= 0)
		fsstack_copy_attr_atime(inode,
					lower_file->f_path.dentry->d_inode);
out:
	return rc;
}