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
struct vm_area_struct {int vm_flags; int vm_end; int vm_start; int vm_pgoff; int /*<<< orphan*/ * vm_ops; } ;
struct inode {int dummy; } ;
struct TYPE_4__ {TYPE_1__* dentry; } ;
struct file {TYPE_2__ f_path; } ;
struct TYPE_3__ {struct inode* d_inode; } ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINTK (char*) ; 
 int EFBIG ; 
 int EINVAL ; 
 int EIO ; 
 int /*<<< orphan*/  NCP_SERVER (struct inode*) ; 
 int PAGE_SHIFT ; 
 int VM_SHARED ; 
 int /*<<< orphan*/  file_accessed (struct file*) ; 
 int /*<<< orphan*/  ncp_conn_valid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ncp_file_mmap ; 

int ncp_mmap(struct file *file, struct vm_area_struct *vma)
{
	struct inode *inode = file->f_path.dentry->d_inode;
	
	DPRINTK("ncp_mmap: called\n");

	if (!ncp_conn_valid(NCP_SERVER(inode)))
		return -EIO;

	/* only PAGE_COW or read-only supported now */
	if (vma->vm_flags & VM_SHARED)
		return -EINVAL;
	/* we do not support files bigger than 4GB... We eventually 
	   supports just 4GB... */
	if (((vma->vm_end - vma->vm_start) >> PAGE_SHIFT) + vma->vm_pgoff 
	   > (1U << (32 - PAGE_SHIFT)))
		return -EFBIG;

	vma->vm_ops = &ncp_file_mmap;
	file_accessed(file);
	return 0;
}