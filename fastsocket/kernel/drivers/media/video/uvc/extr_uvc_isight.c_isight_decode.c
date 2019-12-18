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
struct uvc_video_queue {int* mem; } ;
struct TYPE_3__ {int offset; } ;
struct TYPE_4__ {scalar_t__ bytesused; unsigned int length; TYPE_1__ m; } ;
struct uvc_buffer {scalar_t__ state; TYPE_2__ buf; } ;
typedef  int __u8 ;

/* Variables and functions */
 int EAGAIN ; 
 scalar_t__ UVC_BUF_STATE_ACTIVE ; 
 void* UVC_BUF_STATE_DONE ; 
 int /*<<< orphan*/  UVC_TRACE_FRAME ; 
 scalar_t__ memcmp (int const*,int const*,int) ; 
 int /*<<< orphan*/  memcpy (int*,int const*,unsigned int) ; 
 unsigned int min (unsigned int,unsigned int) ; 
 int /*<<< orphan*/  uvc_trace (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int isight_decode(struct uvc_video_queue *queue, struct uvc_buffer *buf,
		const __u8 *data, unsigned int len)
{
	static const __u8 hdr[] = {
		0x11, 0x22, 0x33, 0x44,
		0xde, 0xad, 0xbe, 0xef,
		0xde, 0xad, 0xfa, 0xce
	};

	unsigned int maxlen, nbytes;
	__u8 *mem;
	int is_header = 0;

	if (buf == NULL)
		return 0;

	if ((len >= 14 && memcmp(&data[2], hdr, 12) == 0) ||
	    (len >= 15 && memcmp(&data[3], hdr, 12) == 0)) {
		uvc_trace(UVC_TRACE_FRAME, "iSight header found\n");
		is_header = 1;
	}

	/* Synchronize to the input stream by waiting for a header packet. */
	if (buf->state != UVC_BUF_STATE_ACTIVE) {
		if (!is_header) {
			uvc_trace(UVC_TRACE_FRAME, "Dropping packet (out of "
				  "sync).\n");
			return 0;
		}

		buf->state = UVC_BUF_STATE_ACTIVE;
	}

	/* Mark the buffer as done if we're at the beginning of a new frame.
	 *
	 * Empty buffers (bytesused == 0) don't trigger end of frame detection
	 * as it doesn't make sense to return an empty buffer.
	 */
	if (is_header && buf->buf.bytesused != 0) {
		buf->state = UVC_BUF_STATE_DONE;
		return -EAGAIN;
	}

	/* Copy the video data to the buffer. Skip header packets, as they
	 * contain no data.
	 */
	if (!is_header) {
		maxlen = buf->buf.length - buf->buf.bytesused;
		mem = queue->mem + buf->buf.m.offset + buf->buf.bytesused;
		nbytes = min(len, maxlen);
		memcpy(mem, data, nbytes);
		buf->buf.bytesused += nbytes;

		if (len > maxlen || buf->buf.bytesused == buf->buf.length) {
			uvc_trace(UVC_TRACE_FRAME, "Frame complete "
				  "(overflow).\n");
			buf->state = UVC_BUF_STATE_DONE;
		}
	}

	return 0;
}