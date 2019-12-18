#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  size_t u8 ;
struct vpif_fh {int* io_allowed; int /*<<< orphan*/  initialized; struct channel_obj* channel; } ;
struct videobuf_buffer {int dummy; } ;
struct v4l2_requestbuffers {int /*<<< orphan*/  memory; int /*<<< orphan*/  type; } ;
struct file {int dummy; } ;
struct TYPE_4__ {scalar_t__ field; } ;
struct TYPE_5__ {TYPE_1__ pix; } ;
struct TYPE_6__ {TYPE_2__ fmt; int /*<<< orphan*/  type; } ;
struct common_obj {int io_usrs; int /*<<< orphan*/  lock; int /*<<< orphan*/  buffer_queue; int /*<<< orphan*/  dma_queue; int /*<<< orphan*/  memory; int /*<<< orphan*/  irqlock; TYPE_3__ fmt; } ;
struct channel_obj {scalar_t__ channel_id; struct common_obj* common; } ;
typedef  enum v4l2_field { ____Placeholder_v4l2_field } v4l2_field ;

/* Variables and functions */
 int EBUSY ; 
 int EINVAL ; 
 int ERESTARTSYS ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  V4L2_BUF_TYPE_VIDEO_OUTPUT ; 
 scalar_t__ V4L2_FIELD_ANY ; 
 int V4L2_FIELD_INTERLACED ; 
 int V4L2_VBI_INTERLACED ; 
 scalar_t__ VPIF_CHANNEL2_VIDEO ; 
 scalar_t__ VPIF_CHANNEL3_VIDEO ; 
 size_t VPIF_VIDEO_INDEX ; 
 scalar_t__ mutex_lock_interruptible (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  video_qops ; 
 int /*<<< orphan*/  videobuf_queue_dma_contig_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int,struct vpif_fh*) ; 
 int videobuf_reqbufs (int /*<<< orphan*/ *,struct v4l2_requestbuffers*) ; 
 int /*<<< orphan*/  vpif_err (char*) ; 

__attribute__((used)) static int vpif_reqbufs(struct file *file, void *priv,
			struct v4l2_requestbuffers *reqbuf)
{
	struct vpif_fh *fh = priv;
	struct channel_obj *ch = fh->channel;
	struct common_obj *common;
	enum v4l2_field field;
	u8 index = 0;
	int ret = 0;

	/* This file handle has not initialized the channel,
	   It is not allowed to do settings */
	if ((VPIF_CHANNEL2_VIDEO == ch->channel_id)
	    || (VPIF_CHANNEL3_VIDEO == ch->channel_id)) {
		if (!fh->initialized) {
			vpif_err("Channel Busy\n");
			return -EBUSY;
		}
	}

	if (V4L2_BUF_TYPE_VIDEO_OUTPUT != reqbuf->type)
		return -EINVAL;

	index = VPIF_VIDEO_INDEX;

	common = &ch->common[index];
	if (mutex_lock_interruptible(&common->lock))
		return -ERESTARTSYS;

	if (common->fmt.type != reqbuf->type) {
		ret = -EINVAL;
		goto reqbuf_exit;
	}

	if (0 != common->io_usrs) {
		ret = -EBUSY;
		goto reqbuf_exit;
	}

	if (reqbuf->type == V4L2_BUF_TYPE_VIDEO_OUTPUT) {
		if (common->fmt.fmt.pix.field == V4L2_FIELD_ANY)
			field = V4L2_FIELD_INTERLACED;
		else
			field = common->fmt.fmt.pix.field;
	} else {
		field = V4L2_VBI_INTERLACED;
	}

	/* Initialize videobuf queue as per the buffer type */
	videobuf_queue_dma_contig_init(&common->buffer_queue,
					    &video_qops, NULL,
					    &common->irqlock,
					    reqbuf->type, field,
					    sizeof(struct videobuf_buffer), fh);

	/* Set io allowed member of file handle to TRUE */
	fh->io_allowed[index] = 1;
	/* Increment io usrs member of channel object to 1 */
	common->io_usrs = 1;
	/* Store type of memory requested in channel object */
	common->memory = reqbuf->memory;
	INIT_LIST_HEAD(&common->dma_queue);

	/* Allocate buffers */
	ret = videobuf_reqbufs(&common->buffer_queue, reqbuf);

reqbuf_exit:
	mutex_unlock(&common->lock);
	return ret;
}