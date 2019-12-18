#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct aic7xxx_scb_dma {int dma_len; unsigned long dma_offset; scalar_t__ dma_address; } ;
struct aic7xxx_host {scalar_t__ fifo_dma; scalar_t__ untagged_scbs; int /*<<< orphan*/  pdev; TYPE_2__* scb_data; } ;
struct TYPE_4__ {void* hscbs; int hscbs_dma_len; int numscbs; TYPE_1__** scb_array; int /*<<< orphan*/ * hscb_kmalloc_ptr; scalar_t__ hscbs_dma; } ;
struct TYPE_3__ {TYPE_2__* kmalloc_ptr; struct aic7xxx_scb_dma* scb_dma; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (TYPE_2__*) ; 
 int /*<<< orphan*/  pci_free_consistent (int /*<<< orphan*/ ,int,void*,scalar_t__) ; 

__attribute__((used)) static void
aic7xxx_free(struct aic7xxx_host *p)
{
  int i;

  /*
   * Free the allocated hardware SCB space.
   */
  if (p->scb_data != NULL)
  {
    struct aic7xxx_scb_dma *scb_dma = NULL;
    if (p->scb_data->hscbs != NULL)
    {
      pci_free_consistent(p->pdev, p->scb_data->hscbs_dma_len,
			  p->scb_data->hscbs, p->scb_data->hscbs_dma);
      p->scb_data->hscbs = p->scb_data->hscb_kmalloc_ptr = NULL;
    }
    /*
     * Free the driver SCBs.  These were allocated on an as-need
     * basis.  We allocated these in groups depending on how many
     * we could fit into a given amount of RAM.  The tail SCB for
     * these allocations has a pointer to the alloced area.
     */
    for (i = 0; i < p->scb_data->numscbs; i++)
    {
      if (p->scb_data->scb_array[i]->scb_dma != scb_dma)
      {
	scb_dma = p->scb_data->scb_array[i]->scb_dma;
	pci_free_consistent(p->pdev, scb_dma->dma_len,
			    (void *)((unsigned long)scb_dma->dma_address
                                     - scb_dma->dma_offset),
			    scb_dma->dma_address);
      }
      kfree(p->scb_data->scb_array[i]->kmalloc_ptr);
      p->scb_data->scb_array[i] = NULL;
    }
  
    /*
     * Free the SCB data area.
     */
    kfree(p->scb_data);
  }

  pci_free_consistent(p->pdev, 3*256, (void *)p->untagged_scbs, p->fifo_dma);
}