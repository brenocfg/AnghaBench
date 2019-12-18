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
struct usb_ep {int dummy; } ;
struct usb_composite_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  disable_ep (struct usb_composite_dev*,struct usb_ep*) ; 

void disable_endpoints(struct usb_composite_dev *cdev,
		struct usb_ep *in, struct usb_ep *out)
{
	disable_ep(cdev, in);
	disable_ep(cdev, out);
}