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
struct amd_page_map {unsigned long* real; unsigned long* remapped; } ;
struct TYPE_2__ {int /*<<< orphan*/  scratch_page; } ;

/* Variables and functions */
 int /*<<< orphan*/  ClearPageReserved (int /*<<< orphan*/ ) ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int PAGE_SIZE ; 
 int /*<<< orphan*/  SetPageReserved (int /*<<< orphan*/ ) ; 
 scalar_t__ __get_free_page (int /*<<< orphan*/ ) ; 
 TYPE_1__* agp_bridge ; 
 int /*<<< orphan*/  free_page (unsigned long) ; 
 int /*<<< orphan*/  global_cache_flush () ; 
 unsigned long* ioremap_nocache (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  readl (unsigned long*) ; 
 int /*<<< orphan*/  set_memory_uc (unsigned long,int) ; 
 int /*<<< orphan*/  virt_to_page (unsigned long*) ; 
 int /*<<< orphan*/  virt_to_phys (unsigned long*) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,unsigned long*) ; 

__attribute__((used)) static int amd_create_page_map(struct amd_page_map *page_map)
{
	int i;

	page_map->real = (unsigned long *) __get_free_page(GFP_KERNEL);
	if (page_map->real == NULL)
		return -ENOMEM;

#ifndef CONFIG_X86
	SetPageReserved(virt_to_page(page_map->real));
	global_cache_flush();
	page_map->remapped = ioremap_nocache(virt_to_phys(page_map->real),
					    PAGE_SIZE);
	if (page_map->remapped == NULL) {
		ClearPageReserved(virt_to_page(page_map->real));
		free_page((unsigned long) page_map->real);
		page_map->real = NULL;
		return -ENOMEM;
	}
	global_cache_flush();
#else
	set_memory_uc((unsigned long)page_map->real, 1);
	page_map->remapped = page_map->real;
#endif

	for (i = 0; i < PAGE_SIZE / sizeof(unsigned long); i++) {
		writel(agp_bridge->scratch_page, page_map->remapped+i);
		readl(page_map->remapped+i);	/* PCI Posting. */
	}

	return 0;
}