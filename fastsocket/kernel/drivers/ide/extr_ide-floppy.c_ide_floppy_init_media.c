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
struct gendisk {int dummy; } ;
typedef  int /*<<< orphan*/  ide_drive_t ;

/* Variables and functions */
 int /*<<< orphan*/  ide_do_start_stop (int /*<<< orphan*/ *,struct gendisk*,int) ; 
 scalar_t__ ide_do_test_unit_ready (int /*<<< orphan*/ *,struct gendisk*) ; 
 int ide_floppy_get_capacity (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ide_gd_capacity (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_capacity (struct gendisk*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ide_floppy_init_media(ide_drive_t *drive, struct gendisk *disk)
{
	int ret = 0;

	if (ide_do_test_unit_ready(drive, disk))
		ide_do_start_stop(drive, disk, 1);

	ret = ide_floppy_get_capacity(drive);

	set_capacity(disk, ide_gd_capacity(drive));

	return ret;
}