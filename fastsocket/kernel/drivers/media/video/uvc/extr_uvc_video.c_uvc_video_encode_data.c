#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct uvc_video_queue {int buf_used; void* mem; } ;
struct TYPE_6__ {unsigned int max_payload_size; unsigned int payload_size; } ;
struct uvc_streaming {TYPE_3__ bulk; struct uvc_video_queue queue; } ;
struct TYPE_4__ {int offset; } ;
struct TYPE_5__ {unsigned int bytesused; TYPE_1__ m; } ;
struct uvc_buffer {TYPE_2__ buf; } ;
typedef  int /*<<< orphan*/  __u8 ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,void*,unsigned int) ; 
 unsigned int min (unsigned int,unsigned int) ; 

__attribute__((used)) static int uvc_video_encode_data(struct uvc_streaming *stream,
		struct uvc_buffer *buf, __u8 *data, int len)
{
	struct uvc_video_queue *queue = &stream->queue;
	unsigned int nbytes;
	void *mem;

	/* Copy video data to the URB buffer. */
	mem = queue->mem + buf->buf.m.offset + queue->buf_used;
	nbytes = min((unsigned int)len, buf->buf.bytesused - queue->buf_used);
	nbytes = min(stream->bulk.max_payload_size - stream->bulk.payload_size,
			nbytes);
	memcpy(data, mem, nbytes);

	queue->buf_used += nbytes;

	return nbytes;
}