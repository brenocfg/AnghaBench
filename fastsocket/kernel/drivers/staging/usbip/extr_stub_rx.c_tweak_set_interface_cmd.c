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
struct usb_ctrlrequest {int /*<<< orphan*/  wIndex; int /*<<< orphan*/  wValue; } ;
struct urb {int /*<<< orphan*/  dev; scalar_t__ setup_packet; } ;
typedef  int /*<<< orphan*/  __u16 ;

/* Variables and functions */
 int /*<<< orphan*/  le16_to_cpu (int /*<<< orphan*/ ) ; 
 int usb_set_interface (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usbip_dbg_stub_rx (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usbip_uinfo (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,...) ; 

__attribute__((used)) static int tweak_set_interface_cmd(struct urb *urb)
{
	struct usb_ctrlrequest *req;
	__u16 alternate;
	__u16 interface;
	int ret;

	req = (struct usb_ctrlrequest *) urb->setup_packet;
	alternate = le16_to_cpu(req->wValue);
	interface = le16_to_cpu(req->wIndex);

	usbip_dbg_stub_rx("set_interface: inf %u alt %u\n", interface,
								alternate);

	ret = usb_set_interface(urb->dev, interface, alternate);
	if (ret < 0)
		usbip_uinfo("set_interface error: inf %u alt %u, %d\n",
					interface, alternate, ret);
	else
		usbip_uinfo("set_interface done: inf %u alt %u\n",
							interface,
							alternate);

	return ret;
}