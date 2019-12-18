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
struct pci_dev {int dummy; } ;
typedef  int /*<<< orphan*/  dma_addr_t ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_ATOMIC ; 
 scalar_t__ __get_free_pages (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_order (size_t) ; 
 int /*<<< orphan*/  memset (void*,int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  virt_to_phys (void*) ; 

__attribute__((used)) static void *ccio_alloc_consistent(struct pci_dev *dev, size_t size,
				 dma_addr_t *handle)
{
	void *ret;
	
	ret = (void *)__get_free_pages(GFP_ATOMIC, get_order(size));

	if (ret != NULL) {
		memset(ret, 0, size);
		*handle = virt_to_phys(ret);
	}
	return ret;
}