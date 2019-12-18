#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int cnt; TYPE_2__* region; } ;
struct TYPE_6__ {TYPE_1__ memory; } ;
struct TYPE_5__ {unsigned long base; unsigned long size; } ;

/* Variables and functions */
 unsigned long PAGE_SHIFT ; 
 TYPE_3__ lmb ; 
 unsigned long max_pfn ; 

int page_is_ram(unsigned long pfn)
{
#ifndef CONFIG_PPC64	/* XXX for now */
	return pfn < max_pfn;
#else
	unsigned long paddr = (pfn << PAGE_SHIFT);
	int i;
	for (i=0; i < lmb.memory.cnt; i++) {
		unsigned long base;

		base = lmb.memory.region[i].base;

		if ((paddr >= base) &&
			(paddr < (base + lmb.memory.region[i].size))) {
			return 1;
		}
	}

	return 0;
#endif
}