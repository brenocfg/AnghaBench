#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct ide_atapi_pc {int /*<<< orphan*/ * c; } ;
struct gendisk {int dummy; } ;
typedef  int /*<<< orphan*/  ide_drive_t ;

/* Variables and functions */
 int /*<<< orphan*/  TEST_UNIT_READY ; 
 int /*<<< orphan*/  ide_init_pc (struct ide_atapi_pc*) ; 
 int ide_queue_pc_tail (int /*<<< orphan*/ *,struct gendisk*,struct ide_atapi_pc*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

int ide_do_test_unit_ready(ide_drive_t *drive, struct gendisk *disk)
{
	struct ide_atapi_pc pc;

	ide_init_pc(&pc);
	pc.c[0] = TEST_UNIT_READY;

	return ide_queue_pc_tail(drive, disk, &pc, NULL, 0);
}