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
struct sram_piece {unsigned long size; struct sram_piece* next; } ;

/* Variables and functions */
 void* _sram_alloc (unsigned long,struct sram_piece*,struct sram_piece*) ; 

__attribute__((used)) static void *_sram_alloc_max(struct sram_piece *pfree_head,
				struct sram_piece *pused_head,
				unsigned long *psize)
{
	struct sram_piece *pslot, *pmax;

	if (!pfree_head || !pused_head)
		return NULL;

	pmax = pslot = pfree_head->next;

	/* search an available piece slot */
	while (pslot != NULL) {
		if (pslot->size > pmax->size)
			pmax = pslot;
		pslot = pslot->next;
	}

	if (!pmax)
		return NULL;

	*psize = pmax->size;

	return _sram_alloc(*psize, pfree_head, pused_head);
}