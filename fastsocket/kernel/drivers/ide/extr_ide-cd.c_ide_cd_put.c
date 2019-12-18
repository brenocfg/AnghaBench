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
struct cdrom_info {int /*<<< orphan*/  dev; int /*<<< orphan*/ * drive; } ;
typedef  int /*<<< orphan*/  ide_drive_t ;

/* Variables and functions */
 int /*<<< orphan*/  ide_device_put (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  idecd_ref_mutex ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  put_device (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void ide_cd_put(struct cdrom_info *cd)
{
	ide_drive_t *drive = cd->drive;

	mutex_lock(&idecd_ref_mutex);
	put_device(&cd->dev);
	ide_device_put(drive);
	mutex_unlock(&idecd_ref_mutex);
}