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
struct vm_area_struct {int vm_flags; int vm_start; int vm_end; int /*<<< orphan*/  vm_private_data; int /*<<< orphan*/ * vm_ops; int /*<<< orphan*/  vm_page_prot; } ;
struct file {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int EPERM ; 
 int GRU_GSEG_PAGESIZE ; 
 int /*<<< orphan*/  PAGE_SHARED ; 
 int VM_DONTCOPY ; 
 int VM_DONTEXPAND ; 
 int VM_IO ; 
 int VM_LOCKED ; 
 int VM_PFNMAP ; 
 int VM_RESERVED ; 
 int VM_SHARED ; 
 int VM_WRITE ; 
 int /*<<< orphan*/  gru_alloc_vma_data (struct vm_area_struct*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gru_dbg (int /*<<< orphan*/ ,char*,struct file*,int,struct vm_area_struct*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gru_vm_ops ; 
 int /*<<< orphan*/  grudev ; 

__attribute__((used)) static int gru_file_mmap(struct file *file, struct vm_area_struct *vma)
{
	if ((vma->vm_flags & (VM_SHARED | VM_WRITE)) != (VM_SHARED | VM_WRITE))
		return -EPERM;

	if (vma->vm_start & (GRU_GSEG_PAGESIZE - 1) ||
				vma->vm_end & (GRU_GSEG_PAGESIZE - 1))
		return -EINVAL;

	vma->vm_flags |=
	    (VM_IO | VM_DONTCOPY | VM_LOCKED | VM_DONTEXPAND | VM_PFNMAP |
			VM_RESERVED);
	vma->vm_page_prot = PAGE_SHARED;
	vma->vm_ops = &gru_vm_ops;

	vma->vm_private_data = gru_alloc_vma_data(vma, 0);
	if (!vma->vm_private_data)
		return -ENOMEM;

	gru_dbg(grudev, "file %p, vaddr 0x%lx, vma %p, vdata %p\n",
		file, vma->vm_start, vma, vma->vm_private_data);
	return 0;
}