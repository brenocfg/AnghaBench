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
struct block_device {int dummy; } ;
typedef  int /*<<< orphan*/  ide_drive_t ;
typedef  int /*<<< orphan*/  fmode_t ;

/* Variables and functions */
 int EOPNOTSUPP ; 
 int generic_ide_ioctl (int /*<<< orphan*/ *,struct block_device*,unsigned int,unsigned long) ; 
 int /*<<< orphan*/  ide_disk_ioctl_settings ; 
 int ide_setting_ioctl (int /*<<< orphan*/ *,struct block_device*,unsigned int,unsigned long,int /*<<< orphan*/ ) ; 

int ide_disk_ioctl(ide_drive_t *drive, struct block_device *bdev, fmode_t mode,
		   unsigned int cmd, unsigned long arg)
{
	int err;

	err = ide_setting_ioctl(drive, bdev, cmd, arg, ide_disk_ioctl_settings);
	if (err != -EOPNOTSUPP)
		return err;

	return generic_ide_ioctl(drive, bdev, cmd, arg);
}