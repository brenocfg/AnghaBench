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
struct usb_line6_pod {int dummy; } ;
struct usb_line6 {TYPE_3__* usbdev; TYPE_1__* line6midi; int /*<<< orphan*/  ifcdev; int /*<<< orphan*/  interval; int /*<<< orphan*/  ep_control_write; } ;
struct urb {scalar_t__ actual_length; } ;
struct TYPE_6__ {int idProduct; } ;
struct TYPE_7__ {TYPE_2__ descriptor; } ;
struct TYPE_5__ {int /*<<< orphan*/  num_active_send_urbs; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
#define  LINE6_DEVID_BASSPODXT 134 
#define  LINE6_DEVID_BASSPODXTLIVE 133 
#define  LINE6_DEVID_BASSPODXTPRO 132 
#define  LINE6_DEVID_POCKETPOD 131 
#define  LINE6_DEVID_PODXT 130 
#define  LINE6_DEVID_PODXTLIVE 129 
#define  LINE6_DEVID_PODXTPRO 128 
 int /*<<< orphan*/  MISSING_CASE ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 unsigned char* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  line6_write_hexdump (struct usb_line6*,char,unsigned char*,int) ; 
 int /*<<< orphan*/  memcpy (unsigned char*,unsigned char*,int) ; 
 int /*<<< orphan*/  midi_sent ; 
 int /*<<< orphan*/  pod_midi_postprocess (struct usb_line6_pod*,unsigned char*,int) ; 
 struct urb* usb_alloc_urb (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_fill_int_urb (struct urb*,TYPE_3__*,int /*<<< orphan*/ ,unsigned char*,int,int /*<<< orphan*/ ,struct usb_line6*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_free_urb (struct urb*) ; 
 int /*<<< orphan*/  usb_sndbulkpipe (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int usb_submit_urb (struct urb*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int send_midi_async(struct usb_line6 *line6, unsigned char *data,
			   int length)
{
	struct urb *urb;
	int retval;
	unsigned char *transfer_buffer;

	urb = usb_alloc_urb(0, GFP_ATOMIC);

	if (urb == 0) {
		dev_err(line6->ifcdev, "Out of memory\n");
		return -ENOMEM;
	}

#if DO_DUMP_URB_SEND
	line6_write_hexdump(line6, 'S', data, length);
#endif

	transfer_buffer = kmalloc(length, GFP_ATOMIC);

	if (transfer_buffer == 0) {
		usb_free_urb(urb);
		dev_err(line6->ifcdev, "Out of memory\n");
		return -ENOMEM;
	}

	memcpy(transfer_buffer, data, length);
	usb_fill_int_urb(urb, line6->usbdev,
			 usb_sndbulkpipe(line6->usbdev,
					 line6->ep_control_write),
			 transfer_buffer, length, midi_sent, line6,
			 line6->interval);
	urb->actual_length = 0;
	retval = usb_submit_urb(urb, GFP_ATOMIC);

	if (retval < 0) {
		dev_err(line6->ifcdev, "usb_submit_urb failed\n");
		usb_free_urb(urb);
		return -EINVAL;
	}

	++line6->line6midi->num_active_send_urbs;

	switch (line6->usbdev->descriptor.idProduct) {
	case LINE6_DEVID_BASSPODXT:
	case LINE6_DEVID_BASSPODXTLIVE:
	case LINE6_DEVID_BASSPODXTPRO:
	case LINE6_DEVID_PODXT:
	case LINE6_DEVID_PODXTLIVE:
	case LINE6_DEVID_PODXTPRO:
	case LINE6_DEVID_POCKETPOD:
		pod_midi_postprocess((struct usb_line6_pod *)line6, data,
				     length);
		break;

	default:
		MISSING_CASE;
	}

	return 0;
}