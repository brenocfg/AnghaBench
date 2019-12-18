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
struct TYPE_3__ {int pixelformat; int priv; int /*<<< orphan*/  height; int /*<<< orphan*/  width; } ;
struct TYPE_4__ {TYPE_1__ pix; } ;
struct v4l2_format {TYPE_2__ fmt; } ;
struct pwc_device {int vcompression; int vframes; int pixfmt; scalar_t__ iso_init; } ;
typedef  int /*<<< orphan*/  pixelformat ;

/* Variables and functions */
 int EBUSY ; 
 int EINVAL ; 
 int /*<<< orphan*/  PWC_DEBUG_IOCTL (char*,int,...) ; 
 int PWC_FPS_FRMASK ; 
 int PWC_FPS_SHIFT ; 
 int PWC_FPS_SNAPSHOT ; 
 int PWC_QLT_MASK ; 
 int PWC_QLT_SHIFT ; 
 int V4L2_PIX_FMT_PWC1 ; 
 int V4L2_PIX_FMT_PWC2 ; 
 int V4L2_PIX_FMT_YUV420 ; 
 int pwc_set_video_mode (struct pwc_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int) ; 
 int /*<<< orphan*/  pwc_vidioc_fill_fmt (struct pwc_device*,struct v4l2_format*) ; 
 int pwc_vidioc_try_fmt (struct pwc_device*,struct v4l2_format*) ; 

__attribute__((used)) static int pwc_vidioc_set_fmt(struct pwc_device *pdev, struct v4l2_format *f)
{
	int ret, fps, snapshot, compression, pixelformat;

	ret = pwc_vidioc_try_fmt(pdev, f);
	if (ret<0)
		return ret;

	pixelformat = f->fmt.pix.pixelformat;
	compression = pdev->vcompression;
	snapshot = 0;
	fps = pdev->vframes;
	if (f->fmt.pix.priv) {
		compression = (f->fmt.pix.priv & PWC_QLT_MASK) >> PWC_QLT_SHIFT;
		snapshot = !!(f->fmt.pix.priv & PWC_FPS_SNAPSHOT);
		fps = (f->fmt.pix.priv & PWC_FPS_FRMASK) >> PWC_FPS_SHIFT;
		if (fps == 0)
			fps = pdev->vframes;
	}

	if (pixelformat != V4L2_PIX_FMT_YUV420 &&
	    pixelformat != V4L2_PIX_FMT_PWC1 &&
	    pixelformat != V4L2_PIX_FMT_PWC2)
		return -EINVAL;

	if (pdev->iso_init)
		return -EBUSY;

	PWC_DEBUG_IOCTL("Trying to set format to: width=%d height=%d fps=%d "
			"compression=%d snapshot=%d format=%c%c%c%c\n",
			f->fmt.pix.width, f->fmt.pix.height, fps,
			compression, snapshot,
			(pixelformat)&255,
			(pixelformat>>8)&255,
			(pixelformat>>16)&255,
			(pixelformat>>24)&255);

	ret = pwc_set_video_mode(pdev,
				 f->fmt.pix.width,
				 f->fmt.pix.height,
				 fps,
				 compression,
				 snapshot);

	PWC_DEBUG_IOCTL("pwc_set_video_mode(), return=%d\n", ret);

	if (ret)
		return ret;

	pdev->pixfmt = pixelformat;

	pwc_vidioc_fill_fmt(pdev, f);

	return 0;

}