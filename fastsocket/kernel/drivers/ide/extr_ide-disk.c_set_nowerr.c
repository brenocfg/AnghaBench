#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  bad_wstat; int /*<<< orphan*/  dev_flags; } ;
typedef  TYPE_1__ ide_drive_t ;

/* Variables and functions */
 int /*<<< orphan*/  BAD_R_STAT ; 
 int /*<<< orphan*/  BAD_W_STAT ; 
 int EINVAL ; 
 int /*<<< orphan*/  IDE_DFLAG_NOWERR ; 

__attribute__((used)) static int set_nowerr(ide_drive_t *drive, int arg)
{
	if (arg < 0 || arg > 1)
		return -EINVAL;

	if (arg)
		drive->dev_flags |= IDE_DFLAG_NOWERR;
	else
		drive->dev_flags &= ~IDE_DFLAG_NOWERR;

	drive->bad_wstat = arg ? BAD_R_STAT : BAD_W_STAT;

	return 0;
}