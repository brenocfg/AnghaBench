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
struct vm_area_struct {unsigned long vm_flags; TYPE_1__* vm_ops; struct file* vm_file; } ;
struct file {int dummy; } ;
struct TYPE_2__ {scalar_t__ close; } ;

/* Variables and functions */
 unsigned long VM_CAN_NONLINEAR ; 

__attribute__((used)) static inline int is_mergeable_vma(struct vm_area_struct *vma,
			struct file *file, unsigned long vm_flags)
{
	/* VM_CAN_NONLINEAR may get set later by f_op->mmap() */
	if ((vma->vm_flags ^ vm_flags) & ~VM_CAN_NONLINEAR)
		return 0;
	if (vma->vm_file != file)
		return 0;
	if (vma->vm_ops && vma->vm_ops->close)
		return 0;
	return 1;
}