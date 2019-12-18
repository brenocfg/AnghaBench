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
struct vino_channel_settings {scalar_t__ streaming; scalar_t__ reading; } ;
struct v4l2_buffer {scalar_t__ memory; int /*<<< orphan*/  index; } ;
struct file {int dummy; } ;

/* Variables and functions */
 int EBUSY ; 
 int EINVAL ; 
 scalar_t__ V4L2_MEMORY_MMAP ; 
 int /*<<< orphan*/  dprintk (char*) ; 
 struct vino_channel_settings* video_drvdata (struct file*) ; 
 struct vino_framebuffer* vino_capture_enqueue (struct vino_channel_settings*,int /*<<< orphan*/ ) ; 
 int vino_capture_next (struct vino_channel_settings*,int) ; 
 int /*<<< orphan*/  vino_v4l2_get_buffer_status (struct vino_channel_settings*,struct vino_framebuffer*,struct v4l2_buffer*) ; 

__attribute__((used)) static int vino_qbuf(struct file *file, void *__fh,
			  struct v4l2_buffer *b)
{
	struct vino_channel_settings *vcs = video_drvdata(file);
	struct vino_framebuffer *fb;
	int ret;

	if (vcs->reading)
		return -EBUSY;

	/* TODO: check queue type */
	if (b->memory != V4L2_MEMORY_MMAP) {
		dprintk("type not mmap\n");
		return -EINVAL;
	}

	fb = vino_capture_enqueue(vcs, b->index);
	if (fb == NULL)
		return -EINVAL;

	vino_v4l2_get_buffer_status(vcs, fb, b);

	if (vcs->streaming) {
		ret = vino_capture_next(vcs, 1);
		if (ret)
			return ret;
	}

	return 0;
}