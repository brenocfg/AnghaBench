#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  dev_flags; int /*<<< orphan*/  id; } ;
typedef  TYPE_1__ ide_drive_t ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  IDE_DFLAG_WCACHE ; 
 int /*<<< orphan*/  SETFEATURES_WC_OFF ; 
 int /*<<< orphan*/  SETFEATURES_WC_ON ; 
 scalar_t__ ata_id_flush_enabled (int /*<<< orphan*/ ) ; 
 int ide_do_setfeature (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  update_ordered (TYPE_1__*) ; 

__attribute__((used)) static int set_wcache(ide_drive_t *drive, int arg)
{
	int err = 1;

	if (arg < 0 || arg > 1)
		return -EINVAL;

	if (ata_id_flush_enabled(drive->id)) {
		err = ide_do_setfeature(drive,
			arg ? SETFEATURES_WC_ON : SETFEATURES_WC_OFF, 0);
		if (err == 0) {
			if (arg)
				drive->dev_flags |= IDE_DFLAG_WCACHE;
			else
				drive->dev_flags &= ~IDE_DFLAG_WCACHE;
		}
	}

	update_ordered(drive);

	return err;
}