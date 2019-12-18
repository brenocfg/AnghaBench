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
struct vm_region {unsigned long vm_top; unsigned long vm_end; unsigned long vm_start; unsigned long vm_pgoff; int /*<<< orphan*/  vm_usage; } ;
struct vm_area_struct {unsigned long vm_start; unsigned long vm_end; unsigned long vm_pgoff; struct vm_region* vm_region; TYPE_1__* vm_ops; scalar_t__ vm_file; } ;
struct mm_struct {scalar_t__ map_count; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* open ) (struct vm_area_struct*) ;} ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 unsigned long PAGE_SHIFT ; 
 int /*<<< orphan*/  add_nommu_region (struct vm_region*) ; 
 int /*<<< orphan*/  add_vma_to_mm (struct mm_struct*,struct vm_area_struct*) ; 
 int atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  delete_nommu_region (struct vm_region*) ; 
 int /*<<< orphan*/  delete_vma_from_mm (struct vm_area_struct*) ; 
 int /*<<< orphan*/  down_write (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kenter (char*) ; 
 void* kmem_cache_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kmem_cache_free (int /*<<< orphan*/ ,struct vm_region*) ; 
 int /*<<< orphan*/  nommu_region_sem ; 
 int /*<<< orphan*/  stub1 (struct vm_area_struct*) ; 
 scalar_t__ sysctl_max_map_count ; 
 int /*<<< orphan*/  up_write (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vm_area_cachep ; 
 int /*<<< orphan*/  vm_region_jar ; 

int split_vma(struct mm_struct *mm, struct vm_area_struct *vma,
	      unsigned long addr, int new_below)
{
	struct vm_area_struct *new;
	struct vm_region *region;
	unsigned long npages;

	kenter("");

	/* we're only permitted to split anonymous regions that have a single
	 * owner */
	if (vma->vm_file ||
	    atomic_read(&vma->vm_region->vm_usage) != 1)
		return -ENOMEM;

	if (mm->map_count >= sysctl_max_map_count)
		return -ENOMEM;

	region = kmem_cache_alloc(vm_region_jar, GFP_KERNEL);
	if (!region)
		return -ENOMEM;

	new = kmem_cache_alloc(vm_area_cachep, GFP_KERNEL);
	if (!new) {
		kmem_cache_free(vm_region_jar, region);
		return -ENOMEM;
	}

	/* most fields are the same, copy all, and then fixup */
	*new = *vma;
	*region = *vma->vm_region;
	new->vm_region = region;

	npages = (addr - vma->vm_start) >> PAGE_SHIFT;

	if (new_below) {
		region->vm_top = region->vm_end = new->vm_end = addr;
	} else {
		region->vm_start = new->vm_start = addr;
		region->vm_pgoff = new->vm_pgoff += npages;
	}

	if (new->vm_ops && new->vm_ops->open)
		new->vm_ops->open(new);

	delete_vma_from_mm(vma);
	down_write(&nommu_region_sem);
	delete_nommu_region(vma->vm_region);
	if (new_below) {
		vma->vm_region->vm_start = vma->vm_start = addr;
		vma->vm_region->vm_pgoff = vma->vm_pgoff += npages;
	} else {
		vma->vm_region->vm_end = vma->vm_end = addr;
		vma->vm_region->vm_top = addr;
	}
	add_nommu_region(vma->vm_region);
	add_nommu_region(new->vm_region);
	up_write(&nommu_region_sem);
	add_vma_to_mm(mm, vma);
	add_vma_to_mm(mm, new);
	return 0;
}