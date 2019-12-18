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
struct cdrom_info {int /*<<< orphan*/  devinfo; int /*<<< orphan*/  drive; } ;
struct block_device {int /*<<< orphan*/  bd_disk; } ;
typedef  int /*<<< orphan*/  fmode_t ;

/* Variables and functions */
#define  CDROMGETSPINDOWN 129 
#define  CDROMSETSPINDOWN 128 
 int EINVAL ; 
 int /*<<< orphan*/  cdrom_info ; 
 int cdrom_ioctl (int /*<<< orphan*/ *,struct block_device*,int /*<<< orphan*/ ,unsigned int,unsigned long) ; 
 int generic_ide_ioctl (int /*<<< orphan*/ ,struct block_device*,unsigned int,unsigned long) ; 
 struct cdrom_info* ide_drv_g (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int idecd_get_spindown (int /*<<< orphan*/ *,unsigned long) ; 
 int idecd_set_spindown (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int idecd_ioctl(struct block_device *bdev, fmode_t mode,
			unsigned int cmd, unsigned long arg)
{
	struct cdrom_info *info = ide_drv_g(bdev->bd_disk, cdrom_info);
	int err;

	switch (cmd) {
	case CDROMSETSPINDOWN:
		return idecd_set_spindown(&info->devinfo, arg);
	case CDROMGETSPINDOWN:
		return idecd_get_spindown(&info->devinfo, arg);
	default:
		break;
	}

	err = generic_ide_ioctl(info->drive, bdev, cmd, arg);
	if (err == -EINVAL)
		err = cdrom_ioctl(&info->devinfo, bdev, mode, cmd, arg);

	return err;
}