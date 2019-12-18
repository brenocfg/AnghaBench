#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct ide_port_ops {int /*<<< orphan*/  (* pre_reset ) (TYPE_2__*) ;} ;
struct TYPE_9__ {scalar_t__ media; int dev_flags; int current_speed; int desired_speed; scalar_t__ io_32bit; scalar_t__ crc_count; TYPE_1__* hwif; } ;
typedef  TYPE_2__ ide_drive_t ;
struct TYPE_8__ {struct ide_port_ops* port_ops; } ;

/* Variables and functions */
 int IDE_DFLAG_KEEP_SETTINGS ; 
 int IDE_DFLAG_POST_RESET ; 
 int IDE_DFLAG_UNMASK ; 
 int IDE_DFLAG_USING_DMA ; 
 int /*<<< orphan*/  ide_check_dma_crc (TYPE_2__*) ; 
 scalar_t__ ide_disk ; 
 int /*<<< orphan*/  ide_disk_pre_reset (TYPE_2__*) ; 
 int /*<<< orphan*/  ide_dma_off (TYPE_2__*) ; 
 int /*<<< orphan*/  stub1 (TYPE_2__*) ; 

__attribute__((used)) static void pre_reset(ide_drive_t *drive)
{
	const struct ide_port_ops *port_ops = drive->hwif->port_ops;

	if (drive->media == ide_disk)
		ide_disk_pre_reset(drive);
	else
		drive->dev_flags |= IDE_DFLAG_POST_RESET;

	if (drive->dev_flags & IDE_DFLAG_USING_DMA) {
		if (drive->crc_count)
			ide_check_dma_crc(drive);
		else
			ide_dma_off(drive);
	}

	if ((drive->dev_flags & IDE_DFLAG_KEEP_SETTINGS) == 0) {
		if ((drive->dev_flags & IDE_DFLAG_USING_DMA) == 0) {
			drive->dev_flags &= ~IDE_DFLAG_UNMASK;
			drive->io_32bit = 0;
		}
		return;
	}

	if (port_ops && port_ops->pre_reset)
		port_ops->pre_reset(drive);

	if (drive->current_speed != 0xff)
		drive->desired_speed = drive->current_speed;
	drive->current_speed = 0xff;
}