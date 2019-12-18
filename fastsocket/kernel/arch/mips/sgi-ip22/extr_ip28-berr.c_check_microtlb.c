#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct TYPE_2__ {int dma_ctrl; } ;

/* Variables and functions */
 scalar_t__ PHYS_TO_XKSEG_UNCACHED (unsigned long) ; 
 scalar_t__ addr_is_ram (unsigned long,int) ; 
 unsigned long cpu_err_addr ; 
 TYPE_1__* sgimc ; 

__attribute__((used)) static int check_microtlb(u32 hi, u32 lo, unsigned long vaddr)
{
	/* This is likely rather similar to correct code ;-) */

	vaddr &= 0x7fffffff; /* Doc. states that top bit is ignored */

	/* If tlb-entry is valid and VPN-high (bits [30:21] ?) matches... */
	if ((lo & 2) && (vaddr >> 21) == ((hi<<1) >> 22)) {
		u32 ctl = sgimc->dma_ctrl;
		if (ctl & 1) {
			unsigned int pgsz = (ctl & 2) ? 14:12; /* 16k:4k */
			/* PTEIndex is VPN-low (bits [22:14]/[20:12] ?) */
			unsigned long pte = (lo >> 6) << 12; /* PTEBase */
			pte += 8*((vaddr >> pgsz) & 0x1ff);
			if (addr_is_ram(pte, 8)) {
				/*
				 * Note: Since DMA hardware does look up
				 * translation on its own, this PTE *must*
				 * match the TLB/EntryLo-register format !
				 */
				unsigned long a = *(unsigned long *)
						PHYS_TO_XKSEG_UNCACHED(pte);
				a = (a & 0x3f) << 6; /* PFN */
				a += vaddr & ((1 << pgsz) - 1);
				return (cpu_err_addr == a);
			}
		}
	}
	return 0;
}