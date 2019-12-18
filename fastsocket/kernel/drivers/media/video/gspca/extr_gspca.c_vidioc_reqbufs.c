#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct v4l2_requestbuffers {int memory; scalar_t__ count; } ;
struct gspca_dev {int const memory; int nframes; int streaming; int /*<<< orphan*/  queue_lock; int /*<<< orphan*/  usb_lock; scalar_t__ usb_err; TYPE_1__* frame; struct file* capt_file; } ;
struct file {int dummy; } ;
struct TYPE_2__ {scalar_t__ vma_use_count; } ;

/* Variables and functions */
 int /*<<< orphan*/  D_STREAM ; 
 int EBUSY ; 
 int EINVAL ; 
 int ERESTARTSYS ; 
 int const GSPCA_MEMORY_NO ; 
#define  GSPCA_MEMORY_READ 130 
 int /*<<< orphan*/  PDEBUG (int /*<<< orphan*/ ,char*,int,scalar_t__) ; 
#define  V4L2_MEMORY_MMAP 129 
#define  V4L2_MEMORY_USERPTR 128 
 int frame_alloc (struct gspca_dev*,struct file*,int const,scalar_t__) ; 
 int /*<<< orphan*/  frame_free (struct gspca_dev*) ; 
 int gspca_init_transfer (struct gspca_dev*) ; 
 int /*<<< orphan*/  gspca_stream_off (struct gspca_dev*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 scalar_t__ mutex_lock_interruptible (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int vidioc_reqbufs(struct file *file, void *priv,
			  struct v4l2_requestbuffers *rb)
{
	struct gspca_dev *gspca_dev = priv;
	int i, ret = 0, streaming;

	i = rb->memory;			/* (avoid compilation warning) */
	switch (i) {
	case GSPCA_MEMORY_READ:			/* (internal call) */
	case V4L2_MEMORY_MMAP:
	case V4L2_MEMORY_USERPTR:
		break;
	default:
		return -EINVAL;
	}
	if (mutex_lock_interruptible(&gspca_dev->queue_lock))
		return -ERESTARTSYS;

	if (gspca_dev->memory != GSPCA_MEMORY_NO
	    && gspca_dev->memory != GSPCA_MEMORY_READ
	    && gspca_dev->memory != rb->memory) {
		ret = -EBUSY;
		goto out;
	}

	/* only one file may do the capture */
	if (gspca_dev->capt_file != NULL
	    && gspca_dev->capt_file != file) {
		ret = -EBUSY;
		goto out;
	}

	/* if allocated, the buffers must not be mapped */
	for (i = 0; i < gspca_dev->nframes; i++) {
		if (gspca_dev->frame[i].vma_use_count) {
			ret = -EBUSY;
			goto out;
		}
	}

	/* stop streaming */
	streaming = gspca_dev->streaming;
	if (streaming) {
		mutex_lock(&gspca_dev->usb_lock);
		gspca_dev->usb_err = 0;
		gspca_stream_off(gspca_dev);
		mutex_unlock(&gspca_dev->usb_lock);
	}
	/* Don't restart the stream when switching from read to mmap mode */
	if (gspca_dev->memory == GSPCA_MEMORY_READ)
		streaming = 0;

	/* free the previous allocated buffers, if any */
	if (gspca_dev->nframes != 0)
		frame_free(gspca_dev);
	if (rb->count == 0)			/* unrequest */
		goto out;
	ret = frame_alloc(gspca_dev, file, rb->memory, rb->count);
	if (ret == 0) {
		rb->count = gspca_dev->nframes;
		if (streaming)
			ret = gspca_init_transfer(gspca_dev);
	}
out:
	mutex_unlock(&gspca_dev->queue_lock);
	PDEBUG(D_STREAM, "reqbufs st:%d c:%d", ret, rb->count);
	return ret;
}