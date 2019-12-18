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
struct lpfc_dma_pool {size_t current_count; size_t max_count; TYPE_1__* elements; } ;
struct lpfc_hba {int /*<<< orphan*/  lpfc_mbuf_pool; struct lpfc_dma_pool lpfc_mbuf_safety_pool; } ;
typedef  int /*<<< orphan*/  dma_addr_t ;
struct TYPE_2__ {int /*<<< orphan*/  phys; void* virt; } ;

/* Variables and functions */
 int /*<<< orphan*/  pci_pool_free (int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ) ; 

void
__lpfc_mbuf_free(struct lpfc_hba * phba, void *virt, dma_addr_t dma)
{
	struct lpfc_dma_pool *pool = &phba->lpfc_mbuf_safety_pool;

	if (pool->current_count < pool->max_count) {
		pool->elements[pool->current_count].virt = virt;
		pool->elements[pool->current_count].phys = dma;
		pool->current_count++;
	} else {
		pci_pool_free(phba->lpfc_mbuf_pool, virt, dma);
	}
	return;
}