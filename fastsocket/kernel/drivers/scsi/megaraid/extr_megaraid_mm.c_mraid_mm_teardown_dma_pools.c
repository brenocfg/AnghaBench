#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {TYPE_2__* dma_pool_list; } ;
typedef  TYPE_1__ mraid_mmadp_t ;
struct TYPE_5__ {int /*<<< orphan*/ * handle; int /*<<< orphan*/  paddr; scalar_t__ vaddr; } ;
typedef  TYPE_2__ mm_dmapool_t ;

/* Variables and functions */
 int MAX_DMA_POOLS ; 
 int /*<<< orphan*/  pci_pool_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pci_pool_free (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
mraid_mm_teardown_dma_pools(mraid_mmadp_t *adp)
{
	int		i;
	mm_dmapool_t	*pool;

	for (i = 0; i < MAX_DMA_POOLS; i++) {

		pool = &adp->dma_pool_list[i];

		if (pool->handle) {

			if (pool->vaddr)
				pci_pool_free(pool->handle, pool->vaddr,
							pool->paddr);

			pci_pool_destroy(pool->handle);
			pool->handle = NULL;
		}
	}

	return;
}