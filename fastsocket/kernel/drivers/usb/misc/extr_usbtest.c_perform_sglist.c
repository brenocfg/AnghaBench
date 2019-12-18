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
struct usbtest_dev {int dummy; } ;
struct usb_sg_request {int status; } ;
struct usb_device {scalar_t__ speed; } ;
struct scatterlist {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ERROR (struct usbtest_dev*,char*,unsigned int,int) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int INTERRUPT_RATE ; 
 scalar_t__ USB_SPEED_HIGH ; 
 struct usb_device* testdev_to_usbdev (struct usbtest_dev*) ; 
 int usb_sg_init (struct usb_sg_request*,struct usb_device*,int,int,struct scatterlist*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_sg_wait (struct usb_sg_request*) ; 

__attribute__((used)) static int perform_sglist (
	struct usbtest_dev	*tdev,
	unsigned		iterations,
	int			pipe,
	struct usb_sg_request	*req,
	struct scatterlist	*sg,
	int			nents
)
{
	struct usb_device	*udev = testdev_to_usbdev(tdev);
	int			retval = 0;

	while (retval == 0 && iterations-- > 0) {
		retval = usb_sg_init (req, udev, pipe,
				(udev->speed == USB_SPEED_HIGH)
					? (INTERRUPT_RATE << 3)
					: INTERRUPT_RATE,
				sg, nents, 0, GFP_KERNEL);

		if (retval)
			break;
		usb_sg_wait (req);
		retval = req->status;

		/* FIXME check resulting data pattern */

		/* FIXME if endpoint halted, clear halt (and log) */
	}

	// FIXME for unlink or fault handling tests, don't report
	// failure if retval is as we expected ...

	if (retval)
		ERROR(tdev, "perform_sglist failed, "
				"iterations left %d, status %d\n",
				iterations, retval);
	return retval;
}