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
struct videobuf_queue {struct front_face* priv_data; } ;
struct v4l2_pix_format {int height; int width; int /*<<< orphan*/  sizeimage; } ;
struct TYPE_2__ {struct v4l2_pix_format pix; } ;
struct video_data {int endpoint_addr; int lines_per_field; int lines_size; struct front_face* front; struct poseidon* pd; struct vbi_data* vbi; TYPE_1__ context; } ;
struct vbi_data {int /*<<< orphan*/  vbi_size; struct video_data* video; } ;
struct poseidon {struct vbi_data vbi_data; struct video_data video_data; } ;
struct front_face {int type; struct poseidon* pd; } ;

/* Variables and functions */
 int EINVAL ; 
 unsigned int PAGE_ALIGN (int /*<<< orphan*/ ) ; 
#define  V4L2_BUF_TYPE_VBI_CAPTURE 129 
#define  V4L2_BUF_TYPE_VIDEO_CAPTURE 128 
 int /*<<< orphan*/  log (char*,unsigned int) ; 
 int start_video_stream (struct poseidon*) ; 

__attribute__((used)) static int pd_buf_setup(struct videobuf_queue *q, unsigned int *count,
		       unsigned int *size)
{
	struct front_face *front = q->priv_data;
	struct poseidon *pd	= front->pd;

	switch (front->type) {
	default:
		return -EINVAL;
	case V4L2_BUF_TYPE_VIDEO_CAPTURE: {
		struct video_data *video = &pd->video_data;
		struct v4l2_pix_format *pix = &video->context.pix;

		*size = PAGE_ALIGN(pix->sizeimage);/* page aligned frame size */
		if (*count < 4)
			*count = 4;
		if (1) {
			/* same in different altersetting */
			video->endpoint_addr	= 0x82;
			video->vbi		= &pd->vbi_data;
			video->vbi->video	= video;
			video->pd		= pd;
			video->lines_per_field	= pix->height / 2;
			video->lines_size	= pix->width * 2;
			video->front 		= front;
		}
		return start_video_stream(pd);
	}

	case V4L2_BUF_TYPE_VBI_CAPTURE: {
		struct vbi_data *vbi = &pd->vbi_data;

		*size = PAGE_ALIGN(vbi->vbi_size);
		log("size : %d", *size);
		if (*count == 0)
			*count = 4;
	}
		break;
	}
	return 0;
}