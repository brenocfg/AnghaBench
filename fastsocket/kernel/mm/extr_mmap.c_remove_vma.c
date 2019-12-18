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
struct vm_area_struct {int vm_flags; int /*<<< orphan*/  vm_mm; scalar_t__ vm_file; TYPE_1__* vm_ops; struct vm_area_struct* vm_next; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* close ) (struct vm_area_struct*) ;} ;

/* Variables and functions */
 int VM_EXECUTABLE ; 
 int /*<<< orphan*/  fput (scalar_t__) ; 
 int /*<<< orphan*/  kmem_cache_free (int /*<<< orphan*/ ,struct vm_area_struct*) ; 
 int /*<<< orphan*/  might_sleep () ; 
 int /*<<< orphan*/  mpol_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  removed_exe_file_vma (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct vm_area_struct*) ; 
 int /*<<< orphan*/  vm_area_cachep ; 
 int /*<<< orphan*/  vma_policy (struct vm_area_struct*) ; 

__attribute__((used)) static struct vm_area_struct *remove_vma(struct vm_area_struct *vma)
{
	struct vm_area_struct *next = vma->vm_next;

	might_sleep();
	if (vma->vm_ops && vma->vm_ops->close)
		vma->vm_ops->close(vma);
	if (vma->vm_file) {
		fput(vma->vm_file);
		if (vma->vm_flags & VM_EXECUTABLE)
			removed_exe_file_vma(vma->vm_mm);
	}
	mpol_put(vma_policy(vma));
	kmem_cache_free(vm_area_cachep, vma);
	return next;
}