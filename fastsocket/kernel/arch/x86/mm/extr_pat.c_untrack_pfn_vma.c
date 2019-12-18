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
struct vm_area_struct {unsigned long vm_end; unsigned long vm_start; scalar_t__ vm_pgoff; } ;
typedef  int resource_size_t ;

/* Variables and functions */
 int PAGE_SHIFT ; 
 int /*<<< orphan*/  free_pfn_range (int,unsigned long) ; 
 scalar_t__ is_linear_pfn_mapping (struct vm_area_struct*) ; 

void untrack_pfn_vma(struct vm_area_struct *vma, unsigned long pfn,
			unsigned long size)
{
	resource_size_t paddr;
	unsigned long vma_size = vma->vm_end - vma->vm_start;

	if (is_linear_pfn_mapping(vma)) {
		/* free the whole chunk starting from vm_pgoff */
		paddr = (resource_size_t)vma->vm_pgoff << PAGE_SHIFT;
		free_pfn_range(paddr, vma_size);
		return;
	}
}