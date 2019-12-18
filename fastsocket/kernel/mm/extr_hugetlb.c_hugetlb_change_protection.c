#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct vm_area_struct {TYPE_2__* vm_file; struct mm_struct* vm_mm; } ;
struct mm_struct {int /*<<< orphan*/  page_table_lock; } ;
struct hstate {int dummy; } ;
typedef  int /*<<< orphan*/  pte_t ;
typedef  int /*<<< orphan*/  pgprot_t ;
struct TYPE_4__ {TYPE_1__* f_mapping; } ;
struct TYPE_3__ {int /*<<< orphan*/  i_mmap_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  flush_cache_range (struct vm_area_struct*,unsigned long,unsigned long) ; 
 int /*<<< orphan*/  flush_tlb_range (struct vm_area_struct*,unsigned long,unsigned long) ; 
 struct hstate* hstate_vma (struct vm_area_struct*) ; 
 scalar_t__ huge_page_size (struct hstate*) ; 
 scalar_t__ huge_pmd_unshare (struct mm_struct*,unsigned long*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  huge_pte_none (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * huge_pte_offset (struct mm_struct*,unsigned long) ; 
 int /*<<< orphan*/  huge_ptep_get (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  huge_ptep_get_and_clear (struct mm_struct*,unsigned long,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pte_mkhuge (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pte_modify (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_huge_pte_at (struct mm_struct*,unsigned long,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

void hugetlb_change_protection(struct vm_area_struct *vma,
		unsigned long address, unsigned long end, pgprot_t newprot)
{
	struct mm_struct *mm = vma->vm_mm;
	unsigned long start = address;
	pte_t *ptep;
	pte_t pte;
	struct hstate *h = hstate_vma(vma);

	BUG_ON(address >= end);
	flush_cache_range(vma, address, end);

	spin_lock(&vma->vm_file->f_mapping->i_mmap_lock);
	spin_lock(&mm->page_table_lock);
	for (; address < end; address += huge_page_size(h)) {
		ptep = huge_pte_offset(mm, address);
		if (!ptep)
			continue;
		if (huge_pmd_unshare(mm, &address, ptep))
			continue;
		if (!huge_pte_none(huge_ptep_get(ptep))) {
			pte = huge_ptep_get_and_clear(mm, address, ptep);
			pte = pte_mkhuge(pte_modify(pte, newprot));
			set_huge_pte_at(mm, address, ptep, pte);
		}
	}
	spin_unlock(&mm->page_table_lock);
	/*
	 * Must flush TLB before releasing i_mmap_lock: x86's huge_pmd_unshare
	 * may have cleared our pud entry and done put_page on the page table:
	 * once we release i_mmap_lock, another task can do the final put_page
	 * and that page table be reused and filled with junk.
	 */
	flush_tlb_range(vma, start, end);
	spin_unlock(&vma->vm_file->f_mapping->i_mmap_lock);
}