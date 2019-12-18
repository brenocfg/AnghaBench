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
struct vm_area_struct {int vm_flags; int /*<<< orphan*/ * vm_ops; } ;
struct file {int dummy; } ;

/* Variables and functions */
 int ENOSYS ; 
 int VM_SHARED ; 
 int /*<<< orphan*/  file_accessed (struct file*) ; 
 int /*<<< orphan*/  generic_file_vm_ops ; 

int ramfs_nommu_mmap(struct file *file, struct vm_area_struct *vma)
{
	if (!(vma->vm_flags & VM_SHARED))
		return -ENOSYS;

	file_accessed(file);
	vma->vm_ops = &generic_file_vm_ops;
	return 0;
}