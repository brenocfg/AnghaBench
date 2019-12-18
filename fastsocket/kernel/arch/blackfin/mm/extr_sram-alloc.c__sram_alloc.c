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
struct sram_piece {size_t size; scalar_t__ paddr; struct sram_piece* next; int /*<<< orphan*/  pid; } ;
struct TYPE_2__ {int /*<<< orphan*/  pid; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 TYPE_1__* current ; 
 struct sram_piece* kmem_cache_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sram_piece_cache ; 

__attribute__((used)) static void *_sram_alloc(size_t size, struct sram_piece *pfree_head,
		struct sram_piece *pused_head)
{
	struct sram_piece *pslot, *plast, *pavail;

	if (size <= 0 || !pfree_head || !pused_head)
		return NULL;

	/* Align the size */
	size = (size + 3) & ~3;

	pslot = pfree_head->next;
	plast = pfree_head;

	/* search an available piece slot */
	while (pslot != NULL && size > pslot->size) {
		plast = pslot;
		pslot = pslot->next;
	}

	if (!pslot)
		return NULL;

	if (pslot->size == size) {
		plast->next = pslot->next;
		pavail = pslot;
	} else {
		pavail = kmem_cache_alloc(sram_piece_cache, GFP_KERNEL);

		if (!pavail)
			return NULL;

		pavail->paddr = pslot->paddr;
		pavail->size = size;
		pslot->paddr += size;
		pslot->size -= size;
	}

	pavail->pid = current->pid;

	pslot = pused_head->next;
	plast = pused_head;

	/* insert new piece into used piece list !!! */
	while (pslot != NULL && pavail->paddr < pslot->paddr) {
		plast = pslot;
		pslot = pslot->next;
	}

	pavail->next = pslot;
	plast->next = pavail;

	return pavail->paddr;
}