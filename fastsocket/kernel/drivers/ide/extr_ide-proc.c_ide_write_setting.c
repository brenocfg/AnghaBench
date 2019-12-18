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
struct ide_proc_devset {int min; int max; struct ide_devset* setting; } ;
struct ide_devset {int flags; int /*<<< orphan*/  set; } ;
typedef  int /*<<< orphan*/  ide_drive_t ;

/* Variables and functions */
 int /*<<< orphan*/  CAP_SYS_ADMIN ; 
 int DS_SYNC ; 
 int EACCES ; 
 int EINVAL ; 
 int EPERM ; 
 int /*<<< orphan*/  capable (int /*<<< orphan*/ ) ; 
 int ide_devset_execute (int /*<<< orphan*/ *,struct ide_devset const*,int) ; 

__attribute__((used)) static int ide_write_setting(ide_drive_t *drive,
			     const struct ide_proc_devset *setting, int val)
{
	const struct ide_devset *ds = setting->setting;

	if (!capable(CAP_SYS_ADMIN))
		return -EACCES;
	if (!ds->set)
		return -EPERM;
	if ((ds->flags & DS_SYNC)
	    && (val < setting->min || val > setting->max))
		return -EINVAL;
	return ide_devset_execute(drive, ds, val);
}