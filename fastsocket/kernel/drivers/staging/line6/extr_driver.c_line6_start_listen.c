#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct usb_line6 {TYPE_1__* urb_listen; int /*<<< orphan*/  interval; int /*<<< orphan*/  buffer_listen; int /*<<< orphan*/  ep_control_read; int /*<<< orphan*/  usbdev; } ;
struct TYPE_3__ {scalar_t__ actual_length; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  LINE6_BUFSIZE_LISTEN ; 
 int /*<<< orphan*/  line6_data_received ; 
 int /*<<< orphan*/  usb_fill_int_urb (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct usb_line6*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_rcvintpipe (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int usb_submit_urb (TYPE_1__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int line6_start_listen(struct usb_line6 *line6)
{
	usb_fill_int_urb(line6->urb_listen, line6->usbdev,
			 usb_rcvintpipe(line6->usbdev, line6->ep_control_read),
			 line6->buffer_listen, LINE6_BUFSIZE_LISTEN,
			 line6_data_received, line6, line6->interval);
	line6->urb_listen->actual_length = 0;
	return usb_submit_urb(line6->urb_listen, GFP_KERNEL);
}