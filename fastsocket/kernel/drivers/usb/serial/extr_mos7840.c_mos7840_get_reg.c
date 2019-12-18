#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct usb_device {int dummy; } ;
struct usb_ctrlrequest {void* wLength; void* wIndex; void* wValue; int /*<<< orphan*/  bRequest; int /*<<< orphan*/  bRequestType; } ;
struct moschip_port {unsigned char* ctrl_buf; TYPE_3__* control_urb; struct usb_ctrlrequest* dr; TYPE_2__* port; } ;
typedef  int __u16 ;
struct TYPE_7__ {int transfer_buffer_length; } ;
struct TYPE_6__ {TYPE_1__* serial; } ;
struct TYPE_5__ {struct usb_device* dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  MCS_RDREQ ; 
 int /*<<< orphan*/  MCS_RD_RTYPE ; 
 void* cpu_to_le16 (int) ; 
 int /*<<< orphan*/  mos7840_control_callback ; 
 int /*<<< orphan*/  usb_fill_control_urb (TYPE_3__*,struct usb_device*,int /*<<< orphan*/ ,unsigned char*,unsigned char*,int,int /*<<< orphan*/ ,struct moschip_port*) ; 
 int /*<<< orphan*/  usb_rcvctrlpipe (struct usb_device*,int /*<<< orphan*/ ) ; 
 int usb_submit_urb (TYPE_3__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mos7840_get_reg(struct moschip_port *mcs, __u16 Wval, __u16 reg,
			   __u16 *val)
{
	struct usb_device *dev = mcs->port->serial->dev;
	struct usb_ctrlrequest *dr = mcs->dr;
	unsigned char *buffer = mcs->ctrl_buf;
	int ret;

	dr->bRequestType = MCS_RD_RTYPE;
	dr->bRequest = MCS_RDREQ;
	dr->wValue = cpu_to_le16(Wval);	/* 0 */
	dr->wIndex = cpu_to_le16(reg);
	dr->wLength = cpu_to_le16(2);

	usb_fill_control_urb(mcs->control_urb, dev, usb_rcvctrlpipe(dev, 0),
			     (unsigned char *)dr, buffer, 2,
			     mos7840_control_callback, mcs);
	mcs->control_urb->transfer_buffer_length = 2;
	ret = usb_submit_urb(mcs->control_urb, GFP_ATOMIC);
	return ret;
}