#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct vm_area_struct {int /*<<< orphan*/ * vm_ops; } ;
struct inode {int dummy; } ;
struct TYPE_5__ {struct dentry* dentry; } ;
struct file {int /*<<< orphan*/  f_mapping; TYPE_1__ f_path; } ;
struct TYPE_8__ {int /*<<< orphan*/  name; } ;
struct dentry {TYPE_4__ d_name; TYPE_3__* d_parent; struct inode* d_inode; } ;
struct TYPE_6__ {int /*<<< orphan*/  name; } ;
struct TYPE_7__ {TYPE_2__ d_name; } ;

/* Variables and functions */
 int /*<<< orphan*/  dprintk (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int generic_file_mmap (struct file*,struct vm_area_struct*) ; 
 int /*<<< orphan*/  nfs_file_vm_ops ; 
 int nfs_revalidate_mapping (struct inode*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
nfs_file_mmap(struct file * file, struct vm_area_struct * vma)
{
	struct dentry *dentry = file->f_path.dentry;
	struct inode *inode = dentry->d_inode;
	int	status;

	dprintk("NFS: mmap(%s/%s)\n",
		dentry->d_parent->d_name.name, dentry->d_name.name);

	/* Note: generic_file_mmap() returns ENOSYS on nommu systems
	 *       so we call that before revalidating the mapping
	 */
	status = generic_file_mmap(file, vma);
	if (!status) {
		vma->vm_ops = &nfs_file_vm_ops;
		status = nfs_revalidate_mapping(inode, file->f_mapping);
	}
	return status;
}