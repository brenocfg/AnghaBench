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
typedef  scalar_t__ ppnum_t ;
struct TYPE_2__ {scalar_t__ end; } ;

/* Variables and functions */
 unsigned int pmap_memory_region_count ; 
 TYPE_1__* pmap_memory_regions ; 

ppnum_t IOGetLastPageNumber(void)
{
#if __i386__ || __x86_64__
	ppnum_t	 lastPage, highest = 0;
	unsigned int idx;

	for (idx = 0; idx < pmap_memory_region_count; idx++)
	{
		lastPage = pmap_memory_regions[idx].end - 1;
		if (lastPage > highest)
			highest = lastPage;
	}
	return (highest);
#elif __arm__ || __arm64__
	return 0;
#else
#error unknown arch
#endif
}