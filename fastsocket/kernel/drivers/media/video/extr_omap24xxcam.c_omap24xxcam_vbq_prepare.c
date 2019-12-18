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
struct videobuf_queue {struct omap24xxcam_fh* priv_data; } ;
struct videobuf_buffer {scalar_t__ bsize; scalar_t__ size; scalar_t__ state; int field; scalar_t__ memory; int /*<<< orphan*/  height; int /*<<< orphan*/  width; scalar_t__ baddr; } ;
struct TYPE_2__ {scalar_t__ sizeimage; int /*<<< orphan*/  height; int /*<<< orphan*/  width; } ;
struct omap24xxcam_fh {TYPE_1__ pix; } ;
typedef  enum v4l2_field { ____Placeholder_v4l2_field } v4l2_field ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ V4L2_MEMORY_MMAP ; 
 scalar_t__ VIDEOBUF_NEEDS_INIT ; 
 scalar_t__ VIDEOBUF_PREPARED ; 
 int omap24xxcam_dma_iolock (struct videobuf_queue*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  omap24xxcam_vbq_release (struct videobuf_queue*,struct videobuf_buffer*) ; 
 int videobuf_iolock (struct videobuf_queue*,struct videobuf_buffer*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  videobuf_to_dma (struct videobuf_buffer*) ; 

__attribute__((used)) static int omap24xxcam_vbq_prepare(struct videobuf_queue *vbq,
				   struct videobuf_buffer *vb,
				   enum v4l2_field field)
{
	struct omap24xxcam_fh *fh = vbq->priv_data;
	int err = 0;

	/*
	 * Accessing pix here is okay since it's constant while
	 * streaming is on (and we only get called then).
	 */
	if (vb->baddr) {
		/* This is a userspace buffer. */
		if (fh->pix.sizeimage > vb->bsize) {
			/* The buffer isn't big enough. */
			err = -EINVAL;
		} else
			vb->size = fh->pix.sizeimage;
	} else {
		if (vb->state != VIDEOBUF_NEEDS_INIT) {
			/*
			 * We have a kernel bounce buffer that has
			 * already been allocated.
			 */
			if (fh->pix.sizeimage > vb->size) {
				/*
				 * The image size has been changed to
				 * a larger size since this buffer was
				 * allocated, so we need to free and
				 * reallocate it.
				 */
				omap24xxcam_vbq_release(vbq, vb);
				vb->size = fh->pix.sizeimage;
			}
		} else {
			/* We need to allocate a new kernel bounce buffer. */
			vb->size = fh->pix.sizeimage;
		}
	}

	if (err)
		return err;

	vb->width = fh->pix.width;
	vb->height = fh->pix.height;
	vb->field = field;

	if (vb->state == VIDEOBUF_NEEDS_INIT) {
		if (vb->memory == V4L2_MEMORY_MMAP)
			/*
			 * we have built the scatter-gather list by ourself so
			 * do the scatter-gather mapping as well
			 */
			err = omap24xxcam_dma_iolock(vbq, videobuf_to_dma(vb));
		else
			err = videobuf_iolock(vbq, vb, NULL);
	}

	if (!err)
		vb->state = VIDEOBUF_PREPARED;
	else
		omap24xxcam_vbq_release(vbq, vb);

	return err;
}