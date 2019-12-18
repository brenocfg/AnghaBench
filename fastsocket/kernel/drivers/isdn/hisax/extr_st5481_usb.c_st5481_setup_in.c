#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct usb_device {int dummy; } ;
struct st5481_in {int num_packets; int packet_size; int /*<<< orphan*/  rcvbuf; int /*<<< orphan*/  ep; int /*<<< orphan*/  urb; int /*<<< orphan*/  bufsize; TYPE_1__* adapter; } ;
struct TYPE_2__ {struct usb_device* usb_dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBG (int,char*) ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kmalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int st5481_setup_isocpipes (int /*<<< orphan*/ ,struct usb_device*,int /*<<< orphan*/ ,int,int,int,int /*<<< orphan*/ ,struct st5481_in*) ; 
 int /*<<< orphan*/  usb_in_complete ; 
 int /*<<< orphan*/  usb_rcvisocpipe (struct usb_device*,int /*<<< orphan*/ ) ; 

int st5481_setup_in(struct st5481_in *in)
{
	struct usb_device *dev = in->adapter->usb_dev;
	int retval;

	DBG(4,"");

	in->rcvbuf = kmalloc(in->bufsize, GFP_KERNEL);
	retval = -ENOMEM;
	if (!in->rcvbuf)
		goto err;

	retval = st5481_setup_isocpipes(in->urb, dev, 
					usb_rcvisocpipe(dev, in->ep),
					in->num_packets,  in->packet_size,
					in->num_packets * in->packet_size,
					usb_in_complete, in);
	if (retval)
		goto err_free;
	return 0;

 err_free:
	kfree(in->rcvbuf);
 err:
	return retval;
}