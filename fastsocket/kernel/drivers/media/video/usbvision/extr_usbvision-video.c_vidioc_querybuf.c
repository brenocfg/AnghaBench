#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int offset; } ;
struct v4l2_buffer {size_t index; int length; int /*<<< orphan*/  sequence; int /*<<< orphan*/  timestamp; int /*<<< orphan*/  field; void* memory; TYPE_1__ m; int /*<<< orphan*/  flags; } ;
struct usbvision_frame {scalar_t__ grabstate; int /*<<< orphan*/  sequence; int /*<<< orphan*/  timestamp; } ;
struct TYPE_4__ {int bytes_per_pixel; } ;
struct usb_usbvision {size_t num_frames; int curwidth; int curheight; struct usbvision_frame* frame; TYPE_2__ palette; int /*<<< orphan*/  max_frame_size; } ;
struct file {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int PAGE_ALIGN (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  V4L2_BUF_FLAG_DONE ; 
 int /*<<< orphan*/  V4L2_BUF_FLAG_MAPPED ; 
 int /*<<< orphan*/  V4L2_BUF_FLAG_QUEUED ; 
 int /*<<< orphan*/  V4L2_FIELD_NONE ; 
 void* V4L2_MEMORY_MMAP ; 
 scalar_t__ frame_state_done ; 
 scalar_t__ frame_state_ready ; 
 scalar_t__ frame_state_unused ; 
 struct usb_usbvision* video_drvdata (struct file*) ; 

__attribute__((used)) static int vidioc_querybuf(struct file *file,
			    void *priv, struct v4l2_buffer *vb)
{
	struct usb_usbvision *usbvision = video_drvdata(file);
	struct usbvision_frame *frame;

	/* FIXME : must control
	   that buffers are mapped (VIDIOC_REQBUFS has been called) */
	if (vb->index >= usbvision->num_frames)
		return -EINVAL;
	/* Updating the corresponding frame state */
	vb->flags = 0;
	frame = &usbvision->frame[vb->index];
	if (frame->grabstate >= frame_state_ready)
		vb->flags |= V4L2_BUF_FLAG_QUEUED;
	if (frame->grabstate >= frame_state_done)
		vb->flags |= V4L2_BUF_FLAG_DONE;
	if (frame->grabstate == frame_state_unused)
		vb->flags |= V4L2_BUF_FLAG_MAPPED;
	vb->memory = V4L2_MEMORY_MMAP;

	vb->m.offset = vb->index * PAGE_ALIGN(usbvision->max_frame_size);

	vb->memory = V4L2_MEMORY_MMAP;
	vb->field = V4L2_FIELD_NONE;
	vb->length = usbvision->curwidth *
		usbvision->curheight *
		usbvision->palette.bytes_per_pixel;
	vb->timestamp = usbvision->frame[vb->index].timestamp;
	vb->sequence = usbvision->frame[vb->index].sequence;
	return 0;
}