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
struct ide_tape_obj {int /*<<< orphan*/ * drive; } ;
struct block_device {int /*<<< orphan*/  bd_disk; } ;
typedef  int /*<<< orphan*/  ide_drive_t ;
typedef  int /*<<< orphan*/  fmode_t ;

/* Variables and functions */
 int EINVAL ; 
 int generic_ide_ioctl (int /*<<< orphan*/ *,struct block_device*,unsigned int,unsigned long) ; 
 struct ide_tape_obj* ide_drv_g (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ide_tape_obj ; 
 int idetape_blkdev_ioctl (int /*<<< orphan*/ *,unsigned int,unsigned long) ; 

__attribute__((used)) static int idetape_ioctl(struct block_device *bdev, fmode_t mode,
			unsigned int cmd, unsigned long arg)
{
	struct ide_tape_obj *tape = ide_drv_g(bdev->bd_disk, ide_tape_obj);
	ide_drive_t *drive = tape->drive;
	int err = generic_ide_ioctl(drive, bdev, cmd, arg);
	if (err == -EINVAL)
		err = idetape_blkdev_ioctl(drive, cmd, arg);
	return err;
}