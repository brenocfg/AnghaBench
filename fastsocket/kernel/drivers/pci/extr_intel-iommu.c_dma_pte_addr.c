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
typedef  int u64 ;
struct dma_pte {int val; } ;

/* Variables and functions */
 int VTD_PAGE_MASK ; 
 int __cmpxchg64 (struct dma_pte*,unsigned long long,unsigned long long) ; 

__attribute__((used)) static inline u64 dma_pte_addr(struct dma_pte *pte)
{
#ifdef CONFIG_64BIT
	return pte->val & VTD_PAGE_MASK;
#else
	/* Must have a full atomic 64-bit read */
	return  __cmpxchg64(pte, 0ULL, 0ULL) & VTD_PAGE_MASK;
#endif
}