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
struct file {struct address_space* f_mapping; } ;
struct address_space {TYPE_1__* a_ops; } ;
struct TYPE_2__ {int /*<<< orphan*/  readpage; } ;

/* Variables and functions */
 int ENOEXEC ; 
 int /*<<< orphan*/  VM_CAN_NONLINEAR ; 
 int /*<<< orphan*/  ext4_file_vm_ops ; 
 int /*<<< orphan*/  file_accessed (struct file*) ; 

__attribute__((used)) static int ext4_file_mmap(struct file *file, struct vm_area_struct *vma)
{
	struct address_space *mapping = file->f_mapping;

	if (!mapping->a_ops->readpage)
		return -ENOEXEC;
	file_accessed(file);
	vma->vm_ops = &ext4_file_vm_ops;
	vma->vm_flags |= VM_CAN_NONLINEAR;
	return 0;
}