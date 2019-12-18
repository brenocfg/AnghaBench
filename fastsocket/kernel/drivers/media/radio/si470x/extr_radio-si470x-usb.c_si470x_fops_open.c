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
struct si470x_device {int users; int int_in_running; TYPE_2__* intf; int /*<<< orphan*/  int_in_urb; TYPE_1__* int_in_endpoint; int /*<<< orphan*/  int_in_buffer; int /*<<< orphan*/  usbdev; } ;
struct file {int dummy; } ;
struct TYPE_5__ {int /*<<< orphan*/  dev; } ;
struct TYPE_4__ {int /*<<< orphan*/  bInterval; int /*<<< orphan*/  wMaxPacketSize; int /*<<< orphan*/  bEndpointAddress; } ;

/* Variables and functions */
 int EIO ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  le16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lock_kernel () ; 
 int /*<<< orphan*/  mb () ; 
 int /*<<< orphan*/  si470x_int_in_callback ; 
 int si470x_start (struct si470x_device*) ; 
 int /*<<< orphan*/  unlock_kernel () ; 
 int usb_autopm_get_interface (TYPE_2__*) ; 
 int /*<<< orphan*/  usb_autopm_put_interface (TYPE_2__*) ; 
 int /*<<< orphan*/  usb_fill_int_urb (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct si470x_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_rcvintpipe (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int usb_submit_urb (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct si470x_device* video_drvdata (struct file*) ; 

__attribute__((used)) static int si470x_fops_open(struct file *file)
{
	struct si470x_device *radio = video_drvdata(file);
	int retval;

	lock_kernel();
	radio->users++;

	retval = usb_autopm_get_interface(radio->intf);
	if (retval < 0) {
		radio->users--;
		retval = -EIO;
		goto done;
	}

	if (radio->users == 1) {
		/* start radio */
		retval = si470x_start(radio);
		if (retval < 0) {
			usb_autopm_put_interface(radio->intf);
			goto done;
		}

		/* initialize interrupt urb */
		usb_fill_int_urb(radio->int_in_urb, radio->usbdev,
			usb_rcvintpipe(radio->usbdev,
			radio->int_in_endpoint->bEndpointAddress),
			radio->int_in_buffer,
			le16_to_cpu(radio->int_in_endpoint->wMaxPacketSize),
			si470x_int_in_callback,
			radio,
			radio->int_in_endpoint->bInterval);

		radio->int_in_running = 1;
		mb();

		retval = usb_submit_urb(radio->int_in_urb, GFP_KERNEL);
		if (retval) {
			dev_info(&radio->intf->dev,
				 "submitting int urb failed (%d)\n", retval);
			radio->int_in_running = 0;
			usb_autopm_put_interface(radio->intf);
		}
	}

done:
	unlock_kernel();
	return retval;
}