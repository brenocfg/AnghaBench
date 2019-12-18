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
typedef  scalar_t__ u32 ;
struct v4l2_subdev {int dummy; } ;
struct v4l2_rect {int /*<<< orphan*/  top; int /*<<< orphan*/  left; int /*<<< orphan*/  height; int /*<<< orphan*/  width; } ;
struct v4l2_mbus_framefmt {int /*<<< orphan*/  height; int /*<<< orphan*/  width; struct v4l2_rect c; } ;
struct v4l2_crop {int /*<<< orphan*/  height; int /*<<< orphan*/  width; struct v4l2_rect c; } ;
struct soc_camera_sense {int pixel_clock_max; int flags; scalar_t__ pixel_clock; int /*<<< orphan*/  master_clock; } ;
struct soc_camera_host {struct pxa_camera_dev* priv; } ;
struct TYPE_6__ {struct device* parent; } ;
struct soc_camera_device {int /*<<< orphan*/  user_height; int /*<<< orphan*/  user_width; TYPE_3__ dev; struct soc_camera_sense* sense; TYPE_2__* current_fmt; struct pxa_cam* host_priv; } ;
struct pxa_camera_dev {int ciclk; int platform_flags; int /*<<< orphan*/  mclk; } ;
struct pxa_cam {int /*<<< orphan*/  flags; } ;
struct device {int dummy; } ;
struct TYPE_5__ {TYPE_1__* host_fmt; } ;
struct TYPE_4__ {scalar_t__ fourcc; } ;

/* Variables and functions */
 int EINVAL ; 
 int EIO ; 
 int PXA_CAMERA_PCLK_EN ; 
 int SOCAM_SENSE_PCLK_CHANGED ; 
 scalar_t__ V4L2_PIX_FMT_YUV422P ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,scalar_t__) ; 
 int /*<<< orphan*/  dev_warn (struct device*,char*,...) ; 
 int /*<<< orphan*/  g_mbus_fmt ; 
 scalar_t__ pxa_camera_check_frame (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pxa_camera_setup_cicr (struct soc_camera_device*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  recalculate_fifo_timeout (struct pxa_camera_dev*,scalar_t__) ; 
 int /*<<< orphan*/  s_crop ; 
 int /*<<< orphan*/  s_mbus_fmt ; 
 struct v4l2_subdev* soc_camera_to_subdev (struct soc_camera_device*) ; 
 struct soc_camera_host* to_soc_camera_host (struct device*) ; 
 int v4l2_subdev_call (struct v4l2_subdev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct v4l2_mbus_framefmt*) ; 
 int /*<<< orphan*/  v4l_bound_align_image (int /*<<< orphan*/ *,int,int,int,int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  video ; 

__attribute__((used)) static int pxa_camera_set_crop(struct soc_camera_device *icd,
			       struct v4l2_crop *a)
{
	struct v4l2_rect *rect = &a->c;
	struct soc_camera_host *ici = to_soc_camera_host(icd->dev.parent);
	struct pxa_camera_dev *pcdev = ici->priv;
	struct device *dev = icd->dev.parent;
	struct v4l2_subdev *sd = soc_camera_to_subdev(icd);
	struct soc_camera_sense sense = {
		.master_clock = pcdev->mclk,
		.pixel_clock_max = pcdev->ciclk / 4,
	};
	struct v4l2_mbus_framefmt mf;
	struct pxa_cam *cam = icd->host_priv;
	u32 fourcc = icd->current_fmt->host_fmt->fourcc;
	int ret;

	/* If PCLK is used to latch data from the sensor, check sense */
	if (pcdev->platform_flags & PXA_CAMERA_PCLK_EN)
		icd->sense = &sense;

	ret = v4l2_subdev_call(sd, video, s_crop, a);

	icd->sense = NULL;

	if (ret < 0) {
		dev_warn(dev, "Failed to crop to %ux%u@%u:%u\n",
			 rect->width, rect->height, rect->left, rect->top);
		return ret;
	}

	ret = v4l2_subdev_call(sd, video, g_mbus_fmt, &mf);
	if (ret < 0)
		return ret;

	if (pxa_camera_check_frame(mf.width, mf.height)) {
		/*
		 * Camera cropping produced a frame beyond our capabilities.
		 * FIXME: just extract a subframe, that we can process.
		 */
		v4l_bound_align_image(&mf.width, 48, 2048, 1,
			&mf.height, 32, 2048, 0,
			fourcc == V4L2_PIX_FMT_YUV422P ? 4 : 0);
		ret = v4l2_subdev_call(sd, video, s_mbus_fmt, &mf);
		if (ret < 0)
			return ret;

		if (pxa_camera_check_frame(mf.width, mf.height)) {
			dev_warn(icd->dev.parent,
				 "Inconsistent state. Use S_FMT to repair\n");
			return -EINVAL;
		}
	}

	if (sense.flags & SOCAM_SENSE_PCLK_CHANGED) {
		if (sense.pixel_clock > sense.pixel_clock_max) {
			dev_err(dev,
				"pixel clock %lu set by the camera too high!",
				sense.pixel_clock);
			return -EIO;
		}
		recalculate_fifo_timeout(pcdev, sense.pixel_clock);
	}

	icd->user_width		= mf.width;
	icd->user_height	= mf.height;

	pxa_camera_setup_cicr(icd, cam->flags, fourcc);

	return ret;
}