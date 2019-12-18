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
struct cdrom_info {int /*<<< orphan*/  dev; int /*<<< orphan*/  drive; } ;

/* Variables and functions */
 int /*<<< orphan*/  cdrom_info ; 
 int /*<<< orphan*/  get_device (int /*<<< orphan*/ *) ; 
 scalar_t__ ide_device_get (int /*<<< orphan*/ ) ; 
 struct cdrom_info* ide_drv_g (struct gendisk*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  idecd_ref_mutex ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct cdrom_info *ide_cd_get(struct gendisk *disk)
{
	struct cdrom_info *cd = NULL;

	mutex_lock(&idecd_ref_mutex);
	cd = ide_drv_g(disk, cdrom_info);
	if (cd) {
		if (ide_device_get(cd->drive))
			cd = NULL;
		else
			get_device(&cd->dev);

	}
	mutex_unlock(&idecd_ref_mutex);
	return cd;
}