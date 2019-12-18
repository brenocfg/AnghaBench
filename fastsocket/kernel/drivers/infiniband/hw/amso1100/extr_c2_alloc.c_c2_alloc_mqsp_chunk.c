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
typedef  int /*<<< orphan*/  u16 ;
struct sp_chunk {int* shared_ptr; scalar_t__ head; int /*<<< orphan*/ * next; int /*<<< orphan*/  dma_addr; } ;
struct c2_dev {TYPE_1__* pcidev; } ;
typedef  int /*<<< orphan*/  gfp_t ;
typedef  int /*<<< orphan*/  dma_addr_t ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int ENOMEM ; 
 int PAGE_SIZE ; 
 struct sp_chunk* dma_alloc_coherent (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mapping ; 
 int /*<<< orphan*/  pci_unmap_addr_set (struct sp_chunk*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int c2_alloc_mqsp_chunk(struct c2_dev *c2dev, gfp_t gfp_mask,
			       struct sp_chunk **head)
{
	int i;
	struct sp_chunk *new_head;
	dma_addr_t dma_addr;

	new_head = dma_alloc_coherent(&c2dev->pcidev->dev, PAGE_SIZE,
				      &dma_addr, gfp_mask);
	if (new_head == NULL)
		return -ENOMEM;

	new_head->dma_addr = dma_addr;
	pci_unmap_addr_set(new_head, mapping, new_head->dma_addr);

	new_head->next = NULL;
	new_head->head = 0;

	/* build list where each index is the next free slot */
	for (i = 0;
	     i < (PAGE_SIZE - sizeof(struct sp_chunk) -
		  sizeof(u16)) / sizeof(u16) - 1;
	     i++) {
		new_head->shared_ptr[i] = i + 1;
	}
	/* terminate list */
	new_head->shared_ptr[i] = 0xFFFF;

	*head = new_head;
	return 0;
}