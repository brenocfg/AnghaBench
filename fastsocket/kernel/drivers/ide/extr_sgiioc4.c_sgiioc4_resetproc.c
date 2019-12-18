#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct ide_cmd {int dummy; } ;
struct TYPE_8__ {TYPE_1__* hwif; } ;
typedef  TYPE_2__ ide_drive_t ;
struct TYPE_7__ {struct ide_cmd cmd; } ;

/* Variables and functions */
 int /*<<< orphan*/  ide_dma_unmap_sg (TYPE_2__*,struct ide_cmd*) ; 
 int /*<<< orphan*/  sgiioc4_clearirq (TYPE_2__*) ; 
 int /*<<< orphan*/  sgiioc4_dma_end (TYPE_2__*) ; 

__attribute__((used)) static void sgiioc4_resetproc(ide_drive_t *drive)
{
	struct ide_cmd *cmd = &drive->hwif->cmd;

	sgiioc4_dma_end(drive);
	ide_dma_unmap_sg(drive, cmd);
	sgiioc4_clearirq(drive);
}