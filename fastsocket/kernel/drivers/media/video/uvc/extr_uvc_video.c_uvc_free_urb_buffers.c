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
struct uvc_streaming {scalar_t__ urb_size; int /*<<< orphan*/ ** urb_buffer; int /*<<< orphan*/ * urb_dma; TYPE_1__* dev; } ;
struct TYPE_2__ {int /*<<< orphan*/  udev; } ;

/* Variables and functions */
 unsigned int UVC_URBS ; 
 int /*<<< orphan*/  usb_buffer_free (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void uvc_free_urb_buffers(struct uvc_streaming *stream)
{
	unsigned int i;

	for (i = 0; i < UVC_URBS; ++i) {
		if (stream->urb_buffer[i]) {
			usb_buffer_free(stream->dev->udev, stream->urb_size,
				stream->urb_buffer[i], stream->urb_dma[i]);
			stream->urb_buffer[i] = NULL;
		}
	}

	stream->urb_size = 0;
}