#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct ide_port_info {int dummy; } ;
struct TYPE_4__ {scalar_t__ extra_base; scalar_t__ dma_base; } ;
typedef  TYPE_1__ ide_hwif_t ;

/* Variables and functions */
 int /*<<< orphan*/  TX4939IDE_DMA_Cmd ; 
 int ide_allocate_dma_engine (TYPE_1__*) ; 
 scalar_t__ tx4939ide_swizzleb (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int tx4939ide_init_dma(ide_hwif_t *hwif, const struct ide_port_info *d)
{
	hwif->dma_base =
		hwif->extra_base + tx4939ide_swizzleb(TX4939IDE_DMA_Cmd);
	/*
	 * Note that we cannot use ATA_DMA_TABLE_OFS, ATA_DMA_STATUS
	 * for big endian.
	 */
	return ide_allocate_dma_engine(hwif);
}