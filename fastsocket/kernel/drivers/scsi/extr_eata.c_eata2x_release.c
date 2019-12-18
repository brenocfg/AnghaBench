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
struct mssp {int dummy; } ;
struct mscp {int dummy; } ;
struct hostdata {size_t board_number; int /*<<< orphan*/  sp_dma_addr; scalar_t__ sp_cpu_addr; int /*<<< orphan*/  pdev; TYPE_1__* cp; } ;
struct Scsi_Host {unsigned int can_queue; scalar_t__ dma_channel; int /*<<< orphan*/  n_io_port; int /*<<< orphan*/  io_port; int /*<<< orphan*/  irq; scalar_t__ hostdata; } ;
struct TYPE_2__ {int /*<<< orphan*/  cp_dma_addr; int /*<<< orphan*/  sglist; } ;

/* Variables and functions */
 scalar_t__ NO_DMA ; 
 int /*<<< orphan*/  PCI_DMA_BIDIRECTIONAL ; 
 int /*<<< orphan*/  free_dma (scalar_t__) ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_free_consistent (int /*<<< orphan*/ ,int,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_unmap_single (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  release_region (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  scsi_unregister (struct Scsi_Host*) ; 
 int /*<<< orphan*/ * sha ; 

__attribute__((used)) static int eata2x_release(struct Scsi_Host *shost)
{
	struct hostdata *ha = (struct hostdata *)shost->hostdata;
	unsigned int i;

	for (i = 0; i < shost->can_queue; i++)
		kfree((&ha->cp[i])->sglist);

	for (i = 0; i < shost->can_queue; i++)
		pci_unmap_single(ha->pdev, ha->cp[i].cp_dma_addr,
				 sizeof(struct mscp), PCI_DMA_BIDIRECTIONAL);

	if (ha->sp_cpu_addr)
		pci_free_consistent(ha->pdev, sizeof(struct mssp),
				    ha->sp_cpu_addr, ha->sp_dma_addr);

	free_irq(shost->irq, &sha[ha->board_number]);

	if (shost->dma_channel != NO_DMA)
		free_dma(shost->dma_channel);

	release_region(shost->io_port, shost->n_io_port);
	scsi_unregister(shost);
	return 0;
}