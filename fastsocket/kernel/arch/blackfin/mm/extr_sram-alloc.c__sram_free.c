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
struct sram_piece {void const* paddr; int size; struct sram_piece* next; scalar_t__ pid; } ;

/* Variables and functions */
 int /*<<< orphan*/  kmem_cache_free (int /*<<< orphan*/ ,struct sram_piece*) ; 
 int /*<<< orphan*/  sram_piece_cache ; 

__attribute__((used)) static int _sram_free(const void *addr,
			struct sram_piece *pfree_head,
			struct sram_piece *pused_head)
{
	struct sram_piece *pslot, *plast, *pavail;

	if (!pfree_head || !pused_head)
		return -1;

	/* search the relevant memory slot */
	pslot = pused_head->next;
	plast = pused_head;

	/* search an available piece slot */
	while (pslot != NULL && pslot->paddr != addr) {
		plast = pslot;
		pslot = pslot->next;
	}

	if (!pslot)
		return -1;

	plast->next = pslot->next;
	pavail = pslot;
	pavail->pid = 0;

	/* insert free pieces back to the free list */
	pslot = pfree_head->next;
	plast = pfree_head;

	while (pslot != NULL && addr > pslot->paddr) {
		plast = pslot;
		pslot = pslot->next;
	}

	if (plast != pfree_head && plast->paddr + plast->size == pavail->paddr) {
		plast->size += pavail->size;
		kmem_cache_free(sram_piece_cache, pavail);
	} else {
		pavail->next = plast->next;
		plast->next = pavail;
		plast = pavail;
	}

	if (pslot && plast->paddr + plast->size == pslot->paddr) {
		plast->size += pslot->size;
		plast->next = pslot->next;
		kmem_cache_free(sram_piece_cache, pslot);
	}

	return 0;
}