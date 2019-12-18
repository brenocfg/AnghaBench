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
struct tape_device {int dummy; } ;
struct gendisk {struct tape_device* private_data; } ;
struct block_device {int /*<<< orphan*/  bd_dev; struct gendisk* bd_disk; } ;
typedef  int /*<<< orphan*/  fmode_t ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  DBF_LH (int,char*,unsigned int,...) ; 
 int EINVAL ; 
 int MINOR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tapeblock_major ; 

__attribute__((used)) static int
tapeblock_ioctl(
	struct block_device *	bdev,
	fmode_t			mode,
	unsigned int		command,
	unsigned long		arg
) {
	int rc;
	int minor;
	struct gendisk *disk = bdev->bd_disk;
	struct tape_device *device;

	rc     = 0;
	BUG_ON(!disk);
	device = disk->private_data;
	BUG_ON(!device);
	minor  = MINOR(bdev->bd_dev);

	DBF_LH(6, "tapeblock_ioctl(0x%0x)\n", command);
	DBF_LH(6, "device = %d:%d\n", tapeblock_major, minor);

	switch (command) {
		/* Refuse some IOCTL calls without complaining (mount). */
		case 0x5310:		/* CDROMMULTISESSION */
			rc = -EINVAL;
			break;
		default:
			rc = -EINVAL;
	}

	return rc;
}