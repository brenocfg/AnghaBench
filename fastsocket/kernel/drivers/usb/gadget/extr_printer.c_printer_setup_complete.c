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
struct usb_request {scalar_t__ actual; scalar_t__ length; scalar_t__ status; } ;
struct usb_ep {scalar_t__ driver_data; } ;
struct printer_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBG (struct printer_dev*,char*,scalar_t__,scalar_t__,scalar_t__) ; 

__attribute__((used)) static void printer_setup_complete(struct usb_ep *ep, struct usb_request *req)
{
	if (req->status || req->actual != req->length)
		DBG((struct printer_dev *) ep->driver_data,
				"setup complete --> %d, %d/%d\n",
				req->status, req->actual, req->length);
}