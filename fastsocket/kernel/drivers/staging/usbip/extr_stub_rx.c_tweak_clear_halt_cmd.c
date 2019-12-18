#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct usb_ctrlrequest {int /*<<< orphan*/  wIndex; } ;
struct urb {TYPE_1__* dev; scalar_t__ setup_packet; } ;
struct TYPE_4__ {int /*<<< orphan*/  devnum; } ;

/* Variables and functions */
 int le16_to_cpu (int /*<<< orphan*/ ) ; 
 int usb_clear_halt (TYPE_1__*,int) ; 
 int usb_rcvctrlpipe (TYPE_1__*,int) ; 
 int usb_sndctrlpipe (TYPE_1__*,int) ; 
 int /*<<< orphan*/  usbip_uinfo (char*,int /*<<< orphan*/ ,int,...) ; 

__attribute__((used)) static int tweak_clear_halt_cmd(struct urb *urb)
{
	struct usb_ctrlrequest *req;
	int target_endp;
	int target_dir;
	int target_pipe;
	int ret;

	req = (struct usb_ctrlrequest *) urb->setup_packet;

	/*
	 * The stalled endpoint is specified in the wIndex value. The endpoint
	 * of the urb is the target of this clear_halt request (i.e., control
	 * endpoint).
	 */
	target_endp = le16_to_cpu(req->wIndex) & 0x000f;

	/* the stalled endpoint direction is IN or OUT?. USB_DIR_IN is 0x80.  */
	target_dir = le16_to_cpu(req->wIndex) & 0x0080;

	if (target_dir)
		target_pipe = usb_rcvctrlpipe(urb->dev, target_endp);
	else
		target_pipe = usb_sndctrlpipe(urb->dev, target_endp);

	ret = usb_clear_halt(urb->dev, target_pipe);
	if (ret < 0)
		usbip_uinfo("clear_halt error: devnum %d endp %d, %d\n",
					urb->dev->devnum, target_endp, ret);
	else
		usbip_uinfo("clear_halt done: devnum %d endp %d\n",
					urb->dev->devnum, target_endp);

	return ret;
}