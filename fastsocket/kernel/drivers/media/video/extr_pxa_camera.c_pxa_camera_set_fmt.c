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
struct v4l2_pix_format {int /*<<< orphan*/  colorspace; int /*<<< orphan*/  field; int /*<<< orphan*/  height; int /*<<< orphan*/  width; int /*<<< orphan*/  pixelformat; } ;
struct v4l2_mbus_framefmt {scalar_t__ code; int /*<<< orphan*/  colorspace; int /*<<< orphan*/  field; int /*<<< orphan*/  height; int /*<<< orphan*/  width; } ;
struct TYPE_4__ {struct v4l2_pix_format pix; } ;
struct v4l2_format {TYPE_2__ fmt; } ;
struct soc_camera_sense {int pixel_clock_max; int flags; scalar_t__ pixel_clock; int /*<<< orphan*/  master_clock; } ;
struct soc_camera_host {struct pxa_camera_dev* priv; } ;
struct soc_camera_format_xlate {scalar_t__ code; } ;
struct TYPE_3__ {struct device* parent; } ;
struct soc_camera_device {struct soc_camera_format_xlate const* current_fmt; struct soc_camera_sense* sense; TYPE_1__ dev; } ;
struct pxa_camera_dev {int ciclk; int platform_flags; int /*<<< orphan*/  mclk; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int EIO ; 
 int PXA_CAMERA_PCLK_EN ; 
 int SOCAM_SENSE_PCLK_CHANGED ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,scalar_t__) ; 
 int /*<<< orphan*/  dev_warn (struct device*,char*,int /*<<< orphan*/ ,...) ; 
 scalar_t__ pxa_camera_check_frame (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  recalculate_fifo_timeout (struct pxa_camera_dev*,scalar_t__) ; 
 int /*<<< orphan*/  s_mbus_fmt ; 
 struct v4l2_subdev* soc_camera_to_subdev (struct soc_camera_device*) ; 
 struct soc_camera_format_xlate* soc_camera_xlate_by_fourcc (struct soc_camera_device*,int /*<<< orphan*/ ) ; 
 struct soc_camera_host* to_soc_camera_host (struct device*) ; 
 int v4l2_subdev_call (struct v4l2_subdev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct v4l2_mbus_framefmt*) ; 
 int /*<<< orphan*/  video ; 

__attribute__((used)) static int pxa_camera_set_fmt(struct soc_camera_device *icd,
			      struct v4l2_format *f)
{
	struct soc_camera_host *ici = to_soc_camera_host(icd->dev.parent);
	struct pxa_camera_dev *pcdev = ici->priv;
	struct device *dev = icd->dev.parent;
	struct v4l2_subdev *sd = soc_camera_to_subdev(icd);
	const struct soc_camera_format_xlate *xlate = NULL;
	struct soc_camera_sense sense = {
		.master_clock = pcdev->mclk,
		.pixel_clock_max = pcdev->ciclk / 4,
	};
	struct v4l2_pix_format *pix = &f->fmt.pix;
	struct v4l2_mbus_framefmt mf;
	int ret;

	xlate = soc_camera_xlate_by_fourcc(icd, pix->pixelformat);
	if (!xlate) {
		dev_warn(dev, "Format %x not found\n", pix->pixelformat);
		return -EINVAL;
	}

	/* If PCLK is used to latch data from the sensor, check sense */
	if (pcdev->platform_flags & PXA_CAMERA_PCLK_EN)
		/* The caller holds a mutex. */
		icd->sense = &sense;

	mf.width	= pix->width;
	mf.height	= pix->height;
	mf.field	= pix->field;
	mf.colorspace	= pix->colorspace;
	mf.code		= xlate->code;

	ret = v4l2_subdev_call(sd, video, s_mbus_fmt, &mf);

	if (mf.code != xlate->code)
		return -EINVAL;

	icd->sense = NULL;

	if (ret < 0) {
		dev_warn(dev, "Failed to configure for format %x\n",
			 pix->pixelformat);
	} else if (pxa_camera_check_frame(mf.width, mf.height)) {
		dev_warn(dev,
			 "Camera driver produced an unsupported frame %dx%d\n",
			 mf.width, mf.height);
		ret = -EINVAL;
	} else if (sense.flags & SOCAM_SENSE_PCLK_CHANGED) {
		if (sense.pixel_clock > sense.pixel_clock_max) {
			dev_err(dev,
				"pixel clock %lu set by the camera too high!",
				sense.pixel_clock);
			return -EIO;
		}
		recalculate_fifo_timeout(pcdev, sense.pixel_clock);
	}

	if (ret < 0)
		return ret;

	pix->width		= mf.width;
	pix->height		= mf.height;
	pix->field		= mf.field;
	pix->colorspace		= mf.colorspace;
	icd->current_fmt	= xlate;

	return ret;
}