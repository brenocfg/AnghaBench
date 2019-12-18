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
struct urb {unsigned int transfer_flags; int actual_length; int status; } ;
struct sisusb_usb_data {scalar_t__ completein; int /*<<< orphan*/  wait_q; int /*<<< orphan*/  sisusb_dev; struct urb* sisurbin; } ;

/* Variables and functions */
 int ETIMEDOUT ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  sisusb_bulk_completein ; 
 int /*<<< orphan*/  usb_fill_bulk_urb (struct urb*,int /*<<< orphan*/ ,unsigned int,void*,int,int /*<<< orphan*/ ,struct sisusb_usb_data*) ; 
 int /*<<< orphan*/  usb_kill_urb (struct urb*) ; 
 int usb_submit_urb (struct urb*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wait_event_timeout (int /*<<< orphan*/ ,scalar_t__,int) ; 

__attribute__((used)) static int
sisusb_bulkin_msg(struct sisusb_usb_data *sisusb, unsigned int pipe, void *data,
	int len, int *actual_length, int timeout, unsigned int tflags)
{
	struct urb *urb = sisusb->sisurbin;
	int retval, readbytes = 0;

	urb->transfer_flags = 0;

	usb_fill_bulk_urb(urb, sisusb->sisusb_dev, pipe, data, len,
			sisusb_bulk_completein, sisusb);

	urb->transfer_flags |= tflags;
	urb->actual_length = 0;

	sisusb->completein = 0;
	retval = usb_submit_urb(urb, GFP_ATOMIC);
	if (retval == 0) {
		wait_event_timeout(sisusb->wait_q, sisusb->completein, timeout);
		if (!sisusb->completein) {
			/* URB timed out... kill it and report error */
			usb_kill_urb(urb);
			retval = -ETIMEDOUT;
		} else {
			/* URB completed within timeout */
			retval = urb->status;
			readbytes = urb->actual_length;
		}
	}

	if (actual_length)
		*actual_length = readbytes;

	return retval;
}