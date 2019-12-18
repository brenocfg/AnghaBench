#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct cdrom_device_info {int options; int /*<<< orphan*/  use_count; TYPE_1__* ops; int /*<<< orphan*/  name; scalar_t__ media_written; } ;
struct block_device {int dummy; } ;
typedef  int fmode_t ;
struct TYPE_2__ {int (* open ) (struct cdrom_device_info*,int) ;int /*<<< orphan*/  (* release ) (struct cdrom_device_info*) ;int /*<<< orphan*/  (* lock_door ) (struct cdrom_device_info*,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  CDC_LOCK ; 
 int /*<<< orphan*/  CDC_RAM ; 
 int CDO_LOCK ; 
 int CDO_USE_FFLAGS ; 
 scalar_t__ CDROM_CAN (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CD_OPEN ; 
 int EROFS ; 
 int FMODE_NDELAY ; 
 int FMODE_WRITE ; 
 int /*<<< orphan*/  cdinfo (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  cdrom_mmc3_profile (struct cdrom_device_info*) ; 
 scalar_t__ cdrom_open_write (struct cdrom_device_info*) ; 
 int /*<<< orphan*/  check_disk_change (struct block_device*) ; 
 int open_for_data (struct cdrom_device_info*) ; 
 int stub1 (struct cdrom_device_info*,int) ; 
 int /*<<< orphan*/  stub2 (struct cdrom_device_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub3 (struct cdrom_device_info*) ; 

int cdrom_open(struct cdrom_device_info *cdi, struct block_device *bdev, fmode_t mode)
{
	int ret;

	cdinfo(CD_OPEN, "entering cdrom_open\n"); 

	/* if this was a O_NONBLOCK open and we should honor the flags,
	 * do a quick open without drive/disc integrity checks. */
	cdi->use_count++;
	if ((mode & FMODE_NDELAY) && (cdi->options & CDO_USE_FFLAGS)) {
		ret = cdi->ops->open(cdi, 1);
	} else {
		ret = open_for_data(cdi);
		if (ret)
			goto err;
		cdrom_mmc3_profile(cdi);
		if (mode & FMODE_WRITE) {
			ret = -EROFS;
			if (cdrom_open_write(cdi))
				goto err_release;
			if (!CDROM_CAN(CDC_RAM))
				goto err_release;
			ret = 0;
			cdi->media_written = 0;
		}
	}

	if (ret)
		goto err;

	cdinfo(CD_OPEN, "Use count for \"/dev/%s\" now %d\n",
			cdi->name, cdi->use_count);
	/* Do this on open.  Don't wait for mount, because they might
	    not be mounting, but opening with O_NONBLOCK */
	check_disk_change(bdev);
	return 0;
err_release:
	if (CDROM_CAN(CDC_LOCK) && cdi->options & CDO_LOCK) {
		cdi->ops->lock_door(cdi, 0);
		cdinfo(CD_OPEN, "door unlocked.\n");
	}
	cdi->ops->release(cdi);
err:
	cdi->use_count--;
	return ret;
}