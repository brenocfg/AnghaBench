#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct videobuf_queue {struct front_face* priv_data; } ;
struct videobuf_buffer {int field; int /*<<< orphan*/  state; int /*<<< orphan*/  size; int /*<<< orphan*/  height; int /*<<< orphan*/  width; } ;
struct v4l2_pix_format {int /*<<< orphan*/  height; int /*<<< orphan*/  width; int /*<<< orphan*/  sizeimage; } ;
struct front_face {int type; TYPE_4__* pd; } ;
typedef  enum v4l2_field { ____Placeholder_v4l2_field } v4l2_field ;
struct TYPE_7__ {int /*<<< orphan*/  vbi_size; } ;
struct TYPE_5__ {struct v4l2_pix_format pix; } ;
struct TYPE_6__ {TYPE_1__ context; } ;
struct TYPE_8__ {TYPE_3__ vbi_data; TYPE_2__ video_data; } ;

/* Variables and functions */
 int EINVAL ; 
#define  V4L2_BUF_TYPE_VBI_CAPTURE 129 
#define  V4L2_BUF_TYPE_VIDEO_CAPTURE 128 
 int /*<<< orphan*/  VIDEOBUF_NEEDS_INIT ; 
 int /*<<< orphan*/  VIDEOBUF_PREPARED ; 
 int videobuf_iolock (struct videobuf_queue*,struct videobuf_buffer*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int pd_buf_prepare(struct videobuf_queue *q, struct videobuf_buffer *vb,
			   enum v4l2_field field)
{
	struct front_face *front = q->priv_data;
	int rc;

	switch (front->type) {
	case V4L2_BUF_TYPE_VIDEO_CAPTURE:
		if (VIDEOBUF_NEEDS_INIT == vb->state) {
			struct v4l2_pix_format *pix;

			pix = &front->pd->video_data.context.pix;
			vb->size	= pix->sizeimage; /* real frame size */
			vb->width	= pix->width;
			vb->height	= pix->height;
			rc = videobuf_iolock(q, vb, NULL);
			if (rc < 0)
				return rc;
		}
		break;
	case V4L2_BUF_TYPE_VBI_CAPTURE:
		if (VIDEOBUF_NEEDS_INIT == vb->state) {
			vb->size	= front->pd->vbi_data.vbi_size;
			rc = videobuf_iolock(q, vb, NULL);
			if (rc < 0)
				return rc;
		}
		break;
	default:
		return -EINVAL;
	}
	vb->field = field;
	vb->state = VIDEOBUF_PREPARED;
	return 0;
}