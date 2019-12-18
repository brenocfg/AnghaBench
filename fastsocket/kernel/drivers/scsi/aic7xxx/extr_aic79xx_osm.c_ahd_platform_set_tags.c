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
typedef  scalar_t__ u_int ;
struct scsi_device {int dummy; } ;
struct ahd_softc {int dummy; } ;
struct ahd_linux_device {int flags; int active; int openings; scalar_t__ maxtags; int /*<<< orphan*/  qfrozen; } ;
struct ahd_devinfo {int dummy; } ;
typedef  int ahd_queue_alg ;

/* Variables and functions */
 int AHD_DEV_FREEZE_TIL_EMPTY ; 
 int AHD_DEV_PERIODIC_OTAG ; 
#define  AHD_DEV_Q_BASIC 132 
#define  AHD_DEV_Q_TAGGED 131 
#define  AHD_QUEUE_BASIC 130 
#define  AHD_QUEUE_NONE 129 
#define  AHD_QUEUE_TAGGED 128 
 int /*<<< orphan*/  MSG_ORDERED_TASK ; 
 int /*<<< orphan*/  MSG_SIMPLE_TASK ; 
 scalar_t__ ahd_linux_user_tagdepth (struct ahd_softc*,struct ahd_devinfo*) ; 
 scalar_t__ aic79xx_periodic_otag ; 
 int /*<<< orphan*/  scsi_activate_tcq (struct scsi_device*,int) ; 
 int /*<<< orphan*/  scsi_deactivate_tcq (struct scsi_device*,int) ; 
 int /*<<< orphan*/  scsi_set_tag_type (struct scsi_device*,int /*<<< orphan*/ ) ; 
 struct ahd_linux_device* scsi_transport_device_data (struct scsi_device*) ; 

void
ahd_platform_set_tags(struct ahd_softc *ahd, struct scsi_device *sdev,
		      struct ahd_devinfo *devinfo, ahd_queue_alg alg)
{
	struct ahd_linux_device *dev;
	int was_queuing;
	int now_queuing;

	if (sdev == NULL)
		return;

	dev = scsi_transport_device_data(sdev);

	if (dev == NULL)
		return;
	was_queuing = dev->flags & (AHD_DEV_Q_BASIC|AHD_DEV_Q_TAGGED);
	switch (alg) {
	default:
	case AHD_QUEUE_NONE:
		now_queuing = 0;
		break; 
	case AHD_QUEUE_BASIC:
		now_queuing = AHD_DEV_Q_BASIC;
		break;
	case AHD_QUEUE_TAGGED:
		now_queuing = AHD_DEV_Q_TAGGED;
		break;
	}
	if ((dev->flags & AHD_DEV_FREEZE_TIL_EMPTY) == 0
	 && (was_queuing != now_queuing)
	 && (dev->active != 0)) {
		dev->flags |= AHD_DEV_FREEZE_TIL_EMPTY;
		dev->qfrozen++;
	}

	dev->flags &= ~(AHD_DEV_Q_BASIC|AHD_DEV_Q_TAGGED|AHD_DEV_PERIODIC_OTAG);
	if (now_queuing) {
		u_int usertags;

		usertags = ahd_linux_user_tagdepth(ahd, devinfo);
		if (!was_queuing) {
			/*
			 * Start out agressively and allow our
			 * dynamic queue depth algorithm to take
			 * care of the rest.
			 */
			dev->maxtags = usertags;
			dev->openings = dev->maxtags - dev->active;
		}
		if (dev->maxtags == 0) {
			/*
			 * Queueing is disabled by the user.
			 */
			dev->openings = 1;
		} else if (alg == AHD_QUEUE_TAGGED) {
			dev->flags |= AHD_DEV_Q_TAGGED;
			if (aic79xx_periodic_otag != 0)
				dev->flags |= AHD_DEV_PERIODIC_OTAG;
		} else
			dev->flags |= AHD_DEV_Q_BASIC;
	} else {
		/* We can only have one opening. */
		dev->maxtags = 0;
		dev->openings =  1 - dev->active;
	}

	switch ((dev->flags & (AHD_DEV_Q_BASIC|AHD_DEV_Q_TAGGED))) {
	case AHD_DEV_Q_BASIC:
		scsi_set_tag_type(sdev, MSG_SIMPLE_TASK);
		scsi_activate_tcq(sdev, dev->openings + dev->active);
		break;
	case AHD_DEV_Q_TAGGED:
		scsi_set_tag_type(sdev, MSG_ORDERED_TASK);
		scsi_activate_tcq(sdev, dev->openings + dev->active);
		break;
	default:
		/*
		 * We allow the OS to queue 2 untagged transactions to
		 * us at any time even though we can only execute them
		 * serially on the controller/device.  This should
		 * remove some latency.
		 */
		scsi_deactivate_tcq(sdev, 1);
		break;
	}
}