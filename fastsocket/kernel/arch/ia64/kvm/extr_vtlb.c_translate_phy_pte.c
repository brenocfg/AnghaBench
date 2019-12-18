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
union pte_flags {unsigned long val; unsigned long ppn; } ;
typedef  unsigned long u64 ;

/* Variables and functions */
 unsigned long ARCH_PAGE_SHIFT ; 
 unsigned long GPFN_IO_MASK ; 
 unsigned long GPFN_PHYS_MMIO ; 
 unsigned long PAGE_MASK ; 
 unsigned long PAGE_SHIFT ; 
 unsigned long VTLB_PTE_IO ; 
 unsigned long _PAGE_PPN_MASK ; 
 unsigned long itir_ps (unsigned long) ; 
 unsigned long kvm_get_mpt_entry (unsigned long) ; 

u64 translate_phy_pte(u64 *pte, u64 itir, u64 va)
{
	u64 ps, ps_mask, paddr, maddr, io_mask;
	union pte_flags phy_pte;

	ps = itir_ps(itir);
	ps_mask = ~((1UL << ps) - 1);
	phy_pte.val = *pte;
	paddr = *pte;
	paddr = ((paddr & _PAGE_PPN_MASK) & ps_mask) | (va & ~ps_mask);
	maddr = kvm_get_mpt_entry(paddr >> PAGE_SHIFT);
	io_mask = maddr & GPFN_IO_MASK;
	if (io_mask && (io_mask != GPFN_PHYS_MMIO)) {
		*pte |= VTLB_PTE_IO;
		return -1;
	}
	maddr = ((maddr & _PAGE_PPN_MASK) & PAGE_MASK) |
					(paddr & ~PAGE_MASK);
	phy_pte.ppn = maddr >> ARCH_PAGE_SHIFT;
	return phy_pte.val;
}