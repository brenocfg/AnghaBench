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
struct vm_area_struct {int vm_flags; int /*<<< orphan*/ * vm_ops; } ;
struct inode {int dummy; } ;
struct fuse_inode {int /*<<< orphan*/  write_files; } ;
struct fuse_file {int /*<<< orphan*/  write_entry; } ;
struct fuse_conn {int /*<<< orphan*/  lock; } ;
struct file {struct fuse_file* private_data; TYPE_1__* f_dentry; } ;
struct TYPE_2__ {struct inode* d_inode; } ;

/* Variables and functions */
 int VM_MAYWRITE ; 
 int VM_SHARED ; 
 int /*<<< orphan*/  file_accessed (struct file*) ; 
 int /*<<< orphan*/  fuse_file_vm_ops ; 
 struct fuse_conn* get_fuse_conn (struct inode*) ; 
 struct fuse_inode* get_fuse_inode (struct inode*) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int fuse_file_mmap(struct file *file, struct vm_area_struct *vma)
{
	if ((vma->vm_flags & VM_SHARED) && (vma->vm_flags & VM_MAYWRITE)) {
		struct inode *inode = file->f_dentry->d_inode;
		struct fuse_conn *fc = get_fuse_conn(inode);
		struct fuse_inode *fi = get_fuse_inode(inode);
		struct fuse_file *ff = file->private_data;
		/*
		 * file may be written through mmap, so chain it onto the
		 * inodes's write_file list
		 */
		spin_lock(&fc->lock);
		if (list_empty(&ff->write_entry))
			list_add(&ff->write_entry, &fi->write_files);
		spin_unlock(&fc->lock);
	}
	file_accessed(file);
	vma->vm_ops = &fuse_file_vm_ops;
	return 0;
}