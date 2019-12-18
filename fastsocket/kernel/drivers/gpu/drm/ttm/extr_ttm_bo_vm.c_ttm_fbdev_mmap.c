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
struct vm_area_struct {scalar_t__ vm_pgoff; int vm_flags; int /*<<< orphan*/  vm_private_data; int /*<<< orphan*/ * vm_ops; } ;
struct ttm_buffer_object {int dummy; } ;

/* Variables and functions */
 int EACCES ; 
 int VM_DONTEXPAND ; 
 int VM_IO ; 
 int VM_MIXEDMAP ; 
 int /*<<< orphan*/  ttm_bo_reference (struct ttm_buffer_object*) ; 
 int /*<<< orphan*/  ttm_bo_vm_ops ; 

int ttm_fbdev_mmap(struct vm_area_struct *vma, struct ttm_buffer_object *bo)
{
	if (vma->vm_pgoff != 0)
		return -EACCES;

	vma->vm_ops = &ttm_bo_vm_ops;
	vma->vm_private_data = ttm_bo_reference(bo);
	vma->vm_flags |= VM_IO | VM_MIXEDMAP | VM_DONTEXPAND;
	return 0;
}