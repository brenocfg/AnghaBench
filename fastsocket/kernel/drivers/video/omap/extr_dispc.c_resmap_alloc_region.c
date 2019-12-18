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
struct resmap {unsigned int page_cnt; unsigned int start; } ;
struct TYPE_2__ {struct resmap** res_map; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int DISPC_MEMTYPE_NUM ; 
 unsigned int PAGE_ALIGN (size_t) ; 
 unsigned int PAGE_SIZE ; 
 TYPE_1__ dispc ; 
 scalar_t__ resmap_page_reserved (struct resmap*,unsigned int) ; 
 int /*<<< orphan*/  resmap_reserve_region (unsigned long,size_t) ; 

__attribute__((used)) static unsigned long resmap_alloc_region(int mtype, size_t size)
{
	unsigned i;
	unsigned total;
	unsigned start_page;
	unsigned long start;
	struct resmap *res_map = dispc.res_map[mtype];

	BUG_ON(mtype >= DISPC_MEMTYPE_NUM || res_map == NULL || !size);

	size = PAGE_ALIGN(size) / PAGE_SIZE;
	start_page = 0;
	total = 0;
	for (i = 0; i < res_map->page_cnt; i++) {
		if (resmap_page_reserved(res_map, i)) {
			start_page = i + 1;
			total = 0;
		} else if (++total == size)
			break;
	}
	if (total < size)
		return 0;

	start = res_map->start + start_page * PAGE_SIZE;
	resmap_reserve_region(start, size * PAGE_SIZE);

	return start;
}