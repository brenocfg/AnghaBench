#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct usbduxsub {int numOfInBuffers; TYPE_1__* interface; TYPE_2__** urbIn; TYPE_3__* comedidev; int /*<<< orphan*/  usbdev; int /*<<< orphan*/  ai_interval; } ;
struct TYPE_6__ {int /*<<< orphan*/  minor; } ;
struct TYPE_5__ {int /*<<< orphan*/  interval; int /*<<< orphan*/  dev; TYPE_3__* context; int /*<<< orphan*/  transfer_flags; scalar_t__ status; } ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EFAULT ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  URB_ISO_ASAP ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int,TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int,int) ; 
 int usb_submit_urb (TYPE_2__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int usbduxsub_submit_InURBs(struct usbduxsub *usbduxsub)
{
	int i, errFlag;

	if (!usbduxsub)
		return -EFAULT;

	/* Submit all URBs and start the transfer on the bus */
	for (i = 0; i < usbduxsub->numOfInBuffers; i++) {
		/* in case of a resubmission after an unlink... */
		usbduxsub->urbIn[i]->interval = usbduxsub->ai_interval;
		usbduxsub->urbIn[i]->context = usbduxsub->comedidev;
		usbduxsub->urbIn[i]->dev = usbduxsub->usbdev;
		usbduxsub->urbIn[i]->status = 0;
		usbduxsub->urbIn[i]->transfer_flags = URB_ISO_ASAP;
		dev_dbg(&usbduxsub->interface->dev,
			"comedi%d: submitting in-urb[%d]: %p,%p intv=%d\n",
			usbduxsub->comedidev->minor, i,
			(usbduxsub->urbIn[i]->context),
			(usbduxsub->urbIn[i]->dev),
			(usbduxsub->urbIn[i]->interval));
		errFlag = usb_submit_urb(usbduxsub->urbIn[i], GFP_ATOMIC);
		if (errFlag) {
			dev_err(&usbduxsub->interface->dev,
				"comedi_: ai: usb_submit_urb(%d) error %d\n",
				i, errFlag);
			return errFlag;
		}
	}
	return 0;
}