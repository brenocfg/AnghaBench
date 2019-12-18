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
typedef  int /*<<< orphan*/  pgprot_t ;
typedef  enum km_type { ____Placeholder_km_type } km_type ;

/* Variables and functions */
 int /*<<< orphan*/  PAGE_KERNEL_UC_MINUS ; 
 int /*<<< orphan*/  PAGE_KERNEL_WC ; 
 void* kmap_atomic_prot_pfn (unsigned long,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pat_enabled ; 
 scalar_t__ pgprot_val (int /*<<< orphan*/ ) ; 

void *
iomap_atomic_prot_pfn(unsigned long pfn, enum km_type type, pgprot_t prot)
{
	/*
	 * For non-PAT systems, promote PAGE_KERNEL_WC to PAGE_KERNEL_UC_MINUS.
	 * PAGE_KERNEL_WC maps to PWT, which translates to uncached if the
	 * MTRR is UC or WC.  UC_MINUS gets the real intention, of the
	 * user, which is "WC if the MTRR is WC, UC if you can't do that."
	 */
	if (!pat_enabled && pgprot_val(prot) == pgprot_val(PAGE_KERNEL_WC))
		prot = PAGE_KERNEL_UC_MINUS;

	return kmap_atomic_prot_pfn(pfn, type, prot);
}