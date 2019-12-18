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

/* Variables and functions */
 int MMU_PAGE_16G ; 
 int MMU_PAGE_16M ; 
 int MMU_PAGE_64K ; 
#define  PAGE_SHIFT_16G 130 
#define  PAGE_SHIFT_16M 129 
#define  PAGE_SHIFT_64K 128 

__attribute__((used)) static inline int shift_to_mmu_psize(unsigned int shift)
{
	switch (shift) {
#ifndef CONFIG_PPC_64K_PAGES
	case PAGE_SHIFT_64K:
	    return MMU_PAGE_64K;
#endif
	case PAGE_SHIFT_16M:
	    return MMU_PAGE_16M;
	case PAGE_SHIFT_16G:
	    return MMU_PAGE_16G;
	}
	return -1;
}