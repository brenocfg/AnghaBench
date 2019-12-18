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
struct usb_data_stream {int buf_num; unsigned long buf_size; int /*<<< orphan*/  state; int /*<<< orphan*/ ** buf_list; scalar_t__* dma_addr; int /*<<< orphan*/  udev; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  USB_STATE_URB_BUF ; 
 int /*<<< orphan*/  deb_mem (char*,...) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/ * usb_buffer_alloc (int /*<<< orphan*/ ,unsigned long,int /*<<< orphan*/ ,scalar_t__*) ; 
 int /*<<< orphan*/  usb_free_stream_buffers (struct usb_data_stream*) ; 

__attribute__((used)) static int usb_allocate_stream_buffers(struct usb_data_stream *stream, int num, unsigned long size)
{
	stream->buf_num = 0;
	stream->buf_size = size;

	deb_mem("all in all I will use %lu bytes for streaming\n",num*size);

	for (stream->buf_num = 0; stream->buf_num < num; stream->buf_num++) {
		deb_mem("allocating buffer %d\n",stream->buf_num);
		if (( stream->buf_list[stream->buf_num] =
					usb_buffer_alloc(stream->udev, size, GFP_ATOMIC,
					&stream->dma_addr[stream->buf_num]) ) == NULL) {
			deb_mem("not enough memory for urb-buffer allocation.\n");
			usb_free_stream_buffers(stream);
			return -ENOMEM;
		}
		deb_mem("buffer %d: %p (dma: %Lu)\n",
			stream->buf_num,
stream->buf_list[stream->buf_num], (long long)stream->dma_addr[stream->buf_num]);
		memset(stream->buf_list[stream->buf_num],0,size);
		stream->state |= USB_STATE_URB_BUF;
	}
	deb_mem("allocation successful\n");

	return 0;
}