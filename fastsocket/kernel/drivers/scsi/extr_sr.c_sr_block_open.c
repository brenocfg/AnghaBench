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
struct scsi_cd {int /*<<< orphan*/  cdi; } ;
struct block_device {int /*<<< orphan*/  bd_disk; } ;
typedef  int /*<<< orphan*/  fmode_t ;

/* Variables and functions */
 int ENXIO ; 
 int cdrom_open (int /*<<< orphan*/ *,struct block_device*,int /*<<< orphan*/ ) ; 
 struct scsi_cd* scsi_cd_get (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  scsi_cd_put (struct scsi_cd*) ; 

__attribute__((used)) static int sr_block_open(struct block_device *bdev, fmode_t mode)
{
	struct scsi_cd *cd = scsi_cd_get(bdev->bd_disk);
	int ret = -ENXIO;

	if (cd) {
		ret = cdrom_open(&cd->cdi, bdev, mode);
		if (ret)
			scsi_cd_put(cd);
	}
	return ret;
}