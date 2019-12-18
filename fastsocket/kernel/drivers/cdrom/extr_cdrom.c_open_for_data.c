#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int error; scalar_t__ data; } ;
typedef  TYPE_1__ tracktype ;
struct cdrom_device_ops {int (* drive_status ) (struct cdrom_device_info*,int /*<<< orphan*/ ) ;int (* tray_move ) (struct cdrom_device_info*,int /*<<< orphan*/ ) ;int (* open ) (struct cdrom_device_info*,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* lock_door ) (struct cdrom_device_info*,int) ;} ;
struct cdrom_device_info {int options; struct cdrom_device_ops* ops; } ;

/* Variables and functions */
 int /*<<< orphan*/  CDC_CLOSE_TRAY ; 
 int /*<<< orphan*/  CDC_LOCK ; 
 int CDO_AUTO_CLOSE ; 
 int CDO_CHECK_TYPE ; 
 int CDO_LOCK ; 
 scalar_t__ CDROM_CAN (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CDSL_CURRENT ; 
 int CDS_DISC_OK ; 
 int CDS_NO_DISC ; 
 int CDS_TRAY_OPEN ; 
 int /*<<< orphan*/  CD_OPEN ; 
 int /*<<< orphan*/  CD_WARNING ; 
 int EMEDIUMTYPE ; 
 int ENOMEDIUM ; 
 int /*<<< orphan*/  cdinfo (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  cdrom_count_tracks (struct cdrom_device_info*,TYPE_1__*) ; 
 int /*<<< orphan*/  current ; 
 int stub1 (struct cdrom_device_info*,int /*<<< orphan*/ ) ; 
 int stub2 (struct cdrom_device_info*,int /*<<< orphan*/ ) ; 
 int stub3 (struct cdrom_device_info*,int /*<<< orphan*/ ) ; 
 int stub4 (struct cdrom_device_info*,int /*<<< orphan*/ ) ; 
 int stub5 (struct cdrom_device_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub6 (struct cdrom_device_info*,int) ; 
 int /*<<< orphan*/  stub7 (struct cdrom_device_info*,int) ; 
 scalar_t__ task_pid_nr (int /*<<< orphan*/ ) ; 

__attribute__((used)) static
int open_for_data(struct cdrom_device_info * cdi)
{
	int ret;
	struct cdrom_device_ops *cdo = cdi->ops;
	tracktype tracks;
	cdinfo(CD_OPEN, "entering open_for_data\n");
	/* Check if the driver can report drive status.  If it can, we
	   can do clever things.  If it can't, well, we at least tried! */
	if (cdo->drive_status != NULL) {
		ret = cdo->drive_status(cdi, CDSL_CURRENT);
		cdinfo(CD_OPEN, "drive_status=%d\n", ret); 
		if (ret == CDS_TRAY_OPEN) {
			cdinfo(CD_OPEN, "the tray is open...\n"); 
			/* can/may i close it? */
			if (CDROM_CAN(CDC_CLOSE_TRAY) &&
			    cdi->options & CDO_AUTO_CLOSE) {
				cdinfo(CD_OPEN, "trying to close the tray.\n"); 
				ret=cdo->tray_move(cdi,0);
				if (ret) {
					cdinfo(CD_OPEN, "bummer. tried to close the tray but failed.\n"); 
					/* Ignore the error from the low
					level driver.  We don't care why it
					couldn't close the tray.  We only care 
					that there is no disc in the drive, 
					since that is the _REAL_ problem here.*/
					ret=-ENOMEDIUM;
					goto clean_up_and_return;
				}
			} else {
				cdinfo(CD_OPEN, "bummer. this drive can't close the tray.\n"); 
				ret=-ENOMEDIUM;
				goto clean_up_and_return;
			}
			/* Ok, the door should be closed now.. Check again */
			ret = cdo->drive_status(cdi, CDSL_CURRENT);
			if ((ret == CDS_NO_DISC) || (ret==CDS_TRAY_OPEN)) {
				cdinfo(CD_OPEN, "bummer. the tray is still not closed.\n"); 
				cdinfo(CD_OPEN, "tray might not contain a medium.\n");
				ret=-ENOMEDIUM;
				goto clean_up_and_return;
			}
			cdinfo(CD_OPEN, "the tray is now closed.\n"); 
		}
		/* the door should be closed now, check for the disc */
		ret = cdo->drive_status(cdi, CDSL_CURRENT);
		if (ret!=CDS_DISC_OK) {
			ret = -ENOMEDIUM;
			goto clean_up_and_return;
		}
	}
	cdrom_count_tracks(cdi, &tracks);
	if (tracks.error == CDS_NO_DISC) {
		cdinfo(CD_OPEN, "bummer. no disc.\n");
		ret=-ENOMEDIUM;
		goto clean_up_and_return;
	}
	/* CD-Players which don't use O_NONBLOCK, workman
	 * for example, need bit CDO_CHECK_TYPE cleared! */
	if (tracks.data==0) {
		if (cdi->options & CDO_CHECK_TYPE) {
		    /* give people a warning shot, now that CDO_CHECK_TYPE
		       is the default case! */
		    cdinfo(CD_OPEN, "bummer. wrong media type.\n"); 
		    cdinfo(CD_WARNING, "pid %d must open device O_NONBLOCK!\n",
					(unsigned int)task_pid_nr(current));
		    ret=-EMEDIUMTYPE;
		    goto clean_up_and_return;
		}
		else {
		    cdinfo(CD_OPEN, "wrong media type, but CDO_CHECK_TYPE not set.\n");
		}
	}

	cdinfo(CD_OPEN, "all seems well, opening the device.\n"); 

	/* all seems well, we can open the device */
	ret = cdo->open(cdi, 0); /* open for data */
	cdinfo(CD_OPEN, "opening the device gave me %d.\n", ret); 
	/* After all this careful checking, we shouldn't have problems
	   opening the device, but we don't want the device locked if 
	   this somehow fails... */
	if (ret) {
		cdinfo(CD_OPEN, "open device failed.\n"); 
		goto clean_up_and_return;
	}
	if (CDROM_CAN(CDC_LOCK) && (cdi->options & CDO_LOCK)) {
			cdo->lock_door(cdi, 1);
			cdinfo(CD_OPEN, "door locked.\n");
	}
	cdinfo(CD_OPEN, "device opened successfully.\n"); 
	return ret;

	/* Something failed.  Try to unlock the drive, because some drivers
	(notably ide-cd) lock the drive after every command.  This produced
	a nasty bug where after mount failed, the drive would remain locked!  
	This ensures that the drive gets unlocked after a mount fails.  This 
	is a goto to avoid bloating the driver with redundant code. */ 
clean_up_and_return:
	cdinfo(CD_OPEN, "open failed.\n"); 
	if (CDROM_CAN(CDC_LOCK) && cdi->options & CDO_LOCK) {
			cdo->lock_door(cdi, 0);
			cdinfo(CD_OPEN, "door unlocked.\n");
	}
	return ret;
}