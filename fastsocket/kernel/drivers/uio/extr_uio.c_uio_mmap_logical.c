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
struct vm_area_struct {int /*<<< orphan*/ * vm_ops; int /*<<< orphan*/  vm_flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  VM_RESERVED ; 
 int /*<<< orphan*/  uio_vm_ops ; 
 int /*<<< orphan*/  uio_vma_open (struct vm_area_struct*) ; 

__attribute__((used)) static int uio_mmap_logical(struct vm_area_struct *vma)
{
	vma->vm_flags |= VM_RESERVED;
	vma->vm_ops = &uio_vm_ops;
	uio_vma_open(vma);
	return 0;
}