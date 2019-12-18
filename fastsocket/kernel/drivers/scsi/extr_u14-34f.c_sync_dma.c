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
struct scsi_cmnd {unsigned int sc_data_direction; } ;
struct mscp {int /*<<< orphan*/  data_len; int /*<<< orphan*/  data_address; int /*<<< orphan*/  sense_len; int /*<<< orphan*/  sense_addr; struct scsi_cmnd* SCpnt; } ;
struct TYPE_2__ {int /*<<< orphan*/  pdev; struct mscp* cp; } ;

/* Variables and functions */
 scalar_t__ DEV2H (int /*<<< orphan*/ ) ; 
 TYPE_1__* HD (unsigned int) ; 
 unsigned int PCI_DMA_BIDIRECTIONAL ; 
 unsigned int PCI_DMA_FROMDEVICE ; 
 int /*<<< orphan*/  pci_dma_sync_sg_for_cpu (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,unsigned int) ; 
 int /*<<< orphan*/  pci_dma_sync_single_for_cpu (int /*<<< orphan*/ ,scalar_t__,scalar_t__,unsigned int) ; 
 scalar_t__ scsi_sg_count (struct scsi_cmnd*) ; 
 int /*<<< orphan*/  scsi_sglist (struct scsi_cmnd*) ; 

__attribute__((used)) static void sync_dma(unsigned int i, unsigned int j) {
   unsigned int pci_dir;
   struct mscp *cpp;
   struct scsi_cmnd *SCpnt;

   cpp = &HD(j)->cp[i]; SCpnt = cpp->SCpnt;
   pci_dir = SCpnt->sc_data_direction;

   if (DEV2H(cpp->sense_addr))
      pci_dma_sync_single_for_cpu(HD(j)->pdev, DEV2H(cpp->sense_addr),
                          DEV2H(cpp->sense_len), PCI_DMA_FROMDEVICE);

   if (scsi_sg_count(SCpnt))
	   pci_dma_sync_sg_for_cpu(HD(j)->pdev, scsi_sglist(SCpnt),
				   scsi_sg_count(SCpnt), pci_dir);

   if (!DEV2H(cpp->data_len)) pci_dir = PCI_DMA_BIDIRECTIONAL;

   if (DEV2H(cpp->data_address))
      pci_dma_sync_single_for_cpu(HD(j)->pdev, DEV2H(cpp->data_address),
                       DEV2H(cpp->data_len), pci_dir);
}