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
struct video_data {int /*<<< orphan*/  buffers_queued; int /*<<< orphan*/  fd; } ;
struct v4l2_buffer {int dummy; } ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int /*<<< orphan*/  VIDIOC_QBUF ; 
 int /*<<< orphan*/  atomic_fetch_add (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  av_err2str (int) ; 
 int /*<<< orphan*/  av_log (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errno ; 
 scalar_t__ v4l2_ioctl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct v4l2_buffer*) ; 

__attribute__((used)) static int enqueue_buffer(struct video_data *s, struct v4l2_buffer *buf)
{
    int res = 0;

    if (v4l2_ioctl(s->fd, VIDIOC_QBUF, buf) < 0) {
        res = AVERROR(errno);
        av_log(NULL, AV_LOG_ERROR, "ioctl(VIDIOC_QBUF): %s\n", av_err2str(res));
    } else {
        atomic_fetch_add(&s->buffers_queued, 1);
    }

    return res;
}