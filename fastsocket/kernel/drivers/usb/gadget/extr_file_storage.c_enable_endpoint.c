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
struct usb_ep {int /*<<< orphan*/  name; struct fsg_dev* driver_data; } ;
struct usb_endpoint_descriptor {int dummy; } ;
struct fsg_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ERROR (struct fsg_dev*,char*,int /*<<< orphan*/ ,int) ; 
 int usb_ep_enable (struct usb_ep*,struct usb_endpoint_descriptor const*) ; 

__attribute__((used)) static int enable_endpoint(struct fsg_dev *fsg, struct usb_ep *ep,
		const struct usb_endpoint_descriptor *d)
{
	int	rc;

	ep->driver_data = fsg;
	rc = usb_ep_enable(ep, d);
	if (rc)
		ERROR(fsg, "can't enable %s, result %d\n", ep->name, rc);
	return rc;
}