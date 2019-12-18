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
struct uvc_streaming {int /*<<< orphan*/  queue; int /*<<< orphan*/  ctrl; scalar_t__ frozen; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_NOIO ; 
 int uvc_commit_video (struct uvc_streaming*,int /*<<< orphan*/ *) ; 
 int uvc_init_video (struct uvc_streaming*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uvc_queue_enable (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uvc_queue_streaming (int /*<<< orphan*/ *) ; 

int uvc_video_resume(struct uvc_streaming *stream)
{
	int ret;

	stream->frozen = 0;

	ret = uvc_commit_video(stream, &stream->ctrl);
	if (ret < 0) {
		uvc_queue_enable(&stream->queue, 0);
		return ret;
	}

	if (!uvc_queue_streaming(&stream->queue))
		return 0;

	ret = uvc_init_video(stream, GFP_NOIO);
	if (ret < 0)
		uvc_queue_enable(&stream->queue, 0);

	return ret;
}