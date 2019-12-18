#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u_int ;
struct scsi_device {scalar_t__ tagged_supported; TYPE_2__* sdev_target; int /*<<< orphan*/  lun; TYPE_1__* host; } ;
struct ahc_softc {int /*<<< orphan*/  our_id_b; int /*<<< orphan*/  our_id; } ;
struct ahc_devinfo {int /*<<< orphan*/  lun; int /*<<< orphan*/  target; int /*<<< orphan*/  channel; } ;
struct TYPE_4__ {scalar_t__ channel; int /*<<< orphan*/  id; } ;
struct TYPE_3__ {scalar_t__ hostdata; } ;

/* Variables and functions */
 int /*<<< orphan*/  AC_TRANSFER_NEG ; 
 int /*<<< orphan*/  AHC_QUEUE_NONE ; 
 int /*<<< orphan*/  AHC_QUEUE_TAGGED ; 
 int /*<<< orphan*/  ROLE_INITIATOR ; 
 int /*<<< orphan*/  ahc_compile_devinfo (struct ahc_devinfo*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char,int /*<<< orphan*/ ) ; 
 scalar_t__ ahc_linux_user_tagdepth (struct ahc_softc*,struct ahc_devinfo*) ; 
 int /*<<< orphan*/  ahc_platform_set_tags (struct ahc_softc*,struct scsi_device*,struct ahc_devinfo*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ahc_print_devinfo (struct ahc_softc*,struct ahc_devinfo*) ; 
 int /*<<< orphan*/  ahc_send_async (struct ahc_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,scalar_t__) ; 

__attribute__((used)) static void
ahc_linux_device_queue_depth(struct scsi_device *sdev)
{
	struct	ahc_devinfo devinfo;
	u_int	tags;
	struct ahc_softc *ahc = *((struct ahc_softc **)sdev->host->hostdata);

	ahc_compile_devinfo(&devinfo,
			    sdev->sdev_target->channel == 0
			  ? ahc->our_id : ahc->our_id_b,
			    sdev->sdev_target->id, sdev->lun,
			    sdev->sdev_target->channel == 0 ? 'A' : 'B',
			    ROLE_INITIATOR);
	tags = ahc_linux_user_tagdepth(ahc, &devinfo);
	if (tags != 0 && sdev->tagged_supported != 0) {

		ahc_platform_set_tags(ahc, sdev, &devinfo, AHC_QUEUE_TAGGED);
		ahc_send_async(ahc, devinfo.channel, devinfo.target,
			       devinfo.lun, AC_TRANSFER_NEG);
		ahc_print_devinfo(ahc, &devinfo);
		printf("Tagged Queuing enabled.  Depth %d\n", tags);
	} else {
		ahc_platform_set_tags(ahc, sdev, &devinfo, AHC_QUEUE_NONE);
		ahc_send_async(ahc, devinfo.channel, devinfo.target,
			       devinfo.lun, AC_TRANSFER_NEG);
	}
}