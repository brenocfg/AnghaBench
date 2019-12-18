#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct usbduxsub {TYPE_1__* interface; TYPE_2__* urbPwm; int /*<<< orphan*/  comedidev; int /*<<< orphan*/  sizePwmBuf; int /*<<< orphan*/  usbdev; } ;
struct TYPE_5__ {int /*<<< orphan*/  transfer_buffer; } ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EFAULT ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  PWM_EP ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  usb_fill_bulk_urb (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_sndbulkpipe (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int usb_submit_urb (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usbduxsub_pwm_irq ; 

__attribute__((used)) static int usbduxsub_submit_PwmURBs(struct usbduxsub *usbduxsub)
{
	int errFlag;

	if (!usbduxsub)
		return -EFAULT;

	dev_dbg(&usbduxsub->interface->dev, "comedi_: submitting pwm-urb\n");

	/* in case of a resubmission after an unlink... */
	usb_fill_bulk_urb(usbduxsub->urbPwm,
			  usbduxsub->usbdev,
			  usb_sndbulkpipe(usbduxsub->usbdev, PWM_EP),
			  usbduxsub->urbPwm->transfer_buffer,
			  usbduxsub->sizePwmBuf, usbduxsub_pwm_irq,
			  usbduxsub->comedidev);

	errFlag = usb_submit_urb(usbduxsub->urbPwm, GFP_ATOMIC);
	if (errFlag) {
		dev_err(&usbduxsub->interface->dev,
			"comedi_: usbdux: pwm: usb_submit_urb error %d\n",
			errFlag);
		return errFlag;
	}
	return 0;
}