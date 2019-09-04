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
typedef  int /*<<< orphan*/  uint8_t ;
struct video_data {int dummy; } ;
struct v4l2_buffer {int /*<<< orphan*/  index; int /*<<< orphan*/  memory; int /*<<< orphan*/  type; int /*<<< orphan*/  member_0; } ;
struct buff_data {int /*<<< orphan*/  index; struct video_data* s; } ;

/* Variables and functions */
 int /*<<< orphan*/  V4L2_BUF_TYPE_VIDEO_CAPTURE ; 
 int /*<<< orphan*/  V4L2_MEMORY_MMAP ; 
 int /*<<< orphan*/  av_free (struct buff_data*) ; 
 int /*<<< orphan*/  enqueue_buffer (struct video_data*,struct v4l2_buffer*) ; 

__attribute__((used)) static void mmap_release_buffer(void *opaque, uint8_t *data)
{
    struct v4l2_buffer buf = { 0 };
    struct buff_data *buf_descriptor = opaque;
    struct video_data *s = buf_descriptor->s;

    buf.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
    buf.memory = V4L2_MEMORY_MMAP;
    buf.index = buf_descriptor->index;
    av_free(buf_descriptor);

    enqueue_buffer(s, &buf);
}