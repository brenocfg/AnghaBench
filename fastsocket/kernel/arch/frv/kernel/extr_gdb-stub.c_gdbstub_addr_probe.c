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
 unsigned long xAMPRx_V ; 

__attribute__((used)) static inline int gdbstub_addr_probe(const void *vaddr)
{
#ifdef CONFIG_MMU
	unsigned long paddr;

	asm("lrad %1,%0,#1,#0,#0" : "=r"(paddr) : "r"(vaddr));
	if (!(paddr & xAMPRx_V))
		return 0;
#endif

	return 1;
}