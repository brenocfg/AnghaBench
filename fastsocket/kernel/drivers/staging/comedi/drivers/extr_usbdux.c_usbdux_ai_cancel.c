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
struct usbduxsub {int /*<<< orphan*/  sem; int /*<<< orphan*/  ai_cmd_running; int /*<<< orphan*/  probed; TYPE_1__* interface; } ;
struct comedi_subdevice {int dummy; } ;
struct comedi_device {struct usbduxsub* private; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EFAULT ; 
 int ENODEV ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  down (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  up (int /*<<< orphan*/ *) ; 
 int usbdux_ai_stop (struct usbduxsub*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int usbdux_ai_cancel(struct comedi_device *dev,
			    struct comedi_subdevice *s)
{
	struct usbduxsub *this_usbduxsub;
	int res = 0;

	/* force unlink of all urbs */
	this_usbduxsub = dev->private;
	if (!this_usbduxsub)
		return -EFAULT;

	dev_dbg(&this_usbduxsub->interface->dev, "comedi: usbdux_ai_cancel\n");

	/* prevent other CPUs from submitting new commands just now */
	down(&this_usbduxsub->sem);
	if (!(this_usbduxsub->probed)) {
		up(&this_usbduxsub->sem);
		return -ENODEV;
	}
	/* unlink only if the urb really has been submitted */
	res = usbdux_ai_stop(this_usbduxsub, this_usbduxsub->ai_cmd_running);
	up(&this_usbduxsub->sem);
	return res;
}