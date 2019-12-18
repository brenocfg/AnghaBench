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
struct vino_channel_settings {int /*<<< orphan*/  fb_queue; scalar_t__ streaming; scalar_t__ reading; } ;
struct v4l2_requestbuffers {scalar_t__ memory; int /*<<< orphan*/  count; } ;
struct file {int dummy; } ;

/* Variables and functions */
 int EBUSY ; 
 int EINVAL ; 
 scalar_t__ V4L2_MEMORY_MMAP ; 
 int /*<<< orphan*/  dprintk (char*,...) ; 
 struct vino_channel_settings* video_drvdata (struct file*) ; 
 int /*<<< orphan*/  vino_capture_stop (struct vino_channel_settings*) ; 
 scalar_t__ vino_is_capturing (struct vino_channel_settings*) ; 
 int /*<<< orphan*/  vino_queue_free (int /*<<< orphan*/ *) ; 
 scalar_t__ vino_queue_has_mapped_buffers (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vino_queue_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int vino_reqbufs(struct file *file, void *__fh,
			     struct v4l2_requestbuffers *rb)
{
	struct vino_channel_settings *vcs = video_drvdata(file);

	if (vcs->reading)
		return -EBUSY;

	/* TODO: check queue type */
	if (rb->memory != V4L2_MEMORY_MMAP) {
		dprintk("type not mmap\n");
		return -EINVAL;
	}

	dprintk("count = %d\n", rb->count);
	if (rb->count > 0) {
		if (vino_is_capturing(vcs)) {
			dprintk("busy, capturing\n");
			return -EBUSY;
		}

		if (vino_queue_has_mapped_buffers(&vcs->fb_queue)) {
			dprintk("busy, buffers still mapped\n");
			return -EBUSY;
		} else {
			vcs->streaming = 0;
			vino_queue_free(&vcs->fb_queue);
			vino_queue_init(&vcs->fb_queue, &rb->count);
		}
	} else {
		vcs->streaming = 0;
		vino_capture_stop(vcs);
		vino_queue_free(&vcs->fb_queue);
	}

	return 0;
}