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
struct ide_atapi_pc {int* c; int /*<<< orphan*/  flags; } ;
struct gendisk {int dummy; } ;
struct TYPE_4__ {scalar_t__ media; } ;
typedef  TYPE_1__ ide_drive_t ;

/* Variables and functions */
 int /*<<< orphan*/  PC_FLAG_WAIT_FOR_DSC ; 
 int START_STOP ; 
 int /*<<< orphan*/  ide_init_pc (struct ide_atapi_pc*) ; 
 int ide_queue_pc_tail (TYPE_1__*,struct gendisk*,struct ide_atapi_pc*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ ide_tape ; 

int ide_do_start_stop(ide_drive_t *drive, struct gendisk *disk, int start)
{
	struct ide_atapi_pc pc;

	ide_init_pc(&pc);
	pc.c[0] = START_STOP;
	pc.c[4] = start;

	if (drive->media == ide_tape)
		pc.flags |= PC_FLAG_WAIT_FOR_DSC;

	return ide_queue_pc_tail(drive, disk, &pc, NULL, 0);
}