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
struct page {size_t private; } ;
typedef  int gfp_t ;

/* Variables and functions */
 int /*<<< orphan*/  ARCH_KMALLOC_MINALIGN ; 
 int /*<<< orphan*/  ARCH_SLAB_MINALIGN ; 
 int PAGE_SIZE ; 
 void* ZERO_SIZE_PTR ; 
 int /*<<< orphan*/  _RET_IP_ ; 
 int __GFP_COMP ; 
 unsigned int get_order (size_t) ; 
 int /*<<< orphan*/  kmemleak_alloc (void*,size_t,int,int) ; 
 int /*<<< orphan*/  lockdep_trace_alloc (int) ; 
 int max (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 unsigned int* slob_alloc (size_t,int,int,int) ; 
 void* slob_new_pages (int,unsigned int,int) ; 
 int /*<<< orphan*/  trace_kmalloc_node (int /*<<< orphan*/ ,void*,size_t,int,int,int) ; 
 struct page* virt_to_page (void*) ; 

void *__kmalloc_node(size_t size, gfp_t gfp, int node)
{
	unsigned int *m;
	int align = max(ARCH_KMALLOC_MINALIGN, ARCH_SLAB_MINALIGN);
	void *ret;

	lockdep_trace_alloc(gfp);

	if (size < PAGE_SIZE - align) {
		if (!size)
			return ZERO_SIZE_PTR;

		m = slob_alloc(size + align, gfp, align, node);

		if (!m)
			return NULL;
		*m = size;
		ret = (void *)m + align;

		trace_kmalloc_node(_RET_IP_, ret,
				   size, size + align, gfp, node);
	} else {
		unsigned int order = get_order(size);

		ret = slob_new_pages(gfp | __GFP_COMP, get_order(size), node);
		if (ret) {
			struct page *page;
			page = virt_to_page(ret);
			page->private = size;
		}

		trace_kmalloc_node(_RET_IP_, ret,
				   size, PAGE_SIZE << order, gfp, node);
	}

	kmemleak_alloc(ret, size, 1, gfp);
	return ret;
}