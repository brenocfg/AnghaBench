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
struct cdrom_info {int /*<<< orphan*/  devinfo; } ;
struct block_device {int /*<<< orphan*/  bd_disk; } ;
typedef  int /*<<< orphan*/  fmode_t ;

/* Variables and functions */
 int ENOMEM ; 
 int ENXIO ; 
 int cdrom_open (int /*<<< orphan*/ *,struct block_device*,int /*<<< orphan*/ ) ; 
 struct cdrom_info* ide_cd_get (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ide_cd_put (struct cdrom_info*) ; 

__attribute__((used)) static int idecd_open(struct block_device *bdev, fmode_t mode)
{
	struct cdrom_info *info = ide_cd_get(bdev->bd_disk);
	int rc = -ENOMEM;

	if (!info)
		return -ENXIO;

	rc = cdrom_open(&info->devinfo, bdev, mode);

	if (rc < 0)
		ide_cd_put(info);

	return rc;
}