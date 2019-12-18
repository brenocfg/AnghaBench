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
struct uvc_video_queue {void* mem; } ;
struct uvc_streaming {struct uvc_video_queue queue; } ;
struct TYPE_3__ {int offset; } ;
struct TYPE_4__ {unsigned int length; unsigned int bytesused; TYPE_1__ m; } ;
struct uvc_buffer {int /*<<< orphan*/  state; TYPE_2__ buf; } ;
typedef  int /*<<< orphan*/  __u8 ;

/* Variables and functions */
 int /*<<< orphan*/  UVC_BUF_STATE_READY ; 
 int /*<<< orphan*/  UVC_TRACE_FRAME ; 
 int /*<<< orphan*/  memcpy (void*,int /*<<< orphan*/  const*,unsigned int) ; 
 unsigned int min (unsigned int,unsigned int) ; 
 int /*<<< orphan*/  uvc_trace (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void uvc_video_decode_data(struct uvc_streaming *stream,
		struct uvc_buffer *buf, const __u8 *data, int len)
{
	struct uvc_video_queue *queue = &stream->queue;
	unsigned int maxlen, nbytes;
	void *mem;

	if (len <= 0)
		return;

	/* Copy the video data to the buffer. */
	maxlen = buf->buf.length - buf->buf.bytesused;
	mem = queue->mem + buf->buf.m.offset + buf->buf.bytesused;
	nbytes = min((unsigned int)len, maxlen);
	memcpy(mem, data, nbytes);
	buf->buf.bytesused += nbytes;

	/* Complete the current frame if the buffer size was exceeded. */
	if (len > maxlen) {
		uvc_trace(UVC_TRACE_FRAME, "Frame complete (overflow).\n");
		buf->state = UVC_BUF_STATE_READY;
	}
}