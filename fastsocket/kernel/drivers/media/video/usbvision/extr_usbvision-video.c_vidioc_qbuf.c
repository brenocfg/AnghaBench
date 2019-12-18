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
struct v4l2_buffer {size_t index; int /*<<< orphan*/  flags; } ;
struct usbvision_frame {scalar_t__ grabstate; int /*<<< orphan*/  frame; int /*<<< orphan*/  v4l2_format; scalar_t__ scanlength; int /*<<< orphan*/  scanstate; } ;
struct usb_usbvision {size_t num_frames; int /*<<< orphan*/  queue_lock; int /*<<< orphan*/  inqueue; struct usbvision_frame* frame; int /*<<< orphan*/  palette; } ;
struct file {int dummy; } ;

/* Variables and functions */
 int EAGAIN ; 
 int EINVAL ; 
 int /*<<< orphan*/  V4L2_BUF_FLAG_DONE ; 
 scalar_t__ frame_state_ready ; 
 scalar_t__ frame_state_unused ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  scan_state_scanning ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 struct usb_usbvision* video_drvdata (struct file*) ; 

__attribute__((used)) static int vidioc_qbuf(struct file *file, void *priv, struct v4l2_buffer *vb)
{
	struct usb_usbvision *usbvision = video_drvdata(file);
	struct usbvision_frame *frame;
	unsigned long lock_flags;

	/* FIXME : works only on VIDEO_CAPTURE MODE, MMAP. */
	if (vb->index >= usbvision->num_frames)
		return -EINVAL;

	frame = &usbvision->frame[vb->index];

	if (frame->grabstate != frame_state_unused)
		return -EAGAIN;

	/* Mark it as ready and enqueue frame */
	frame->grabstate = frame_state_ready;
	frame->scanstate = scan_state_scanning;
	frame->scanlength = 0;	/* Accumulated in usbvision_parse_data() */

	vb->flags &= ~V4L2_BUF_FLAG_DONE;

	/* set v4l2_format index */
	frame->v4l2_format = usbvision->palette;

	spin_lock_irqsave(&usbvision->queue_lock, lock_flags);
	list_add_tail(&usbvision->frame[vb->index].frame, &usbvision->inqueue);
	spin_unlock_irqrestore(&usbvision->queue_lock, lock_flags);

	return 0;
}