#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct ide_disk_obj {TYPE_2__* drive; } ;
struct block_device {int /*<<< orphan*/  bd_disk; } ;
struct TYPE_5__ {TYPE_1__* disk_ops; } ;
typedef  TYPE_2__ ide_drive_t ;
typedef  int /*<<< orphan*/  fmode_t ;
struct TYPE_4__ {int (* ioctl ) (TYPE_2__*,struct block_device*,int /*<<< orphan*/ ,unsigned int,unsigned long) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  ide_disk_obj ; 
 struct ide_disk_obj* ide_drv_g (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int stub1 (TYPE_2__*,struct block_device*,int /*<<< orphan*/ ,unsigned int,unsigned long) ; 

__attribute__((used)) static int ide_gd_ioctl(struct block_device *bdev, fmode_t mode,
			     unsigned int cmd, unsigned long arg)
{
	struct ide_disk_obj *idkp = ide_drv_g(bdev->bd_disk, ide_disk_obj);
	ide_drive_t *drive = idkp->drive;

	return drive->disk_ops->ioctl(drive, bdev, mode, cmd, arg);
}