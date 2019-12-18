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
struct cdrom_device_ops {int capability; int /*<<< orphan*/  (* tray_move ) (struct cdrom_device_info*,int) ;int /*<<< orphan*/  (* release ) (struct cdrom_device_info*) ;int /*<<< orphan*/  (* lock_door ) (struct cdrom_device_info*,int /*<<< orphan*/ ) ;} ;
struct cdrom_device_info {scalar_t__ use_count; int options; scalar_t__ for_data; int /*<<< orphan*/  name; struct cdrom_device_ops* ops; } ;
typedef  int fmode_t ;

/* Variables and functions */
 int CDC_LOCK ; 
 int /*<<< orphan*/  CDC_OPEN_TRAY ; 
 int /*<<< orphan*/  CDC_RAM ; 
 int CDO_AUTO_EJECT ; 
 int CDO_USE_FFLAGS ; 
 scalar_t__ CDROM_CAN (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CD_CLOSE ; 
 int FMODE_NDELAY ; 
 int /*<<< orphan*/  cdinfo (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  cdrom_close_write (struct cdrom_device_info*) ; 
 int /*<<< orphan*/  cdrom_dvd_rw_close_write (struct cdrom_device_info*) ; 
 int /*<<< orphan*/  keeplocked ; 
 int /*<<< orphan*/  stub1 (struct cdrom_device_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (struct cdrom_device_info*) ; 
 int /*<<< orphan*/  stub3 (struct cdrom_device_info*,int) ; 

void cdrom_release(struct cdrom_device_info *cdi, fmode_t mode)
{
	struct cdrom_device_ops *cdo;
	int opened_for_data;

	if (cdi == NULL)	/* device is gone */
		return;
	cdo = cdi->ops;

	cdinfo(CD_CLOSE, "entering cdrom_release\n");

	if (cdi->use_count > 0)
		cdi->use_count--;

	if (cdi->use_count == 0) {
		cdinfo(CD_CLOSE, "Use count for \"/dev/%s\" now zero\n", cdi->name);
		cdrom_dvd_rw_close_write(cdi);

		if ((cdo->capability & CDC_LOCK) && !keeplocked) {
			cdinfo(CD_CLOSE, "Unlocking door!\n");
			cdo->lock_door(cdi, 0);
		}
	}

	opened_for_data = !(cdi->options & CDO_USE_FFLAGS) ||
		!(mode & FMODE_NDELAY);

	/*
	 * flush cache on last write release
	 */
	if (CDROM_CAN(CDC_RAM) && !cdi->use_count && cdi->for_data)
		cdrom_close_write(cdi);

	cdo->release(cdi);
	if (cdi->use_count == 0) {      /* last process that closes dev*/
		if (opened_for_data &&
		    cdi->options & CDO_AUTO_EJECT && CDROM_CAN(CDC_OPEN_TRAY))
			cdo->tray_move(cdi, 1);
	}
}