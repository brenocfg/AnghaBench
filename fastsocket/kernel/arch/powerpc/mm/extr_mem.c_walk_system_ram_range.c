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
struct lmb_property {int base; int size; } ;

/* Variables and functions */
 int PAGE_SHIFT ; 
 scalar_t__ lmb_find (struct lmb_property*) ; 
 int stub1 (unsigned long,unsigned long,void*) ; 

int
walk_system_ram_range(unsigned long start_pfn, unsigned long nr_pages,
		void *arg, int (*func)(unsigned long, unsigned long, void *))
{
	struct lmb_property res;
	unsigned long pfn, len;
	u64 end;
	int ret = -1;

	res.base = (u64) start_pfn << PAGE_SHIFT;
	res.size = (u64) nr_pages << PAGE_SHIFT;

	end = res.base + res.size - 1;
	while ((res.base < end) && (lmb_find(&res) >= 0)) {
		pfn = (unsigned long)(res.base >> PAGE_SHIFT);
		len = (unsigned long)(res.size >> PAGE_SHIFT);
		ret = (*func)(pfn, len, arg);
		if (ret)
			break;
		res.base += (res.size + 1);
		res.size = (end - res.base + 1);
	}
	return ret;
}