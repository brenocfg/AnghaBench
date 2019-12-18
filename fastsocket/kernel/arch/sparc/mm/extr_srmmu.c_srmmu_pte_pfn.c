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
typedef  int /*<<< orphan*/  pte_t ;

/* Variables and functions */
 int PAGE_SHIFT ; 
 int SRMMU_PTE_PMASK ; 
 int pte_val (int /*<<< orphan*/ ) ; 
 scalar_t__ srmmu_device_memory (int) ; 

__attribute__((used)) static unsigned long srmmu_pte_pfn(pte_t pte)
{
	if (srmmu_device_memory(pte_val(pte))) {
		/* Just return something that will cause
		 * pfn_valid() to return false.  This makes
		 * copy_one_pte() to just directly copy to
		 * PTE over.
		 */
		return ~0UL;
	}
	return (pte_val(pte) & SRMMU_PTE_PMASK) >> (PAGE_SHIFT-4);
}