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
struct mscp {int dummy; } ;
struct Scsi_Host {unsigned int can_queue; scalar_t__ dma_channel; int /*<<< orphan*/  n_io_port; int /*<<< orphan*/  io_port; int /*<<< orphan*/  irq; } ;
struct TYPE_4__ {TYPE_1__* cp; int /*<<< orphan*/  pdev; } ;
struct TYPE_3__ {int /*<<< orphan*/  cp_dma_addr; int /*<<< orphan*/  sglist; } ;

/* Variables and functions */
 int FALSE ; 
 TYPE_2__* HD (unsigned int) ; 
 scalar_t__ NO_DMA ; 
 int /*<<< orphan*/  PCI_DMA_BIDIRECTIONAL ; 
 int /*<<< orphan*/  driver_name ; 
 int /*<<< orphan*/  free_dma (scalar_t__) ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  panic (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_unmap_single (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  release_region (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  scsi_unregister (struct Scsi_Host*) ; 
 struct Scsi_Host** sh ; 
 int /*<<< orphan*/ * sha ; 

__attribute__((used)) static int u14_34f_release(struct Scsi_Host *shpnt) {
   unsigned int i, j;

   for (j = 0; sh[j] != NULL && sh[j] != shpnt; j++);

   if (sh[j] == NULL)
      panic("%s: release, invalid Scsi_Host pointer.\n", driver_name);

   for (i = 0; i < sh[j]->can_queue; i++)
      kfree((&HD(j)->cp[i])->sglist);

   for (i = 0; i < sh[j]->can_queue; i++)
      pci_unmap_single(HD(j)->pdev, HD(j)->cp[i].cp_dma_addr,
                     sizeof(struct mscp), PCI_DMA_BIDIRECTIONAL);

   free_irq(sh[j]->irq, &sha[j]);

   if (sh[j]->dma_channel != NO_DMA)
      free_dma(sh[j]->dma_channel);

   release_region(sh[j]->io_port, sh[j]->n_io_port);
   scsi_unregister(sh[j]);
   return FALSE;
}