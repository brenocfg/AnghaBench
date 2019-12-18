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
 unsigned long MEM_INTMEM_START ; 
 unsigned long RESERVED_SIZE ; 
 scalar_t__ intmem_virtual ; 

void* crisv32_intmem_phys_to_virt(unsigned long addr)
{
	return (void *)(addr - (MEM_INTMEM_START + RESERVED_SIZE) +
		(unsigned long)intmem_virtual);
}