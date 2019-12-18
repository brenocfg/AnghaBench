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
struct vm_area_struct {unsigned long vm_start; unsigned long vm_end; struct vm_area_struct* vm_next; } ;
struct mm_struct {unsigned long free_area_cache; } ;
struct file {int dummy; } ;
struct TYPE_2__ {struct mm_struct* mm; } ;

/* Variables and functions */
 unsigned long EINVAL ; 
 unsigned long ENOMEM ; 
 unsigned long MAP_FIXED ; 
 unsigned long MAP_SHARED ; 
 int PAGE_SIZE ; 
 scalar_t__ REGION_NUMBER (unsigned long) ; 
 unsigned long REGION_OFFSET (unsigned long) ; 
 scalar_t__ RGN_HPAGE ; 
 unsigned long RGN_MAP_LIMIT ; 
 int SHMLBA ; 
 int TASK_SIZE ; 
 unsigned long TASK_UNMAPPED_BASE ; 
 TYPE_1__* current ; 
 struct vm_area_struct* find_vma (struct mm_struct*,unsigned long) ; 
 scalar_t__ is_hugepage_only_range (struct mm_struct*,unsigned long,unsigned long) ; 

unsigned long
arch_get_unmapped_area (struct file *filp, unsigned long addr, unsigned long len,
			unsigned long pgoff, unsigned long flags)
{
	long map_shared = (flags & MAP_SHARED);
	unsigned long start_addr, align_mask = PAGE_SIZE - 1;
	struct mm_struct *mm = current->mm;
	struct vm_area_struct *vma;

	if (len > RGN_MAP_LIMIT)
		return -ENOMEM;

	/* handle fixed mapping: prevent overlap with huge pages */
	if (flags & MAP_FIXED) {
		if (is_hugepage_only_range(mm, addr, len))
			return -EINVAL;
		return addr;
	}

#ifdef CONFIG_HUGETLB_PAGE
	if (REGION_NUMBER(addr) == RGN_HPAGE)
		addr = 0;
#endif
	if (!addr)
		addr = mm->free_area_cache;

	if (map_shared && (TASK_SIZE > 0xfffffffful))
		/*
		 * For 64-bit tasks, align shared segments to 1MB to avoid potential
		 * performance penalty due to virtual aliasing (see ASDM).  For 32-bit
		 * tasks, we prefer to avoid exhausting the address space too quickly by
		 * limiting alignment to a single page.
		 */
		align_mask = SHMLBA - 1;

  full_search:
	start_addr = addr = (addr + align_mask) & ~align_mask;

	for (vma = find_vma(mm, addr); ; vma = vma->vm_next) {
		/* At this point:  (!vma || addr < vma->vm_end). */
		if (TASK_SIZE - len < addr || RGN_MAP_LIMIT - len < REGION_OFFSET(addr)) {
			if (start_addr != TASK_UNMAPPED_BASE) {
				/* Start a new search --- just in case we missed some holes.  */
				addr = TASK_UNMAPPED_BASE;
				goto full_search;
			}
			return -ENOMEM;
		}
		if (!vma || addr + len <= vma->vm_start) {
			/* Remember the address where we stopped this search:  */
			mm->free_area_cache = addr + len;
			return addr;
		}
		addr = (vma->vm_end + align_mask) & ~align_mask;
	}
}