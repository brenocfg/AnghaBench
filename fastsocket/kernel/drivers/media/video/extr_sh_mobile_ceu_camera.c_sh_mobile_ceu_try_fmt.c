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
struct v4l2_subdev {int dummy; } ;
struct v4l2_pix_format {int pixelformat; int width; int height; int bytesperline; int sizeimage; } ;
struct TYPE_5__ {struct v4l2_pix_format pix; } ;
struct v4l2_format {TYPE_1__ fmt; } ;
struct soc_camera_format_xlate {TYPE_3__* cam_fmt; TYPE_2__* host_fmt; } ;
struct TYPE_8__ {int /*<<< orphan*/  parent; } ;
struct soc_camera_device {TYPE_4__ dev; } ;
typedef  int __u32 ;
struct TYPE_7__ {int fourcc; } ;
struct TYPE_6__ {int /*<<< orphan*/  depth; } ;

/* Variables and functions */
 int DIV_ROUND_UP (int /*<<< orphan*/ ,int) ; 
 int EINVAL ; 
#define  V4L2_PIX_FMT_NV12 131 
#define  V4L2_PIX_FMT_NV16 130 
#define  V4L2_PIX_FMT_NV21 129 
#define  V4L2_PIX_FMT_NV61 128 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ ,char*,int) ; 
 struct v4l2_subdev* soc_camera_to_subdev (struct soc_camera_device*) ; 
 struct soc_camera_format_xlate* soc_camera_xlate_by_fourcc (struct soc_camera_device*,int) ; 
 int /*<<< orphan*/  try_fmt ; 
 int v4l2_subdev_call (struct v4l2_subdev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct v4l2_format*) ; 
 int /*<<< orphan*/  v4l_bound_align_image (int*,int,int,int,int*,int,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  video ; 

__attribute__((used)) static int sh_mobile_ceu_try_fmt(struct soc_camera_device *icd,
				 struct v4l2_format *f)
{
	const struct soc_camera_format_xlate *xlate;
	struct v4l2_pix_format *pix = &f->fmt.pix;
	struct v4l2_subdev *sd = soc_camera_to_subdev(icd);
	__u32 pixfmt = pix->pixelformat;
	int width, height;
	int ret;

	xlate = soc_camera_xlate_by_fourcc(icd, pixfmt);
	if (!xlate) {
		dev_warn(icd->dev.parent, "Format %x not found\n", pixfmt);
		return -EINVAL;
	}

	/* FIXME: calculate using depth and bus width */

	v4l_bound_align_image(&pix->width, 2, 2560, 1,
			      &pix->height, 4, 1920, 2, 0);

	width = pix->width;
	height = pix->height;

	pix->bytesperline = pix->width *
		DIV_ROUND_UP(xlate->host_fmt->depth, 8);
	pix->sizeimage = pix->height * pix->bytesperline;

	pix->pixelformat = xlate->cam_fmt->fourcc;

	/* limit to sensor capabilities */
	ret = v4l2_subdev_call(sd, video, try_fmt, f);
	pix->pixelformat = pixfmt;
	if (ret < 0)
		return ret;

	switch (pixfmt) {
	case V4L2_PIX_FMT_NV12:
	case V4L2_PIX_FMT_NV21:
	case V4L2_PIX_FMT_NV16:
	case V4L2_PIX_FMT_NV61:
		/* FIXME: check against rect_max after converting soc-camera */
		/* We can scale precisely, need a bigger image from camera */
		if (pix->width < width || pix->height < height) {
			int tmp_w = pix->width, tmp_h = pix->height;
			pix->width = 2560;
			pix->height = 1920;
			ret = v4l2_subdev_call(sd, video, try_fmt, f);
			if (ret < 0) {
				/* Shouldn't actually happen... */
				dev_err(icd->dev.parent,
					"FIXME: try_fmt() returned %d\n", ret);
				pix->width = tmp_w;
				pix->height = tmp_h;
			}
		}
		if (pix->width > width)
			pix->width = width;
		if (pix->height > height)
			pix->height = height;
	}

	return ret;
}