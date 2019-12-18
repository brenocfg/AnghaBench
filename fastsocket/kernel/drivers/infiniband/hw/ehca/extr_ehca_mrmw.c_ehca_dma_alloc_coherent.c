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
typedef  int /*<<< orphan*/  u64 ;
struct page {int dummy; } ;
struct ib_device {int dummy; } ;
typedef  int /*<<< orphan*/  gfp_t ;

/* Variables and functions */
 struct page* alloc_pages (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ ehca_dma_mapping_error (struct ib_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ehca_map_vaddr (void*) ; 
 int /*<<< orphan*/  free_pages (unsigned long,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_order (size_t) ; 
 void* page_address (struct page*) ; 

__attribute__((used)) static void *ehca_dma_alloc_coherent(struct ib_device *dev, size_t size,
				     u64 *dma_handle, gfp_t flag)
{
	struct page *p;
	void *addr = NULL;
	u64 dma_addr;

	p = alloc_pages(flag, get_order(size));
	if (p) {
		addr = page_address(p);
		dma_addr = ehca_map_vaddr(addr);
		if (ehca_dma_mapping_error(dev, dma_addr)) {
			free_pages((unsigned long)addr,	get_order(size));
			return NULL;
		}
		if (dma_handle)
			*dma_handle = dma_addr;
		return addr;
	}
	return NULL;
}