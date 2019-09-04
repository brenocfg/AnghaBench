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
typedef  scalar_t__ vm_offset_t ;
typedef  int uint64_t ;

/* Variables and functions */
 int /*<<< orphan*/  MBUF_IN_MAP (char*) ; 
 int PAGE_MASK ; 
 size_t atop_64 (int) ; 
 scalar_t__ mbutl ; 
 scalar_t__* mcl_paddr ; 
 int ptoa_64 (scalar_t__) ; 

uint64_t
mcl_to_paddr(char *addr)
{
	vm_offset_t base_phys;

	if (!MBUF_IN_MAP(addr))
		return (0);
	base_phys = mcl_paddr[atop_64(addr - (char *)mbutl)];

	if (base_phys == 0)
		return (0);
	return ((uint64_t)(ptoa_64(base_phys) | ((uint64_t)addr & PAGE_MASK)));
}