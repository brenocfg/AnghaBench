#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int pixelformat; scalar_t__ width; int height; int priv; int bytesperline; int sizeimage; int /*<<< orphan*/  colorspace; int /*<<< orphan*/  field; } ;
struct TYPE_6__ {TYPE_1__ pix; } ;
struct v4l2_format {TYPE_2__ fmt; } ;
struct file {int dummy; } ;
struct TYPE_7__ {scalar_t__ w; int h; } ;

/* Variables and functions */
 int ARRAY_SIZE (TYPE_3__*) ; 
 int EINVAL ; 
 int /*<<< orphan*/  V4L2_COLORSPACE_SRGB ; 
 int /*<<< orphan*/  V4L2_FIELD_NONE ; 
#define  V4L2_PIX_FMT_RGB565 132 
#define  V4L2_PIX_FMT_RGB565X 131 
#define  V4L2_PIX_FMT_SBGGR8 130 
#define  V4L2_PIX_FMT_UYVY 129 
#define  V4L2_PIX_FMT_YUYV 128 
 scalar_t__ abs (scalar_t__) ; 
 TYPE_3__* stk_sizes ; 

__attribute__((used)) static int stk_vidioc_try_fmt_vid_cap(struct file *filp,
		void *priv, struct v4l2_format *fmtd)
{
	int i;
	switch (fmtd->fmt.pix.pixelformat) {
	case V4L2_PIX_FMT_RGB565:
	case V4L2_PIX_FMT_RGB565X:
	case V4L2_PIX_FMT_UYVY:
	case V4L2_PIX_FMT_YUYV:
	case V4L2_PIX_FMT_SBGGR8:
		break;
	default:
		return -EINVAL;
	}
	for (i = 1; i < ARRAY_SIZE(stk_sizes); i++) {
		if (fmtd->fmt.pix.width > stk_sizes[i].w)
			break;
	}
	if (i == ARRAY_SIZE(stk_sizes)
		|| (abs(fmtd->fmt.pix.width - stk_sizes[i-1].w)
			< abs(fmtd->fmt.pix.width - stk_sizes[i].w))) {
		fmtd->fmt.pix.height = stk_sizes[i-1].h;
		fmtd->fmt.pix.width = stk_sizes[i-1].w;
		fmtd->fmt.pix.priv = i - 1;
	} else {
		fmtd->fmt.pix.height = stk_sizes[i].h;
		fmtd->fmt.pix.width = stk_sizes[i].w;
		fmtd->fmt.pix.priv = i;
	}

	fmtd->fmt.pix.field = V4L2_FIELD_NONE;
	fmtd->fmt.pix.colorspace = V4L2_COLORSPACE_SRGB;
	if (fmtd->fmt.pix.pixelformat == V4L2_PIX_FMT_SBGGR8)
		fmtd->fmt.pix.bytesperline = fmtd->fmt.pix.width;
	else
		fmtd->fmt.pix.bytesperline = 2 * fmtd->fmt.pix.width;
	fmtd->fmt.pix.sizeimage = fmtd->fmt.pix.bytesperline
		* fmtd->fmt.pix.height;
	return 0;
}