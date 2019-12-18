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
struct TYPE_2__ {int flags; } ;

/* Variables and functions */
 int CPU_HAS_MMU_PAGE_ASSOC ; 
 int MMU_NTLB_WAYS ; 
 unsigned long MMU_PAGE_ASSOC_BIT ; 
 unsigned long MMU_TLB_ADDRESS_ARRAY ; 
 int /*<<< orphan*/  ctrl_outl (unsigned long,unsigned long) ; 
 TYPE_1__ current_cpu_data ; 

void local_flush_tlb_one(unsigned long asid, unsigned long page)
{
	unsigned long addr, data;
	int i, ways = MMU_NTLB_WAYS;

	/*
	 * NOTE: PTEH.ASID should be set to this MM
	 *       _AND_ we need to write ASID to the array.
	 *
	 * It would be simple if we didn't need to set PTEH.ASID...
	 */
	addr = MMU_TLB_ADDRESS_ARRAY | (page & 0x1F000);
	data = (page & 0xfffe0000) | asid; /* VALID bit is off */

	if ((current_cpu_data.flags & CPU_HAS_MMU_PAGE_ASSOC)) {
		addr |= MMU_PAGE_ASSOC_BIT;
		ways = 1;	/* we already know the way .. */
	}

	for (i = 0; i < ways; i++)
		ctrl_outl(data, addr + (i << 8));
}