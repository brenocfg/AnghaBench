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
typedef  int /*<<< orphan*/  swp_entry_t ;
struct vm_area_struct {int dummy; } ;
struct page {int dummy; } ;
typedef  int /*<<< orphan*/  pte_t ;
typedef  int /*<<< orphan*/  pmd_t ;

/* Variables and functions */
 scalar_t__ PAGE_SIZE ; 
 int /*<<< orphan*/ * pte_offset_map (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  pte_same (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pte_unmap (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  swp_entry_to_pte (int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 
 int unuse_pte (struct vm_area_struct*,int /*<<< orphan*/ *,unsigned long,int /*<<< orphan*/ ,struct page*) ; 

__attribute__((used)) static int unuse_pte_range(struct vm_area_struct *vma, pmd_t *pmd,
				unsigned long addr, unsigned long end,
				swp_entry_t entry, struct page *page)
{
	pte_t swp_pte = swp_entry_to_pte(entry);
	pte_t *pte;
	int ret = 0;

	/*
	 * We don't actually need pte lock while scanning for swp_pte: since
	 * we hold page lock and mmap_sem, swp_pte cannot be inserted into the
	 * page table while we're scanning; though it could get zapped, and on
	 * some architectures (e.g. x86_32 with PAE) we might catch a glimpse
	 * of unmatched parts which look like swp_pte, so unuse_pte must
	 * recheck under pte lock.  Scanning without pte lock lets it be
	 * preemptible whenever CONFIG_PREEMPT but not CONFIG_HIGHPTE.
	 */
	pte = pte_offset_map(pmd, addr);
	do {
		/*
		 * swapoff spends a _lot_ of time in this loop!
		 * Test inline before going to call unuse_pte.
		 */
		if (unlikely(pte_same(*pte, swp_pte))) {
			pte_unmap(pte);
			ret = unuse_pte(vma, pmd, addr, entry, page);
			if (ret)
				goto out;
			pte = pte_offset_map(pmd, addr);
		}
	} while (pte++, addr += PAGE_SIZE, addr != end);
	pte_unmap(pte - 1);
out:
	return ret;
}