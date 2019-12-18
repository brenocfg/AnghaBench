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
struct gendisk {struct disk_info* private_data; } ;
struct disk_info {int /*<<< orphan*/  viocd_info; } ;

/* Variables and functions */
 int cdrom_media_changed (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int viocd_blk_media_changed(struct gendisk *disk)
{
	struct disk_info *di = disk->private_data;
	return cdrom_media_changed(&di->viocd_info);
}