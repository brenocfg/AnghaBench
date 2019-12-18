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
typedef  int pteval_t ;

/* Variables and functions */
 unsigned long INVALID_P2M_ENTRY ; 
 int PAGE_SHIFT ; 
 int PTE_FLAGS_MASK ; 
 int PTE_PFN_MASK ; 
 int _PAGE_PRESENT ; 
 unsigned long pfn_to_mfn (unsigned long) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static pteval_t pte_pfn_to_mfn(pteval_t val)
{
	if (val & _PAGE_PRESENT) {
		unsigned long pfn = (val & PTE_PFN_MASK) >> PAGE_SHIFT;
		pteval_t flags = val & PTE_FLAGS_MASK;
		unsigned long mfn = pfn_to_mfn(pfn);

		/*
		 * If there's no mfn for the pfn, then just create an
		 * empty non-present pte.  Unfortunately this loses
		 * information about the original pfn, so
		 * pte_mfn_to_pfn is asymmetric.
		 */
		if (unlikely(mfn == INVALID_P2M_ENTRY)) {
			mfn = 0;
			flags = 0;
		}

		val = ((pteval_t)mfn << PAGE_SHIFT) | flags;
	}

	return val;
}