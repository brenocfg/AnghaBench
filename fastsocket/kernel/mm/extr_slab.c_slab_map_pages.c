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
struct slab {int dummy; } ;
struct page {int dummy; } ;
struct kmem_cache {int gfporder; } ;

/* Variables and functions */
 int /*<<< orphan*/  PageCompound (struct page*) ; 
 scalar_t__ likely (int) ; 
 int /*<<< orphan*/  page_set_cache (struct page*,struct kmem_cache*) ; 
 int /*<<< orphan*/  page_set_slab (struct page*,struct slab*) ; 
 struct page* virt_to_page (void*) ; 

__attribute__((used)) static void slab_map_pages(struct kmem_cache *cache, struct slab *slab,
			   void *addr)
{
	int nr_pages;
	struct page *page;

	page = virt_to_page(addr);

	nr_pages = 1;
	if (likely(!PageCompound(page)))
		nr_pages <<= cache->gfporder;

	do {
		page_set_cache(page, cache);
		page_set_slab(page, slab);
		page++;
	} while (--nr_pages);
}