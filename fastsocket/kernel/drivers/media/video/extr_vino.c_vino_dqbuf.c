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
struct v4l2_buffer {int /*<<< orphan*/  index; } ;
struct file {unsigned int f_flags; } ;

/* Variables and functions */
 int EAGAIN ; 
 int EBUSY ; 
 int EINVAL ; 
 int EIO ; 
 unsigned int O_NONBLOCK ; 
 int /*<<< orphan*/  dprintk (char*,...) ; 
 struct vino_channel_settings* video_drvdata (struct file*) ; 
 int vino_check_buffer (struct vino_channel_settings*,struct vino_framebuffer*) ; 
 int vino_queue_get_incoming (int /*<<< orphan*/ *,unsigned int*) ; 
 int vino_queue_get_outgoing (int /*<<< orphan*/ *,unsigned int*) ; 
 struct vino_framebuffer* vino_queue_remove (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vino_v4l2_get_buffer_status (struct vino_channel_settings*,struct vino_framebuffer*,struct v4l2_buffer*) ; 
 int vino_wait_for_frame (struct vino_channel_settings*) ; 

__attribute__((used)) static int vino_dqbuf(struct file *file, void *__fh,
			   struct v4l2_buffer *b)
{
	struct vino_channel_settings *vcs = video_drvdata(file);
	unsigned int nonblocking = file->f_flags & O_NONBLOCK;
	struct vino_framebuffer *fb;
	unsigned int incoming, outgoing;
	int err;

	if (vcs->reading)
		return -EBUSY;

	/* TODO: check queue type */

	err = vino_queue_get_incoming(&vcs->fb_queue, &incoming);
	if (err) {
		dprintk("vino_queue_get_incoming() failed\n");
		return -EINVAL;
	}
	err = vino_queue_get_outgoing(&vcs->fb_queue, &outgoing);
	if (err) {
		dprintk("vino_queue_get_outgoing() failed\n");
		return -EINVAL;
	}

	dprintk("incoming = %d, outgoing = %d\n", incoming, outgoing);

	if (outgoing == 0) {
		if (incoming == 0) {
			dprintk("no incoming or outgoing buffers\n");
			return -EINVAL;
		}
		if (nonblocking) {
			dprintk("non-blocking I/O was selected and "
				"there are no buffers to dequeue\n");
			return -EAGAIN;
		}

		err = vino_wait_for_frame(vcs);
		if (err) {
			err = vino_wait_for_frame(vcs);
			if (err) {
				/* interrupted or no frames captured because of
				 * frame skipping */
				/* vino_capture_failed(vcs); */
				return -EIO;
			}
		}
	}

	fb = vino_queue_remove(&vcs->fb_queue, &b->index);
	if (fb == NULL) {
		dprintk("vino_queue_remove() failed\n");
		return -EINVAL;
	}

	err = vino_check_buffer(vcs, fb);

	vino_v4l2_get_buffer_status(vcs, fb, b);

	if (err)
		return -EIO;

	return 0;
}