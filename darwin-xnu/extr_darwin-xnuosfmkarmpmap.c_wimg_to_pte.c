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
typedef  int pt_entry_t ;

/* Variables and functions */
 int ARM_PTE_ATTRINDX (int /*<<< orphan*/ ) ; 
 int ARM_PTE_NX ; 
 int ARM_PTE_PNX ; 
 int ARM_PTE_SH ; 
 int /*<<< orphan*/  CACHE_ATTRINDX_DEFAULT ; 
 int /*<<< orphan*/  CACHE_ATTRINDX_DISABLE ; 
 int /*<<< orphan*/  CACHE_ATTRINDX_INNERWRITEBACK ; 
 int /*<<< orphan*/  CACHE_ATTRINDX_POSTED ; 
 int /*<<< orphan*/  CACHE_ATTRINDX_WRITEBACK ; 
 int /*<<< orphan*/  CACHE_ATTRINDX_WRITECOMB ; 
 int /*<<< orphan*/  CACHE_ATTRINDX_WRITETHRU ; 
#define  VM_WIMG_COPYBACK 134 
#define  VM_WIMG_INNERWBACK 133 
#define  VM_WIMG_IO 132 
 unsigned int VM_WIMG_MASK ; 
#define  VM_WIMG_POSTED 131 
#define  VM_WIMG_RT 130 
#define  VM_WIMG_WCOMB 129 
#define  VM_WIMG_WTHRU 128 

__attribute__((used)) static pt_entry_t
wimg_to_pte(unsigned int wimg)
{
	pt_entry_t pte;

	switch (wimg & (VM_WIMG_MASK)) {
		case VM_WIMG_IO:
		case VM_WIMG_RT:
			pte = ARM_PTE_ATTRINDX(CACHE_ATTRINDX_DISABLE);
			pte |= ARM_PTE_NX | ARM_PTE_PNX;
			break;
		case VM_WIMG_POSTED:
			pte = ARM_PTE_ATTRINDX(CACHE_ATTRINDX_POSTED);
			pte |= ARM_PTE_NX | ARM_PTE_PNX;
			break;
		case VM_WIMG_WCOMB:
			pte = ARM_PTE_ATTRINDX(CACHE_ATTRINDX_WRITECOMB);
			pte |= ARM_PTE_NX | ARM_PTE_PNX;
			break;
		case VM_WIMG_WTHRU:
			pte = ARM_PTE_ATTRINDX(CACHE_ATTRINDX_WRITETHRU);
#if	(__ARM_VMSA__ > 7)
			pte |= ARM_PTE_SH(SH_OUTER_MEMORY);
#else
			pte |= ARM_PTE_SH;
#endif
			break;
		case VM_WIMG_COPYBACK:
			pte = ARM_PTE_ATTRINDX(CACHE_ATTRINDX_WRITEBACK);
#if	(__ARM_VMSA__ > 7)
			pte |= ARM_PTE_SH(SH_OUTER_MEMORY);
#else
			pte |= ARM_PTE_SH;
#endif
			break;
		case VM_WIMG_INNERWBACK:
			pte = ARM_PTE_ATTRINDX(CACHE_ATTRINDX_INNERWRITEBACK);
#if	(__ARM_VMSA__ > 7)
			pte |= ARM_PTE_SH(SH_INNER_MEMORY);
#else
			pte |= ARM_PTE_SH;
#endif
			break;
		default:
			pte = ARM_PTE_ATTRINDX(CACHE_ATTRINDX_DEFAULT);
#if	(__ARM_VMSA__ > 7)
			pte |= ARM_PTE_SH(SH_OUTER_MEMORY);
#else
			pte |= ARM_PTE_SH;
#endif
	}

	return pte;
}