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
typedef  unsigned int u16 ;
struct TYPE_6__ {unsigned int max_payload_size; } ;
struct TYPE_5__ {unsigned int dwMaxPayloadTransferSize; } ;
struct uvc_streaming {scalar_t__ type; struct urb** urb; int /*<<< orphan*/ * urb_dma; int /*<<< orphan*/ * urb_buffer; TYPE_3__* dev; TYPE_2__ bulk; TYPE_1__ ctrl; } ;
struct TYPE_8__ {int /*<<< orphan*/  bEndpointAddress; int /*<<< orphan*/  wMaxPacketSize; } ;
struct usb_host_endpoint {TYPE_4__ desc; } ;
struct urb {int /*<<< orphan*/  transfer_dma; int /*<<< orphan*/  transfer_flags; } ;
typedef  int /*<<< orphan*/  gfp_t ;
struct TYPE_7__ {int /*<<< orphan*/  udev; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  URB_NO_TRANSFER_DMA_MAP ; 
 unsigned int UVC_URBS ; 
 scalar_t__ V4L2_BUF_TYPE_VIDEO_OUTPUT ; 
 int le16_to_cpu (int /*<<< orphan*/ ) ; 
 struct urb* usb_alloc_urb (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ usb_endpoint_dir_in (TYPE_4__*) ; 
 int /*<<< orphan*/  usb_fill_bulk_urb (struct urb*,int /*<<< orphan*/ ,unsigned int,int /*<<< orphan*/ ,unsigned int,int /*<<< orphan*/ ,struct uvc_streaming*) ; 
 unsigned int usb_rcvbulkpipe (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 unsigned int usb_sndbulkpipe (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 unsigned int uvc_alloc_urb_buffers (struct uvc_streaming*,unsigned int,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uvc_uninit_video (struct uvc_streaming*,int) ; 
 int /*<<< orphan*/  uvc_video_complete ; 

__attribute__((used)) static int uvc_init_video_bulk(struct uvc_streaming *stream,
	struct usb_host_endpoint *ep, gfp_t gfp_flags)
{
	struct urb *urb;
	unsigned int npackets, pipe, i;
	u16 psize;
	u32 size;

	psize = le16_to_cpu(ep->desc.wMaxPacketSize) & 0x07ff;
	size = stream->ctrl.dwMaxPayloadTransferSize;
	stream->bulk.max_payload_size = size;

	npackets = uvc_alloc_urb_buffers(stream, size, psize, gfp_flags);
	if (npackets == 0)
		return -ENOMEM;

	size = npackets * psize;

	if (usb_endpoint_dir_in(&ep->desc))
		pipe = usb_rcvbulkpipe(stream->dev->udev,
				       ep->desc.bEndpointAddress);
	else
		pipe = usb_sndbulkpipe(stream->dev->udev,
				       ep->desc.bEndpointAddress);

	if (stream->type == V4L2_BUF_TYPE_VIDEO_OUTPUT)
		size = 0;

	for (i = 0; i < UVC_URBS; ++i) {
		urb = usb_alloc_urb(0, gfp_flags);
		if (urb == NULL) {
			uvc_uninit_video(stream, 1);
			return -ENOMEM;
		}

		usb_fill_bulk_urb(urb, stream->dev->udev, pipe,
			stream->urb_buffer[i], size, uvc_video_complete,
			stream);
		urb->transfer_flags = URB_NO_TRANSFER_DMA_MAP;
		urb->transfer_dma = stream->urb_dma[i];

		stream->urb[i] = urb;
	}

	return 0;
}