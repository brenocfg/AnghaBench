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
struct vm_area_struct {int /*<<< orphan*/  vm_file; int /*<<< orphan*/  vm_flags; } ;
struct mm_struct {long total_vm; long cached_hole_size; } ;

/* Variables and functions */
 struct vm_area_struct* remove_vma (struct vm_area_struct*) ; 
 unsigned int sysctl_unmap_area_factor ; 
 scalar_t__ unlikely (unsigned int) ; 
 int /*<<< orphan*/  update_hiwater_vm (struct mm_struct*) ; 
 int /*<<< orphan*/  validate_mm (struct mm_struct*) ; 
 int /*<<< orphan*/  vm_stat_account (struct mm_struct*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,long) ; 
 long vma_pages (struct vm_area_struct*) ; 

__attribute__((used)) static void remove_vma_list(struct mm_struct *mm, struct vm_area_struct *vma)
{
	unsigned int unmap_factor = sysctl_unmap_area_factor;
	/* Update high watermark before we lower total_vm */
	update_hiwater_vm(mm);
	do {
		long nrpages = vma_pages(vma);

		mm->total_vm -= nrpages;
		if (unlikely(unmap_factor))
			mm->cached_hole_size += nrpages;
		vm_stat_account(mm, vma->vm_flags, vma->vm_file, -nrpages);
		vma = remove_vma(vma);
	} while (vma);
	validate_mm(mm);
}