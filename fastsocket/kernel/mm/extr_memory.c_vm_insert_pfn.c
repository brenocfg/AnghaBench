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
struct vm_area_struct {int vm_flags; unsigned long vm_start; unsigned long vm_end; int /*<<< orphan*/  vm_page_prot; } ;
typedef  int /*<<< orphan*/  pgprot_t ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int EFAULT ; 
 int EINVAL ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 int VM_MIXEDMAP ; 
 int VM_PFNMAP ; 
 int insert_pfn (struct vm_area_struct*,unsigned long,unsigned long,int /*<<< orphan*/ ) ; 
 scalar_t__ is_cow_mapping (int) ; 
 scalar_t__ pfn_valid (unsigned long) ; 
 scalar_t__ track_pfn_vma_new (struct vm_area_struct*,int /*<<< orphan*/ *,unsigned long,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  untrack_pfn_vma (struct vm_area_struct*,unsigned long,int /*<<< orphan*/ ) ; 

int vm_insert_pfn(struct vm_area_struct *vma, unsigned long addr,
			unsigned long pfn)
{
	int ret;
	pgprot_t pgprot = vma->vm_page_prot;
	/*
	 * Technically, architectures with pte_special can avoid all these
	 * restrictions (same for remap_pfn_range).  However we would like
	 * consistency in testing and feature parity among all, so we should
	 * try to keep these invariants in place for everybody.
	 */
	BUG_ON(!(vma->vm_flags & (VM_PFNMAP|VM_MIXEDMAP)));
	BUG_ON((vma->vm_flags & (VM_PFNMAP|VM_MIXEDMAP)) ==
						(VM_PFNMAP|VM_MIXEDMAP));
	BUG_ON((vma->vm_flags & VM_PFNMAP) && is_cow_mapping(vma->vm_flags));
	BUG_ON((vma->vm_flags & VM_MIXEDMAP) && pfn_valid(pfn));

	if (addr < vma->vm_start || addr >= vma->vm_end)
		return -EFAULT;
	if (track_pfn_vma_new(vma, &pgprot, pfn, PAGE_SIZE))
		return -EINVAL;

	ret = insert_pfn(vma, addr, pfn, pgprot);

	if (ret)
		untrack_pfn_vma(vma, pfn, PAGE_SIZE);

	return ret;
}