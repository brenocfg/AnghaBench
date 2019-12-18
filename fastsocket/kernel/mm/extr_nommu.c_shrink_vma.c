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
struct vm_region {unsigned long vm_start; unsigned long vm_top; unsigned long vm_end; int /*<<< orphan*/  vm_usage; } ;
struct vm_area_struct {unsigned long vm_start; unsigned long vm_end; struct vm_region* vm_region; } ;
struct mm_struct {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  add_nommu_region (struct vm_region*) ; 
 int /*<<< orphan*/  add_vma_to_mm (struct mm_struct*,struct vm_area_struct*) ; 
 int atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  delete_nommu_region (struct vm_region*) ; 
 int /*<<< orphan*/  delete_vma_from_mm (struct vm_area_struct*) ; 
 int /*<<< orphan*/  down_write (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free_page_series (unsigned long,unsigned long) ; 
 int /*<<< orphan*/  kenter (char*) ; 
 int /*<<< orphan*/  nommu_region_sem ; 
 int /*<<< orphan*/  up_write (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int shrink_vma(struct mm_struct *mm,
		      struct vm_area_struct *vma,
		      unsigned long from, unsigned long to)
{
	struct vm_region *region;

	kenter("");

	/* adjust the VMA's pointers, which may reposition it in the MM's tree
	 * and list */
	delete_vma_from_mm(vma);
	if (from > vma->vm_start)
		vma->vm_end = from;
	else
		vma->vm_start = to;
	add_vma_to_mm(mm, vma);

	/* cut the backing region down to size */
	region = vma->vm_region;
	BUG_ON(atomic_read(&region->vm_usage) != 1);

	down_write(&nommu_region_sem);
	delete_nommu_region(region);
	if (from > region->vm_start) {
		to = region->vm_top;
		region->vm_top = region->vm_end = from;
	} else {
		region->vm_start = to;
	}
	add_nommu_region(region);
	up_write(&nommu_region_sem);

	free_page_series(from, to);
	return 0;
}