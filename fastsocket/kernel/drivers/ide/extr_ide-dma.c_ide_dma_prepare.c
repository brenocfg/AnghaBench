#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct ide_dma_ops {scalar_t__ (* dma_setup ) (TYPE_2__*,struct ide_cmd*) ;scalar_t__ (* dma_check ) (TYPE_2__*,struct ide_cmd*) ;} ;
struct ide_cmd {int dummy; } ;
struct TYPE_10__ {int dev_flags; int waiting_for_dma; TYPE_1__* hwif; } ;
typedef  TYPE_2__ ide_drive_t ;
struct TYPE_9__ {struct ide_dma_ops* dma_ops; } ;

/* Variables and functions */
 int IDE_DFLAG_USING_DMA ; 
 scalar_t__ ide_dma_map_sg (TYPE_2__*,struct ide_cmd*) ; 
 int /*<<< orphan*/  ide_dma_unmap_sg (TYPE_2__*,struct ide_cmd*) ; 
 int /*<<< orphan*/  ide_map_sg (TYPE_2__*,struct ide_cmd*) ; 
 scalar_t__ stub1 (TYPE_2__*,struct ide_cmd*) ; 
 scalar_t__ stub2 (TYPE_2__*,struct ide_cmd*) ; 

int ide_dma_prepare(ide_drive_t *drive, struct ide_cmd *cmd)
{
	const struct ide_dma_ops *dma_ops = drive->hwif->dma_ops;

	if ((drive->dev_flags & IDE_DFLAG_USING_DMA) == 0 ||
	    (dma_ops->dma_check && dma_ops->dma_check(drive, cmd)))
		goto out;
	ide_map_sg(drive, cmd);
	if (ide_dma_map_sg(drive, cmd) == 0)
		goto out_map;
	if (dma_ops->dma_setup(drive, cmd))
		goto out_dma_unmap;
	drive->waiting_for_dma = 1;
	return 0;
out_dma_unmap:
	ide_dma_unmap_sg(drive, cmd);
out_map:
	ide_map_sg(drive, cmd);
out:
	return 1;
}