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
struct vm_area_struct {int /*<<< orphan*/  vm_flags; int /*<<< orphan*/ * vm_ops; } ;
struct file {TYPE_1__* f_dentry; int /*<<< orphan*/  f_vfsmnt; } ;
struct TYPE_2__ {int /*<<< orphan*/  d_inode; } ;

/* Variables and functions */
 int /*<<< orphan*/  VM_CAN_NONLINEAR ; 
 int /*<<< orphan*/  mlog_errno (int) ; 
 int /*<<< orphan*/  ocfs2_file_vm_ops ; 
 int ocfs2_inode_lock_atime (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  ocfs2_inode_unlock (int /*<<< orphan*/ ,int) ; 

int ocfs2_mmap(struct file *file, struct vm_area_struct *vma)
{
	int ret = 0, lock_level = 0;

	ret = ocfs2_inode_lock_atime(file->f_dentry->d_inode,
				    file->f_vfsmnt, &lock_level);
	if (ret < 0) {
		mlog_errno(ret);
		goto out;
	}
	ocfs2_inode_unlock(file->f_dentry->d_inode, lock_level);
out:
	vma->vm_ops = &ocfs2_file_vm_ops;
	vma->vm_flags |= VM_CAN_NONLINEAR;
	return 0;
}