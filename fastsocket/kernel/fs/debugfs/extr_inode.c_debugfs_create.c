#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct inode {int dummy; } ;
struct file_operations {int dummy; } ;
struct dentry {int dummy; } ;

/* Variables and functions */
 int S_IALLUGO ; 
 int S_IFREG ; 
 int debugfs_mknod (struct inode*,struct dentry*,int,int /*<<< orphan*/ ,void*,struct file_operations const*) ; 
 int /*<<< orphan*/  fsnotify_create (struct inode*,struct dentry*) ; 

__attribute__((used)) static int debugfs_create(struct inode *dir, struct dentry *dentry, int mode,
			  void *data, const struct file_operations *fops)
{
	int res;

	mode = (mode & S_IALLUGO) | S_IFREG;
	res = debugfs_mknod(dir, dentry, mode, 0, data, fops);
	if (!res)
		fsnotify_create(dir, dentry);
	return res;
}