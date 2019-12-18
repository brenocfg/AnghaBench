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
struct uvd {int last_error; int /*<<< orphan*/  ifaceAltInactive; int /*<<< orphan*/  iface; TYPE_2__* dev; int /*<<< orphan*/  remove_pending; TYPE_1__* sbuf; scalar_t__ streaming; scalar_t__ user_data; } ;
struct qcm {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;
struct TYPE_3__ {int /*<<< orphan*/  urb; } ;

/* Variables and functions */
 int USBVIDEO_NUMSBUF ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  err (char*,int) ; 
 int qcm_camera_off (struct uvd*) ; 
 int /*<<< orphan*/  qcm_stop_int_data (struct qcm*) ; 
 int /*<<< orphan*/  usb_kill_urb (int /*<<< orphan*/ ) ; 
 int usb_set_interface (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void qcm_stop_data(struct uvd *uvd)
{
	struct qcm *cam = (struct qcm *) uvd->user_data;
	int i, j;
	int ret;

	if ((uvd == NULL) || (!uvd->streaming) || (uvd->dev == NULL))
		return;

	ret = qcm_camera_off(uvd);
	if (ret)
		dev_warn(&uvd->dev->dev, "couldn't turn the cam off.\n");

	uvd->streaming = 0;

	/* Unschedule all of the iso td's */
	for (i=0; i < USBVIDEO_NUMSBUF; i++)
		usb_kill_urb(uvd->sbuf[i].urb);

	qcm_stop_int_data(cam);

	if (!uvd->remove_pending) {
		/* Set packet size to 0 */
		j = usb_set_interface(uvd->dev, uvd->iface,
					uvd->ifaceAltInactive);
		if (j < 0) {
			err("usb_set_interface() error %d.", j);
			uvd->last_error = j;
		}
	}
}