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
struct vm_area_struct {int vm_flags; int /*<<< orphan*/ * vm_ops; } ;
struct file {TYPE_2__* f_mapping; } ;
struct TYPE_4__ {TYPE_1__* a_ops; } ;
struct TYPE_3__ {int /*<<< orphan*/  get_xip_mem; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int VM_CAN_NONLINEAR ; 
 int VM_MIXEDMAP ; 
 int /*<<< orphan*/  file_accessed (struct file*) ; 
 int /*<<< orphan*/  xip_file_vm_ops ; 

int xip_file_mmap(struct file * file, struct vm_area_struct * vma)
{
	BUG_ON(!file->f_mapping->a_ops->get_xip_mem);

	file_accessed(file);
	vma->vm_ops = &xip_file_vm_ops;
	vma->vm_flags |= VM_CAN_NONLINEAR | VM_MIXEDMAP;
	return 0;
}