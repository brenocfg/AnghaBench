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
struct vm_area_struct {unsigned long vm_start; scalar_t__ vm_end; } ;
struct page {int dummy; } ;
struct mm_struct {int dummy; } ;
typedef  int /*<<< orphan*/  pte_t ;
typedef  int /*<<< orphan*/  pmd_t ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 unsigned long HPAGE_PMD_MASK ; 
 scalar_t__ HPAGE_PMD_SIZE ; 
 int /*<<< orphan*/  THP_FAULT_ALLOC ; 
 int /*<<< orphan*/  THP_FAULT_FALLBACK ; 
 int VM_FAULT_OOM ; 
 int __do_huge_pmd_anonymous_page (struct mm_struct*,struct vm_area_struct*,unsigned long,int /*<<< orphan*/ *,struct page*) ; 
 int __pte_alloc (struct mm_struct*,struct vm_area_struct*,int /*<<< orphan*/ *,unsigned long) ; 
 struct page* alloc_hugepage_vma (int /*<<< orphan*/ ,struct vm_area_struct*,unsigned long,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int anon_vma_prepare (struct vm_area_struct*) ; 
 int /*<<< orphan*/  count_vm_event (int /*<<< orphan*/ ) ; 
 int handle_pte_fault (struct mm_struct*,struct vm_area_struct*,unsigned long,int /*<<< orphan*/ *,int /*<<< orphan*/ *,unsigned int) ; 
 int khugepaged_enter (struct vm_area_struct*) ; 
 int mem_cgroup_newpage_charge (struct page*,struct mm_struct*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  numa_node_id () ; 
 int pmd_none (int /*<<< orphan*/ ) ; 
 int pmd_trans_huge (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * pte_offset_map (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  put_page (struct page*) ; 
 int /*<<< orphan*/  transparent_hugepage_defrag (struct vm_area_struct*) ; 
 scalar_t__ unlikely (int) ; 

int do_huge_pmd_anonymous_page(struct mm_struct *mm, struct vm_area_struct *vma,
			       unsigned long address, pmd_t *pmd,
			       unsigned int flags)
{
	struct page *page;
	unsigned long haddr = address & HPAGE_PMD_MASK;
	pte_t *pte;

	if (haddr >= vma->vm_start && haddr + HPAGE_PMD_SIZE <= vma->vm_end) {
		if (unlikely(anon_vma_prepare(vma)))
			return VM_FAULT_OOM;
		if (unlikely(khugepaged_enter(vma)))
			return VM_FAULT_OOM;
		page = alloc_hugepage_vma(transparent_hugepage_defrag(vma),
					  vma, haddr, numa_node_id(), 0);
		if (unlikely(!page)) {
			count_vm_event(THP_FAULT_FALLBACK);
			goto out;
		}
		count_vm_event(THP_FAULT_ALLOC);
		if (unlikely(mem_cgroup_newpage_charge(page, mm, GFP_KERNEL))) {
			put_page(page);
			goto out;
		}

		return __do_huge_pmd_anonymous_page(mm, vma, haddr, pmd, page);
	}
out:
	/*
	 * Use __pte_alloc instead of pte_alloc_map, because we can't
	 * run pte_offset_map on the pmd, if an huge pmd could
	 * materialize from under us from a different thread.
	 */
	if (unlikely(pmd_none(*pmd)) &&
	    unlikely(__pte_alloc(mm, vma, pmd, address)))
		return VM_FAULT_OOM;
	/* if an huge pmd materialized from under us just retry later */
	if (unlikely(pmd_trans_huge(*pmd)))
		return 0;
	/*
	 * A regular pmd is established and it can't morph into a huge pmd
	 * from under us anymore at this point because we hold the mmap_sem
	 * read mode and khugepaged takes it in write mode. So now it's
	 * safe to run pte_offset_map().
	 */
	pte = pte_offset_map(pmd, address);
	return handle_pte_fault(mm, vma, address, pte, pmd, flags);
}