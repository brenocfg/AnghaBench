#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct video_data {int /*<<< orphan*/  endpoint_addr; int /*<<< orphan*/  front; struct urb** urb_array; TYPE_1__* pd; } ;
struct usb_device {int dummy; } ;
struct urb {int interval; int transfer_flags; int number_of_packets; int transfer_buffer_length; TYPE_2__* iso_frame_desc; void* transfer_buffer; int /*<<< orphan*/  pipe; int /*<<< orphan*/  context; struct usb_device* dev; int /*<<< orphan*/  complete; int /*<<< orphan*/  transfer_dma; } ;
struct TYPE_4__ {int offset; int length; } ;
struct TYPE_3__ {struct usb_device* udev; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int ISO_PKT_SIZE ; 
 int PK_PER_URB ; 
 int SBUF_NUM ; 
 int URB_ISO_ASAP ; 
 int URB_NO_TRANSFER_DMA_MAP ; 
 int /*<<< orphan*/  urb_complete_iso ; 
 struct urb* usb_alloc_urb (int,int /*<<< orphan*/ ) ; 
 void* usb_buffer_alloc (struct usb_device*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usb_rcvisocpipe (struct usb_device*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int prepare_iso_urb(struct video_data *video)
{
	struct usb_device *udev = video->pd->udev;
	int i;

	if (video->urb_array[0])
		return 0;

	for (i = 0; i < SBUF_NUM; i++) {
		struct urb *urb;
		void *mem;
		int j;

		urb = usb_alloc_urb(PK_PER_URB, GFP_KERNEL);
		if (urb == NULL)
			goto out;

		video->urb_array[i] = urb;
		mem = usb_buffer_alloc(udev,
					 ISO_PKT_SIZE * PK_PER_URB,
					 GFP_KERNEL,
					 &urb->transfer_dma);

		urb->complete	= urb_complete_iso;	/* handler */
		urb->dev	= udev;
		urb->context	= video->front;
		urb->pipe	= usb_rcvisocpipe(udev,
						video->endpoint_addr);
		urb->interval	= 1;
		urb->transfer_flags = URB_ISO_ASAP | URB_NO_TRANSFER_DMA_MAP;
		urb->number_of_packets	= PK_PER_URB;
		urb->transfer_buffer	= mem;
		urb->transfer_buffer_length = PK_PER_URB * ISO_PKT_SIZE;

		for (j = 0; j < PK_PER_URB; j++) {
			urb->iso_frame_desc[j].offset = ISO_PKT_SIZE * j;
			urb->iso_frame_desc[j].length = ISO_PKT_SIZE;
		}
	}
	return 0;
out:
	for (; i > 0; i--)
		;
	return -ENOMEM;
}