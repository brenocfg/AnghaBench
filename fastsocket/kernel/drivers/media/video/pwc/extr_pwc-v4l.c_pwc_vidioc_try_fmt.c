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
struct TYPE_6__ {int pixelformat; scalar_t__ width; scalar_t__ height; } ;
struct TYPE_7__ {TYPE_2__ pix; } ;
struct v4l2_format {scalar_t__ type; TYPE_3__ fmt; } ;
struct TYPE_8__ {scalar_t__ x; scalar_t__ y; } ;
struct TYPE_5__ {scalar_t__ x; scalar_t__ y; } ;
struct pwc_device {TYPE_4__ view_min; TYPE_1__ view_max; int /*<<< orphan*/  type; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEVICE_USE_CODEC1 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DEVICE_USE_CODEC23 (int /*<<< orphan*/ ) ; 
 int EINVAL ; 
 int /*<<< orphan*/  PWC_DEBUG_IOCTL (char*) ; 
 scalar_t__ V4L2_BUF_TYPE_VIDEO_CAPTURE ; 
#define  V4L2_PIX_FMT_PWC1 130 
#define  V4L2_PIX_FMT_PWC2 129 
#define  V4L2_PIX_FMT_YUV420 128 

__attribute__((used)) static int pwc_vidioc_try_fmt(struct pwc_device *pdev, struct v4l2_format *f)
{
	if (f->type != V4L2_BUF_TYPE_VIDEO_CAPTURE) {
		PWC_DEBUG_IOCTL("Bad video type must be V4L2_BUF_TYPE_VIDEO_CAPTURE\n");
		return -EINVAL;
	}

	switch (f->fmt.pix.pixelformat) {
		case V4L2_PIX_FMT_YUV420:
			break;
		case V4L2_PIX_FMT_PWC1:
			if (DEVICE_USE_CODEC23(pdev->type)) {
				PWC_DEBUG_IOCTL("codec1 is only supported for old pwc webcam\n");
				return -EINVAL;
			}
			break;
		case V4L2_PIX_FMT_PWC2:
			if (DEVICE_USE_CODEC1(pdev->type)) {
				PWC_DEBUG_IOCTL("codec23 is only supported for new pwc webcam\n");
				return -EINVAL;
			}
			break;
		default:
			PWC_DEBUG_IOCTL("Unsupported pixel format\n");
			return -EINVAL;

	}

	if (f->fmt.pix.width > pdev->view_max.x)
		f->fmt.pix.width = pdev->view_max.x;
	else if (f->fmt.pix.width < pdev->view_min.x)
		f->fmt.pix.width = pdev->view_min.x;

	if (f->fmt.pix.height > pdev->view_max.y)
		f->fmt.pix.height = pdev->view_max.y;
	else if (f->fmt.pix.height < pdev->view_min.y)
		f->fmt.pix.height = pdev->view_min.y;

	return 0;
}