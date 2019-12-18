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
struct usbduxsub {int numOfOutBuffers; TYPE_1__* interface; TYPE_2__** urbOut; int /*<<< orphan*/  usbdev; int /*<<< orphan*/  comedidev; } ;
struct TYPE_4__ {int /*<<< orphan*/  transfer_flags; scalar_t__ status; int /*<<< orphan*/  dev; int /*<<< orphan*/  context; } ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EFAULT ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  URB_ISO_ASAP ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int,int) ; 
 int usb_submit_urb (TYPE_2__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int usbduxsub_submit_OutURBs(struct usbduxsub *usbduxsub)
{
	int i, errFlag;

	if (!usbduxsub)
		return -EFAULT;

	for (i = 0; i < usbduxsub->numOfOutBuffers; i++) {
		dev_dbg(&usbduxsub->interface->dev,
			"comedi_: submitting out-urb[%d]\n", i);
		/* in case of a resubmission after an unlink... */
		usbduxsub->urbOut[i]->context = usbduxsub->comedidev;
		usbduxsub->urbOut[i]->dev = usbduxsub->usbdev;
		usbduxsub->urbOut[i]->status = 0;
		usbduxsub->urbOut[i]->transfer_flags = URB_ISO_ASAP;
		errFlag = usb_submit_urb(usbduxsub->urbOut[i], GFP_ATOMIC);
		if (errFlag) {
			dev_err(&usbduxsub->interface->dev,
				"comedi_: ao: usb_submit_urb(%d) error %d\n",
				i, errFlag);
			return errFlag;
		}
	}
	return 0;
}