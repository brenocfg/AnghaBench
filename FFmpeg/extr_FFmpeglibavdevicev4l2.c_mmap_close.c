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
struct video_data {int buffers; int /*<<< orphan*/ * buf_len; int /*<<< orphan*/ * buf_start; int /*<<< orphan*/  fd; } ;
typedef  enum v4l2_buf_type { ____Placeholder_v4l2_buf_type } v4l2_buf_type ;

/* Variables and functions */
 int V4L2_BUF_TYPE_VIDEO_CAPTURE ; 
 int /*<<< orphan*/  VIDIOC_STREAMOFF ; 
 int /*<<< orphan*/  av_freep (int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  v4l2_ioctl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  v4l2_munmap (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void mmap_close(struct video_data *s)
{
    enum v4l2_buf_type type;
    int i;

    type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
    /* We do not check for the result, because we could
     * not do anything about it anyway...
     */
    v4l2_ioctl(s->fd, VIDIOC_STREAMOFF, &type);
    for (i = 0; i < s->buffers; i++) {
        v4l2_munmap(s->buf_start[i], s->buf_len[i]);
    }
    av_freep(&s->buf_start);
    av_freep(&s->buf_len);
}