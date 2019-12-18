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
struct uvc_streaming {int /*<<< orphan*/  queue; } ;
struct uvc_buffer {scalar_t__ state; } ;
struct urb {int number_of_packets; TYPE_1__* iso_frame_desc; scalar_t__ transfer_buffer; } ;
struct TYPE_2__ {scalar_t__ status; int /*<<< orphan*/  actual_length; scalar_t__ offset; } ;

/* Variables and functions */
 int EAGAIN ; 
 scalar_t__ UVC_BUF_STATE_DONE ; 
 scalar_t__ UVC_BUF_STATE_ERROR ; 
 int /*<<< orphan*/  UVC_TRACE_FRAME ; 
 int isight_decode (int /*<<< orphan*/ *,struct uvc_buffer*,scalar_t__,int /*<<< orphan*/ ) ; 
 struct uvc_buffer* uvc_queue_next_buffer (int /*<<< orphan*/ *,struct uvc_buffer*) ; 
 int /*<<< orphan*/  uvc_trace (int /*<<< orphan*/ ,char*,scalar_t__) ; 

void uvc_video_decode_isight(struct urb *urb, struct uvc_streaming *stream,
		struct uvc_buffer *buf)
{
	int ret, i;

	for (i = 0; i < urb->number_of_packets; ++i) {
		if (urb->iso_frame_desc[i].status < 0) {
			uvc_trace(UVC_TRACE_FRAME, "USB isochronous frame "
				  "lost (%d).\n",
				  urb->iso_frame_desc[i].status);
		}

		/* Decode the payload packet.
		 * uvc_video_decode is entered twice when a frame transition
		 * has been detected because the end of frame can only be
		 * reliably detected when the first packet of the new frame
		 * is processed. The first pass detects the transition and
		 * closes the previous frame's buffer, the second pass
		 * processes the data of the first payload of the new frame.
		 */
		do {
			ret = isight_decode(&stream->queue, buf,
					urb->transfer_buffer +
					urb->iso_frame_desc[i].offset,
					urb->iso_frame_desc[i].actual_length);

			if (buf == NULL)
				break;

			if (buf->state == UVC_BUF_STATE_DONE ||
			    buf->state == UVC_BUF_STATE_ERROR)
				buf = uvc_queue_next_buffer(&stream->queue,
							buf);
		} while (ret == -EAGAIN);
	}
}