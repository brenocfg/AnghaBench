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
struct v4l2_subdev {int dummy; } ;
struct v4l2_rect {int /*<<< orphan*/  height; int /*<<< orphan*/  top; int /*<<< orphan*/  width; int /*<<< orphan*/  left; } ;
struct v4l2_pix_format {int width; scalar_t__ height; } ;
struct TYPE_3__ {struct v4l2_pix_format pix; } ;
struct v4l2_format {TYPE_1__ fmt; int /*<<< orphan*/  type; struct v4l2_rect c; } ;
struct v4l2_crop {TYPE_1__ fmt; int /*<<< orphan*/  type; struct v4l2_rect c; } ;
struct soc_camera_host {struct mx3_camera_dev* priv; } ;
struct TYPE_4__ {int /*<<< orphan*/  parent; } ;
struct soc_camera_device {int user_width; scalar_t__ user_height; TYPE_2__ dev; } ;
struct mx3_camera_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  V4L2_BUF_TYPE_VIDEO_CAPTURE ; 
 int acquire_dma_channel (struct mx3_camera_dev*) ; 
 scalar_t__ channel_change_requested (struct soc_camera_device*,struct v4l2_rect*) ; 
 int /*<<< orphan*/  configure_geometry (struct mx3_camera_dev*,int,scalar_t__) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int,scalar_t__) ; 
 int /*<<< orphan*/  g_fmt ; 
 int /*<<< orphan*/  s_crop ; 
 int /*<<< orphan*/  s_fmt ; 
 int /*<<< orphan*/  soc_camera_limit_side (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int) ; 
 struct v4l2_subdev* soc_camera_to_subdev (struct soc_camera_device*) ; 
 int /*<<< orphan*/  stride_align (int*) ; 
 struct soc_camera_host* to_soc_camera_host (int /*<<< orphan*/ ) ; 
 int v4l2_subdev_call (struct v4l2_subdev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct v4l2_format*) ; 
 int /*<<< orphan*/  video ; 

__attribute__((used)) static int mx3_camera_set_crop(struct soc_camera_device *icd,
			       struct v4l2_crop *a)
{
	struct v4l2_rect *rect = &a->c;
	struct soc_camera_host *ici = to_soc_camera_host(icd->dev.parent);
	struct mx3_camera_dev *mx3_cam = ici->priv;
	struct v4l2_subdev *sd = soc_camera_to_subdev(icd);
	struct v4l2_format f = {.type = V4L2_BUF_TYPE_VIDEO_CAPTURE};
	struct v4l2_pix_format *pix = &f.fmt.pix;
	int ret;

	soc_camera_limit_side(&rect->left, &rect->width, 0, 2, 4096);
	soc_camera_limit_side(&rect->top, &rect->height, 0, 2, 4096);

	ret = v4l2_subdev_call(sd, video, s_crop, a);
	if (ret < 0)
		return ret;

	/* The capture device might have changed its output  */
	ret = v4l2_subdev_call(sd, video, g_fmt, &f);
	if (ret < 0)
		return ret;

	if (pix->width & 7) {
		/* Ouch! We can only handle 8-byte aligned width... */
		stride_align(&pix->width);
		ret = v4l2_subdev_call(sd, video, s_fmt, &f);
		if (ret < 0)
			return ret;
	}

	if (pix->width != icd->user_width || pix->height != icd->user_height) {
		/*
		 * We now know pixel formats and can decide upon DMA-channel(s)
		 * So far only direct camera-to-memory is supported
		 */
		if (channel_change_requested(icd, rect)) {
			int ret = acquire_dma_channel(mx3_cam);
			if (ret < 0)
				return ret;
		}

		configure_geometry(mx3_cam, pix->width, pix->height);
	}

	dev_dbg(icd->dev.parent, "Sensor cropped %dx%d\n",
		pix->width, pix->height);

	icd->user_width = pix->width;
	icd->user_height = pix->height;

	return ret;
}