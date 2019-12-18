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
 unsigned long PAGE_OFFSET ; 
 scalar_t__ PAGE_SIZE ; 
 unsigned long find_pa (unsigned long) ; 
 int /*<<< orphan*/  srm_printk (char*,unsigned long,unsigned long,unsigned long,unsigned long) ; 

int
check_range(unsigned long vstart, unsigned long vend,
	    unsigned long kstart, unsigned long kend)
{
	unsigned long vaddr, kaddr;

#ifdef DEBUG_CHECK_RANGE
	srm_printk("check_range: V[0x%lx:0x%lx] K[0x%lx:0x%lx]\n",
		   vstart, vend, kstart, kend);
#endif
	/* do some range checking for detecting an overlap... */
	for (vaddr = vstart; vaddr <= vend; vaddr += PAGE_SIZE)
	{
		kaddr = (find_pa(vaddr) | PAGE_OFFSET);
		if (kaddr >= kstart && kaddr <= kend)
		{
#ifdef DEBUG_CHECK_RANGE
			srm_printk("OVERLAP: vaddr 0x%lx kaddr 0x%lx"
				   " [0x%lx:0x%lx]\n",
				   vaddr, kaddr, kstart, kend);
#endif
			return 1;
		}
	}
	return 0;
}