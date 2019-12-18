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
struct uvc_streaming {int /*<<< orphan*/  last_fid; TYPE_2__* dev; } ;
struct TYPE_3__ {scalar_t__ bytesused; } ;
struct uvc_buffer {int /*<<< orphan*/  state; TYPE_1__ buf; } ;
typedef  int __u8 ;
struct TYPE_4__ {int quirks; } ;

/* Variables and functions */
 int /*<<< orphan*/  UVC_BUF_STATE_READY ; 
 int UVC_QUIRK_STREAM_NO_FID ; 
 int const UVC_STREAM_EOF ; 
 int /*<<< orphan*/  UVC_STREAM_FID ; 
 int /*<<< orphan*/  UVC_TRACE_FRAME ; 
 int /*<<< orphan*/  uvc_trace (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void uvc_video_decode_end(struct uvc_streaming *stream,
		struct uvc_buffer *buf, const __u8 *data, int len)
{
	/* Mark the buffer as done if the EOF marker is set. */
	if (data[1] & UVC_STREAM_EOF && buf->buf.bytesused != 0) {
		uvc_trace(UVC_TRACE_FRAME, "Frame complete (EOF found).\n");
		if (data[0] == len)
			uvc_trace(UVC_TRACE_FRAME, "EOF in empty payload.\n");
		buf->state = UVC_BUF_STATE_READY;
		if (stream->dev->quirks & UVC_QUIRK_STREAM_NO_FID)
			stream->last_fid ^= UVC_STREAM_FID;
	}
}