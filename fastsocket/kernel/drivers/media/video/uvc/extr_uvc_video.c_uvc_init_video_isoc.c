#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  unsigned int u32 ;
typedef  int u16 ;
struct TYPE_5__ {unsigned int dwMaxVideoFrameSize; } ;
struct uvc_streaming {struct urb** urb; int /*<<< orphan*/ * urb_dma; int /*<<< orphan*/ * urb_buffer; TYPE_2__* dev; TYPE_1__ ctrl; } ;
struct TYPE_7__ {int /*<<< orphan*/  bInterval; int /*<<< orphan*/  bEndpointAddress; int /*<<< orphan*/  wMaxPacketSize; } ;
struct usb_host_endpoint {TYPE_3__ desc; } ;
struct urb {int transfer_flags; unsigned int number_of_packets; unsigned int transfer_buffer_length; TYPE_4__* iso_frame_desc; int /*<<< orphan*/  complete; int /*<<< orphan*/  transfer_dma; int /*<<< orphan*/  transfer_buffer; int /*<<< orphan*/  interval; int /*<<< orphan*/  pipe; struct uvc_streaming* context; int /*<<< orphan*/  dev; } ;
typedef  int /*<<< orphan*/  gfp_t ;
struct TYPE_8__ {unsigned int offset; int length; } ;
struct TYPE_6__ {int /*<<< orphan*/  udev; } ;

/* Variables and functions */
 int ENOMEM ; 
 int URB_ISO_ASAP ; 
 int URB_NO_TRANSFER_DMA_MAP ; 
 unsigned int UVC_URBS ; 
 int le16_to_cpu (int /*<<< orphan*/ ) ; 
 struct urb* usb_alloc_urb (unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_rcvisocpipe (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 unsigned int uvc_alloc_urb_buffers (struct uvc_streaming*,unsigned int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uvc_uninit_video (struct uvc_streaming*,int) ; 
 int /*<<< orphan*/  uvc_video_complete ; 

__attribute__((used)) static int uvc_init_video_isoc(struct uvc_streaming *stream,
	struct usb_host_endpoint *ep, gfp_t gfp_flags)
{
	struct urb *urb;
	unsigned int npackets, i, j;
	u16 psize;
	u32 size;

	psize = le16_to_cpu(ep->desc.wMaxPacketSize);
	psize = (psize & 0x07ff) * (1 + ((psize >> 11) & 3));
	size = stream->ctrl.dwMaxVideoFrameSize;

	npackets = uvc_alloc_urb_buffers(stream, size, psize, gfp_flags);
	if (npackets == 0)
		return -ENOMEM;

	size = npackets * psize;

	for (i = 0; i < UVC_URBS; ++i) {
		urb = usb_alloc_urb(npackets, gfp_flags);
		if (urb == NULL) {
			uvc_uninit_video(stream, 1);
			return -ENOMEM;
		}

		urb->dev = stream->dev->udev;
		urb->context = stream;
		urb->pipe = usb_rcvisocpipe(stream->dev->udev,
				ep->desc.bEndpointAddress);
		urb->transfer_flags = URB_ISO_ASAP | URB_NO_TRANSFER_DMA_MAP;
		urb->interval = ep->desc.bInterval;
		urb->transfer_buffer = stream->urb_buffer[i];
		urb->transfer_dma = stream->urb_dma[i];
		urb->complete = uvc_video_complete;
		urb->number_of_packets = npackets;
		urb->transfer_buffer_length = size;

		for (j = 0; j < npackets; ++j) {
			urb->iso_frame_desc[j].offset = j * psize;
			urb->iso_frame_desc[j].length = psize;
		}

		stream->urb[i] = urb;
	}

	return 0;
}