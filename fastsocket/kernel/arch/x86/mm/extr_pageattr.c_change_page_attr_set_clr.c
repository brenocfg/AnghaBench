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
struct page {int dummy; } ;
struct cpa_data {unsigned long* vaddr; int numpages; int flags; int force_split; scalar_t__ curpage; void* mask_clr; void* mask_set; struct page** pages; } ;
typedef  void* pgprot_t ;

/* Variables and functions */
 int CPA_ARRAY ; 
 int CPA_FLUSHTLB ; 
 int CPA_PAGES_ARRAY ; 
 unsigned long PAGE_MASK ; 
 int /*<<< orphan*/  WARN_ON_ONCE (int) ; 
 int _PAGE_NX ; 
 int __change_page_attr_set_clr (struct cpa_data*,int) ; 
 int cache_attr (void*) ; 
 void* canon_pgprot (void*) ; 
 int /*<<< orphan*/  cpa_flush_all (int) ; 
 int /*<<< orphan*/  cpa_flush_array (unsigned long*,int,int,int,struct page**) ; 
 int /*<<< orphan*/  cpa_flush_range (unsigned long,int,int) ; 
 scalar_t__ cpu_has_clflush ; 
 int /*<<< orphan*/  kmap_flush_unused () ; 
 int pgprot_val (void*) ; 
 int /*<<< orphan*/  vm_unmap_aliases () ; 

__attribute__((used)) static int change_page_attr_set_clr(unsigned long *addr, int numpages,
				    pgprot_t mask_set, pgprot_t mask_clr,
				    int force_split, int in_flag,
				    struct page **pages)
{
	struct cpa_data cpa;
	int ret, cache, checkalias;
	unsigned long baddr = 0;

	/*
	 * Check, if we are requested to change a not supported
	 * feature:
	 */
	mask_set = canon_pgprot(mask_set);
	mask_clr = canon_pgprot(mask_clr);
	if (!pgprot_val(mask_set) && !pgprot_val(mask_clr) && !force_split)
		return 0;

	/* Ensure we are PAGE_SIZE aligned */
	if (in_flag & CPA_ARRAY) {
		int i;
		for (i = 0; i < numpages; i++) {
			if (addr[i] & ~PAGE_MASK) {
				addr[i] &= PAGE_MASK;
				WARN_ON_ONCE(1);
			}
		}
	} else if (!(in_flag & CPA_PAGES_ARRAY)) {
		/*
		 * in_flag of CPA_PAGES_ARRAY implies it is aligned.
		 * No need to cehck in that case
		 */
		if (*addr & ~PAGE_MASK) {
			*addr &= PAGE_MASK;
			/*
			 * People should not be passing in unaligned addresses:
			 */
			WARN_ON_ONCE(1);
		}
		/*
		 * Save address for cache flush. *addr is modified in the call
		 * to __change_page_attr_set_clr() below.
		 */
		baddr = *addr;
	}

	/* Must avoid aliasing mappings in the highmem code */
	kmap_flush_unused();

	vm_unmap_aliases();

	cpa.vaddr = addr;
	cpa.pages = pages;
	cpa.numpages = numpages;
	cpa.mask_set = mask_set;
	cpa.mask_clr = mask_clr;
	cpa.flags = 0;
	cpa.curpage = 0;
	cpa.force_split = force_split;

	if (in_flag & (CPA_ARRAY | CPA_PAGES_ARRAY))
		cpa.flags |= in_flag;

	/* No alias checking for _NX bit modifications */
	checkalias = (pgprot_val(mask_set) | pgprot_val(mask_clr)) != _PAGE_NX;

	ret = __change_page_attr_set_clr(&cpa, checkalias);

	/*
	 * Check whether we really changed something:
	 */
	if (!(cpa.flags & CPA_FLUSHTLB))
		goto out;

	/*
	 * No need to flush, when we did not set any of the caching
	 * attributes:
	 */
	cache = cache_attr(mask_set);

	/*
	 * On success we use clflush, when the CPU supports it to
	 * avoid the wbindv. If the CPU does not support it and in the
	 * error case we fall back to cpa_flush_all (which uses
	 * wbindv):
	 */
	if (!ret && cpu_has_clflush) {
		if (cpa.flags & (CPA_PAGES_ARRAY | CPA_ARRAY)) {
			cpa_flush_array(addr, numpages, cache,
					cpa.flags, pages);
		} else
			cpa_flush_range(baddr, numpages, cache);
	} else
		cpa_flush_all(cache);

out:
	return ret;
}