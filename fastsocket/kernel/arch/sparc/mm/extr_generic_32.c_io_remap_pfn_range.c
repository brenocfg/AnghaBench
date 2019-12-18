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
struct vm_area_struct {int vm_flags; unsigned long vm_pgoff; struct mm_struct* vm_mm; } ;
struct mm_struct {int dummy; } ;
typedef  int /*<<< orphan*/  pmd_t ;
typedef  int /*<<< orphan*/  pgprot_t ;
typedef  int /*<<< orphan*/  pgd_t ;

/* Variables and functions */
 int ENOMEM ; 
 int GET_IOSPACE (unsigned long) ; 
 unsigned long GET_PFN (unsigned long) ; 
 unsigned long PAGE_SHIFT ; 
 unsigned long PGDIR_MASK ; 
 unsigned long PGDIR_SIZE ; 
 int VM_IO ; 
 int VM_PFNMAP ; 
 int VM_RESERVED ; 
 int /*<<< orphan*/  flush_cache_range (struct vm_area_struct*,unsigned long,unsigned long) ; 
 int /*<<< orphan*/  flush_tlb_range (struct vm_area_struct*,unsigned long,unsigned long) ; 
 int io_remap_pmd_range (struct mm_struct*,int /*<<< orphan*/ *,unsigned long,unsigned long,unsigned long,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/ * pgd_offset (struct mm_struct*,unsigned long) ; 
 int /*<<< orphan*/ * pmd_alloc (struct mm_struct*,int /*<<< orphan*/ *,unsigned long) ; 

int io_remap_pfn_range(struct vm_area_struct *vma, unsigned long from,
		       unsigned long pfn, unsigned long size, pgprot_t prot)
{
	int error = 0;
	pgd_t * dir;
	unsigned long beg = from;
	unsigned long end = from + size;
	struct mm_struct *mm = vma->vm_mm;
	int space = GET_IOSPACE(pfn);
	unsigned long offset = GET_PFN(pfn) << PAGE_SHIFT;

	/* See comment in mm/memory.c remap_pfn_range */
	vma->vm_flags |= VM_IO | VM_RESERVED | VM_PFNMAP;
	vma->vm_pgoff = (offset >> PAGE_SHIFT) |
		((unsigned long)space << 28UL);

	offset -= from;
	dir = pgd_offset(mm, from);
	flush_cache_range(vma, beg, end);

	while (from < end) {
		pmd_t *pmd = pmd_alloc(mm, dir, from);
		error = -ENOMEM;
		if (!pmd)
			break;
		error = io_remap_pmd_range(mm, pmd, from, end - from, offset + from, prot, space);
		if (error)
			break;
		from = (from + PGDIR_SIZE) & PGDIR_MASK;
		dir++;
	}

	flush_tlb_range(vma, beg, end);
	return error;
}