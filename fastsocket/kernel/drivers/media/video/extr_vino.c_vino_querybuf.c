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
struct vino_framebuffer {int dummy; } ;
struct vino_channel_settings {int /*<<< orphan*/  fb_queue; scalar_t__ reading; } ;
struct v4l2_buffer {scalar_t__ index; } ;
struct file {int dummy; } ;

/* Variables and functions */
 int EBUSY ; 
 int EINVAL ; 
 int /*<<< orphan*/  dprintk (char*,...) ; 
 struct vino_channel_settings* video_drvdata (struct file*) ; 
 struct vino_framebuffer* vino_queue_get_buffer (int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ vino_queue_get_length (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vino_v4l2_get_buffer_status (struct vino_channel_settings*,struct vino_framebuffer*,struct v4l2_buffer*) ; 

__attribute__((used)) static int vino_querybuf(struct file *file, void *__fh,
			      struct v4l2_buffer *b)
{
	struct vino_channel_settings *vcs = video_drvdata(file);
	struct vino_framebuffer *fb;

	if (vcs->reading)
		return -EBUSY;

	/* TODO: check queue type */
	if (b->index >= vino_queue_get_length(&vcs->fb_queue)) {
		dprintk("invalid index = %d\n",
		       b->index);
		return -EINVAL;
	}

	fb = vino_queue_get_buffer(&vcs->fb_queue,
				   b->index);
	if (fb == NULL) {
		dprintk("vino_queue_get_buffer() failed");
		return -EINVAL;
	}

	vino_v4l2_get_buffer_status(vcs, fb, b);

	return 0;
}