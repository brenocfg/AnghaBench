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
struct vm_area_struct {unsigned long vm_pgoff; unsigned long vm_end; unsigned long vm_start; int vm_flags; int /*<<< orphan*/ * vm_ops; } ;
struct file {struct b3dfg_dev* private_data; } ;
struct b3dfg_dev {int frame_size; } ;

/* Variables and functions */
 int EINVAL ; 
 unsigned long PAGE_SHIFT ; 
 int VM_CAN_NONLINEAR ; 
 int VM_IO ; 
 int VM_PFNMAP ; 
 int VM_RESERVED ; 
 int b3dfg_nbuf ; 
 int /*<<< orphan*/  b3dfg_vm_ops ; 

__attribute__((used)) static int b3dfg_mmap(struct file *filp, struct vm_area_struct *vma)
{
	struct b3dfg_dev *fgdev = filp->private_data;
	unsigned long offset = vma->vm_pgoff << PAGE_SHIFT;
	unsigned long vsize = vma->vm_end - vma->vm_start;
	unsigned long bufdatalen = b3dfg_nbuf * fgdev->frame_size * 3;
	unsigned long psize = bufdatalen - offset;
	int r = 0;

	if (vsize <= psize) {
		vma->vm_flags |= VM_IO | VM_RESERVED | VM_CAN_NONLINEAR |
				 VM_PFNMAP;
		vma->vm_ops = &b3dfg_vm_ops;
	} else {
		r = -EINVAL;
	}

	return r;
}