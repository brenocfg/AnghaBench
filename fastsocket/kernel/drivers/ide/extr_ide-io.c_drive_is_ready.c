#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
struct TYPE_12__ {scalar_t__ ctl_addr; } ;
struct TYPE_13__ {int host_flags; TYPE_1__* tp_ops; TYPE_3__ io_ports; TYPE_2__* dma_ops; } ;
typedef  TYPE_4__ ide_hwif_t ;
struct TYPE_14__ {scalar_t__ waiting_for_dma; TYPE_4__* hwif; } ;
typedef  TYPE_5__ ide_drive_t ;
struct TYPE_11__ {int (* dma_test_irq ) (TYPE_5__*) ;} ;
struct TYPE_10__ {int (* read_altstatus ) (TYPE_4__*) ;int (* read_status ) (TYPE_4__*) ;} ;

/* Variables and functions */
 int ATA_BUSY ; 
 int IDE_HFLAG_BROKEN_ALTSTATUS ; 
 int stub1 (TYPE_5__*) ; 
 int stub2 (TYPE_4__*) ; 
 int stub3 (TYPE_4__*) ; 

__attribute__((used)) static int drive_is_ready(ide_drive_t *drive)
{
	ide_hwif_t *hwif = drive->hwif;
	u8 stat = 0;

	if (drive->waiting_for_dma)
		return hwif->dma_ops->dma_test_irq(drive);

	if (hwif->io_ports.ctl_addr &&
	    (hwif->host_flags & IDE_HFLAG_BROKEN_ALTSTATUS) == 0)
		stat = hwif->tp_ops->read_altstatus(hwif);
	else
		/* Note: this may clear a pending IRQ!! */
		stat = hwif->tp_ops->read_status(hwif);

	if (stat & ATA_BUSY)
		/* drive busy: definitely not interrupting */
		return 0;

	/* drive ready: *might* be interrupting */
	return 1;
}