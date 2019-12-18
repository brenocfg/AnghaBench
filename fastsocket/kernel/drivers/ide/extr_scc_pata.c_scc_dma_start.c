#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
struct TYPE_4__ {int /*<<< orphan*/  dma_base; } ;
typedef  TYPE_1__ ide_hwif_t ;
struct TYPE_5__ {TYPE_1__* hwif; } ;
typedef  TYPE_2__ ide_drive_t ;

/* Variables and functions */
 int scc_ide_inb (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  scc_ide_outb (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void scc_dma_start(ide_drive_t *drive)
{
	ide_hwif_t *hwif = drive->hwif;
	u8 dma_cmd = scc_ide_inb(hwif->dma_base);

	/* start DMA */
	scc_ide_outb(dma_cmd | 1, hwif->dma_base);
}