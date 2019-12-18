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
struct vm_struct {int /*<<< orphan*/  addr; } ;
struct page {int dummy; } ;
typedef  int /*<<< orphan*/  gfp_t ;
typedef  unsigned long dma_addr_t ;

/* Variables and functions */
 int /*<<< orphan*/  BUG () ; 
 size_t PAGE_ALIGN (size_t) ; 
 int /*<<< orphan*/  PAGE_KERNEL_NOCACHE ; 
 scalar_t__ PAGE_SIZE ; 
 unsigned long VMALLOC_VMADDR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VM_ALLOC ; 
 unsigned long __get_free_pages (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  free_pages (unsigned long,int) ; 
 int /*<<< orphan*/  frv_cache_invalidate (unsigned long,unsigned long) ; 
 int get_order (size_t) ; 
 struct vm_struct* get_vm_area (size_t,int /*<<< orphan*/ ) ; 
 scalar_t__ in_interrupt () ; 
 int map_page (unsigned long,unsigned long,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  split_page (struct page*,int) ; 
 int /*<<< orphan*/  vfree (void*) ; 
 unsigned long virt_to_bus (void*) ; 
 struct page* virt_to_page (unsigned long) ; 

void *consistent_alloc(gfp_t gfp, size_t size, dma_addr_t *dma_handle)
{
	struct vm_struct *area;
	unsigned long page, va, pa;
	void *ret;
	int order, err, i;

	if (in_interrupt())
		BUG();

	/* only allocate page size areas */
	size = PAGE_ALIGN(size);
	order = get_order(size);

	page = __get_free_pages(gfp, order);
	if (!page) {
		BUG();
		return NULL;
	}

	/* allocate some common virtual space to map the new pages */
	area = get_vm_area(size, VM_ALLOC);
	if (area == 0) {
		free_pages(page, order);
		return NULL;
	}
	va = VMALLOC_VMADDR(area->addr);
	ret = (void *) va;

	/* this gives us the real physical address of the first page */
	*dma_handle = pa = virt_to_bus((void *) page);

	/* set refcount=1 on all pages in an order>0 allocation so that vfree() will actually free
	 * all pages that were allocated.
	 */
	if (order > 0) {
		struct page *rpage = virt_to_page(page);
		split_page(rpage, order);
	}

	err = 0;
	for (i = 0; i < size && err == 0; i += PAGE_SIZE)
		err = map_page(va + i, pa + i, PAGE_KERNEL_NOCACHE);

	if (err) {
		vfree((void *) va);
		return NULL;
	}

	/* we need to ensure that there are no cachelines in use, or worse dirty in this area
	 * - can't do until after virtual address mappings are created
	 */
	frv_cache_invalidate(va, va + size);

	return ret;
}