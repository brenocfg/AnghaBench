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
typedef  int /*<<< orphan*/  u8 ;
struct TYPE_7__ {int transfer_flags; unsigned int transfer_dma; unsigned int transfer_buffer_length; int number_of_packets; int interval; void (* complete ) (struct urb*) ;TYPE_1__* iso_frame_desc; struct ua101* context; int /*<<< orphan*/ * transfer_buffer; int /*<<< orphan*/  pipe; TYPE_2__* dev; } ;
struct ua101_urb {TYPE_3__ urb; } ;
struct ua101_stream {unsigned int max_packet_bytes; unsigned int queue_length; struct ua101_urb** urbs; int /*<<< orphan*/  usb_pipe; TYPE_4__* buffers; } ;
struct ua101 {TYPE_2__* dev; } ;
typedef  unsigned int dma_addr_t ;
struct TYPE_8__ {unsigned int size; unsigned int dma; int /*<<< orphan*/ * addr; } ;
struct TYPE_6__ {int /*<<< orphan*/  dev; } ;
struct TYPE_5__ {unsigned int length; scalar_t__ offset; } ;

/* Variables and functions */
 unsigned int ARRAY_SIZE (TYPE_4__*) ; 
 int ENOMEM ; 
 int ENXIO ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int URB_ISO_ASAP ; 
 int URB_NO_TRANSFER_DMA_MAP ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 struct ua101_urb* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_init_urb (TYPE_3__*) ; 

__attribute__((used)) static int alloc_stream_urbs(struct ua101 *ua, struct ua101_stream *stream,
			     void (*urb_complete)(struct urb *))
{
	unsigned max_packet_size = stream->max_packet_bytes;
	struct ua101_urb *urb;
	unsigned int b, u = 0;

	for (b = 0; b < ARRAY_SIZE(stream->buffers); ++b) {
		unsigned int size = stream->buffers[b].size;
		u8 *addr = stream->buffers[b].addr;
		dma_addr_t dma = stream->buffers[b].dma;

		while (size >= max_packet_size) {
			if (u >= stream->queue_length)
				goto bufsize_error;
			urb = kmalloc(sizeof(*urb), GFP_KERNEL);
			if (!urb)
				return -ENOMEM;
			usb_init_urb(&urb->urb);
			urb->urb.dev = ua->dev;
			urb->urb.pipe = stream->usb_pipe;
			urb->urb.transfer_flags = URB_ISO_ASAP |
					URB_NO_TRANSFER_DMA_MAP;
			urb->urb.transfer_buffer = addr;
			urb->urb.transfer_dma = dma;
			urb->urb.transfer_buffer_length = max_packet_size;
			urb->urb.number_of_packets = 1;
			urb->urb.interval = 1;
			urb->urb.context = ua;
			urb->urb.complete = urb_complete;
			urb->urb.iso_frame_desc[0].offset = 0;
			urb->urb.iso_frame_desc[0].length = max_packet_size;
			stream->urbs[u++] = urb;
			size -= max_packet_size;
			addr += max_packet_size;
			dma += max_packet_size;
		}
	}
	if (u == stream->queue_length)
		return 0;
bufsize_error:
	dev_err(&ua->dev->dev, "internal buffer size error\n");
	return -ENXIO;
}