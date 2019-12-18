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
struct lpfc_dma_pool {size_t current_count; TYPE_1__* elements; } ;
struct lpfc_hba {int /*<<< orphan*/  hbalock; int /*<<< orphan*/  lpfc_mbuf_pool; struct lpfc_dma_pool lpfc_mbuf_safety_pool; } ;
typedef  int /*<<< orphan*/  dma_addr_t ;
struct TYPE_2__ {int /*<<< orphan*/  phys; void* virt; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int MEM_PRI ; 
 void* pci_pool_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

void *
lpfc_mbuf_alloc(struct lpfc_hba *phba, int mem_flags, dma_addr_t *handle)
{
	struct lpfc_dma_pool *pool = &phba->lpfc_mbuf_safety_pool;
	unsigned long iflags;
	void *ret;

	ret = pci_pool_alloc(phba->lpfc_mbuf_pool, GFP_KERNEL, handle);

	spin_lock_irqsave(&phba->hbalock, iflags);
	if (!ret && (mem_flags & MEM_PRI) && pool->current_count) {
		pool->current_count--;
		ret = pool->elements[pool->current_count].virt;
		*handle = pool->elements[pool->current_count].phys;
	}
	spin_unlock_irqrestore(&phba->hbalock, iflags);
	return ret;
}