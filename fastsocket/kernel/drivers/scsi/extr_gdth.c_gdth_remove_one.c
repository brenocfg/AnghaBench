#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct Scsi_Host {int dma_channel; scalar_t__ irq; } ;
typedef  int /*<<< orphan*/  gdth_msg_str ;
struct TYPE_5__ {scalar_t__ ccb_phys; int /*<<< orphan*/  pdev; int /*<<< orphan*/  msg_phys; scalar_t__ pmsg; int /*<<< orphan*/  scratch_phys; scalar_t__ pscratch; int /*<<< orphan*/  coal_stat_phys; scalar_t__ coal_stat; int /*<<< orphan*/ * sdev; struct Scsi_Host* shost; } ;
typedef  TYPE_1__ gdth_ha_str ;
typedef  int /*<<< orphan*/  gdth_coal_status ;
typedef  int /*<<< orphan*/  gdth_cmd_str ;

/* Variables and functions */
 int GDTH_SCRATCH ; 
 int MAXOFFSETS ; 
 int /*<<< orphan*/  PCI_DMA_BIDIRECTIONAL ; 
 int /*<<< orphan*/  TRACE2 (char*) ; 
 int /*<<< orphan*/  free_dma (int) ; 
 int /*<<< orphan*/  free_irq (scalar_t__,TYPE_1__*) ; 
 int /*<<< orphan*/  gdth_flush (TYPE_1__*) ; 
 int /*<<< orphan*/  pci_free_consistent (int /*<<< orphan*/ ,int,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_unmap_single (int /*<<< orphan*/ ,scalar_t__,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  scsi_free_host_dev (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  scsi_host_put (struct Scsi_Host*) ; 
 int /*<<< orphan*/  scsi_remove_host (struct Scsi_Host*) ; 

__attribute__((used)) static void gdth_remove_one(gdth_ha_str *ha)
{
	struct Scsi_Host *shp = ha->shost;

	TRACE2(("gdth_remove_one()\n"));

	scsi_remove_host(shp);

	gdth_flush(ha);

	if (ha->sdev) {
		scsi_free_host_dev(ha->sdev);
		ha->sdev = NULL;
	}

	if (shp->irq)
		free_irq(shp->irq,ha);

#ifdef CONFIG_ISA
	if (shp->dma_channel != 0xff)
		free_dma(shp->dma_channel);
#endif
#ifdef INT_COAL
	if (ha->coal_stat)
		pci_free_consistent(ha->pdev, sizeof(gdth_coal_status) *
			MAXOFFSETS, ha->coal_stat, ha->coal_stat_phys);
#endif
	if (ha->pscratch)
		pci_free_consistent(ha->pdev, GDTH_SCRATCH,
			ha->pscratch, ha->scratch_phys);
	if (ha->pmsg)
		pci_free_consistent(ha->pdev, sizeof(gdth_msg_str),
			ha->pmsg, ha->msg_phys);
	if (ha->ccb_phys)
		pci_unmap_single(ha->pdev,ha->ccb_phys,
			sizeof(gdth_cmd_str),PCI_DMA_BIDIRECTIONAL);

	scsi_host_put(shp);
}