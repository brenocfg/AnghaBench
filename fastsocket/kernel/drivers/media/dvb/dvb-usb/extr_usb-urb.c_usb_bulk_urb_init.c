#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  buffersize; } ;
struct TYPE_8__ {TYPE_1__ bulk; } ;
struct TYPE_9__ {int count; TYPE_2__ u; int /*<<< orphan*/  endpoint; } ;
struct usb_data_stream {int /*<<< orphan*/  urbs_initialized; int /*<<< orphan*/ * dma_addr; TYPE_4__** urb_list; TYPE_3__ props; int /*<<< orphan*/ * buf_list; int /*<<< orphan*/  udev; } ;
struct TYPE_10__ {int /*<<< orphan*/  transfer_dma; int /*<<< orphan*/  transfer_flags; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  URB_NO_TRANSFER_DMA_MAP ; 
 int /*<<< orphan*/  deb_mem (char*) ; 
 TYPE_4__* usb_alloc_urb (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int usb_allocate_stream_buffers (struct usb_data_stream*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_fill_bulk_urb (TYPE_4__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct usb_data_stream*) ; 
 int /*<<< orphan*/  usb_free_urb (TYPE_4__*) ; 
 int /*<<< orphan*/  usb_rcvbulkpipe (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_urb_complete ; 

__attribute__((used)) static int usb_bulk_urb_init(struct usb_data_stream *stream)
{
	int i, j;

	if ((i = usb_allocate_stream_buffers(stream,stream->props.count,
					stream->props.u.bulk.buffersize)) < 0)
		return i;

	/* allocate the URBs */
	for (i = 0; i < stream->props.count; i++) {
		stream->urb_list[i] = usb_alloc_urb(0, GFP_ATOMIC);
		if (!stream->urb_list[i]) {
			deb_mem("not enough memory for urb_alloc_urb!.\n");
			for (j = 0; j < i; j++)
				usb_free_urb(stream->urb_list[i]);
			return -ENOMEM;
		}
		usb_fill_bulk_urb( stream->urb_list[i], stream->udev,
				usb_rcvbulkpipe(stream->udev,stream->props.endpoint),
				stream->buf_list[i],
				stream->props.u.bulk.buffersize,
				usb_urb_complete, stream);

		stream->urb_list[i]->transfer_flags = URB_NO_TRANSFER_DMA_MAP;
		stream->urb_list[i]->transfer_dma = stream->dma_addr[i];
		stream->urbs_initialized++;
	}
	return 0;
}