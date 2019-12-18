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
struct vm_struct {unsigned int size; unsigned int nr_pages; void* addr; struct page** pages; void* caller; int /*<<< orphan*/  flags; } ;
struct page {int dummy; } ;
typedef  int /*<<< orphan*/  pgprot_t ;
typedef  int gfp_t ;

/* Variables and functions */
 int GFP_RECLAIM_MASK ; 
 int /*<<< orphan*/  PAGE_KERNEL ; 
 unsigned int PAGE_SHIFT ; 
 unsigned int PAGE_SIZE ; 
 int /*<<< orphan*/  VM_VPAGES ; 
 int __GFP_ZERO ; 
 struct page** __vmalloc_node (unsigned int,int,int,int /*<<< orphan*/ ,int,void*) ; 
 struct page* alloc_page (int) ; 
 struct page* alloc_pages_node (int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct vm_struct*) ; 
 struct page** kmalloc_node (unsigned int,int,int) ; 
 scalar_t__ map_vm_area (struct vm_struct*,int /*<<< orphan*/ ,struct page***) ; 
 int /*<<< orphan*/  remove_vm_area (void*) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  vfree (void*) ; 

__attribute__((used)) static void *__vmalloc_area_node(struct vm_struct *area, gfp_t gfp_mask,
				 pgprot_t prot, int node, void *caller)
{
	struct page **pages;
	unsigned int nr_pages, array_size, i;

	nr_pages = (area->size - PAGE_SIZE) >> PAGE_SHIFT;
	array_size = (nr_pages * sizeof(struct page *));

	area->nr_pages = nr_pages;
	/* Please note that the recursion is strictly bounded. */
	if (array_size > PAGE_SIZE) {
		pages = __vmalloc_node(array_size, 1, gfp_mask | __GFP_ZERO,
				PAGE_KERNEL, node, caller);
		area->flags |= VM_VPAGES;
	} else {
		pages = kmalloc_node(array_size,
				(gfp_mask & GFP_RECLAIM_MASK) | __GFP_ZERO,
				node);
	}
	area->pages = pages;
	area->caller = caller;
	if (!area->pages) {
		remove_vm_area(area->addr);
		kfree(area);
		return NULL;
	}

	for (i = 0; i < area->nr_pages; i++) {
		struct page *page;

		if (node < 0)
			page = alloc_page(gfp_mask);
		else
			page = alloc_pages_node(node, gfp_mask, 0);

		if (unlikely(!page)) {
			/* Successfully allocated i pages, free them in __vunmap() */
			area->nr_pages = i;
			goto fail;
		}
		area->pages[i] = page;
	}

	if (map_vm_area(area, prot, &pages))
		goto fail;
	return area->addr;

fail:
	vfree(area->addr);
	return NULL;
}