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
struct resmap {unsigned long start; unsigned int page_cnt; unsigned long* map; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 unsigned int PAGE_ALIGN (size_t) ; 
 unsigned int PAGE_SIZE ; 
 scalar_t__ RESMAP_SIZE (unsigned int) ; 
 struct resmap* kzalloc (scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct resmap *init_resmap(unsigned long start, size_t size)
{
	unsigned page_cnt;
	struct resmap *res_map;

	page_cnt = PAGE_ALIGN(size) / PAGE_SIZE;
	res_map =
	    kzalloc(sizeof(struct resmap) + RESMAP_SIZE(page_cnt), GFP_KERNEL);
	if (res_map == NULL)
		return NULL;
	res_map->start = start;
	res_map->page_cnt = page_cnt;
	res_map->map = (unsigned long *)(res_map + 1);
	return res_map;
}