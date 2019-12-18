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
struct usb_device {int dummy; } ;
struct usb_ctrlrequest {int dummy; } ;
struct urb {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_NOIO ; 
 struct urb* usb_alloc_urb (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_api_blocking_completion ; 
 int /*<<< orphan*/  usb_fill_control_urb (struct urb*,struct usb_device*,unsigned int,unsigned char*,void*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int usb_start_wait_urb (struct urb*,int,int*) ; 

__attribute__((used)) static int usb_internal_control_msg(struct usb_device *usb_dev,
				    unsigned int pipe,
				    struct usb_ctrlrequest *cmd,
				    void *data, int len, int timeout)
{
	struct urb *urb;
	int retv;
	int length;

	urb = usb_alloc_urb(0, GFP_NOIO);
	if (!urb)
		return -ENOMEM;

	usb_fill_control_urb(urb, usb_dev, pipe, (unsigned char *)cmd, data,
			     len, usb_api_blocking_completion, NULL);

	retv = usb_start_wait_urb(urb, timeout, &length);
	if (retv < 0)
		return retv;
	else
		return length;
}