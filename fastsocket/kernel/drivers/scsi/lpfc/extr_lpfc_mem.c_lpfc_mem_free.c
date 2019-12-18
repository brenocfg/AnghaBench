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
struct lpfc_dma_pool {int current_count; TYPE_1__* elements; } ;
struct lpfc_hba {int /*<<< orphan*/ * lpfc_scsi_dma_buf_pool; int /*<<< orphan*/ * lpfc_mbuf_pool; int /*<<< orphan*/ * mbox_mem_pool; int /*<<< orphan*/ * nlp_mem_pool; int /*<<< orphan*/ * rrq_pool; int /*<<< orphan*/ * lpfc_hbq_pool; int /*<<< orphan*/ * lpfc_hrb_pool; int /*<<< orphan*/ * lpfc_drb_pool; struct lpfc_dma_pool lpfc_mbuf_safety_pool; } ;
struct TYPE_2__ {int /*<<< orphan*/  phys; int /*<<< orphan*/  virt; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (TYPE_1__*) ; 
 int /*<<< orphan*/  lpfc_sli_hbqbuf_free_all (struct lpfc_hba*) ; 
 int /*<<< orphan*/  mempool_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pci_pool_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pci_pool_free (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
lpfc_mem_free(struct lpfc_hba *phba)
{
	int i;
	struct lpfc_dma_pool *pool = &phba->lpfc_mbuf_safety_pool;

	/* Free HBQ pools */
	lpfc_sli_hbqbuf_free_all(phba);
	if (phba->lpfc_drb_pool)
		pci_pool_destroy(phba->lpfc_drb_pool);
	phba->lpfc_drb_pool = NULL;
	if (phba->lpfc_hrb_pool)
		pci_pool_destroy(phba->lpfc_hrb_pool);
	phba->lpfc_hrb_pool = NULL;

	if (phba->lpfc_hbq_pool)
		pci_pool_destroy(phba->lpfc_hbq_pool);
	phba->lpfc_hbq_pool = NULL;

	if (phba->rrq_pool)
		mempool_destroy(phba->rrq_pool);
	phba->rrq_pool = NULL;

	/* Free NLP memory pool */
	mempool_destroy(phba->nlp_mem_pool);
	phba->nlp_mem_pool = NULL;

	/* Free mbox memory pool */
	mempool_destroy(phba->mbox_mem_pool);
	phba->mbox_mem_pool = NULL;

	/* Free MBUF memory pool */
	for (i = 0; i < pool->current_count; i++)
		pci_pool_free(phba->lpfc_mbuf_pool, pool->elements[i].virt,
			      pool->elements[i].phys);
	kfree(pool->elements);

	pci_pool_destroy(phba->lpfc_mbuf_pool);
	phba->lpfc_mbuf_pool = NULL;

	/* Free DMA buffer memory pool */
	pci_pool_destroy(phba->lpfc_scsi_dma_buf_pool);
	phba->lpfc_scsi_dma_buf_pool = NULL;

	return;
}