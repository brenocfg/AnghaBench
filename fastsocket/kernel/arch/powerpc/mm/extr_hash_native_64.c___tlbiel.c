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
struct TYPE_2__ {unsigned int penc; unsigned long shift; } ;

/* Variables and functions */
#define  MMU_PAGE_4K 128 
 TYPE_1__* mmu_psize_defs ; 

__attribute__((used)) static inline void __tlbiel(unsigned long va, int psize, int ssize)
{
	unsigned int penc;

	/* clear top 16 bits, non SLS segment */
	va &= ~(0xffffULL << 48);

	switch (psize) {
	case MMU_PAGE_4K:
		va &= ~0xffful;
		va |= ssize << 8;
		asm volatile(".long 0x7c000224 | (%0 << 11) | (0 << 21)"
			     : : "r"(va) : "memory");
		break;
	default:
		penc = mmu_psize_defs[psize].penc;
		va &= ~((1ul << mmu_psize_defs[psize].shift) - 1);
		va |= penc << 12;
		va |= ssize << 8;
		va |= 1; /* L */
		asm volatile(".long 0x7c000224 | (%0 << 11) | (1 << 21)"
			     : : "r"(va) : "memory");
		break;
	}

}